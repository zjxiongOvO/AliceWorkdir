#include "AliceRun3_draw_tool.h"
#include "AliceRun3tool.h"
#include "AliceRun3_signal_extraction.h"

using namespace std;

int signal::pol = 2;
double signal::massranger[2] = {2.0,4.0};
double signal::masswindow[2] = {2.92,3.16};
double signal::ptrange[2] = {0.0,15.0};
double signal::etarange[2] = {-0.9,0.9};
double signal::rawcounts = 0;
double signal::rawcounts_err = 0;
double signal::S_over_B = 0;
double signal::S_over_B_err = 0;
double signal::significance = 0;
double signal::significance_err = 0;
double signal::events = 0;
TH1* signal::MCsignal = nullptr;
TF1* signal::fBkgFitFunction = nullptr;
string signal::commonpath = "output/";

void signal::set_pol(int pol)
{
    signal::pol = pol;
    signal::fBkgFitFunction = new TF1("fBkgFitFunction",Form("pol%d",signal::pol),0,10);
};

void signal::set_events(double events)
{
    signal::events = events;
};

void signal::set_MCsignal(TH1* MCsignal)
{
    signal::MCsignal = MCsignal;
};

void signal::set_commonpath(string commonpath)
{
    signal::commonpath = commonpath;
};

double signal::GlobalFitFunction(double* x,double* par)
{
    double val = signal::MCsignal->GetBinContent(signal::MCsignal->FindBin(x[0]));
	val *= par[0];
	for(int i=0;i<signal::fBkgFitFunction->GetNpar();++i) {
		signal::fBkgFitFunction->SetParameter(i, par[i+1]);
	}
	val += signal::fBkgFitFunction->Eval(x[0]);
	return val;
};

