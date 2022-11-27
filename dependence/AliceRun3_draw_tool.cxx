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
string usedhisto::cutsname="";

void usedhisto::setcutsname(string name){
    cutsname=name;
}

//_________________________________________________________
void usedhisto::gethisto(TFile* file){
    usedhisto::Pt=reader::get_histo<TH1>(reader::get_makerList(file,usedhisto::cutsname),"Pt");
    usedhisto::Eta=reader::get_histo<TH1>(reader::get_makerList(file,usedhisto::cutsname),"Eta");
    usedhisto::Phi=reader::get_histo<TH1>(reader::get_makerList(file,usedhisto::cutsname),"Phi");
    usedhisto::TPCncls=reader::get_histo<TH1>(reader::get_makerList(file,usedhisto::cutsname),"TPCncls");
    usedhisto::TPCnclsCR=reader::get_histo<TH1>(reader::get_makerList(file,usedhisto::cutsname),"TPCnclsCR");
    usedhisto::TPCchi2=reader::get_histo<TH1>(reader::get_makerList(file,usedhisto::cutsname),"TPCchi2");
    usedhisto::DCAxy=reader::get_histo<TH1>(reader::get_makerList(file,usedhisto::cutsname),"DCAxy");
    usedhisto::DCAz=reader::get_histo<TH1>(reader::get_makerList(file,usedhisto::cutsname),"DCAz");
    usedhisto::TPCdedx_pIN=reader::get_histo<TH2>(reader::get_makerList(file,usedhisto::cutsname),"TPCdedx_pIN");
    usedhisto::TPCnSigEle_pIN=reader::get_histo<TH2>(reader::get_makerList(file,usedhisto::cutsname),"TPCnSigEle_pIN");
    usedhisto::TPCnSigPi_pIN=reader::get_histo<TH2>(reader::get_makerList(file,usedhisto::cutsname),"TPCnSigPi_pIN");
    usedhisto::TPCnSigPr_pIN=reader::get_histo<TH2>(reader::get_makerList(file,usedhisto::cutsname),"TPCnSigPr_pIN");
};
//_________________________________________________________

//___________________histogram setting_____________________
string sethisto::settingmode[2]={"standard","special"};
//_________________________________________________________

template <class HISTO>
void sethisto::commonsetting(HISTO* histo){
    histo->SetStats(0);
    histo->GetXaxis()->SetTitleSize(0.05);
    histo->GetYaxis()->SetTitleSize(0.05);
    histo->GetXaxis()->SetLabelSize(0.05);
    histo->GetYaxis()->SetLabelSize(0.05);
    histo->GetXaxis()->SetTitleOffset(1.2);
    histo->GetYaxis()->SetTitleOffset(1.2);
    histo->SetTitle("");
};
//_________________________________________________________

void sethisto::standardsetting(){
    sethisto::commonsetting(usedhisto::Pt);
    sethisto::commonsetting(usedhisto::Eta);
    sethisto::commonsetting(usedhisto::Phi);
    sethisto::commonsetting(usedhisto::TPCncls);
    sethisto::commonsetting(usedhisto::TPCnclsCR);
    sethisto::commonsetting(usedhisto::TPCchi2);
    sethisto::commonsetting(usedhisto::DCAxy);
    sethisto::commonsetting(usedhisto::DCAz);
    sethisto::commonsetting(usedhisto::TPCdedx_pIN);
    sethisto::commonsetting(usedhisto::TPCnSigEle_pIN);
    sethisto::commonsetting(usedhisto::TPCnSigPi_pIN);
    sethisto::commonsetting(usedhisto::TPCnSigPr_pIN);
};
//_________________________________________________________

