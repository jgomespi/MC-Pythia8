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
using namespace Pythia8;
int main() {
  // Generator. Process selection. LHC initialization. Histogram.
  gStyle->SetOptStat(1111111); // Option of stat box

  // Set the beam particles id
  Pythia pythia;
  pythia.readString("Beams:idA = 11");
  pythia.readString("Beams:idB = -11");

  // Set the ECM, we will set this value every time we run the program
  pythia.readString("Beams:eCM = 50.");

  // Options
  pythia.readString("WeakSingleBoson:ffbar2gmZ = on");
  pythia.readString("PDF:lepton = off");
  pythia.readString("HadronLevel:all = off");
  pythia.readString("23:onMode = off");
  pythia.readString("23:onIfAny = 1 2 3 4 5");

  // Initialize
  pythia.init();

  // Declaring the file where the hist will be written
  // Update option will write the hists to the same file
  TFile *file = TFile::Open("ex5.root","update");
  // Declaring the histogram where the parton multiplicity will be filled. Its name has to change every time the program is run.
  TH1F *multH = new TH1F("multH50","Parton Multiplicity", 40, 0, 40);
  Event *event = &pythia.event;
  // The variable that will count the parton multiplicity
  int mult;
  // Begin event loop. Generate event. Skip if error. List first one.
  for (int iEvent = 0; iEvent < 10000; ++iEvent) {
    if (!pythia.next()) continue;
    // Set the multiplicity to 0 at the begin of the event
    mult = 0;
    // Find number of all final charged particles and fill histogram.
    for (int i = 0; i < pythia.event.size(); ++i){
      // Select only final state partons
      if (pythia.event[i].isFinal() && pythia.event[i].isParton()) ++mult;
    }
    multH->Fill( mult );
  // End of event loop. Statistics. Histogram. Done.
  }
  
  // Print stat info
  pythia.stat();
  // Creat a canvas to draw the mult hist
  TCanvas* c1 = new TCanvas("c1","Parton Multiplicity",800,800);  
  multH->Draw();
  // Save in pdf format
  c1->SaveAs("multH_50.pdf","pdf");
  // Write in the file
  multH->Write();

  delete file;
  return 0;
}
