#include "AliceRun3_draw_tool.h"
#include "AliceRun3tool.h"
#include "AliceRun3_its_tool.h"

using namespace std;

ClassImp(usedhisto)


//___________________histogram getting_____________________
TH1* usedhisto::Pt=nullptr;
TH1* usedhisto::Eta=nullptr;
TH1* usedhisto::Phi=nullptr;
TH1* usedhisto::TPCncls=nullptr;
TH1* usedhisto::TPCnclsCR=nullptr;
TH1* usedhisto::TPCchi2=nullptr;
TH1* usedhisto::DCAxy=nullptr;
TH1* usedhisto::DCAz=nullptr;
TH2* usedhisto::TPCdedx_pIN=nullptr;
TH2* usedhisto::TPCnSigEle_pIN=nullptr;
TH2* usedhisto::TPCnSigPi_pIN=nullptr;
TH2* usedhisto::TPCnSigPr_pIN=nullptr;
TH1* usedhisto::ITSClusterMap=nullptr;
TH2* usedhisto::ITSClusterMap_Pt=nullptr;
TH2* usedhisto::ITSClusterMap_Eta=nullptr;
TH2* usedhisto::ITSClusterMap_Phi=nullptr;
TH2* usedhisto::ITSClusterMap_Pin=nullptr;
TH2* usedhisto::Pin_P=nullptr;
TH1* usedhisto::ITSncls=nullptr;
TH1* usedhisto::ITSchi2=nullptr;
TH2* usedhisto::Pt_DCAxy=nullptr;
TH2* usedhisto::Pt_DCAz=nullptr;
TH1* usedhisto::VtxZ=nullptr;
TH1* usedhisto::VtxX=nullptr;
TH1* usedhisto::VtxY=nullptr;
TH2* usedhisto::VtxYVtxX=nullptr;
TH1* usedhisto::VtxContrib=nullptr;

string usedhisto::hashlistname="";
string usedhisto::listtitle="";
string usedhisto::cutsname="";

void usedhisto::setcutsname(string name){
    cutsname=name;
};

void usedhisto::setlisttitle(string name){
    listtitle=name;
};

void usedhisto::sethashlistname(string name){
    hashlistname=name;
};

//_________________________________________________________
void usedhisto::gethisto(TFile* file, TString detector){
    //usedhisto::Pt=reader::get_histo<TH1>(reader::get_List(file,usedhisto::hashlistname,usedhisto::listtitle,usedhisto::cutsname),"Pt");
        
    if (detector.Contains("QA")){
        usedhisto::Pt=reader::get_histo<TH1>(reader::get_List(file,usedhisto::hashlistname,usedhisto::listtitle,usedhisto::cutsname),"Pt");
        usedhisto::Eta=reader::get_histo<TH1>(reader::get_List(file,usedhisto::hashlistname,usedhisto::listtitle,usedhisto::cutsname),"Eta");
        usedhisto::Phi=reader::get_histo<TH1>(reader::get_List(file,usedhisto::hashlistname,usedhisto::listtitle,usedhisto::cutsname),"Phi");
        usedhisto::TPCncls=reader::get_histo<TH1>(reader::get_List(file,usedhisto::hashlistname,usedhisto::listtitle,usedhisto::cutsname),"TPCncls");
        usedhisto::ITSncls=reader::get_histo<TH1>(reader::get_List(file,usedhisto::hashlistname,usedhisto::listtitle,usedhisto::cutsname),"ITSncls");
        usedhisto::TPCnclsCR=reader::get_histo<TH1>(reader::get_List(file,usedhisto::hashlistname,usedhisto::listtitle,usedhisto::cutsname),"TPCnclsCR");
        usedhisto::TPCchi2=reader::get_histo<TH1>(reader::get_List(file,usedhisto::hashlistname,usedhisto::listtitle,usedhisto::cutsname),"TPCchi2");
        usedhisto::ITSchi2=reader::get_histo<TH1>(reader::get_List(file,usedhisto::hashlistname,usedhisto::listtitle,usedhisto::cutsname),"ITSchi2");
        usedhisto::DCAxy=reader::get_histo<TH1>(reader::get_List(file,usedhisto::hashlistname,usedhisto::listtitle,usedhisto::cutsname),"DCAxy");
        usedhisto::DCAz=reader::get_histo<TH1>(reader::get_List(file,usedhisto::hashlistname,usedhisto::listtitle,usedhisto::cutsname),"DCAz");
        usedhisto::TPCdedx_pIN=reader::get_histo<TH2>(reader::get_List(file,usedhisto::hashlistname,usedhisto::listtitle,usedhisto::cutsname),"TPCdedx_pIN");
        usedhisto::TPCnSigEle_pIN=reader::get_histo<TH2>(reader::get_List(file,usedhisto::hashlistname,usedhisto::listtitle,usedhisto::cutsname),"TPCnSigEle_pIN");
        usedhisto::TPCnSigPi_pIN=reader::get_histo<TH2>(reader::get_List(file,usedhisto::hashlistname,usedhisto::listtitle,usedhisto::cutsname),"TPCnSigPi_pIN");
        usedhisto::TPCnSigPr_pIN=reader::get_histo<TH2>(reader::get_List(file,usedhisto::hashlistname,usedhisto::listtitle,usedhisto::cutsname),"TPCnSigPr_pIN");
        usedhisto::Pt_DCAxy=reader::get_histo<TH2>(reader::get_List(file,usedhisto::hashlistname,usedhisto::listtitle,usedhisto::cutsname),"Pt_DCAxy");
        usedhisto::Pt_DCAz=reader::get_histo<TH2>(reader::get_List(file,usedhisto::hashlistname,usedhisto::listtitle,usedhisto::cutsname),"Pt_DCAz");
    }
    if(detector.Contains("ITS")){
        usedhisto::Pin_P=reader::get_histo<TH2>(reader::get_List(file,usedhisto::hashlistname,usedhisto::listtitle,usedhisto::cutsname),"pin_vs_p");
        usedhisto::ITSClusterMap=reader::get_histo<TH1>(reader::get_List(file,usedhisto::hashlistname,usedhisto::listtitle,usedhisto::cutsname),"ITSClusterMap");
        usedhisto::ITSClusterMap_Pt=reader::get_histo<TH2>(reader::get_List(file,usedhisto::hashlistname,usedhisto::listtitle,usedhisto::cutsname),"ITSClustermap_vs_pt");
        usedhisto::ITSClusterMap_Eta=reader::get_histo<TH2>(reader::get_List(file,usedhisto::hashlistname,usedhisto::listtitle,usedhisto::cutsname),"ITSClustermap_vs_eta");
        usedhisto::ITSClusterMap_Phi=reader::get_histo<TH2>(reader::get_List(file,usedhisto::hashlistname,usedhisto::listtitle,usedhisto::cutsname),"ITSClustermap_vs_phi");
        usedhisto::ITSClusterMap_Pin=reader::get_histo<TH2>(reader::get_List(file,usedhisto::hashlistname,usedhisto::listtitle,usedhisto::cutsname),"ITSClustermap_vs_pin");
    }
    if(detector.Contains("Vtx")){
        usedhisto::VtxContrib=reader::get_histo<TH1>(reader::get_List(file,"table-maker/output","Event",usedhisto::cutsname),"VtxNContrib");
        usedhisto::VtxZ=reader::get_histo<TH1>(reader::get_List(file,"table-maker/output","Event",usedhisto::cutsname),"VtxZ");
        usedhisto::VtxX=reader::get_histo<TH1>(reader::get_List(file,"table-maker/output","Event",usedhisto::cutsname),"VtxX");
        usedhisto::VtxY=reader::get_histo<TH1>(reader::get_List(file,"table-maker/output","Event",usedhisto::cutsname),"VtxY");
        usedhisto::VtxYVtxX=reader::get_histo<TH2>(reader::get_List(file,"table-maker/output","Event",usedhisto::cutsname),"VtxYVtxX");
    }
};
//_________________________________________________________


