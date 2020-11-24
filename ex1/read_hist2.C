#include "TH1.h"
#include "TTree.h"
#include "TInterpreter.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TH2.h"
#include "TNtuple.h"
#include "TPaveLabel.h"
#include "TPaveText.h"
#include "TFrame.h"
#include "TSystem.h"
#include "TInterpreter.h"

void read_hist2() {
  gROOT->ForceStyle();
  gStyle->SetOptStat(1111); // for the sumperimposed plots
  //gStyle->SetOptStat("n");
  //gStyle->SetOptFit(1);	// for the fit plot

  TFile *file = new TFile("ex6.root","read");
  file->cd();

  TH1F * pTMPIHist = (TH1F*)file->Get("pTMPIHist");
  TH1F * pTnoMPIHist = (TH1F*)file->Get("pTnoMPIHist");
  TH1F * etaMPIHist = (TH1F*)file->Get("etaMPIHist");
  TH1F * etanoMPIHist = (TH1F*)file->Get("etanoMPIHist");

  pTnoMPIHist->SetLineColor(2);
  etanoMPIHist->SetLineColor(2);

  auto legend = new TLegend(0.8,0.5,0.9,0.7);
  //legend->SetHeader("e^{+}e^{-}; #sqrt{s}=14TeV","C");
  legend->AddEntry (pTMPIHist,"with MPI","f");
  legend->AddEntry(pTnoMPIHist,"no MPI","f");

  TCanvas* c1 = new TCanvas("c1","",800,800);  
  etaMPIHist->SetTitle("MPI influence on dN/d#eta minimum bias distribuition pp at #sqrt{s}=14 TeV");
  c1->Divide(1, 2);
  c1->cd(1);
  
  etaMPIHist->Scale(1/etaMPIHist->Integral()); 
  etanoMPIHist->Scale(1/etanoMPIHist->Integral()); 
  
  etaMPIHist->SetXTitle("#eta");
  etaMPIHist->SetYTitle("dN/d#eta");  
  etaMPIHist->Draw("HIST");
  TPaveStats *st = (TPaveStats*)etaMPIHist->FindObject("stats");
  st->SetX1NDC(0.25);
  st->SetX2NDC(0.42); 
  st->SetY1NDC(0.15);
  st->SetY2NDC(0.35);
  etanoMPIHist->Draw("sames,HIST");
  TPaveStats *st2 = (TPaveStats*)etanoMPIHist->FindObject("stats");
  st2->SetX1NDC(0.6);
  st2->SetX2NDC(0.77); 
  st2->SetY1NDC(0.15);
  st2->SetY2NDC(0.35);  
  legend->Draw("SAME");  

  c1->cd(2);
  gPad->SetLogy();
  pTMPIHist->SetTitle("MPI influence on dN/dp_{T} minimum bias distribution pp at #sqrt{s}=14 TeV");
  pTMPIHist->SetXTitle("p_{T} (GeV)");
  pTMPIHist->SetYTitle("dN/d#p_{T} (GeV^{-1})");  
  pTMPIHist->Draw();
  TPaveStats *st3 = (TPaveStats*)pTMPIHist->FindObject("stats");
  st3->SetX1NDC(0.56);
  st3->SetX2NDC(0.72); 
  st3->SetY1NDC(0.7);
  st3->SetY2NDC(0.9);
  pTnoMPIHist->Draw("sames");
  TPaveStats *st4 = (TPaveStats*)pTnoMPIHist->FindObject("stats");
  st4->SetX1NDC(0.72);
  st4->SetX2NDC(0.9); 
  st4->SetY1NDC(0.7);
  st4->SetY2NDC(0.9);  
  legend->Draw("SAME"); 
  c1->SaveAs("MPI_analysis.pdf","pdf");
  c1->Close();



}