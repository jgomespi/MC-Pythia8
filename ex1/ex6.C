//gSystem.Load("../libPythia8");
/*
Use e+e- annihilation as an environment for the clean study of final-state QCD radiation.
Specifically study how the average number of final-state partons increases with ECM. Also,
how well/badly the number of partons is described by Poisson distributions. Hint: some
useful settings are:

WeakSingleBoson:ffbar2gmZ = on
PDF:lepton = off
HadronLevel:all = off
23:onMode = off
23:onIfAny = 1 2 3 4 5

*/
#include "Pythia8/Pythia.h"
#include "TH1.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TSystem.h"
#include "TStyle.h"
#include "TFile.h"
#include <math.h>
using namespace Pythia8;
int main() {
  // Generator. Process selection. LHC initialization. Histogram.
  gStyle->SetOptStat(1111111); // Option of stat box

  // Set the beam particles id
  Pythia pythia;
  // pp colision at ecm = 14 TeV
  pythia.readString("Beams:eCM = 14000.");
  pythia.readString("Beams:idA = 2212");
  pythia.readString("Beams:idB = 2212");

  // Options
  pythia.readString("SoftQCD:nonDiffractive = on");
  pythia.readString("PartonLevel:MPI = on");
 
  // Initialize
  pythia.init();

  // Declaring the file where the hist will be written
  // Update option will write the hists to the same file
  TFile *file = TFile::Open("ex6.root","update");
  // Declaring the histogram of pT and eta. Its name has to change every time the program run.
  TH1F *etaHist = new TH1F("etaMPIHist",  "dN/d#eta x #eta", 100, -10, 10);
  TH1F *pTHist = new TH1F("pTMPIHist",    "dN/dp_{T} x p_{T}", 100, 0, 70);
  Double_t px_part, py_part, pz_part, pT_part, theta_part, eta_part;

  Event *event = &pythia.event;

  int nev = 1000000; // number of events
  // Begin event loop. Generate event. Skip if error. List first one.
  for (int iEvent = 0; iEvent < nev; ++iEvent) {
    if (!pythia.next()) continue;

    // Begin particle loop
    for (int i = 0; i < pythia.event.size(); ++i){
      // Get px, py e pz
      px_part = pythia.event[i].px();
      py_part = pythia.event[i].py();
      pz_part = pythia.event[i].pz();
      // Calculating pT
      pT_part = pow(px_part*px_part+py_part*py_part,0.5);
      // Verify if pT in nonzero
      if (pT_part == 0) continue;
      // Calculating theta
      theta_part = atan(pT_part/pz_part);
      // Calculating eta
      if (theta_part >=0) eta_part = -log(tan(theta_part/2));
      if (theta_part < 0) eta_part = log(tan(-1*theta_part/2));
      // Select final and charged particles
      if (pythia.event[i].isFinal() && pythia.event[i].isCharged()) {
        // Fill pt and eta histograms
        if (pT_part != 0) pTHist->Fill(pT_part);
        etaHist->Fill(eta_part);        
      }
    }
  // End of event loop. Statistics. Histogram. Done.
  }
  
  // Print stat info
  pythia.stat();
  // Creat a canvas to draw the mult hist
  TCanvas* c1 = new TCanvas("c1","",800,800);
  c1->Divide(1, 2);
  c1->cd(1);
  //etaHist->SetLogy();
  etaHist->SetXTitle("#eta");
  etaHist->SetYTitle("dN/d#eta");  
  etaHist->Draw();

  c1->cd(2);
  gPad->SetLogy();
  pTHist->SetXTitle("p_{t} (GeV)");
  pTHist->SetYTitle("dN/dp_{T} (GeV^{-1})");  
  pTHist->Draw();
  // Save in pdf format (this change every time the program run)
  c1->SaveAs("minimumbias_withMPI.pdf","pdf");
  // Write in the file
  pTHist->Write();
  etaHist->Write();

  delete file;
  return 0;
}
