#include "dependence/AliceRun3tool.h"
#include "dependence/AliceRun3_draw_tool.h"
#include "dependence/AliceRun3_draw_tool.cxx"

using namespace std;

void qa4run3(string filename){
    string data="LHC22s_apass2";
    string energy="5.3 TeV";
    string system="Pb-Pb";
    //string cutname="BeforeCuts";
    string cutname="Jpsi_TPCPost_calib_debug1";
    //input root file
    TFile* file = new TFile(Form("input/%s.root",filename.c_str()));

    //get all used histograms 
    usedhisto::setcutsname(cutname);
    usedhisto::gethisto(file);

    //set all used histograms
    sethisto::standardsetting();
    sethisto::specialsetting();

    //draw in canvas
    setcanvas::collision_set(data,energy,system);
    savecanvas::standardsave();

    //set canvas

    //save canvas
}