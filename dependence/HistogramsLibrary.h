#include <TFile.h>
#include <TH1.h>
#include <TList.h>
#include <TLatex.h>
#include <TMath.h>
#include <TH2.h>
#include <TCanvas.h>
#include <THn.h>
#include <TLine.h>
#include <iostream>

#ifndef _HISTOGRAMS_LIBRARY_H_
#define _HISTOGRAMS_LIBRARY_H_
using namespace std;

class histolib
{
    public:
        static string eventhistoname[1];
        static string trk1dhistoname[8];
        static string trk1dhistoxtitle[8];
        static string trk1dhistoxunit[8];
        static string trk2dhistoname[4];
        // static vector<TH1> trk1dhisto;
        // static vector<TH1> addhisto(TH1*);
};

string histolib::eventhistoname[1] = {"VtxZ"};

string histolib::trk1dhistoname[8] = {"Pt","Eta","Phi","TPCncls","TPCnclsCR","TPCchi2","DCAxy","DCAz"};
string histolib::trk1dhistoxtitle[8] = {"p_{T}","#eta","#phi","TPCncls","TPCnclsCR","TPC #chi^{2}","DCA_{xy}","DCA_{z}"};
string histolib::trk1dhistoxunit[8] = {"(GeV/c)","","","","","","(cm)","(cm)"};

string histolib::trk2dhistoname[4] = {"TPCdedx_pIN","TPCnSigEle_pIN","TPCnSigPi_pIN","TPCnSigPr_pIN"};

// vector<TH1> histolib::trk1dhisto = {};

// vector<TH1> histolib::addhisto(TH1* h1){
//     trk1dhisto.push_back(*h1);
//     return trk1dhisto;
// };

#endif