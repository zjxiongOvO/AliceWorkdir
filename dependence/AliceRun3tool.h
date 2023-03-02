//for run3 analysis(common tool)
//Author: zhxiong
//cern box: zhenjun.xiong@cern.ch

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

#ifndef _ALICE_RUN3_TOOL_H_
#define _ALICE_RUN3_TOOL_H_
using namespace std;

class reader
{
    public:
        static TList* get_trkList(TFile*, string);
        static TList* get_makerList(TFile*, string);
        static TList* get_makerList_event(TFile*,string);
        static TList* get_pairList(TFile*, string);
        static TList* get_pairList_mm(TFile*, string);
        static TList* get_pairList_pp(TFile*, string);
        static TList* get_List(TFile*, string, string, string);
        template <class HISTO>
        static HISTO* get_histo(TList* List, string histoname);
    private:
};

class drawer
{
    public:
        static TLatex* drawLatex(double, double, char*, int,double,int);
        static TLine* drawLine(double, double, double, double, int, int, int);
    private:
};

class setter
{
    public:
        template <class HISTO>
        static HISTO* sethistoranger(HISTO*, double, double, double, double);
        static TH1* sethistoaxis(TH1*, string, string, double, double, double, double);
        template <class HISTO>
        static HISTO* standardaxis(HISTO*, string, string);
        static TH1* sethistostyle(TH1*, int, int, int, int, int, int);
    private:
};

TList* reader::get_List(TFile* file, string hashlistname, string listtitle, string cutname)
{
    string listname = listtitle + "_" + cutname;
    THashList *HashList = (THashList*)file->Get(hashlistname.c_str());
    TList *List = (TList*)HashList->FindObject(listname.c_str());
    return List;
};

TList* reader::get_trkList(TFile *file,string cutname)
{
    string HashListname_trk = "analysis-track-selection/output";
    string Listtitle_trk = "TrackBarrel_";
    string listname = Listtitle_trk + cutname;
    THashList *HashList = (THashList*)file->Get(HashListname_trk.c_str());
    TList *List = (TList*)HashList->FindObject(listname.c_str());
    return List;
};

TList* reader::get_makerList(TFile *file,string cutname)
{
    string HashListname_maker = "table-maker/output";
    string Listtitle_maker = "TrackBarrel_";
    string listname = Listtitle_maker + cutname;
    THashList *HashList = (THashList*)file->Get(HashListname_maker.c_str());
    TList *List = (TList*)HashList->FindObject(listname.c_str());
    return List;
};

TList* reader::get_makerList_event(TFile *file,string cutname)
{
    string HashListname_maker = "table-maker/output";
    string Listtitle_maker = "Event_";
    string listname = Listtitle_maker + cutname;
    THashList *HashList = (THashList*)file->Get(HashListname_maker.c_str());
    TList *List = (TList*)HashList->FindObject(listname.c_str());
    return List;
};

TList* reader::get_pairList(TFile *file,string cutname)
{
    string HashListname_pair = "analysis-same-event-pairing/output";
    string Listtitle_pair = "PairsBarrelSEPM_";
    string listname = Listtitle_pair + cutname;
    THashList *HashList = (THashList*)file->Get(HashListname_pair.c_str());
    TList *List = (TList*)HashList->FindObject(listname.c_str());
    return List;
};

TList* reader::get_pairList_mm(TFile *file,string cutname)
{
    string HashListname_pair = "analysis-same-event-pairing/output";
    string Listtitle_pair = "PairsBarrelSEMM_";
    string listname = Listtitle_pair + cutname;
    THashList *HashList = (THashList*)file->Get(HashListname_pair.c_str());
    TList *List = (TList*)HashList->FindObject(listname.c_str());
    return List;
};

TList* reader::get_pairList_pp(TFile *file,string cutname)
{
    string HashListname_pair = "analysis-same-event-pairing/output";
    string Listtitle_pair = "PairsBarrelSEPP_";
    string listname = Listtitle_pair + cutname;
    THashList *HashList = (THashList*)file->Get(HashListname_pair.c_str());
    TList *List = (TList*)HashList->FindObject(listname.c_str());
    return List;
};

template <class HISTO>
HISTO* reader::get_histo(TList* List, string histoname)
{
    HISTO *histo = (HISTO*)List->FindObject(histoname.c_str());
    return histo;
};


TLatex* drawer::drawLatex(double x, double y, char* text, int textFont, double textSize, int colorIndex)
{
  TLatex *latex = new TLatex(x,y,text); 
  latex->SetNDC();
  latex->SetTextFont(textFont);
  latex->SetTextSize(textSize);   
  latex->SetTextColor(colorIndex); 
  latex->Draw("same");
  return latex;
};

TLine* drawer::drawLine(double x1, double y1, double x2, double y2, int colorIndex, int style, int width)
{
  TLine *line = new TLine(x1,y1,x2,y2);
  line->SetLineColor(colorIndex);
  line->SetLineStyle(style);
  line->SetLineWidth(width);
  line->Draw("same");
  return line;
};

template <class HISTO>
HISTO* setter::sethistoranger(HISTO* histo, double xmin, double xmax, double ymin, double ymax)
{
    histo->GetXaxis()->SetRangeUser(xmin,xmax);
    histo->GetYaxis()->SetRangeUser(ymin,ymax);
    return histo;
};

template <class HISTO>
HISTO* setter::standardaxis(HISTO* histo, string xtitle, string ytitle)
{
    histo->GetXaxis()->SetTitle(xtitle.c_str());
    histo->GetYaxis()->SetTitle(ytitle.c_str());
    histo->GetXaxis()->SetTitleOffset(1.2);
    histo->GetYaxis()->SetTitleOffset(1.2);
    histo->GetXaxis()->SetTitleSize(0.06);
    histo->GetYaxis()->SetTitleSize(0.06);
    histo->GetXaxis()->SetLabelSize(0.055);
    histo->GetXaxis()->SetLabelOffset(0.015);
    histo->GetYaxis()->SetLabelSize(0.055);
    histo->GetYaxis()->SetLabelOffset(0.015);
    histo->SetStats(0);
    histo->SetTitle("");
    return histo;
};

TH1* setter::sethistoaxis(TH1* histo, string xtitle, string ytitle,double xoffset, double yoffset, double xsize, double ysize)
{
    histo->GetXaxis()->SetTitle(xtitle.c_str());
    histo->GetYaxis()->SetTitle(ytitle.c_str());
    histo->GetXaxis()->SetTitleOffset(xoffset);
    histo->GetYaxis()->SetTitleOffset(yoffset);
    histo->GetXaxis()->SetTitleSize(xsize);
    histo->GetYaxis()->SetTitleSize(ysize);
    histo->GetXaxis()->SetLabelSize(0.055);
    histo->GetXaxis()->SetLabelOffset(0.015);
    histo->GetYaxis()->SetLabelSize(0.055);
    histo->GetYaxis()->SetLabelOffset(0.015);
    return histo;
};

TH1* setter::sethistostyle(TH1* histo, int markerColor, int markerStyle, int markerSize, int lineColor, int lineStyle, int lineWidth)
{
    histo->SetMarkerColor(markerColor);
    histo->SetMarkerStyle(markerStyle);
    histo->SetMarkerSize(markerSize);
    histo->SetLineColor(lineColor);
    histo->SetLineStyle(lineStyle);
    histo->SetLineWidth(lineWidth);
    return histo;
};

#endif