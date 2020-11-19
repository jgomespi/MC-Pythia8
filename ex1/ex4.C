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


 Pythia pythia;


  // Process to be considered
  pythia.readString("HardQCD:qqbar2bbbar = on");
  pythia.readString("HardQCD:gg2bbbar = on");
  pythia.readString("HardQCD:gg2qqbarg = on");
  pythia.readString("HardQCD:qqbar2qqbargDiff = on");
  pythia.readString("HardQCD:qqbar2qqbargSame = on");
  pythia.readString("HardQCD:nQuarkNew = 5");

  // Colision features
  pythia.readString("Beams:eCM = 14000.");
  pythia.readString("Beams:idA = 2212");
  pythia.readString("Beams:idB = 2212");

  pythia.init();
  // Declaring files and trees
  TFile *file = TFile::Open("ex3.root","recreate");
  Event *event = &pythia.event;
  TTree *T = new TTree("RunI","RunI Tree");
  T->Branch("event",&event);

  int bquark = 0; // variable to count b quarks in hadron process
  int Bmeson = 0; // variable to count B mesons in final state

  // Loop over events:
  for (int iEvent = 0; iEvent < 10000; ++iEvent) {
    if (!pythia.next()) continue;
    // Loop over particles
    for (int i = 0; i < pythia.event.size(); ++i) {
      if (pythia.event[i].id() == 5 && std::abs(pythia.event[i].status()) >= 21 && std::abs(pythia.event[i].status()) <=29){
        ++bquark;
        break;
      }
    }
  }

  // Loop over events
  for (int iEvent = 0; iEvent < 10000; ++iEvent) {
    if (!pythia.next()) continue;
    // Loop over particles
    for (int i = 0; i < pythia.event.size(); ++i) {
        if (std::abs(pythia.event[i].id()) == 511 || std::abs(pythia.event[i].id()) == 521){
          if (pythia.event[i].isFinal() == 0){
             ++Bmeson;
             break;
          }
        }
    } 
    T->Fill();
  }

  pythia.stat();
  cout << "Quantidade de eventos com quark b: "<< bquark << endl;
  cout << "Quantidade de eventos com Méson B: "<< Bmeson << endl;
  T->Print();
  T->Write();
  delete file;  
  return 0;
}
