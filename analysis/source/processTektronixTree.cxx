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

  // FPD
  TH1D *hFPDBottom = new TH1D("hFPDBottom","",200,-1.,1.);
  TH1D *hFPDBottomIndex = new TH1D("hFPDBottomIndex","",5000,0.,5000.);
  TH1D *hFPDBaseline = new TH1D("hFPDBaseline","",2000,-0.1,0.1);
  TH1D *hFPDAmplitude = new TH1D("hFPDAmplitude","",200,0.,1.);

  TH1D *hFPDPointsInFit = new TH1D("hFPDPointsInFit","",20,0.,20.);
  TH2D *hFPDEdgeEndVsBeginIndex = new TH2D("hFPDEdgeEndVsBeginIndex","",2000,0.,2000.,2000,0.,2000.);

  // HRPPD
  TH1D *hHRPPDBottom = new TH1D("hHRPPDBottom","",200,-0.1,0.1);
  TH1D *hHRPPDBottomIndex = new TH1D("hHRPPDBottomIndex","",5000,0.,5000.);
  TH1D *hHRPPDBaseline = new TH1D("hHRPPDBaseline","",2000,-0.1,0.1);
  TH1D *hHRPPDAmplitude = new TH1D("hHRPPDAmplitude","",1000,0.,0.5);
  TH2D *hHRPPDAmplitudeVsBottomIndex = new TH2D("hHRPPDAmplitudeVsBottomIndex","",5000,0.,5000.,200,-1.,1.);

  TH1D *hHRPPDPointsInFit = new TH1D("hHRPPDPointsInFit","",20,0.,20.);
  TH2D *hHRPPDEdgeEndVsBeginIndex = new TH2D("hHRPPDEdgeEndVsBeginIndex","",2000,0.,2000.,2000,0.,2000.);

  // Timing
  TH2D *hHRPPDFPDTimeDiffVsAmp = new TH2D("hHRPPDFPDTimeDiffVsAmp","",1000,0.,0.5,30000,15000.,45000.);

  // Define Constants
  const double _FPD_THRESHOLD_ = -0.2;
  const int _FPD_PULSE_WINDOW_ = 100;
  const int _FPD_BASELINE_WINDOW_OFFSET_ = 150;
  const int _FPD_BASELINE_WINDOW_WIDTH_ = 50;
  const int _FPD_EDGE_SEARCH_LIMIT_ = 100;
  const int _HRPPD_PULSE_WINDOW_ = 25;
  const int _HRPPD_BASELINE_WINDOW_OFFSET_ = 150;
  const int _HRPPD_BASELINE_WINDOW_WIDTH_ = 50;
  const int _HRPPD_EDGE_SEARCH_LIMIT_ = 50;

  // Loop Over Events and Find Offset
  cout << "Do Calibration Pass" << endl;
  while(tree_reader.Next()) {    
    waveform fpd("Fast Photodiode",signalTime,trigger);
    waveform hrppd("HRPPD",signalTime,signal);

    int trigPeak = fpd.findMinimum(0,trigger.GetSize()-1);
    int sigPeak = hrppd.findMinimum(0,signal.GetSize()-1);

    sigTrigOffset->Fill(sigPeak - trigPeak);
  }

  int SIGNAL_OFFSET = (sigTrigOffset->GetMaximumBin()) - 1;
  cout << "End Calibration" << endl;
  cout << "Signal Offset from Trigger = " << SIGNAL_OFFSET << endl;
  cout << endl;

  // Loop Over Events and Do Analysis
  int NEVENTS = 0;
  tree_reader.Restart();
  while(tree_reader.Next()) {
    if(NEVENTS%1000 == 0)
      cout << "Processed " << NEVENTS << " Events" << endl;
    
    waveform fpd("Fast Photodiode",signalTime,trigger);
    waveform hrppd("HRPPD",signalTime,signal);

    //==================================================
    //              Trigger (FPD) Pulse
    //==================================================
    
    // 1. Search for Pulse and Find Baseline
    double fpdBottom = 1000.;
    double fpdBaseline = 0.;
    double fpdAmplitude = 0.;
    int fpdBottomIndex = -1;
    int fpdTriggerIndex = -1;
    //bool fpdTriggerFlag = true;

    // Get Threshold Crossing
    fpdTriggerIndex = fpd.getThresholdIndex(_FPD_THRESHOLD_);
    //if(fpdTriggerIndex != -1) fpdTrigger = 1;

    if(fpdTriggerIndex > -1) // Only do if threshold is crossed
      {
	// Find Peak Position and Value
	fpdBottomIndex = fpd.findMinimum(fpdTriggerIndex,fpdTriggerIndex + _FPD_PULSE_WINDOW_);
	fpdBottom = fpd.getValue(fpdBottomIndex);

	// Find Baseline
	unsigned baselineRangeLo = (fpdTriggerIndex - _FPD_BASELINE_WINDOW_OFFSET_ > 1) ? fpdTriggerIndex - _FPD_BASELINE_WINDOW_OFFSET_ : 1;
	unsigned baselineRangeHi = baselineRangeLo + _FPD_BASELINE_WINDOW_WIDTH_;
	fpdBaseline = fpd.getBaseline(baselineRangeLo,baselineRangeHi);

	//cout << fpdTriggerIndex << " " << baselineRangeLo << " " << baselineRangeHi << endl;

	// Amplitude = Baseline - Bottom
	fpdAmplitude = fpdBaseline - fpdBottom;

	// Reference Histos
	hFPDBottom->Fill(fpdBottom);
	hFPDBottomIndex->Fill(fpdBottomIndex);
	hFPDBaseline->Fill(fpdBaseline);
	hFPDAmplitude->Fill(fpdAmplitude);
      }


    // 2. Define Limits of Leading Edge and Fit
    int fpdEdgeBeginIndex = -1;
    int fpdEdgeEndIndex = -1;
    int pointsInFPDFit = 0;
    double fpd50Percent = 0.0; 
    //double aFPD = 0.;
    //double bFPD = 0.;

    if(fpdTriggerIndex > -1) // Only do if threshold is crossed
      {
	// Define leading edge as between 10% and 90% of amplitude
	double fpdThresh10 = fpdBaseline - 0.1*fpdAmplitude;
	double fpdThresh90 = fpdBaseline - 0.9*fpdAmplitude;

	fpdEdgeEndIndex = fpd.getLeadingEdgeIndex(fpdBottomIndex,fpdThresh90,_FPD_EDGE_SEARCH_LIMIT_);
	fpdEdgeBeginIndex = fpd.getLeadingEdgeIndex(fpdBottomIndex,fpdThresh10,_FPD_EDGE_SEARCH_LIMIT_);

	// Width of the Leading Edge
	pointsInFPDFit = fpdEdgeEndIndex - fpdEdgeBeginIndex + 1;

	// Reference Histos
	hFPDPointsInFit->Fill(pointsInFPDFit);
	hFPDEdgeEndVsBeginIndex->Fill(fpdEdgeBeginIndex,fpdEdgeEndIndex);

	// Do Linear Fit on Pulse Edge
	if(fpdEdgeBeginIndex > -1 && fpdEdgeEndIndex > -1) // Make sure ranges are defined
	  {
	    double workingpoint = 0.5; // Get time at this percentage of the amplitude
	    fpd50Percent = fpd.fitLeadingEdge(fpdEdgeBeginIndex,fpdEdgeEndIndex,fpdAmplitude,fpdBaseline,workingpoint);
	  }	
      }


    //==================================================
    //             Signal (HRPPD) Pulse
    //==================================================
    // 3. Search for Pulse and Find Baseline
    double hrppdBottom = 1000.;
    double hrppdBaseline = 0.;
    double hrppdAmplitude = 0.;
    int hrppdBottomIndex = -1;

    if(fpdTriggerIndex > -1) // Only look for HRPPD pulse if there was a trigger
      {
	// Find Peak Position and Value
	hrppdBottomIndex = hrppd.findMinimum(fpdBottomIndex + SIGNAL_OFFSET - _HRPPD_PULSE_WINDOW_,fpdBottomIndex + SIGNAL_OFFSET + _HRPPD_PULSE_WINDOW_);
	hrppdBottom = hrppd.getValue(hrppdBottomIndex);

	if(hrppdBottomIndex > -1) // Proceed only if pulse position is reasonable
	  {
	    // Find Baseline
	    unsigned baselineRangeLo = (hrppdBottomIndex - _HRPPD_BASELINE_WINDOW_OFFSET_ > 1) ? hrppdBottomIndex - _HRPPD_BASELINE_WINDOW_OFFSET_ : 1;
	    unsigned baselineRangeHi = baselineRangeLo + _HRPPD_BASELINE_WINDOW_WIDTH_;
	    hrppdBaseline = hrppd.getBaseline(baselineRangeLo,baselineRangeHi);

	    //cout << fpdTriggerIndex << " " << baselineRangeLo << " " << baselineRangeHi << endl;

	    // Amplitude = Baseline - Bottom
	    hrppdAmplitude = hrppdBaseline - hrppdBottom;

	    // Reference Histos
	    hHRPPDBottom->Fill(hrppdBottom);
	    hHRPPDBottomIndex->Fill(hrppdBottomIndex);
	    hHRPPDBaseline->Fill(hrppdBaseline);
	    hHRPPDAmplitude->Fill(hrppdAmplitude);
	    hHRPPDAmplitudeVsBottomIndex->Fill(hrppdBottomIndex,hrppdAmplitude);
	  }
      }

    // 4. Define Limits of Leading Edge and Fit
    int hrppdEdgeBeginIndex = -1;
    int hrppdEdgeEndIndex = -1;
    int pointsInHRPPDFit = 0;
    double hrppd50Percent = 0.0; 
    //double aFPD = 0.;
    //double bFPD = 0.;

    if(hrppdBottomIndex > -1) // Only do if Pulse Position is Reasonable 
      {
	// Define leading edge as between 10% and 90% of amplitude
	double hrppdThresh10 = hrppdBaseline - 0.1*hrppdAmplitude;
	double hrppdThresh90 = hrppdBaseline - 0.9*hrppdAmplitude;

	hrppdEdgeEndIndex = hrppd.getLeadingEdgeIndex(hrppdBottomIndex,hrppdThresh90,_HRPPD_EDGE_SEARCH_LIMIT_);
	hrppdEdgeBeginIndex = hrppd.getLeadingEdgeIndex(hrppdBottomIndex,hrppdThresh10,_HRPPD_EDGE_SEARCH_LIMIT_);

	// Width of the Leading Edge
	pointsInHRPPDFit = hrppdEdgeEndIndex - hrppdEdgeBeginIndex + 1;

	// Reference Histos
	hHRPPDPointsInFit->Fill(pointsInHRPPDFit);
	hHRPPDEdgeEndVsBeginIndex->Fill(hrppdEdgeBeginIndex,hrppdEdgeEndIndex);

	// Do Linear Fit on Pulse Edge
	if(hrppdEdgeBeginIndex > -1 && hrppdEdgeEndIndex > -1) // Make sure ranges are defined
	  {
	    double workingpoint = 0.5; // Get time at this percentage of the amplitude
	    hrppd50Percent = hrppd.fitLeadingEdge(hrppdEdgeBeginIndex,hrppdEdgeEndIndex,hrppdAmplitude,hrppdBaseline,workingpoint);
	  }	
      }


    //==================================================
    //                HRPPD - FPD Timing
    //==================================================

    if(fpdTriggerIndex > -1 && hrppdBottomIndex > -1 && pointsInHRPPDFit > 2)
      {
	double hrppdFPDTimeDiff = hrppd50Percent - fpd50Percent;
	hHRPPDFPDTimeDiffVsAmp->Fill(hrppdAmplitude,hrppdFPDTimeDiff);
      }

    NEVENTS++;
  }

  ofile->Write();
  ofile->Close();

  cout << "Number of Events = " << NEVENTS << endl;

}
