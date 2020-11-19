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

Double_t
poissonf(Double_t*x,Double_t*par)                                         
{                                                                              
  return par[0]*TMath::Poisson(x[0],par[1]);
} 

void read_hist() {
  gROOT->ForceStyle();
  gStyle->SetOptStat(0); // for the sumperimposed plots
  //gStyle->SetOptStat("n");
  //gStyle->SetOptFit(1);	// for the fit plot

  TFile *file = new TFile("ex5.root","read");
  file->cd();

  TH1F * multH50 = (TH1F*)file->Get("multH50");
  TH1F * multH100 = (TH1F*)file->Get("multH100");
  TH1F * multH150 = (TH1F*)file->Get("multH150");
  TH1F * multH200 = (TH1F*)file->Get("multH200");
  TH1F * multH250 = (TH1F*)file->Get("multH250");
  TH1F * multH300 = (TH1F*)file->Get("multH300");
  TH1F * multH350 = (TH1F*)file->Get("multH350");
  TH1F * multH400 = (TH1F*)file->Get("multH400");

  multH100->SetLineColor(2);
  multH150->SetLineColor(3);
  multH200->SetLineColor(6);
  multH250->SetLineColor(9);
  multH300->SetLineWidth(2);
  multH300->SetLineStyle(2);
  multH300->SetLineColor(46);
  multH350->SetLineWidth(2);
  multH350->SetLineStyle(2);
  multH350->SetLineColor(8);
  multH400->SetLineWidth(2);
  multH400->SetLineStyle(2);
  multH400->SetLineColor(12);  

  Double_t mean_multH50 = multH50->GetMean();
  TString mean_multH50string ;
  mean_multH50string = Form("%.3f",mean_multH50);

  Double_t mean_multH100 = multH100->GetMean();
  TString mean_multH100string ;
  mean_multH100string = Form("%.3f",mean_multH100);

  Double_t mean_multH150 = multH150->GetMean();
  TString mean_multH150string ;
  mean_multH150string = Form("%.3f",mean_multH150);

  Double_t mean_multH200 = multH200->GetMean();
  TString mean_multH200string ;
  mean_multH200string = Form("%.3f",mean_multH200);

  Double_t mean_multH250 = multH250->GetMean();
  TString mean_multH250string ;
  mean_multH250string = Form("%.3f",mean_multH250);  

  Double_t mean_multH300 = multH300->GetMean();
  TString mean_multH300string ;
  mean_multH300string = Form("%.3f",mean_multH300);  

  Double_t mean_multH350 = multH350->GetMean();
  TString mean_multH350string ;
  mean_multH350string = Form("%.3f",mean_multH350);  

  Double_t mean_multH400 = multH400->GetMean();
  TString mean_multH400string ;
  mean_multH400string = Form("%.3f",mean_multH400);  

  TF1 pois("pois",poissonf,0,10,2);
  pois.SetParameter(0,1); 
  pois.SetParameter(1,1);  

  auto legend = new TLegend(0.5,0.5,0.9,0.9);
  legend->SetHeader("e^{-}e^{+} annihilation for different E_{CM}","C"); // option "C" allows to center the header  
  legend->AddEntry(multH50, "E_{CM} = 50 GeV;  #bar{p}_{mult} =  "+mean_multH50string,"f");
  legend->AddEntry(multH100,"E_{CM} = 100 GeV; #bar{p}_{mult} = "+mean_multH100string,"f");
  legend->AddEntry(multH150,"E_{CM} = 150 GeV; #bar{p}_{mult} = "+mean_multH150string,"f");
  legend->AddEntry(multH200,"E_{CM} = 200 GeV; #bar{p}_{mult} = "+mean_multH200string,"f");
  legend->AddEntry(multH250,"E_{CM} = 250 GeV; #bar{p}_{mult} = "+mean_multH250string,"f");
  legend->AddEntry(multH300,"E_{CM} = 300 GeV; #bar{p}_{mult} = "+mean_multH300string,"f");
  legend->AddEntry(multH350,"E_{CM} = 350 GeV; #bar{p}_{mult} = "+mean_multH350string,"f");
  legend->AddEntry(multH400,"E_{CM} = 400 GeV; #bar{p}_{mult} = "+mean_multH400string,"f");

  TCanvas* c1 = new TCanvas("c1","e^{+}e^{-} parton multiplicity in final state",800,800);  
  multH50->SetTitle("e^{+}e^{-} parton multiplicity in final state");
  multH50->GetYaxis()->SetTitleOffset(1.5);
  multH50->GetXaxis()->SetTitle("p_{mult}");
  multH50->GetYaxis()->SetTitle("entries");
  multH50->Draw();
  legend->Draw("SAME");
  multH100->Draw("SAME");
  multH150->Draw("SAME");
  multH200->Draw("SAME");
  multH250->Draw("SAME");
  multH300->Draw("SAME");
  multH350->Draw("SAME");
  multH400->Draw("SAME");
  c1->SaveAs("mult_all.pdf","pdf");
  c1->Close();

/*
  TCanvas* c2 = new TCanvas("c2","e_{+}e_{-} parton multiplicity in final state",800,800);  
  gStyle->SetOptFit(1111);
  gStyle->SetOptStat(0);
  multH50->Fit("pois");
  multH50->SetTitle("e_{+}e_{-} parton multiplicity in final state E_{CM} = 50 GeV Poisson Fit");
  multH50->GetXaxis()->SetTitle("p_{mult}");
  multH50->GetYaxis()->SetTitle("entries");
  multH50->Draw();
  c2->SaveAs("mult50_fit.pdf","pdf");
  c2->Close();  
*/}