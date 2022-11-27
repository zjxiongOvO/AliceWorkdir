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

#ifndef _ALICE_RUN3_ITS_TOOL_H_
#define _ALICE_RUN3_ITS_TOOL_H_
using namespace std;

class its
{
    public:
        static string itsmatchmode[4];
        static bool ismatch(string type, int itsmap);
        static double geteff(TH1F* itsclustermap, string type);
        static TH1F* getdistribution(TH2F* itsclustermap_vs_var, string type);

};

string its::itsmatchmode[4] = {"ITSibAny","ITSallAny","ITSall7Layers","ITSncls2"};

bool its::ismatch(string type, int itsmap)//can be add more match mode
{
    if (type=="ITSibAny"){
        if ((itsmap & (uint8_t(1) << 0)) || (itsmap & (uint8_t(1) << 1)) || (itsmap & (uint8_t(1) << 2))){
            return true;
        }
    }
    else if (type=="ITSallAny"){
        if ((itsmap & (uint8_t(1) << 0)) || (itsmap & (uint8_t(1) << 1)) || (itsmap & (uint8_t(1) << 2)) || (itsmap & (uint8_t(1) << 3)) || (itsmap & (uint8_t(1) << 4)) || (itsmap & (uint8_t(1) << 5)) || (itsmap & (uint8_t(1) << 6))){
            return true;
        }
    }
    else if (type=="ITSall7Layers"){
        if ((itsmap & (uint8_t(1) << 0)) && (itsmap & (uint8_t(1) << 1)) && (itsmap & (uint8_t(1) << 2)) && (itsmap & (uint8_t(1) << 3)) && (itsmap & (uint8_t(1) << 4)) && (itsmap & (uint8_t(1) << 5)) && (itsmap & (uint8_t(1) << 6))){
            return true;
        }
    }
    else if (type=="ITSncls2"){
        int ncls=0;
        for (int i=0;i<7;i++){
            if (itsmap & (uint8_t(1) << i)){
                ncls++;
            }
        }
        if (ncls>=2){
            return true;
        }
    }
    return false;
};

double its::geteff(TH1F* itsclustermap, string type)
{
    double allhits=0;
    double selhits=0;
    for (int imap=0; imap<128; imap++){
        double nhits = itsclustermap->GetBinContent(imap+1);
        allhits+=nhits;        
        if (ismatch(type,imap)){
            //cout << itsmatchmode[matchmode] <<" "<<bitset<8>(imap)<< endl;
            selhits+=nhits;
        };
    }
    return selhits/allhits;
};

TH1F* its::getdistribution(TH2F* itsclustermap_vs_var, string type)
{
    TH2F* itsclustermap_vs_var_clone = (TH2F*)itsclustermap_vs_var->Clone();
    TH1F* distribution = (TH1F*)itsclustermap_vs_var_clone->ProjectionX();
    distribution->Reset();
    //reset itsclustermap
    for (int imap=0; imap<128; imap++){
        if (ismatch(type,imap)){
            distribution->Add(itsclustermap_vs_var_clone->ProjectionX(Form("imap%d",imap),imap+1,imap+1));
            }
    }
    return distribution;
};

#endif