//___________________histogram drawing_____________________

string setcanvas::data_periods="";
string setcanvas::collision_energy="";
string setcanvas::collision_system="";

void setcanvas::collision_set(string data_periods,string collision_energy,string collision_system){
    setcanvas::data_periods=data_periods;
    setcanvas::collision_energy=collision_energy;
    setcanvas::collision_system=collision_system;
};

void setcanvas::Alice_Common_set(int color){
    drawer::drawLatex(0.2,0.85,Form("ALICE Run3 %s",setcanvas::data_periods.c_str()),22,0.055,color);
    if (setcanvas::collision_system=="Pb-Pb") {
        drawer::drawLatex(0.2,0.78,Form("%s #sqrt{s_{NN}} = %s",setcanvas::collision_system.c_str(),setcanvas::collision_energy.c_str()),22,0.05,color);}
        else{
            drawer::drawLatex(0.2,0.78,Form("%s #sqrt{s} = %s",setcanvas::collision_system.c_str(),setcanvas::collision_energy.c_str()),22,0.05,color);
        }
        
    
};

TCanvas* setcanvas::Alice_Special_set(TCanvas* object,bool islogy ,bool isgrid){
    if(islogy) object->SetLogy();
    if(isgrid) object->SetGrid();
    return object;
};

TCanvas* setcanvas::onehisto(TH1* histo){
    TCanvas* canvas=new TCanvas("canvas","canvas",800,600);
    canvas->cd();
    gPad->SetLeftMargin(0.15);
    gPad->SetBottomMargin(0.15);
    histo->Draw();
    setcanvas::Alice_Common_set(1);
    return canvas;
};

TCanvas* setcanvas::onehisto(TH2* histo){
    TCanvas* canvas=new TCanvas("canvas","canvas",800,600);
    canvas->cd();
    gPad->SetLeftMargin(0.15);
    gPad->SetBottomMargin(0.15);
    histo->Draw("colz");
    gPad->SetLogz();
    setcanvas::Alice_Common_set(2);
    return canvas;
}

TCanvas* setcanvas::twohisto(TH1* histo1,TH1* histo2,int needscale){
    TCanvas* canvas=new TCanvas("canvas","canvas",800,600);
    canvas->cd();
    gPad->SetLeftMargin(0.15);
    gPad->SetBottomMargin(0.15);
    if(needscale==1){
        histo1->Scale(1/histo1->Integral());
        histo2->Scale(1/histo2->Integral());
    }
    histo1->Draw();
    histo2->Draw("same");
    setcanvas::Alice_Common_set(1);
    TLegend* leg=new TLegend(0.3,0.5,0.5,0.65);
    leg->SetFillStyle(0);
    leg->SetBorderSize(0);
    leg->SetTextFont(42);
    leg->SetTextSize(0.06);
    leg->AddEntry(histo1,"Low IR","lep");
    leg->AddEntry(histo2,"High IR","lep");
    leg->Draw();
    return canvas;
};

//______________________Canvas saving_____________________

void savecanvas::savein(TCanvas* canvas, string name){
    canvas->SaveAs(("output/"+name+".pdf").c_str());
    canvas->SaveAs(("output/"+name+".png").c_str());
    canvas->Close();
};