void sethisto::specialsetting(){
    //pt
    setter::sethistostyle(usedhisto::Pt,1,20,1,1,1,2);
    setter::sethistoranger<TH1>(usedhisto::Pt,0,20,0.0001,pow(usedhisto::Pt->GetMaximum(),1.4));
    setter::sethistoaxis(usedhisto::Pt,"p_{T} (GeV/c)","Counts",1.2,1.2,0.05,0.05);

    //eta
    setter::sethistostyle(usedhisto::Eta,1,20,1,1,1,2);
    setter::sethistoranger<TH1>(usedhisto::Eta,-1.5,1.5,0.0001,1.4*usedhisto::Eta->GetMaximum());
    setter::sethistoaxis(usedhisto::Eta,"#eta","Counts",1.2,1.2,0.05,0.05);

    //phi
    setter::sethistostyle(usedhisto::Phi,1,20,1,1,1,2);
    setter::sethistoranger<TH1>(usedhisto::Phi,0,6.3,0.0001,1.4*usedhisto::Phi->GetMaximum());
    setter::sethistoaxis(usedhisto::Phi,"#phi","Counts",1.2,1.2,0.05,0.05);

    //TPCncls
    setter::sethistostyle(usedhisto::TPCncls,1,20,1,1,1,2);
    setter::sethistoranger<TH1>(usedhisto::TPCncls,0,160,0.0001,1.4*usedhisto::TPCncls->GetMaximum());
    setter::sethistoaxis(usedhisto::TPCncls,"TPCncls","Counts",1.2,1.2,0.05,0.05);

    //TPCnclsCR
    setter::sethistostyle(usedhisto::TPCnclsCR,1,20,1,1,1,2);
    setter::sethistoranger<TH1>(usedhisto::TPCnclsCR,0,160,0.0001,1.4*usedhisto::TPCnclsCR->GetMaximum());
    setter::sethistoaxis(usedhisto::TPCnclsCR,"TPCnclsCR","Counts",1.2,1.2,0.05,0.05);

    //TPCchi2
    setter::sethistostyle(usedhisto::TPCchi2,1,20,1,1,1,2);
    setter::sethistoranger<TH1>(usedhisto::TPCchi2,0,10,0.0001,1.4*usedhisto::TPCchi2->GetMaximum());
    setter::sethistoaxis(usedhisto::TPCchi2,"TPCchi2","Counts",1.2,1.2,0.05,0.05);

    //DCAxy
    setter::sethistostyle(usedhisto::DCAxy,1,20,1,1,1,2);
    setter::sethistoranger<TH1>(usedhisto::DCAxy,-1,1,pow(usedhisto::DCAxy->GetMinimum(),0.5),pow(usedhisto::DCAxy->GetMaximum(),1.4));
    setter::sethistoaxis(usedhisto::DCAxy,"DCAxy","Counts",1.2,1.2,0.05,0.05);

    //DCAz
    setter::sethistostyle(usedhisto::DCAz,1,20,1,1,1,2);
    setter::sethistoranger<TH1>(usedhisto::DCAz,-1,1,pow(usedhisto::DCAz->GetMinimum(),0.5),pow(usedhisto::DCAz->GetMaximum(),1.4));
    setter::sethistoaxis(usedhisto::DCAz,"DCAz","Counts",1.2,1.2,0.05,0.05);

    //TPCdedx_pIN
    setter::sethistoranger<TH2>(usedhisto::TPCdedx_pIN,0,10,0,200);

    //TPCnSigEle_pIN
    setter::sethistoranger<TH2>(usedhisto::TPCnSigEle_pIN,0,10,-10,10);

    //TPCnSigPi_pIN
    setter::sethistoranger<TH2>(usedhisto::TPCnSigPi_pIN,0,10,-10,10);

    //TPCnSigPr_pIN
    setter::sethistoranger<TH2>(usedhisto::TPCnSigPr_pIN,0,10,-10,10);
};

//___________________histogram drawing_____________________

string setcanvas::data_periods="";
string setcanvas::collision_energy="";
string setcanvas::collision_system="";

void setcanvas::collision_set(string data_periods,string collision_energy,string collision_system){
    setcanvas::data_periods=data_periods;
    setcanvas::collision_energy=collision_energy;
    setcanvas::collision_system=collision_system;
};

void setcanvas::Alice_Common_set(){
    drawer::drawLatex(0.2,0.85,Form("ALICE Run3 %s",setcanvas::data_periods.c_str()),22,0.055,1);
    drawer::drawLatex(0.2,0.78,Form("%s #sqrt{s_{NN}} = %s",setcanvas::collision_system.c_str(),setcanvas::collision_energy.c_str()),22,0.05,1);
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
    setcanvas::Alice_Common_set();
    return canvas;
};

