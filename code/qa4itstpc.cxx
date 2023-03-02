#include "../dependence/AliceRun3tool.h"
#include "../dependence/AliceRun3_draw_tool.h"
#include "../dependence/AliceRun3_draw_tool.cxx"
#include "../dependence/AliceRun3_its_tool.h"

using namespace std;

TH1F* ITSlayer=nullptr;
TH1F* ITSeff_Pin=nullptr;
TH1F* ITSeff_Pt=nullptr;
TH1F* ITSeff_Eta=nullptr;
TH1F* ITSeff_Phi=nullptr;
TH2F* Pin_P=nullptr;
void get_itsmatch_histo();
void set_itsmatch_histo();

void qa4itstpc(string filename,string data,string cutname){
    gStyle->SetOptStat(0);
    string energy="13.6 TeV";
    string collision_system="pp";
    // string collision_system="Pb-Pb";
    // string energy="5.36 TeV";
//    string hashlistname="analysis-track-selection/output";
	string hashlistname="table-maker/output";
    string listtitle="TrackBarrel";
    // string cutname="Jpsi_TPCPost_calib_debug4";
	// string cutname="BeforeCuts";

    //input root file
    TFile* file = new TFile(Form("inputfile/wagon/QA/%s.root",filename.c_str()));

    //get all used histograms
    usedhisto::sethashlistname(hashlistname);//set hashlistname
    usedhisto::setlisttitle(listtitle);//set listtitle
    usedhisto::setcutsname(cutname);//set cutname
    usedhisto::gethisto(file,"ITS");//get all used histograms

    //set all used histograms
    get_itsmatch_histo();
    set_itsmatch_histo();

    //draw in canvas and save
    setcanvas::collision_set(data,energy,collision_system);

    system(Form("mkdir -p output/%s/%s",setcanvas::data_periods.c_str(),usedhisto::cutsname.c_str()));

    savecanvas::savein(setcanvas::Alice_Special_set(setcanvas::onehisto(ITSeff_Pin),false,false),
                                                            setcanvas::data_periods+"/"+usedhisto::cutsname+"/ITSeff_Pin");

    savecanvas::savein(setcanvas::Alice_Special_set(setcanvas::onehisto(ITSeff_Pt),false,false),
                                                            setcanvas::data_periods+"/"+usedhisto::cutsname+"/ITSeff_Pt");

    savecanvas::savein(setcanvas::Alice_Special_set(setcanvas::onehisto(ITSeff_Eta),false,false),
                                                            setcanvas::data_periods+"/"+usedhisto::cutsname+"/ITSeff_Eta");

    savecanvas::savein(setcanvas::Alice_Special_set(setcanvas::onehisto(ITSeff_Phi),false,false),
                                                            setcanvas::data_periods+"/"+usedhisto::cutsname+"/ITSeff_Phi");

    savecanvas::savein(setcanvas::Alice_Special_set(setcanvas::onehisto(Pin_P),false,false),
                                                            setcanvas::data_periods+"/"+usedhisto::cutsname+"/Pin_P");

    savecanvas::savein(setcanvas::Alice_Special_set(setcanvas::onehisto(ITSlayer),false,false),
                                                            setcanvas::data_periods+"/"+usedhisto::cutsname+"/ITSlayer");


}

void get_itsmatch_histo(){
    //get used histograms
    double pinbin[21]={0,0.5,1,1.5,2,2.5,3,3.5,4,4.5,5,5.5,6,6.5,7,7.5,8,8.5,9,9.5,10};
    int npinbin=sizeof(pinbin)/sizeof(double)-1;
    ITSeff_Pin=its::convert_to_itseff((TH2F*)usedhisto::ITSClusterMap_Pin,pinbin,npinbin,its::itsmatchmode[1]);

    double ptbin[19]={1,1.5,2,2.5,3,3.5,4,4.5,5,5.5,6,6.5,7,7.5,8,8.5,9,9.5,10};
    int nptbin=sizeof(ptbin)/sizeof(double)-1;
    ITSeff_Pt=its::convert_to_itseff((TH2F*)usedhisto::ITSClusterMap_Pt,ptbin,nptbin,its::itsmatchmode[1]);

    double etabin[19]={-0.9,-0.8,-0.7,-0.6,-0.5,-0.4,-0.3,-0.2,-0.1,0,0.1,0.2,0.3,0.4,0.5,0.6,0.7,0.8,0.9};
    int netabin=sizeof(etabin)/sizeof(double)-1;
    ITSeff_Eta=its::convert_to_itseff((TH2F*)usedhisto::ITSClusterMap_Eta,etabin,netabin,its::itsmatchmode[1]);

    double phibin[21]={0,0.314,0.628,0.942,1.256,1.57,1.884,2.198,2.512,2.826,3.14,3.454,3.768,4.082,4.396,4.71,5.024,5.338,5.652,5.966,6.28};
    int nphibin=sizeof(phibin)/sizeof(double)-1;
    ITSeff_Phi=its::convert_to_itseff((TH2F*)usedhisto::ITSClusterMap_Phi,phibin,nphibin,its::itsmatchmode[1]);
    
    Pin_P=(TH2F*)usedhisto::Pin_P;

    ITSlayer=its::convert_to_layer((TH1*)usedhisto::ITSClusterMap);
};

void set_itsmatch_histo(){
    //set used histograms
    //eff_Pin
    setter::sethistoranger<TH1F>(ITSeff_Pin,0,10,0,1);
    setter::sethistostyle(ITSeff_Pin,1,1,1,1,1,2);
    setter::standardaxis<TH1>(ITSeff_Pin,"p_{in} GeV/c","ITS-TPC matching efficiency");

    //eff_Pt
    setter::sethistoranger<TH1F>(ITSeff_Pt,1,10,0,1);
    setter::sethistostyle(ITSeff_Pt,1,1,1,1,1,2);
    setter::standardaxis<TH1>(ITSeff_Pt,"p_{T} GeV/c","ITS-TPC matching efficiency");

    //eff_Eta
    setter::sethistoranger<TH1F>(ITSeff_Eta,-0.9,0.9,0,1);
    setter::sethistostyle(ITSeff_Eta,1,1,1,1,1,2);
    setter::standardaxis<TH1>(ITSeff_Eta,"#eta","ITS-TPC matching efficiency");

    //eff_Phi
    setter::sethistoranger<TH1F>(ITSeff_Phi,0,6.28,0,1);
    setter::sethistostyle(ITSeff_Phi,1,1,1,1,1,2);
    setter::standardaxis<TH1>(ITSeff_Phi,"#phi","ITS-TPC matching efficiency");

    //Pin_P
    setter::standardaxis<TH2>(Pin_P,"p_{in} GeV/c","p GeV/c");

    //ITSlayer
    setter::standardaxis<TH1>(ITSlayer,"","ITS-TPC matching efficiency");
    setter::sethistoranger<TH1F>(ITSlayer,0.5,7.5,0,1.05);
    setter::sethistostyle(ITSlayer,1,1,1,1,1,2);
    for (int i=1;i<=7;i++){
        ITSlayer->GetXaxis()->SetBinLabel(i,Form("Layer %d",i));
    }

};
