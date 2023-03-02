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
        static TH1* ITSClusterMap;
        static TH2* ITSClusterMap_Pt;
        static TH2* ITSClusterMap_Eta;
        static TH2* ITSClusterMap_Phi;
        static TH2* ITSClusterMap_Pin;
        static TH2* Pin_P;
        static TH1* ITSncls;
        static TH1* ITSchi2;
        static TH2* Pt_DCAxy;
        static TH2* Pt_DCAz;
        static TH1* VtxZ;
        static TH1* VtxX;
        static TH1* VtxY;
        static TH2* VtxYVtxX;
        static TH1* VtxContrib;
        static string hashlistname;
        static string listtitle;
        static string cutsname;
        static void sethashlistname(string);
        static void setlisttitle(string);
        static void setcutsname(string); 
        static void gethisto(TFile*,TString);
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
        static TCanvas* twohisto(TH1*,TH1*,int);
        static void Alice_Common_set(int);
        static TCanvas* Alice_Special_set(TCanvas*,bool,bool);
};

class savecanvas
{
    public:
        static void savein(TCanvas*, string);
};


#endif
