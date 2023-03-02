#include "../dependence/AliceRun3tool.h"
#include "../dependence/AliceRun3_signal_extraction.h"
#include "../dependence/AliceRun3_signal_extraction.cxx"

TH1* mass_unlike=nullptr;
TH1* mass_like=nullptr;
TH1* mass_like_pp=nullptr;
TH1* mass_like_mm=nullptr;
TH1* mass_raw=nullptr;
TH1* mcSignal=nullptr;
TH1* Vtxz=nullptr;
double massrange[2]={2.0,4.0};
void gethisto(TFile*,string);
void sethisto();

void qa4pair(string filename,string dataname,string cutname)
{
    gStyle->SetOptStat(0);
    TFile* file = new TFile(Form("inputfile/wagon/QA/%s.root",filename.c_str()));
    gethisto(file,cutname);
    sethisto();

    system(Form("mkdir -p output/%s/%s",dataname.c_str(),cutname.c_str()));
    Vtxz=reader::get_histo<TH1>(reader::get_List(file,"table-maker/output","Event","AfterCuts"),"VtxZ");
    double eventnum=Vtxz->GetEntries();
    //get raw counts in mass range 2.92-3.08
    double rawcounts=mass_raw->Integral(mass_raw->FindBin(2.92),mass_raw->FindBin(3.08));

    TCanvas* c1 = new TCanvas("c1","c1",800,600);
    gPad->SetLeftMargin(0.15);
    gPad->SetBottomMargin(0.15);
    mass_unlike->Draw();
    mass_like->Draw("same");
    TLegend* leg = new TLegend(0.6,0.65,0.9,0.8);
    leg->AddEntry(mass_unlike,"unlike-sign","lep");
    leg->AddEntry(mass_like,"like-sign","lep");
    leg->SetFillStyle(0);
    leg->SetBorderSize(0);
    leg->SetTextFont(42);
    leg->SetTextSize(0.055);
    leg->Draw();
    drawer::drawLatex(0.17,0.80,Form("ALICE Run3 %s",dataname.c_str()),22,0.05,1);
    drawer::drawLatex(0.17,0.74,"pp #sqrt{s}=13.6 TeV",22,0.05,1);
    drawer::drawLatex(0.17,0.68,Form("Events=%.2f B",eventnum/1000000000),22,0.05,1);
    drawer::drawLatex(0.17,0.62,Form("Raw counts=%.0f",rawcounts),22,0.05,1);
    drawer::drawLine(2.92,0,2.92,mass_unlike->GetMaximum(),1,2,1);
    drawer::drawLine(3.16,0,3.16,mass_unlike->GetMaximum(),1,2,1);
    c1->SaveAs(Form("output/%s/%s/pairmass_post.pdf",dataname.c_str(),cutname.c_str()));

    //signal extraction
    TFile* mc = new TFile("inputfile/usedMC/hMass.root");
    mcSignal=(TH1*)mc->Get("hMassPromptSel_3");
    signal::set_commonpath(Form("output/%s/%s",dataname.c_str(),cutname.c_str()));
    signal::set_events(eventnum);
    signal::set_MCsignal(mcSignal);
    signal::set_pol(3);
    signal::fit_directly(mass_unlike,mass_like);


};

void gethisto(TFile* file,string cutname){
    mass_unlike=reader::get_histo<TH1>(reader::get_pairList(file,cutname),"Mass");
    mass_like_pp=reader::get_histo<TH1>(reader::get_pairList_pp(file,cutname),"Mass");
    mass_like_mm=reader::get_histo<TH1>(reader::get_pairList_mm(file,cutname),"Mass");
    mass_like=mass_like_pp;
    mass_like->Add(mass_like_mm);
    mass_raw=(TH1*)mass_unlike->Clone();
    mass_raw->Add(mass_like,-1);
};

void sethisto(){
    mass_unlike->Rebin(4);
    setter::standardaxis<TH1>(mass_unlike,"Mass (GeV/c^{2})","Counts");
    mass_unlike->GetXaxis()->SetRangeUser(massrange[0],massrange[1]);
    setter::sethistoranger(mass_unlike,massrange[0],massrange[1],0,mass_unlike->GetMaximum()*1.5);
    setter::sethistostyle(mass_unlike,2,20,1,2,1,2);

    mass_like->Rebin(4);
    setter::standardaxis<TH1>(mass_like,"Mass (GeV/c^{2})","Counts");
    mass_like->GetXaxis()->SetRangeUser(massrange[0],massrange[1]);
    setter::sethistoranger(mass_like,massrange[0],massrange[1],0,mass_like->GetMaximum()*1.5);
    setter::sethistostyle(mass_like,4,21,1,4,1,2);

};

