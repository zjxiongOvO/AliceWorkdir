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

#ifndef _ALICE_RUN3_SIGNAL_EXTRACTION_H_
#define _ALICE_RUN3_SIGNAL_EXTRACTION_H_

using namespace std;
class signal
{
    public:
        //fit result and fit parameter
        static int pol;
        static double rawcounts;
        static double rawcounts_err;
        static double S_over_B;
        static double S_over_B_err;
        static double significance;
        static double significance_err;
        static double events;//number of events (MB)
        static double masswindow[2];
        static double massranger[2];
        static double ptrange[2];
        static double etarange[2];
        static TH1* MCsignal;
        static string commonpath;

        //function for setting
        static void set_pol(int);
        static void set_events(double);
        static void set_MCsignal(TH1*);
        static void set_commonpath(string);


        //function for fitting
        static double GlobalFitFunction(double*,double*);
        static TF1* fBkgFitFunction;
        static void fit_likesign(TH1*,TH1*);
        static void fit_directly(TH1*,TH1*);
};




#endif