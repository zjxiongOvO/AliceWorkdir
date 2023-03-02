#include "../dependence/AliceRun3tool.h"
#include "../dependence/AliceRun3_draw_tool.h"
#include "../dependence/AliceRun3_draw_tool.cxx"

using namespace std;

void sethisto();//_________________________________________________________
void savehisto();

void qa4run3(string filename,string data,string cutname){
    // string energy="5.36 TeV";
    // string system="Pb-Pb";
    string energy="13.6 TeV";
    string system="pp"; 

    // string hashlistname="analysis-track-selection/output";
	string hashlistname="table-maker/output";
    string listtitle="TrackBarrel";
    //input root file
    TFile* file = new TFile(Form("inputfile/wagon/QA/%s.root",filename.c_str()));

    //get all used histograms 
    usedhisto::setcutsname(cutname);//set cutname
    usedhisto::sethashlistname(hashlistname);//set hashlistname
    usedhisto::setlisttitle(listtitle);//set listtitle
    usedhisto::gethisto(file,"QA");//get all used histograms

    //set all used histograms
    // sethisto::standardsetting();
    sethisto();
    //draw in canvas
    setcanvas::collision_set(data,energy,system);
    savehisto();
}

void sethisto(){
    //pt
    setter::sethistostyle(usedhisto::Pt,1,20,1,1,1,2);
    setter::sethistoranger<TH1>(usedhisto::Pt,0,10,0.1,pow(usedhisto::Pt->GetMaximum(),1.4));
    setter::standardaxis<TH1>(usedhisto::Pt,"p_{T} (GeV/c)","Counts");

    //eta
    setter::sethistostyle(usedhisto::Eta,1,20,1,1,1,2);
    setter::sethistoranger<TH1>(usedhisto::Eta,-1.5,1.5,0.0001,1.4*usedhisto::Eta->GetMaximum());
    setter::standardaxis<TH1>(usedhisto::Eta,"#eta","Counts");

    //phi
    setter::sethistostyle(usedhisto::Phi,1,20,1,1,1,2);
    usedhisto::Phi->Rebin(8);
    setter::sethistoranger<TH1>(usedhisto::Phi,0,6.3,0.0001,1.4*usedhisto::Phi->GetMaximum());
    setter::standardaxis<TH1>(usedhisto::Phi,"#phi","Counts");
    
    //TPCncls
    setter::sethistostyle(usedhisto::TPCncls,1,20,1,1,1,2);
    setter::sethistoranger<TH1>(usedhisto::TPCncls,0,160,0.0001,1.4*usedhisto::TPCncls->GetMaximum());
    setter::standardaxis<TH1>(usedhisto::TPCncls,"TPCncls","Counts");

    //TPCnclsCR
    setter::sethistostyle(usedhisto::TPCnclsCR,1,20,1,1,1,2);
    setter::sethistoranger<TH1>(usedhisto::TPCnclsCR,0,160,0.0001,1.4*usedhisto::TPCnclsCR->GetMaximum());
    setter::standardaxis<TH1>(usedhisto::TPCnclsCR,"TPCnclsCR","Counts");

    //TPCchi2
    setter::sethistostyle(usedhisto::TPCchi2,1,20,1,1,1,2);
    setter::sethistoranger<TH1>(usedhisto::TPCchi2,0,10,0.0001,1.4*usedhisto::TPCchi2->GetMaximum());
    setter::standardaxis<TH1>(usedhisto::TPCchi2,"TPCchi2","Counts");

    //DCAxy
    setter::sethistostyle(usedhisto::DCAxy,1,20,1,1,1,2);
    setter::sethistoranger<TH1>(usedhisto::DCAxy,-0.8,0.8,pow(1+usedhisto::DCAxy->GetMinimum(),0.5),pow(usedhisto::DCAxy->GetMaximum(),1.4));
    setter::standardaxis<TH1>(usedhisto::DCAxy,"DCAxy","Counts");

    //DCAz
    setter::sethistostyle(usedhisto::DCAz,1,20,1,1,1,2);
    setter::sethistoranger<TH1>(usedhisto::DCAz,-0.8,0.8,pow(1+usedhisto::DCAz->GetMinimum(),0.5),pow(usedhisto::DCAz->GetMaximum(),1.4)); 
    setter::standardaxis<TH1>(usedhisto::DCAz,"DCAz","Counts");

    //TPCdedx_pIN
    setter::sethistoranger<TH2>(usedhisto::TPCdedx_pIN,0,10,0,200);
    setter::standardaxis<TH2>(usedhisto::TPCdedx_pIN,"p_{in} (GeV/c)","TPCdedx (a.u.)");

    //TPCnSigEle_pIN
    setter::sethistoranger<TH2>(usedhisto::TPCnSigEle_pIN,0,10,-10,10);
    setter::standardaxis<TH2>(usedhisto::TPCnSigEle_pIN,"p_{in} (GeV/c)","n#sigma_{e}^{TPC}");

    //TPCnSigPi_pIN
    setter::sethistoranger<TH2>(usedhisto::TPCnSigPi_pIN,0,10,-10,10);
    setter::standardaxis<TH2>(usedhisto::TPCnSigPi_pIN,"p_{in} (GeV/c)","n#sigma_{#pi}^{TPC}");

    //TPCnSigPr_pIN
    setter::sethistoranger<TH2>(usedhisto::TPCnSigPr_pIN,0,10,-10,10);
    setter::standardaxis<TH2>(usedhisto::TPCnSigPr_pIN,"p_{in} (GeV/c)","n#sigma_{p}^{TPC}");

    //ITSncls
    setter::sethistostyle(usedhisto::ITSncls,1,20,1,1,1,2);
    setter::sethistoranger<TH1>(usedhisto::ITSncls,-0.5,7.5,0,1.4*usedhisto::ITSncls->GetMaximum());
    setter::standardaxis<TH1>(usedhisto::ITSncls,"ITSncls","Counts");


    //ITSchi2
    setter::sethistostyle(usedhisto::ITSchi2,1,20,1,1,1,2);
    setter::sethistoranger<TH1>(usedhisto::ITSchi2,0,10,0.1+pow(usedhisto::ITSchi2->GetMinimum(),0.5),pow(usedhisto::ITSchi2->GetMaximum(),1.4));
    setter::standardaxis<TH1>(usedhisto::ITSchi2,"ITSchi2","Counts");

    //Pt_DCAxy
    setter::sethistoranger<TH2>(usedhisto::Pt_DCAxy,0,10,-0.8,0.8);
    setter::standardaxis<TH2>(usedhisto::Pt_DCAxy,"p_{T} (GeV/c)","DCAxy");

    //Pt_DCAz
    setter::sethistoranger<TH2>(usedhisto::Pt_DCAz,0,10,-0.8,0.8); 
    setter::standardaxis<TH2>(usedhisto::Pt_DCAz,"p_{T} (GeV/c)","DCAz");
};

void savehisto(){
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

    //ITSncls save
    savecanvas::savein(setcanvas::Alice_Special_set(setcanvas::onehisto(usedhisto::ITSncls),false,false),
                                                            setcanvas::data_periods+"/"+usedhisto::cutsname+"/ITSncls");

    //ITSchi2 save
    savecanvas::savein(setcanvas::Alice_Special_set(setcanvas::onehisto(usedhisto::ITSchi2),true,false),
                                                            setcanvas::data_periods+"/"+usedhisto::cutsname+"/ITSchi2");

    //Pt_DCAxy save
    savecanvas::savein(setcanvas::Alice_Special_set(setcanvas::onehisto(usedhisto::Pt_DCAxy),false,false),
                                                            setcanvas::data_periods+"/"+usedhisto::cutsname+"/Pt_DCAxy");

    //Pt_DCAz save
    savecanvas::savein(setcanvas::Alice_Special_set(setcanvas::onehisto(usedhisto::Pt_DCAz),false,false),
                                                            setcanvas::data_periods+"/"+usedhisto::cutsname+"/Pt_DCAz");

}