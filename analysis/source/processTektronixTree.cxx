// Read Trees

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cassert>


#include "TFile.h"
#include "TChain.h"
#include "TTree.h"
#include "TTreeReader.h"
#include "TTreeReaderArray.h"
#include "TH1.h"
#include "TH2.h"
#include "TVector3.h"
#include "TLorentzVector.h"

#include <waveform.h>

using namespace std;

int main(int argc, char* argv[]) {
  TChain *mychain = new TChain("tree");
  mychain->Add(argv[1]);

  TFile *ofile = TFile::Open(argv[2],"recreate");

  //auto tout = new TTree("t", "HRPPD Tree");

  //auto *hb1 = new TH1D("hb1", "", 100, -0.020, 0.020);
  //auto *hb4 = new TH1D("hb4", "", 100, -0.010, 0.010);
  
  TTreeReader tree_reader(mychain);

  //TTreeReaderArray<double> eventTime    = {tree_reader, "eventTime"};
  TTreeReaderArray<double> signalTime   = {tree_reader, "TIME"};
  TTreeReaderArray<double> trigger = {tree_reader, "CH1"};
  TTreeReaderArray<double> signal = {tree_reader, "CH5"};

  // Histograms
  TH1D *sigTrigOffset = new TH1D("sigTrigOffset","",2000,0.,2000.);

  // Loop Over Events and Find Offset
  int NEVENTS = 0;
  while(tree_reader.Next()) {
    waveform fpd("Fast Photodiode",signalTime,trigger);
    waveform hrppd("HRPPD",signalTime,signal);

    int trigPeak = fpd.findMinimum(0,trigger.GetSize()-1);
    int sigPeak = hrppd.findMinimum(0,signal.GetSize()-1);

    cout << NEVENTS << " " << trigPeak << " " << sigPeak << endl;

    sigTrigOffset->Fill(sigPeak - trigPeak);

    NEVENTS++;
  }

  ofile->Write();
  ofile->Close();

  cout << "Number of Events = " << NEVENTS << endl;

}