TCanvas* setcanvas::onehisto(TH2* histo){
    TCanvas* canvas=new TCanvas("canvas","canvas",800,600);
    canvas->cd();
    gPad->SetLeftMargin(0.15);
    gPad->SetBottomMargin(0.15);
    histo->Draw("colz");
    gPad->SetLogz();
    setcanvas::Alice_Common_set();
    return canvas;
}

//______________________Canvas saving_____________________

void savecanvas::savein(TCanvas* canvas, string name){
    canvas->SaveAs(("output/"+name+".pdf").c_str());
    canvas->Close();
};

void savecanvas::standardsave(){
    system(Form("mkdir -p output/%s/%s",setcanvas::data_periods.c_str(),usedhisto::cutsname.c_str()));
    //pt save 
    savecanvas::savein(setcanvas::Alice_Special_set(setcanvas::onehisto(usedhisto::Pt),true,false),
                                                            setcanvas::data_periods+"/"+usedhisto::cutsname+"/Pt");

    //eta save
    savecanvas::savein(setcanvas::Alice_Special_set(setcanvas::onehisto(usedhisto::Eta),false,false),
                                                            setcanvas::data_periods+"/"+usedhisto::cutsname+"/Eta");

    //phi save
    savecanvas::savein(setcanvas::Alice_Special_set(setcanvas::onehisto(usedhisto::Phi),false,false),
                                                            setcanvas::data_periods+"/"+usedhisto::cutsname+"/Phi");

    //TPCncls save
    savecanvas::savein(setcanvas::Alice_Special_set(setcanvas::onehisto(usedhisto::TPCncls),false,false),
                                                            setcanvas::data_periods+"/"+usedhisto::cutsname+"/TPCncls");

    //TPCnclsCR save
    savecanvas::savein(setcanvas::Alice_Special_set(setcanvas::onehisto(usedhisto::TPCnclsCR),false,false),
                                                            setcanvas::data_periods+"/"+usedhisto::cutsname+"/TPCnclsCR");

    //TPCchi2 save
    savecanvas::savein(setcanvas::Alice_Special_set(setcanvas::onehisto(usedhisto::TPCchi2),false,false),
                                                            setcanvas::data_periods+"/"+usedhisto::cutsname+"/TPCchi2");

    //DCAxy save
    savecanvas::savein(setcanvas::Alice_Special_set(setcanvas::onehisto(usedhisto::DCAxy),true,false),
                                                            setcanvas::data_periods+"/"+usedhisto::cutsname+"/DCAxy");

    //DCAz save
    savecanvas::savein(setcanvas::Alice_Special_set(setcanvas::onehisto(usedhisto::DCAz),true,false),
                                                            setcanvas::data_periods+"/"+usedhisto::cutsname+"/DCAz");

    //TPCdedx_pIN save
    savecanvas::savein(setcanvas::Alice_Special_set(setcanvas::onehisto(usedhisto::TPCdedx_pIN),false,false),
                                                            setcanvas::data_periods+"/"+usedhisto::cutsname+"/TPCdedx_pIN");

    //TPCnSigEle_pIN save
    savecanvas::savein(setcanvas::Alice_Special_set(setcanvas::onehisto(usedhisto::TPCnSigEle_pIN),false,false),
                                                            setcanvas::data_periods+"/"+usedhisto::cutsname+"/TPCnSigEle_pIN");

    //TPCnSigPi_pIN save
    savecanvas::savein(setcanvas::Alice_Special_set(setcanvas::onehisto(usedhisto::TPCnSigPi_pIN),false,false),
                                                            setcanvas::data_periods+"/"+usedhisto::cutsname+"/TPCnSigPi_pIN");

    //TPCnSigPr_pIN save
    savecanvas::savein(setcanvas::Alice_Special_set(setcanvas::onehisto(usedhisto::TPCnSigPr_pIN),false,false),
                                                            setcanvas::data_periods+"/"+usedhisto::cutsname+"/TPCnSigPr_pIN");

};