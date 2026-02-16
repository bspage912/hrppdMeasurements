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
  // Add File to Chain
  TChain *mychain = new TChain("tree");
  mychain->Add(argv[1]);

  // Open Output File
  TFile *ofile = TFile::Open(argv[2],"recreate");

  // Set Up Input Tree Reader
  TTreeReader tree_reader(mychain);
  
  TTreeReaderArray<double> signalTime   = {tree_reader, "TIME"};
  TTreeReaderArray<double> trigger = {tree_reader, "CH1"};
  TTreeReaderArray<double> signal1 = {tree_reader, "CH2"};

  // Histograms
  TH1D *sigTrigOffset1 = new TH1D("sigTrigOffset1","",10000,0.,10000.);

  TH2D *ampVsSigTrigOffset1 = new TH2D("ampVsSigTrigOffset1","",10000,0.,10000.,200,0.,0.1);

  // TRG
  TH1D *hTRGTriggerIndex = new TH1D("hTRGTriggerIndex","",20000,0.,20000.);
  TH1D *hTRGBaselineUp = new TH1D("hTRGBaselineUp","",2000,-0.1,0.1);
  TH1D *hTRGBaselineDown = new TH1D("hTRGBaselineDown","",2000,-1.0,-0.7);
  TH1D *hTRGAmplitude = new TH1D("hTRGAmplitude","",2000,0.,1.);

  TH1D *hTRGPointsInFit = new TH1D("hTRGPointsInFit","",500,0.,500.);
  TH2D *hTRGEdgeEndVsBeginIndex = new TH2D("hTRGEdgeEndVsBeginIndex","",2000,0.,2000.,2000,0.,2000.);

  // HRPPD
  TH1D *hHRPPDBottom1 = new TH1D("hHRPPDBottom1","",200,-0.1,0.1);
  TH1D *hHRPPDBottomIndex1 = new TH1D("hHRPPDBottomIndex1","",5000,0.,5000.);
  TH1D *hHRPPDBaseline1 = new TH1D("hHRPPDBaseline1","",2000,-0.1,0.1);
  TH1D *hHRPPDAmplitude1 = new TH1D("hHRPPDAmplitude1","",1000,0.,0.5);
  TH2D *hHRPPDAmplitudeVsBottomIndex1 = new TH2D("hHRPPDAmplitudeVsBottomIndex1","",5000,0.,5000.,200,-1.,1.);

  TH1D *hHRPPDPointsInFit1 = new TH1D("hHRPPDPointsInFit1","",100,0.,100.);
  TH2D *hHRPPDEdgeEndVsBeginIndex1 = new TH2D("hHRPPDEdgeEndVsBeginIndex1","",2000,0.,2000.,2000,0.,2000.);
  TH1D *hHRPPDPulseWidth1 = new TH1D("hHRPPDPulseWidth1","",300,0.,300.);
  TH1D *hHRPPDPulseCharge1 = new TH1D("hHRPPDPulseCharge1","",900,-0.05,0.25);

  TH2D *hWFLo[10];
  TH2D *hWFMid[10];
  TH2D *hWFHi[10];
  for(int i=0; i<10; i++)
    {
      hWFLo[i] = new TH2D(Form("hWFLo_%d",i),"",10000,0.,10000.,1000,-0.95,0.05);
      hWFMid[i] = new TH2D(Form("hWFMid_%d",i),"",10000,0.,10000.,1000,-0.95,0.05);
      hWFHi[i] = new TH2D(Form("hWFHi_%d",i),"",10000,0.,10000.,1000,-0.95,0.05);
    }

  // Timing
  TH2D *hHRPPDFPDTimeDiffVsAmp1 = new TH2D("hHRPPDFPDTimeDiffVsAmp1","",1000,0.,0.5,30000,110000.,104000.);


  // Define Constants
  const double _TRG_THRESHOLD_ = -0.2;
  const int _TRG_PULSE_WINDOW_ = 100;
  const int _TRG_BASELINE_WINDOW_OFFSET_UP_ = 450;
  const int _TRG_BASELINE_WINDOW_OFFSET_DOWN_ = 700;
  const int _TRG_BASELINE_WINDOW_WIDTH_ = 150;
  const int _TRG_EDGE_SEARCH_LIMIT_ = 800;
  const int _HRPPD_PULSE_WINDOW_ = 25;
  const int _HRPPD_BASELINE_WINDOW_OFFSET_ = 150;
  const int _HRPPD_BASELINE_WINDOW_WIDTH_ = 50;
  const int _HRPPD_EDGE_SEARCH_LIMIT_ = 150;

  // Loop Over Events and Find Offset
  cout << "Do Calibration Pass" << endl;
  while(tree_reader.Next()) {    
    waveform trg("NIM Trigger Pulse",signalTime,trigger);
    waveform hrppd1("HRPPD1",signalTime,signal1);

    int trigThresh = trg.getThresholdIndex(_TRG_THRESHOLD_);
    int sigPeak1 = hrppd1.findMinimum(0,signal1.GetSize()-1);

    sigTrigOffset1->Fill(sigPeak1 - trigThresh);

    ampVsSigTrigOffset1->Fill(sigPeak1-trigThresh,std::abs(hrppd1.getValue(sigPeak1)));
  }

  int SIGNAL_OFFSET1 = (sigTrigOffset1->GetMaximumBin()) - 1;
  
  cout << "End Calibration" << endl;
  cout << "Signal Offset from Trigger = " << SIGNAL_OFFSET1 << endl; 
  cout << endl;


  // Loop Over Events and Do Analysis
  int NEVENTS = 0;
  int numWFLo = 0;
  int numWFMid = 0;
  int numWFHi = 0;
  tree_reader.Restart();
  while(tree_reader.Next()) {
    if(NEVENTS%1000 == 0)
      cout << "Processed " << NEVENTS << " Events" << endl;
    
    waveform trg("NIM Trigger Pulse",signalTime,trigger);
    waveform hrppd1("HRPPD1",signalTime,signal1);

    //==================================================
    //              Trigger (FPD) Pulse
    //==================================================
    
    // 1. Search for Pulse and Find Baseline
    double trgBaselineUp = 1000.;
    double trgBaselineDown = 1000.;
    double trgAmplitude = 0.;
    int trgTriggerIndex = -1;

    // Get Threshold Crossing
    trgTriggerIndex = trg.getThresholdIndex(_TRG_THRESHOLD_);

    if(trgTriggerIndex > -1) // Only do if threshold is crossed
      {
	// Find Peak Position and Value

	// Find Baseline
	unsigned baselineRangeUpLo = (trgTriggerIndex - _TRG_BASELINE_WINDOW_OFFSET_UP_ > 1) ? trgTriggerIndex - _TRG_BASELINE_WINDOW_OFFSET_UP_ : 1;
	unsigned baselineRangeUpHi = baselineRangeUpLo + _TRG_BASELINE_WINDOW_WIDTH_;
	trgBaselineUp = trg.getBaseline(baselineRangeUpLo,baselineRangeUpHi);

	unsigned baselineRangeDownLo = trgTriggerIndex + _TRG_BASELINE_WINDOW_OFFSET_DOWN_;
	unsigned baselineRangeDownHi = baselineRangeDownLo + _TRG_BASELINE_WINDOW_WIDTH_;
	trgBaselineDown = trg.getBaseline(baselineRangeDownLo,baselineRangeDownHi);

	trgAmplitude = trgBaselineUp - trgBaselineDown;

	// Reference Histos
	hTRGTriggerIndex->Fill(trgTriggerIndex);
	hTRGBaselineUp->Fill(trgBaselineUp);
	hTRGBaselineDown->Fill(trgBaselineDown);
	hTRGAmplitude->Fill(trgAmplitude);
      }


    // 2. Define Limits of Leading Edge and Fit
    int trgEdgeBeginIndex = -1;
    int trgEdgeEndIndex = -1;
    int pointsInTRGFit = 0;
    double trg50Percent = 0.0; 

    if(trgTriggerIndex > -1) // Only do if threshold is crossed
      {
	// Define leading edge as between 10% and 90% of amplitude
	double trgThresh10 = trgBaselineUp - 0.1*trgAmplitude;
	double trgThresh90 = trgBaselineUp - 0.9*trgAmplitude;

	trgEdgeEndIndex = trg.getLeadingEdgeIndex(trgTriggerIndex + _TRG_BASELINE_WINDOW_OFFSET_DOWN_,trgThresh90,_TRG_EDGE_SEARCH_LIMIT_);
	trgEdgeBeginIndex = trg.getLeadingEdgeIndex(trgTriggerIndex + _TRG_BASELINE_WINDOW_OFFSET_DOWN_,trgThresh10,_TRG_EDGE_SEARCH_LIMIT_);

	// Width of the Leading Edge
	pointsInTRGFit = trgEdgeEndIndex - trgEdgeBeginIndex + 1;

	// Reference Histos
	hTRGPointsInFit->Fill(pointsInTRGFit);
	hTRGEdgeEndVsBeginIndex->Fill(trgEdgeBeginIndex,trgEdgeEndIndex);

	// Do Linear Fit on Pulse Edge
	if(trgEdgeBeginIndex > -1 && trgEdgeEndIndex > -1) // Make sure ranges are defined
	  {
	    double workingpoint = 0.5; // Get time at this percentage of the amplitude
	    trg50Percent = trg.fitLeadingEdge(trgEdgeBeginIndex,trgEdgeEndIndex,trgAmplitude,trgBaselineUp,workingpoint);
	  }	
      }


    //==================================================
    //             Signal (HRPPD) Pulse 1
    //==================================================
    // 3. Search for Pulse and Find Baseline
    double hrppdBottom1 = 1000.;
    double hrppdBaseline1 = 0.;
    double hrppdAmplitude1 = 0.;
    int hrppdBottomIndex1 = -1;

    if(trgTriggerIndex > -1) // Only look for HRPPD pulse if there was a trigger
      {
	// Find Peak Position and Value
	hrppdBottomIndex1 = hrppd1.findMinimum(trgTriggerIndex + SIGNAL_OFFSET1 - _HRPPD_PULSE_WINDOW_,trgTriggerIndex + SIGNAL_OFFSET1 + _HRPPD_PULSE_WINDOW_);
	hrppdBottom1 = hrppd1.getValue(hrppdBottomIndex1);

	if(hrppdBottomIndex1 > -1) // Proceed only if pulse position is reasonable
	  {
	    // Find Baseline
	    unsigned baselineRangeLo1 = (hrppdBottomIndex1 - _HRPPD_BASELINE_WINDOW_OFFSET_ > 1) ? hrppdBottomIndex1 - _HRPPD_BASELINE_WINDOW_OFFSET_ : 1;
	    unsigned baselineRangeHi1 = baselineRangeLo1 + _HRPPD_BASELINE_WINDOW_WIDTH_;
	    hrppdBaseline1 = hrppd1.getBaseline(baselineRangeLo1,baselineRangeHi1);

	    // Amplitude = Baseline - Bottom
	    hrppdAmplitude1 = hrppdBaseline1 - hrppdBottom1;

	    // Reference Histos
	    hHRPPDBottom1->Fill(hrppdBottom1);
	    hHRPPDBottomIndex1->Fill(hrppdBottomIndex1);
	    hHRPPDBaseline1->Fill(hrppdBaseline1);
	    hHRPPDAmplitude1->Fill(hrppdAmplitude1);
	    hHRPPDAmplitudeVsBottomIndex1->Fill(hrppdBottomIndex1,hrppdAmplitude1);
	  }
      }

    // 4. Define Limits of Leading Edge and Fit
    int hrppdEdgeBeginIndex1 = -1;
    int hrppdEdgeEndIndex1 = -1;
    int hrppdBeginningIndex1 = -1;
    int hrppdTrailingIndex1 = -1;
    int pointsInHRPPDFit1 = 0;
    int hrppdPulseWidth1 = 0;
    double hrppdPulseCharge1 = 0.0;
    double hrppd10Percent1 = 0.0;
    double hrppd50Percent1 = 0.0;
    double hrppd90Percent1 = 0.0;

    if(hrppdBottomIndex1 > -1) // Only do if Pulse Position is Reasonable 
      {
	// Define leading edge as between 10% and 90% of amplitude
	double hrppdThresh011 = hrppdBaseline1 - 0.01*hrppdAmplitude1;
	double hrppdThresh101 = hrppdBaseline1 - 0.1*hrppdAmplitude1;
	double hrppdThresh901 = hrppdBaseline1 - 0.9*hrppdAmplitude1;

	hrppdEdgeEndIndex1 = hrppd1.getLeadingEdgeIndex(hrppdBottomIndex1,hrppdThresh901,_HRPPD_EDGE_SEARCH_LIMIT_);
	hrppdEdgeBeginIndex1 = hrppd1.getLeadingEdgeIndex(hrppdBottomIndex1,hrppdThresh101,_HRPPD_EDGE_SEARCH_LIMIT_);
	hrppdBeginningIndex1 = hrppd1.getLeadingEdgeIndex(hrppdBottomIndex1,hrppdThresh011,_HRPPD_EDGE_SEARCH_LIMIT_+100);
	hrppdTrailingIndex1 = hrppd1.getTrailingEdgeIndex(hrppdBottomIndex1,hrppdThresh011,_HRPPD_EDGE_SEARCH_LIMIT_+100); // Trailing edge is extended

	// Width of the Leading Edge
	pointsInHRPPDFit1 = hrppdEdgeEndIndex1 - hrppdEdgeBeginIndex1 + 1;

	// Width of Pulse
	hrppdPulseWidth1 = hrppdTrailingIndex1 - hrppdBeginningIndex1 + 1;

	// Calculate Integrated Charge
	double q1 = 0.0;
	if(hrppdTrailingIndex1 != -1)
	  {
	    for(unsigned i=hrppdBeginningIndex1; i<=hrppdTrailingIndex1; i++)
	      {
		q1 += (hrppdBaseline1 - hrppd1.getValue(i));//*20E-12;
	      }
	    q1 /= 50.0;
	  }
	hrppdPulseCharge1 = q1;

	// Reference Histos
	hHRPPDPointsInFit1->Fill(pointsInHRPPDFit1);
	hHRPPDEdgeEndVsBeginIndex1->Fill(hrppdEdgeBeginIndex1,hrppdEdgeEndIndex1);
	hHRPPDPulseWidth1->Fill(hrppdPulseWidth1);
	hHRPPDPulseCharge1->Fill(q1);

	// Do Linear Fit on Pulse Edge
	if(hrppdEdgeBeginIndex1 > -1 && hrppdEdgeEndIndex1 > -1) // Make sure ranges are defined
	  {
	    double workingpoint = 0.5; // Get time at this percentage of the amplitude
	    hrppd10Percent1 = hrppd1.fitLeadingEdge(hrppdEdgeBeginIndex1,hrppdEdgeEndIndex1,hrppdAmplitude1,hrppdBaseline1,0.10);
	    hrppd50Percent1 = hrppd1.fitLeadingEdge(hrppdEdgeBeginIndex1,hrppdEdgeEndIndex1,hrppdAmplitude1,hrppdBaseline1,workingpoint);
	    hrppd90Percent1 = hrppd1.fitLeadingEdge(hrppdEdgeBeginIndex1,hrppdEdgeEndIndex1,hrppdAmplitude1,hrppdBaseline1,0.90);
	  }

	// Get Waveform
	if(hrppdAmplitude1 > 0.01 && hrppdAmplitude1 < 0.02 && numWFLo < 10) // 0.03
	  {
	    for(unsigned i=0; i<10000; i++)
	      {
		hWFLo[numWFLo]->Fill(i,hrppd1.getValue(i));
	      }

	    numWFLo++;
	  }
	if(hrppdAmplitude1 > 0.02 && hrppdAmplitude1 < 0.03 && numWFMid < 10) // 0.03
	  {
	    for(unsigned i=0; i<10000; i++)
	      {
		hWFMid[numWFMid]->Fill(i,hrppd1.getValue(i));
	      }

	    numWFMid++;
	  }
	if(hrppdAmplitude1 > 0.03 && numWFHi < 10) // 0.03
	  {
	    for(unsigned i=0; i<10000; i++)
	      {
		hWFHi[numWFHi]->Fill(i,hrppd1.getValue(i));
	      }

	    numWFHi++;
	  }
      }


    //==================================================
    //                HRPPD - FPD Timing
    //==================================================

    if(trgTriggerIndex > -1 && hrppdBottomIndex1 > -1 && pointsInHRPPDFit1 > 2)
      {
	double hrppdTRGTimeDiff1 = hrppd50Percent1 - trg50Percent;
	hHRPPDFPDTimeDiffVsAmp1->Fill(hrppdAmplitude1,hrppdTRGTimeDiff1);
      }

    //tout->Fill();
    NEVENTS++;
  }

  //tout->Write();
  ofile->Write();
  ofile->Close();

  cout << "Number of Events = " << NEVENTS << endl;

}
