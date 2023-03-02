#include "../dependence/AliceRun3tool.h"
#include "../dependence/AliceRun3_draw_tool.h"
#include "../dependence/AliceRun3_draw_tool.cxx"

using namespace std;

void set_vtx_histo();

void qa4vtx(string filename,string data){
    gStyle->SetOptStat(0);
    string energy="13.6 TeV";
    string collision_system="pp";
    // string energy="5.36 TeV";
    // string collision_system="Pb-Pb";
	string cutname="BeforeCuts";

    //input root file
    TFile* file = new TFile(Form("inputfile/wagon/QA/%s.root",filename.c_str()));
    usedhisto::setcutsname(cutname);//set cutname
    usedhisto::gethisto(file,"Vtx");//get all used histograms

    set_vtx_histo();

    //draw in canvas and save
    setcanvas::collision_set(data,energy,collision_system);

    system(Form("mkdir -p output/%s/Vtx/%s",setcanvas::data_periods.c_str(),usedhisto::cutsname.c_str()));

    savecanvas::savein(setcanvas::Alice_Special_set(setcanvas::onehisto(usedhisto::VtxZ),false,false),
                                                            setcanvas::data_periods+"/Vtx/"+usedhisto::cutsname+"/VtxZ");
            
    savecanvas::savein(setcanvas::Alice_Special_set(setcanvas::onehisto(usedhisto::VtxX),false,false),
                                                            setcanvas::data_periods+"/Vtx/"+usedhisto::cutsname+"/VtxX");

    savecanvas::savein(setcanvas::Alice_Special_set(setcanvas::onehisto(usedhisto::VtxY),false,false),
                                                            setcanvas::data_periods+"/Vtx/"+usedhisto::cutsname+"/VtxY");

    savecanvas::savein(setcanvas::Alice_Special_set(setcanvas::onehisto(usedhisto::VtxYVtxX),false,false),
                                                            setcanvas::data_periods+"/Vtx/"+usedhisto::cutsname+"/VtxYVtxX");
                                                        
    savecanvas::savein(setcanvas::Alice_Special_set(setcanvas::onehisto(usedhisto::VtxContrib),false,false),
                                                            setcanvas::data_periods+"/Vtx/"+usedhisto::cutsname+"/VtxContrib");
                                                        

};

void set_vtx_histo(){
    //set used histograms
    //VtxZ
    usedhisto::VtxZ->SetTitle("");
    setter::standardaxis<TH1>(usedhisto::VtxZ,"Vtx Z (cm)","Counts");
    setter::sethistoranger<TH1>(usedhisto::VtxZ,-15,15,0,usedhisto::VtxZ->GetMaximum()*1.2);
    setter::sethistostyle(usedhisto::VtxZ,1,1,1,1,1,2);

    //VtxX
    usedhisto::VtxX->SetTitle("");
    setter::standardaxis<TH1>(usedhisto::VtxX,"Vtx X (cm)","Counts");
    setter::sethistoranger<TH1>(usedhisto::VtxX,-0.2,0.2,0,usedhisto::VtxX->GetMaximum()*1.2);
    setter::sethistostyle(usedhisto::VtxX,1,1,1,1,1,2);

    //VtxY
    usedhisto::VtxY->SetTitle("");
    setter::standardaxis<TH1>(usedhisto::VtxY,"Vtx Y (cm)","Counts");
    setter::sethistoranger<TH1>(usedhisto::VtxY,-0.2,0.2,0,usedhisto::VtxY->GetMaximum()*1.2);
    setter::sethistostyle(usedhisto::VtxY,1,1,1,1,1,2);

    //VtxYVtxX
    usedhisto::VtxYVtxX->SetTitle("");
    setter::standardaxis<TH2>(usedhisto::VtxYVtxX,"Vtx X (cm)","Vtx Y (cm)");
    setter::sethistoranger<TH2>(usedhisto::VtxYVtxX,-0.2,0.2,-0.2,0.2);

    //VtxContrib
    usedhisto::VtxContrib->SetTitle("");
    setter::standardaxis<TH1>(usedhisto::VtxContrib,"Vtx Contrib","Counts");
    setter::sethistoranger<TH1>(usedhisto::VtxContrib,0,100,0,usedhisto::VtxContrib->GetMaximum()*1.2);
    setter::sethistostyle(usedhisto::VtxContrib,1,1,1,1,1,2);
}