void signal::fit_directly(TH1* unlike,TH1* like)
{
    TH1 *hMass = nullptr;
    TH1 *hMCTemp = nullptr;
    TH1 *hunlike = nullptr;
    TH1 *hlike = nullptr;

    TH1 *signal4fit;
    TH1 *bkg;

    hMass = (TH1*)signal::MCsignal->Clone("hMass");
    hMCTemp = (TH1*)signal::MCsignal->Clone("hMCTemp");
    hunlike = (TH1*)unlike->Clone("hunlike");
    hlike = (TH1*)like->Clone("hlike");

    // hMass->Sumw2();
    // hunlike->Sumw2();
    // hlike->Sumw2();

    //set GlobalFitFunction
    TF1 *fGlobalFitFunction = new TF1("fGlobalFitFunction",signal::GlobalFitFunction,0,10,1+signal::fBkgFitFunction->GetNpar());
    fGlobalFitFunction->SetLineColor(2);
	fGlobalFitFunction->SetNpx(10000);
	fGlobalFitFunction->SetLineWidth(3);
	signal::fBkgFitFunction->SetLineColor(3);
	signal::fBkgFitFunction->SetNpx(10000);
	signal::fBkgFitFunction->SetLineWidth(3);
    int nTotalPars = fGlobalFitFunction->GetNpar();

    //set signal histo and bkg histo
    bkg=(TH1*)like->Clone("bkg");
    signal4fit=(TH1*)unlike->Clone("signal4fit");

    //set signal4fit 
    signal4fit->GetXaxis()->SetRangeUser(2,4);
    signal4fit->GetYaxis()->SetRangeUser(0,signal4fit->GetMaximum()*1.4);
    setter::sethistostyle(signal4fit,1,20,1,1,1,2);
    setter::standardaxis<TH1>(signal4fit,"inv.Mass (GeV/c^{2})","Counts");

    TCanvas* c1 = new TCanvas("c1","c1",800,600);
    c1->cd();
    gPad->SetLeftMargin(0.15);
    gPad->SetBottomMargin(0.15);
    signal4fit->Draw();

    signal4fit->Fit("fGlobalFitFunction","R","",2,4);
    // signal::fBkgFitFunction->Draw("same");


    //scale hMCTemp
    for(int ibin=0;ibin<hMCTemp->GetNbinsX();ibin++)
    {
    hMCTemp->SetBinError(ibin+1,hMCTemp->GetBinContent(ibin+1)*fGlobalFitFunction->GetParError(0));
    hMCTemp->SetBinContent(ibin+1,hMCTemp->GetBinContent(ibin+1)*fGlobalFitFunction->GetParameter(0));
    }
    // hMCTemp->SetLineColor(4);
    // hMCTemp->SetLineWidth(3);
    // hMCTemp->Draw("same");

    TFitResultPtr r=signal4fit->Fit(fGlobalFitFunction,"RS","same",2,4);
    TMatrixDSym covTotal = r->GetCovarianceMatrix();
    TMatrixDSym covBG;
    covTotal.GetSub(1,nTotalPars-1,1,nTotalPars-1,covBG);

    double p[nTotalPars]; double perr[nTotalPars];
    for(int ip=0; ip<nTotalPars; ip++)
    {
        p[ip]=fGlobalFitFunction->GetParameter(ip);
        perr[ip]=fGlobalFitFunction->GetParError(ip);
    }

    for(int ip=0; ip<nTotalPars-1; ip++)
    {
        signal::fBkgFitFunction->SetParameter(ip,p[ip+1]);//   p[1], p[2],p[3],p[4]);
        signal::fBkgFitFunction->SetParError(ip,perr[ip+1]);//   p[1], p[2],p[3],p[4]);
    }
    signal::fBkgFitFunction->Draw("same");

    //get used information by intergral

    double chi2 = fGlobalFitFunction->GetChisquare();
    double ndf = fGlobalFitFunction->GetNDF();
    double chi2ndf = chi2/ndf;
    double chi2prob = TMath::Prob(chi2,ndf);

    double fit_total = fGlobalFitFunction->Integral(signal::masswindow[0],signal::masswindow[1]);
    double fit_bkg = signal::fBkgFitFunction->Integral(signal::masswindow[0],signal::masswindow[1]);
    double fit_total_err = fGlobalFitFunction->IntegralError(signal::masswindow[0],signal::masswindow[1]);
    double fit_bkg_err = signal::fBkgFitFunction->IntegralError(signal::masswindow[0],signal::masswindow[1],signal::fBkgFitFunction->GetParameters(), covBG.GetMatrixArray());
    double fit_signal = fit_total - fit_bkg;
    double fit_signal_err = sqrt(fit_total_err*fit_total_err + fit_bkg_err*fit_bkg_err);
    double binWidth = signal4fit->GetBinWidth(1);
    fit_total /= binWidth;
    fit_total_err /= binWidth;
    fit_bkg /= binWidth;
    fit_bkg_err /= binWidth;
    fit_signal /= binWidth;
    fit_signal_err /= binWidth;

    double count_total = signal4fit->Integral(signal4fit->FindBin(signal::masswindow[0]+1.e-9),signal4fit->FindBin(signal::masswindow[1]-1.e-9));
    
    double count_jpsi = count_total - fit_bkg;
    signal::S_over_B = count_jpsi/fit_bkg;
    signal::S_over_B_err = sqrt(count_jpsi)/fit_bkg + count_jpsi*fit_bkg_err/(fit_bkg*fit_bkg);
    signal::significance = count_jpsi/sqrt(count_jpsi+fit_bkg);
    //set information about fit
    drawer::drawLatex(0.7,0.7,Form("#chi^{2}/ndf = %.2f",chi2ndf),22,0.03,1);
    drawer::drawLatex(0.7,0.65,Form("Fit_total = %.0f #pm %.0f",fit_total,fit_total_err),22,0.03,1);
    drawer::drawLatex(0.7,0.6,Form("Fit_Bkg = %.0f #pm %.0f",fit_bkg,fit_bkg_err),22,0.03,1);
    drawer::drawLatex(0.7,0.55,Form("Fit_Signal = %.0f #pm %.0f",fit_signal,fit_signal_err),22,0.03,1);
    drawer::drawLatex(0.7,0.5,Form("Count_jpsi = %.0f",count_jpsi),22,0.03,1);

    drawer::drawLatex(0.2,0.85,Form("Alice Run3 pp @ 13.6 TeV"),22,0.05,1);
    drawer::drawLatex(0.2,0.79,Form("%.1f < p_{T} < %.1f GeV/c",signal::ptrange[0],signal::ptrange[1]),22,0.03,1);
    drawer::drawLatex(0.2,0.75,Form("%.1f < #eta < %.1f",signal::etarange[0],signal::etarange[1]),22,0.03,1);
    drawer::drawLatex(0.2,0.71,Form("Events = %.0f M",signal::events/1000000),22,0.03,1);
    drawer::drawLatex(0.2,0.65,Form("S/B = %.2f #pm %.2f",signal::S_over_B,signal::S_over_B_err),22,0.035,1);
    drawer::drawLatex(0.2,0.59,Form("#frac{S}{#sqrt{S + B}} = %.2f",signal::significance),22,0.035,1);

    //draw mass window 
    drawer::drawLine(signal::masswindow[0],0,signal::masswindow[0],signal4fit->GetMaximum(),2,2,1);
    drawer::drawLine(signal::masswindow[1],0,signal::masswindow[1],signal4fit->GetMaximum(),2,2,1);

    TLegend *leg = new TLegend(0.65,0.73,0.75,0.83);
    leg->SetBorderSize(0);
    leg->SetFillStyle(0);
    leg->AddEntry(signal4fit,"Unlike-sign","lep");
    leg->AddEntry(signal::fBkgFitFunction,Form("pol%.0d",signal::pol),"l");
    leg->Draw();

    c1->SaveAs(Form("%s/signalExtraction_directly.pdf",signal::commonpath.c_str()));
};

