// processTektronixTree.cxx
//
// Usage:
//   process <input.root> <output.root> [config.json]
//
// If no config file is given, built-in defaults are used 

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <memory>
#include <vector>

#include "TFile.h"
#include "TChain.h"
#include "TTree.h"
#include "TTreeReader.h"
#include "TTreeReaderArray.h"
#include "TVector3.h"
#include "TLorentzVector.h"

#include <waveformAnalysisUtil.h>   
                              
using namespace std;

int main(int argc, char* argv[]) {
  
  if(argc < 3)
    {
      cerr << "Usage: " << argv[0] << " <input.root> <output.root> [config.json]" << endl;
      return 1;
    }
    
  //--------------------------------------------------
  // Load analysis configuration
  //--------------------------------------------------
  AnalysisConfig cfg;   // initialised with built-in defaults
  if(argc >= 4)
    {
      try
	{
	  cfg = loadConfig(argv[3]);
	  cout << "Loaded config from: " << argv[3] << endl;
	}
      catch (const std::exception& e)
	{
	  cerr << "Error loading config: " << e.what() << endl;
	  return 1;
	}
    }
  else
    {
      cout << "No config file specified; using built-in defaults." << endl;
    }
  
  // Echo active parameter values
  cout << "--- Analysis parameters ---" << endl;
  cout << "  Trigger channel:                " << cfg.triggerChannel              << endl;
  cout << "  Trigger type:                   " << cfg.triggerType                 << endl;
  cout << "  TRG threshold:                  " << cfg.trgThreshold                << endl;
  cout << "  TRG pulse window:               " << cfg.trgPulseWindow              << endl;
  cout << "  TRG baseline offset upstream:   " << cfg.trgBaselineWindowOffsetUp   << endl;
  cout << "  TRG baseline offset downstream: " << cfg.trgBaselineWindowOffsetDown << endl;
  cout << "  TRG baseline window width:      " << cfg.trgBaselineWindowWidth      << endl;
  cout << "  TRG edge search limit:          " << cfg.trgEdgeSearchLimit          << endl;
  cout << "  HRPPD pulse window:             " << cfg.hrppdPulseWindow            << endl;
  cout << "  HRPPD baseline offset:          " << cfg.hrppdBaselineWindowOffset   << endl;
  cout << "  HRPPD baseline window width:    " << cfg.hrppdBaselineWindowWidth    << endl;
  cout << "  HRPPD edge search limit:        " << cfg.hrppdEdgeSearchLimit        << endl;
  cout << "  Channel branch mapping:         ";
  for(int i = 0; i < NCHANNELS; i++)
    cout << "CH" << i+1 << "->" << cfg.channelBranches[i] << (i<NCHANNELS-1 ? "  " : "");
  cout << endl;
  cout << "---------------------------" << endl << endl;
  
  //--------------------------------------------------
  // Input chain and output file
  //--------------------------------------------------
  TChain *mychain = new TChain("tree");
  mychain->Add(argv[1]);
  
  TFile *ofile = TFile::Open(argv[2], "recreate");
  auto tout = new TTree("t", "Analyzed Scope Tree");
  
  TTreeReader tree_reader(mychain);
  
  //--------------------------------------------------
  // Output tree variables - trigger
  //--------------------------------------------------
  unsigned trgOk = 0, trgPoints = 0, trgBottomIndex = 0;
  double trgBottom = 0., trgBaseUp = 0., trgBaseDown = 0., trgAmp = 0., trg50Time = 0.;
  
  tout->Branch("trgOk",          &trgOk,          "trgOk/I");
  tout->Branch("trgPoints",      &trgPoints,      "trgPoints/I");
  tout->Branch("trgBottomIndex", &trgBottomIndex, "trgBottomIndex/I");
  tout->Branch("trgBottom",      &trgBottom,      "trgBottom/D");
  tout->Branch("trgBaseUp",      &trgBaseUp,      "trgBaseUp/D");
  tout->Branch("trgBaseDown",    &trgBaseDown,    "trgBaseDown/D");
  tout->Branch("trgAmp",         &trgAmp,         "trgAmp/D");
  tout->Branch("trg50Time",      &trg50Time,      "trg50Time/D");
  
  //--------------------------------------------------
  // Output tree variables - HRPPD channels (arrays)
  //--------------------------------------------------
  unsigned hrppdOk[NCHANNELS]        = {};
  unsigned hrppdPeakIndex[NCHANNELS] = {};
  unsigned hrppdPoints[NCHANNELS]    = {};
  unsigned hrppdWidth[NCHANNELS]     = {};
  double   hrppdBase[NCHANNELS]      = {};
  double   hrppdAmp[NCHANNELS]       = {};
  double   hrppdCharge[NCHANNELS]    = {};
  double   hrppd10Time[NCHANNELS]    = {};
  double   hrppd50Time[NCHANNELS]    = {};
  double   hrppd90Time[NCHANNELS]    = {};
  
  for (int i = 0; i < NCHANNELS; i++)
    {
      int ch = i + 1;
      tout->Branch(Form("hrppdOk%d",        ch), &hrppdOk[i],        Form("hrppdOk%d/I",        ch));
      tout->Branch(Form("hrppdPeakIndex%d", ch), &hrppdPeakIndex[i], Form("hrppdPeakIndex%d/I", ch));
      tout->Branch(Form("hrppdPoints%d",    ch), &hrppdPoints[i],    Form("hrppdPoints%d/I",    ch));
      tout->Branch(Form("hrppdBase%d",      ch), &hrppdBase[i],      Form("hrppdBase%d/D",      ch));
      tout->Branch(Form("hrppdAmp%d",       ch), &hrppdAmp[i],       Form("hrppdAmp%d/D",       ch));
      tout->Branch(Form("hrppdWidth%d",     ch), &hrppdWidth[i],     Form("hrppdWidth%d/I",     ch));
      tout->Branch(Form("hrppdCharge%d",    ch), &hrppdCharge[i],    Form("hrppdCharge%d/D",    ch));
      tout->Branch(Form("hrppd10Time%d",    ch), &hrppd10Time[i],    Form("hrppd10Time%d/D",    ch));
      tout->Branch(Form("hrppd50Time%d",    ch), &hrppd50Time[i],    Form("hrppd50Time%d/D",    ch));
      tout->Branch(Form("hrppd90Time%d",    ch), &hrppd90Time[i],    Form("hrppd90Time%d/D",    ch));
    }
  
  //--------------------------------------------------
  // Input branches
  //--------------------------------------------------
  TTreeReaderArray<double> signalTime = {tree_reader, "TIME"};
  TTreeReaderArray<double> trigger    = {tree_reader, cfg.triggerChannel.c_str()};
  
  // TTreeReaderArray is not copyable; use unique_ptr
  // Branch names come from cfg.channelBranches (set in JSON or default "CH2")
  vector<unique_ptr<TTreeReaderArray<double>>> signals;
  signals.reserve(NCHANNELS);
  for(int i = 0; i < NCHANNELS; i++)
    signals.push_back(make_unique<TTreeReaderArray<double>>(tree_reader, cfg.channelBranches[i].c_str()));
  
  //--------------------------------------------------
  // TRG histograms (created by initTriggerHistos)
  //--------------------------------------------------
  TriggerHistos htrg;
  initTriggerHistos(htrg);
  
  //--------------------------------------------------
  // Per-channel histograms (created by initChannelHistos)
  //--------------------------------------------------
  ChannelHistos hch[NCHANNELS];
  for (int i = 0; i < NCHANNELS; i++)
    initChannelHistos(i + 1, hch[i]);
  
  //--------------------------------------------------
  // Calibration pass: determine signal-to-trigger offset per channel
  //--------------------------------------------------
  cout << "Do Calibration Pass" << endl;
  while (tree_reader.Next()) {
    waveform trg((cfg.triggerType + " Trigger Pulse").c_str(), signalTime, trigger);
    int trigThresh = trg.getThresholdIndex(cfg.trgThreshold);
    
    for (int i = 0; i < NCHANNELS; i++)
      {
	waveform hrppd(Form("HRPPD%d", i+1), signalTime, *signals[i]);
	int sigPeak = hrppd.findMinimum(0, signals[i]->GetSize() - 1);
	hch[i].sigTrigOffset->Fill(sigPeak - trigThresh);
	hch[i].ampVsSigTrigOffset->Fill(sigPeak - trigThresh, std::abs(hrppd.getValue(sigPeak)));
      }
  }
  
  int SIGNAL_OFFSET[NCHANNELS];
  for (int i = 0; i < NCHANNELS; i++)
    SIGNAL_OFFSET[i] = hch[i].sigTrigOffset->GetMaximumBin() - 1;
  
  cout << "End Calibration" << endl;
  cout << "Signal Offset from Trigger =";
  for (int i = 0; i < NCHANNELS; i++) cout << " " << SIGNAL_OFFSET[i];
  cout << endl << endl;
  
  //--------------------------------------------------
  // Main analysis loop
  //--------------------------------------------------
  int NEVENTS = 0;
  tree_reader.Restart();
  while (tree_reader.Next()) {
    if (NEVENTS % 1000 == 0)
      cout << "Processed " << NEVENTS << " Events" << endl;
    
    // Set Trigger Waveform
    waveform trg((cfg.triggerType + " Trigger Pulse").c_str(), signalTime, trigger);
    
    // Find Trigger Index
    int trgTriggerIndex = -1;
    trgTriggerIndex = trg.getThresholdIndex(cfg.trgThreshold);
    
    //--- Trigger analysis ---
    TriggerResult tres = analyzeTriggerNIM(trg, trgTriggerIndex, htrg, cfg);
    
    trgOk       = tres.tok;
    trgBaseUp   = tres.tbaseUp; 
    trgBaseDown = tres.tbaseDown; 
    trgPoints   = tres.tpoints; 
    trgAmp      = tres.tamp; 
    trg50Time   = tres.t50Time;
    
    //--- Per-channel HRPPD analysis ---
    for (int i = 0; i < NCHANNELS; i++)
      {
	waveform hrppd(Form("HRPPD%d", i+1), signalTime, *signals[i]);
	ChannelResult res = analyzeChannel(hrppd, trgTriggerIndex, SIGNAL_OFFSET[i], hch[i], cfg);
	
	hrppdOk[i]        = res.ok;
	hrppdPeakIndex[i] = res.peakIndex;
	hrppdPoints[i]    = res.points;
	hrppdBase[i]      = res.base;
	hrppdAmp[i]       = res.amp;
	hrppdWidth[i]     = res.width;
	hrppdCharge[i]    = res.charge;
	hrppd10Time[i]    = res.time10;
	hrppd50Time[i]    = res.time50;
	hrppd90Time[i]    = res.time90;
	
	// HRPPD - TRG timing
	if (trgTriggerIndex > -1 && res.peakIndex > -1 && (int)res.points > 2)
	  hch[i].timeDiffVsAmp->Fill(res.amp, res.time50 - tres.t50Time);
      }

    tout->Fill();
    NEVENTS++;
  }
  
  tout->Write();
  ofile->Write();
  ofile->Close();
  
  cout << "Number of Events = " << NEVENTS << endl;
}
