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

#ifndef _ALICE_RUN3_DRAW_TOOL_H_
#define _ALICE_RUN3_DRAW_TOOL_H_

using namespace std;

class usedhisto
{
    public:
        static TH1* Pt;
        static TH1* Eta;
        static TH1* Phi;
        static TH1* TPCncls;
        static TH1* TPCnclsCR;
        static TH1* TPCchi2;
        static TH1* DCAxy;
        static TH1* DCAz;
        static TH2* TPCdedx_pIN;
        static TH2* TPCnSigEle_pIN;
        static TH2* TPCnSigPi_pIN;
        static TH2* TPCnSigPr_pIN;
        static string cutsname;
        static void setcutsname(string name); 
        static void gethisto(TFile*);
};

class sethisto
{
    public:
        static string settingmode[2];
        static void standardsetting();
        template <class HISTO>
        static void commonsetting(HISTO*);
        static void specialsetting();
};

class setcanvas
{
    public:
        static string data_periods;
        static string collision_system;
        static string collision_energy;
        static void collision_set(string, string, string);
        static TCanvas* onehisto(TH1*);
        static TCanvas* onehisto(TH2*);
        static void Alice_Common_set();
        static TCanvas* Alice_Special_set(TCanvas*,bool,bool);
};

class savecanvas
{
    public:
        static void savein(TCanvas*, string);
        static void standardsave();
};


#endif
