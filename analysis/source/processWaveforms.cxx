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

  // Create Output Tree to Allow Offline Analysis
  //auto tout = new TTree("t", "Analyzed Scope Tree");

  //auto *hb1 = new TH1D("hb1", "", 100, -0.020, 0.020);
  //auto *hb4 = new TH1D("hb4", "", 100, -0.010, 0.010);

  // Set Up Input Tree Reader
  TTreeReader tree_reader(mychain);

  /*
  unsigned trgOk = 0, trgPoints = 0;
  double trgBaseUp = 0.0, trgBaseDown = 0.0, trgAmp = 0.0, trg50Time = 0.0;
  unsigned hrppdOk1 = 0, hrppdPeakIndex1 = 0, hrppdPoints1 = 0, hrppdWidth1 = 0;
  double hrppdBase1 = 0.0, hrppdAmp1 = 0.0, hrppdCharge1 = 0.0, hrppd10Time1 = 0.0, hrppd50Time1 = 0.0, hrppd90Time1 = 0.0;
  unsigned hrppdOk2 = 0, hrppdPeakIndex2 = 0, hrppdPoints2 = 0, hrppdWidth2 = 0;
  double hrppdBase2 = 0.0, hrppdAmp2 = 0.0, hrppdCharge2 = 0.0, hrppd10Time2 = 0.0, hrppd50Time2 = 0.0, hrppd90Time2 = 0.0;
  unsigned hrppdOk3 = 0, hrppdPeakIndex3 = 0, hrppdPoints3 = 0, hrppdWidth3 = 0;
  double hrppdBase3 = 0.0, hrppdAmp3 = 0.0, hrppdCharge3 = 0.0, hrppd10Time3 = 0.0, hrppd50Time3 = 0.0, hrppd90Time3 = 0.0;
  unsigned hrppdOk4 = 0, hrppdPeakIndex4 = 0, hrppdPoints4 = 0, hrppdWidth4 = 0;
  double hrppdBase4 = 0.0, hrppdAmp4 = 0.0, hrppdCharge4 = 0.0, hrppd10Time4 = 0.0, hrppd50Time4 = 0.0, hrppd90Time4 = 0.0;
  unsigned hrppdOk5 = 0, hrppdPeakIndex5 = 0, hrppdPoints5 = 0, hrppdWidth5 = 0;
  double hrppdBase5 = 0.0, hrppdAmp5 = 0.0, hrppdCharge5 = 0.0, hrppd10Time5 = 0.0, hrppd50Time5 = 0.0, hrppd90Time5 = 0.0;
  
  tout->Branch("trgOk", &trgOk, "trgOk/I");
  //tout->Branch("trgPeakIndex", &trgPeakIndex, "trgPeakIndex/I");
  tout->Branch("trgPoints", &trgPoints, "trgPoints/I");
  tout->Branch("trgBaseUp", &trgBaseUp, "trgBaseUp/D");
  tout->Branch("trgBaseDown", &trgBaseDown, "trgBaseDown/D");
  tout->Branch("trgAmp", &trgAmp, "trgAmp/D");
  tout->Branch("trg50Time", &trg50Time, "trg50Time/D");
  
  tout->Branch("hrppdOk1",&hrppdOk1, "hrppdOk1/I");
  tout->Branch("hrppdPeakIndex1", &hrppdPeakIndex1, "hrppdPeakIndex1/I");
  tout->Branch("hrppdPoints1", &hrppdPoints1, "hrppdPoints1/I");
  tout->Branch("hrppdBase1", &hrppdBase1, "hrppdBase1/D");
  tout->Branch("hrppdAmp1", &hrppdAmp1, "hrppdAmp1/D");
  tout->Branch("hrppdWidth1", &hrppdWidth1, "hrppdWidth1/I");
  tout->Branch("hrppdCharge1", &hrppdCharge1, "hrppdCharge1/D");
  tout->Branch("hrppd10Time1", &hrppd10Time1, "hrppd10Time1/D");
  tout->Branch("hrppd50Time1", &hrppd50Time1, "hrppd50Time1/D");
  tout->Branch("hrppd90Time1", &hrppd90Time1, "hrppd90Time1/D");
  
  tout->Branch("hrppdOk2",&hrppdOk2, "hrppdOk2/I");
  tout->Branch("hrppdPeakIndex2", &hrppdPeakIndex2, "hrppdPeakIndex2/I");
  tout->Branch("hrppdPoints2", &hrppdPoints2, "hrppdPoints2/I");
  tout->Branch("hrppdBase2", &hrppdBase2, "hrppdBase2/D");
  tout->Branch("hrppdAmp2", &hrppdAmp2, "hrppdAmp2/D");
  tout->Branch("hrppdWidth2", &hrppdWidth2, "hrppdWidth2/I");
  tout->Branch("hrppdCharge2", &hrppdCharge2, "hrppdCharge2/D");
  tout->Branch("hrppd10Time2", &hrppd10Time2, "hrppd10Time2/D");
  tout->Branch("hrppd50Time2", &hrppd50Time2, "hrppd50Time2/D");
  tout->Branch("hrppd90Time2", &hrppd90Time2, "hrppd90Time2/D");
  
  tout->Branch("hrppdOk3",&hrppdOk3, "hrppdOk3/I");
  tout->Branch("hrppdPeakIndex3", &hrppdPeakIndex3, "hrppdPeakIndex3/I");
  tout->Branch("hrppdPoints3", &hrppdPoints3, "hrppdPoints3/I");
  tout->Branch("hrppdBase3", &hrppdBase3, "hrppdBase3/D");
  tout->Branch("hrppdAmp3", &hrppdAmp3, "hrppdAmp3/D");
  tout->Branch("hrppdWidth3", &hrppdWidth3, "hrppdWidth3/I");
  tout->Branch("hrppdCharge3", &hrppdCharge3, "hrppdCharge3/D");
  tout->Branch("hrppd10Time3", &hrppd10Time3, "hrppd10Time3/D");
  tout->Branch("hrppd50Time3", &hrppd50Time3, "hrppd50Time3/D");
  tout->Branch("hrppd90Time3", &hrppd90Time3, "hrppd90Time3/D");
  
  tout->Branch("hrppdOk4",&hrppdOk4, "hrppdOk4/I");
  tout->Branch("hrppdPeakIndex4", &hrppdPeakIndex4, "hrppdPeakIndex4/I");
  tout->Branch("hrppdPoints4", &hrppdPoints4, "hrppdPoints4/I");
  tout->Branch("hrppdBase4", &hrppdBase4, "hrppdBase4/D");
  tout->Branch("hrppdAmp4", &hrppdAmp4, "hrppdAmp4/D");
  tout->Branch("hrppdWidth4", &hrppdWidth4, "hrppdWidth4/I");
  tout->Branch("hrppdCharge4", &hrppdCharge4, "hrppdCharge4/D");
  tout->Branch("hrppd10Time4", &hrppd10Time4, "hrppd10Time4/D");
  tout->Branch("hrppd50Time4", &hrppd50Time4, "hrppd50Time4/D");
  tout->Branch("hrppd90Time4", &hrppd90Time4, "hrppd90Time4/D");
  
  tout->Branch("hrppdOk5",&hrppdOk5, "hrppdOk5/I");
  tout->Branch("hrppdPeakIndex5", &hrppdPeakIndex5, "hrppdPeakIndex5/I");
  tout->Branch("hrppdPoints5", &hrppdPoints5, "hrppdPoints5/I");
  tout->Branch("hrppdBase5", &hrppdBase5, "hrppdBase5/D");
  tout->Branch("hrppdAmp5", &hrppdAmp5, "hrppdAmp5/D");
  tout->Branch("hrppdWidth5", &hrppdWidth5, "hrppdWidth5/I");
  tout->Branch("hrppdCharge5", &hrppdCharge5, "hrppdCharge5/D");
  tout->Branch("hrppd10Time5", &hrppd10Time5, "hrppd10Time5/D");
  tout->Branch("hrppd50Time5", &hrppd50Time5, "hrppd50Time5/D");
  tout->Branch("hrppd90Time5", &hrppd90Time5, "hrppd90Time5/D");
  */
  

  //TTreeReaderArray<double> eventTime    = {tree_reader, "eventTime"};
  TTreeReaderArray<double> signalTime   = {tree_reader, "TIME"};
  TTreeReaderArray<double> trigger = {tree_reader, "CH1"};
  TTreeReaderArray<double> signal1 = {tree_reader, "CH2"};
  //TTreeReaderArray<double> signal2 = {tree_reader, "CH2"}; //CH3
  //TTreeReaderArray<double> signal3 = {tree_reader, "CH4"};
  //TTreeReaderArray<double> signal4 = {tree_reader, "CH2"}; // CH5
  //TTreeReaderArray<double> signal5 = {tree_reader, "CH2"}; // CH6

  // Histograms
  TH1D *sigTrigOffset1 = new TH1D("sigTrigOffset1","",10000,0.,10000.);
  //TH1D *sigTrigOffset2 = new TH1D("sigTrigOffset2","",10000,0.,10000.);
  //TH1D *sigTrigOffset3 = new TH1D("sigTrigOffset3","",10000,0.,10000.);
  //TH1D *sigTrigOffset4 = new TH1D("sigTrigOffset4","",10000,0.,10000.);
  //TH1D *sigTrigOffset5 = new TH1D("sigTrigOffset5","",10000,0.,10000.);

  TH2D *ampVsSigTrigOffset1 = new TH2D("ampVsSigTrigOffset1","",10000,0.,10000.,200,0.,0.1);
  //TH2D *ampVsSigTrigOffset2 = new TH2D("ampVsSigTrigOffset2","",10000,0.,10000.,200,0.,0.1);
  //TH2D *ampVsSigTrigOffset3 = new TH2D("ampVsSigTrigOffset3","",10000,0.,10000.,200,0.,0.1);
  //TH2D *ampVsSigTrigOffset4 = new TH2D("ampVsSigTrigOffset4","",10000,0.,10000.,200,0.,0.1);
  //TH2D *ampVsSigTrigOffset5 = new TH2D("ampVsSigTrigOffset5","",10000,0.,10000.,200,0.,0.1);

  // TRG
  //TH1D *hFPDBottom = new TH1D("hFPDBottom","",200,-1.,1.);
  //TH1D *hFPDBottomIndex = new TH1D("hFPDBottomIndex","",5000,0.,5000.);
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

  TH2D *hWF[10];
  for(int i=0; i<10; i++)
    {
      hWF[i] = new TH2D(Form("hWF_%d",i),"",10000,0.,10000.,1000,-0.95,0.05);
    }

  /*
  TH1D *hHRPPDBottom2 = new TH1D("hHRPPDBottom2","",200,-0.1,0.1);
  TH1D *hHRPPDBottomIndex2 = new TH1D("hHRPPDBottomIndex2","",5000,0.,5000.);
  TH1D *hHRPPDBaseline2 = new TH1D("hHRPPDBaseline2","",2000,-0.1,0.1);
  TH1D *hHRPPDAmplitude2 = new TH1D("hHRPPDAmplitude2","",1000,0.,0.5);
  TH2D *hHRPPDAmplitudeVsBottomIndex2 = new TH2D("hHRPPDAmplitudeVsBottomIndex2","",5000,0.,5000.,200,-1.,1.);

  TH1D *hHRPPDPointsInFit2 = new TH1D("hHRPPDPointsInFit2","",100,0.,100.);
  TH2D *hHRPPDEdgeEndVsBeginIndex2 = new TH2D("hHRPPDEdgeEndVsBeginIndex2","",2000,0.,2000.,2000,0.,2000.);
  TH1D *hHRPPDPulseWidth2 = new TH1D("hHRPPDPulseWidth2","",300,0.,300.);
  TH1D *hHRPPDPulseCharge2 = new TH1D("hHRPPDPulseCharge2","",900,-0.05,0.25);

  TH1D *hHRPPDBottom3 = new TH1D("hHRPPDBottom3","",200,-0.1,0.1);
  TH1D *hHRPPDBottomIndex3 = new TH1D("hHRPPDBottomIndex3","",5000,0.,5000.);
  TH1D *hHRPPDBaseline3 = new TH1D("hHRPPDBaseline3","",2000,-0.1,0.1);
  TH1D *hHRPPDAmplitude3 = new TH1D("hHRPPDAmplitude3","",1000,0.,0.5);
  TH2D *hHRPPDAmplitudeVsBottomIndex3 = new TH2D("hHRPPDAmplitudeVsBottomIndex3","",5000,0.,5000.,200,-1.,1.);

  TH1D *hHRPPDPointsInFit3 = new TH1D("hHRPPDPointsInFit3","",100,0.,100.);
  TH2D *hHRPPDEdgeEndVsBeginIndex3 = new TH2D("hHRPPDEdgeEndVsBeginIndex3","",2000,0.,2000.,2000,0.,2000.);
  TH1D *hHRPPDPulseWidth3 = new TH1D("hHRPPDPulseWidth3","",300,0.,300.);
  TH1D *hHRPPDPulseCharge3 = new TH1D("hHRPPDPulseCharge3","",900,-0.05,0.25);

  TH1D *hHRPPDBottom4 = new TH1D("hHRPPDBottom4","",200,-0.1,0.1);
  TH1D *hHRPPDBottomIndex4 = new TH1D("hHRPPDBottomIndex4","",5000,0.,5000.);
  TH1D *hHRPPDBaseline4 = new TH1D("hHRPPDBaseline4","",2000,-0.1,0.1);
  TH1D *hHRPPDAmplitude4 = new TH1D("hHRPPDAmplitude4","",1000,0.,0.5);
  TH2D *hHRPPDAmplitudeVsBottomIndex4 = new TH2D("hHRPPDAmplitudeVsBottomIndex4","",5000,0.,5000.,200,-1.,1.);

  TH1D *hHRPPDPointsInFit4 = new TH1D("hHRPPDPointsInFit4","",100,0.,100.);
  TH2D *hHRPPDEdgeEndVsBeginIndex4 = new TH2D("hHRPPDEdgeEndVsBeginIndex4","",2000,0.,2000.,2000,0.,2000.);
  TH1D *hHRPPDPulseWidth4 = new TH1D("hHRPPDPulseWidth4","",300,0.,300.);
  TH1D *hHRPPDPulseCharge4 = new TH1D("hHRPPDPulseCharge4","",900,-0.05,0.25);

  TH1D *hHRPPDBottom5 = new TH1D("hHRPPDBottom5","",200,-0.1,0.1);
  TH1D *hHRPPDBottomIndex5 = new TH1D("hHRPPDBottomIndex5","",5000,0.,5000.);
  TH1D *hHRPPDBaseline5 = new TH1D("hHRPPDBaseline5","",2000,-0.1,0.1);
  TH1D *hHRPPDAmplitude5 = new TH1D("hHRPPDAmplitude5","",1000,0.,0.5);
  TH2D *hHRPPDAmplitudeVsBottomIndex5 = new TH2D("hHRPPDAmplitudeVsBottomIndex5","",5000,0.,5000.,200,-1.,1.);

  TH1D *hHRPPDPointsInFit5 = new TH1D("hHRPPDPointsInFit5","",100,0.,100.);
  TH2D *hHRPPDEdgeEndVsBeginIndex5 = new TH2D("hHRPPDEdgeEndVsBeginIndex5","",2000,0.,2000.,2000,0.,2000.);
  TH1D *hHRPPDPulseWidth5 = new TH1D("hHRPPDPulseWidth5","",300,0.,300.);
  TH1D *hHRPPDPulseCharge5 = new TH1D("hHRPPDPulseCharge5","",900,-0.05,0.25);
  */

  // Timing
  TH2D *hHRPPDFPDTimeDiffVsAmp1 = new TH2D("hHRPPDFPDTimeDiffVsAmp1","",1000,0.,0.5,30000,110000.,104000.);
  //TH2D *hHRPPDFPDTimeDiffVsAmp2 = new TH2D("hHRPPDFPDTimeDiffVsAmp2","",1000,0.,0.5,30000,110000.,140000.);
  //TH2D *hHRPPDFPDTimeDiffVsAmp3 = new TH2D("hHRPPDFPDTimeDiffVsAmp3","",1000,0.,0.5,30000,110000.,140000.);
  //TH2D *hHRPPDFPDTimeDiffVsAmp4 = new TH2D("hHRPPDFPDTimeDiffVsAmp4","",1000,0.,0.5,30000,110000.,140000.);
  //TH2D *hHRPPDFPDTimeDiffVsAmp5 = new TH2D("hHRPPDFPDTimeDiffVsAmp5","",1000,0.,0.5,30000,110000.,140000.);

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
  const int _HRPPD_EDGE_SEARCH_LIMIT_ = 50;

  // Loop Over Events and Find Offset
  cout << "Do Calibration Pass" << endl;
  while(tree_reader.Next()) {    
    waveform trg("NIM Trigger Pulse",signalTime,trigger);
    waveform hrppd1("HRPPD1",signalTime,signal1);
    //waveform hrppd2("HRPPD2",signalTime,signal2);
    //waveform hrppd3("HRPPD3",signalTime,signal3);
    //waveform hrppd4("HRPPD4",signalTime,signal4);
    //waveform hrppd5("HRPPD5",signalTime,signal5);

    int trigThresh = trg.getThresholdIndex(_TRG_THRESHOLD_);
    int sigPeak1 = hrppd1.findMinimum(0,signal1.GetSize()-1);
    //int sigPeak2 = hrppd2.findMinimum(0,signal2.GetSize()-1);
    //int sigPeak3 = hrppd3.findMinimum(0,signal3.GetSize()-1);
    //int sigPeak4 = hrppd4.findMinimum(0,signal4.GetSize()-1);
    //int sigPeak5 = hrppd5.findMinimum(0,signal5.GetSize()-1);

    sigTrigOffset1->Fill(sigPeak1 - trigThresh);
    //sigTrigOffset2->Fill(sigPeak2 - trigThresh);
    //sigTrigOffset3->Fill(sigPeak3 - trigThresh);
    //sigTrigOffset4->Fill(sigPeak4 - trigThresh);
    //sigTrigOffset5->Fill(sigPeak5 - trigThresh);

    ampVsSigTrigOffset1->Fill(sigPeak1-trigThresh,std::abs(hrppd1.getValue(sigPeak1)));
    //ampVsSigTrigOffset2->Fill(sigPeak2-trigThresh,std::abs(hrppd2.getValue(sigPeak2)));
    //ampVsSigTrigOffset3->Fill(sigPeak3-trigThresh,std::abs(hrppd3.getValue(sigPeak3)));
    //ampVsSigTrigOffset4->Fill(sigPeak4-trigThresh,std::abs(hrppd4.getValue(sigPeak4)));
    //ampVsSigTrigOffset5->Fill(sigPeak5-trigThresh,std::abs(hrppd5.getValue(sigPeak5)));
  }

  int SIGNAL_OFFSET1 = (sigTrigOffset1->GetMaximumBin()) - 1;
  //int SIGNAL_OFFSET2 = (sigTrigOffset2->GetMaximumBin()) - 1;
  //int SIGNAL_OFFSET3 = (sigTrigOffset3->GetMaximumBin()) - 1;
  //int SIGNAL_OFFSET4 = (sigTrigOffset4->GetMaximumBin()) - 1;
  //int SIGNAL_OFFSET5 = (sigTrigOffset5->GetMaximumBin()) - 1;
  cout << "End Calibration" << endl;
  cout << "Signal Offset from Trigger = " << SIGNAL_OFFSET1 << endl; //" " << SIGNAL_OFFSET2 << " " << SIGNAL_OFFSET3 << " " << SIGNAL_OFFSET4 << " " << SIGNAL_OFFSET5 << endl;
  cout << endl;

  // Loop Over Events and Do Analysis
  int NEVENTS = 0;
  int numWF = 0;
  tree_reader.Restart();
  while(tree_reader.Next()) {
    if(NEVENTS%1000 == 0)
      cout << "Processed " << NEVENTS << " Events" << endl;
    
    waveform trg("NIM Trigger Pulse",signalTime,trigger);
    waveform hrppd1("HRPPD1",signalTime,signal1);
    //waveform hrppd2("HRPPD2",signalTime,signal2);
    //waveform hrppd3("HRPPD3",signalTime,signal3);
    //waveform hrppd4("HRPPD4",signalTime,signal4);
    //waveform hrppd5("HRPPD5",signalTime,signal5);

    //int numWF = 0;

    //==================================================
    //              Trigger (FPD) Pulse
    //==================================================
    
    // 1. Search for Pulse and Find Baseline
    //double fpdBottom = 1000.;
    //double fpdBaseline = 0.;
    double trgBaselineUp = 1000.;
    double trgBaselineDown = 1000.;
    double trgAmplitude = 0.;
    //int fpdBottomIndex = -1;
    int trgTriggerIndex = -1;
    //bool fpdTriggerFlag = true;

    //trgOk = 0;

    // Get Threshold Crossing
    trgTriggerIndex = trg.getThresholdIndex(_TRG_THRESHOLD_);
    //if(fpdTriggerIndex != -1) fpdTrigger = 1;

    if(trgTriggerIndex > -1) // Only do if threshold is crossed
      {
	// Find Peak Position and Value
	//fpdBottomIndex = fpd.findMinimum(fpdTriggerIndex,fpdTriggerIndex + _FPD_PULSE_WINDOW_);
	//fpdBottom = fpd.getValue(fpdBottomIndex);

	// Find Baseline
	unsigned baselineRangeUpLo = (trgTriggerIndex - _TRG_BASELINE_WINDOW_OFFSET_UP_ > 1) ? trgTriggerIndex - _TRG_BASELINE_WINDOW_OFFSET_UP_ : 1;
	unsigned baselineRangeUpHi = baselineRangeUpLo + _TRG_BASELINE_WINDOW_WIDTH_;
	trgBaselineUp = trg.getBaseline(baselineRangeUpLo,baselineRangeUpHi);

	unsigned baselineRangeDownLo = trgTriggerIndex + _TRG_BASELINE_WINDOW_OFFSET_DOWN_;
	unsigned baselineRangeDownHi = baselineRangeDownLo + _TRG_BASELINE_WINDOW_WIDTH_;
	trgBaselineDown = trg.getBaseline(baselineRangeDownLo,baselineRangeDownHi);

	//cout << fpdTriggerIndex << " " << baselineRangeLo << " " << baselineRangeHi << endl;

	// Amplitude = Baseline - Bottom
	trgAmplitude = trgBaselineUp - trgBaselineDown;

	// Reference Histos
	//hFPDBottom->Fill(fpdBottom);
	//hFPDBottomIndex->Fill(fpdBottomIndex);
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
    //double aFPD = 0.;
    //double bFPD = 0.;

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

    // Set FPD Tree Variables
    //if(trgTriggerIndex > -1) trgOk = 1;
    ////fpdPeakIndex = fpdBottomIndex;
    //trgPoints = pointsInTRGFit;
    //trgBaseUp = trgBaselineUp;
    //trgBaseDown = trgBaselineDown;
    //trgAmp = trgAmplitude;
    //trg50Time = trg50Percent;


    //==================================================
    //             Signal (HRPPD) Pulse 1
    //==================================================
    // 3. Search for Pulse and Find Baseline
    double hrppdBottom1 = 1000.;
    double hrppdBaseline1 = 0.;
    double hrppdAmplitude1 = 0.;
    int hrppdBottomIndex1 = -1;

    //hrppdOk1 = 0;

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

	    //cout << fpdTriggerIndex << " " << baselineRangeLo << " " << baselineRangeHi << endl;

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
    //double aFPD = 0.;
    //double bFPD = 0.;

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
	if(hrppdAmplitude1 > 0.03 && numWF < 10) // 0.03
	  {
	    for(unsigned i=0; i<10000; i++)
	      {
		hWF[numWF]->Fill(i,hrppd1.getValue(i));
	      }

	    numWF++;
	  }
      }

    // Set HRPPD Tree Variables
    //if(hrppdBottomIndex1 > -1) hrppdOk1 = 1;
    //hrppdPeakIndex1 = hrppdBottomIndex1;
    //hrppdPoints1 = pointsInHRPPDFit1;
    //hrppdBase1 = hrppdBaseline1;
    //hrppdAmp1 = hrppdAmplitude1;
    //hrppdWidth1 = hrppdPulseWidth1;
    //hrppdCharge1 = hrppdPulseCharge1;
    //hrppd10Time1 = hrppd10Percent1;
    //hrppd50Time1 = hrppd50Percent1;
    //hrppd90Time1 = hrppd90Percent1;

    /*
    //==================================================
    //             Signal (HRPPD) Pulse 2
    //==================================================
    // 3. Search for Pulse and Find Baseline
    double hrppdBottom2 = 1000.;
    double hrppdBaseline2 = 0.;
    double hrppdAmplitude2 = 0.;
    int hrppdBottomIndex2 = -1;

    hrppdOk2 = 0;

    if(trgTriggerIndex > -1) // Only look for HRPPD pulse if there was a trigger
      {
	// Find Peak Position and Value
	hrppdBottomIndex2 = hrppd2.findMinimum(trgTriggerIndex + SIGNAL_OFFSET2 - _HRPPD_PULSE_WINDOW_,trgTriggerIndex + SIGNAL_OFFSET2 + _HRPPD_PULSE_WINDOW_);
	hrppdBottom2 = hrppd2.getValue(hrppdBottomIndex2);

	if(hrppdBottomIndex2 > -1) // Proceed only if pulse position is reasonable
	  {
	    // Find Baseline
	    unsigned baselineRangeLo2 = (hrppdBottomIndex2 - _HRPPD_BASELINE_WINDOW_OFFSET_ > 1) ? hrppdBottomIndex2 - _HRPPD_BASELINE_WINDOW_OFFSET_ : 1;
	    unsigned baselineRangeHi2 = baselineRangeLo2 + _HRPPD_BASELINE_WINDOW_WIDTH_;
	    hrppdBaseline2 = hrppd2.getBaseline(baselineRangeLo2,baselineRangeHi2);

	    //cout << fpdTriggerIndex << " " << baselineRangeLo << " " << baselineRangeHi << endl;

	    // Amplitude = Baseline - Bottom
	    hrppdAmplitude2 = hrppdBaseline2 - hrppdBottom2;

	    // Reference Histos
	    hHRPPDBottom2->Fill(hrppdBottom2);
	    hHRPPDBottomIndex2->Fill(hrppdBottomIndex2);
	    hHRPPDBaseline2->Fill(hrppdBaseline2);
	    hHRPPDAmplitude2->Fill(hrppdAmplitude2);
	    hHRPPDAmplitudeVsBottomIndex2->Fill(hrppdBottomIndex2,hrppdAmplitude2);
	  }
      }

    // 4. Define Limits of Leading Edge and Fit
    int hrppdEdgeBeginIndex2 = -1;
    int hrppdEdgeEndIndex2 = -1;
    int hrppdBeginningIndex2 = -1;
    int hrppdTrailingIndex2 = -1;
    int pointsInHRPPDFit2 = 0;
    int hrppdPulseWidth2 = 0;
    double hrppdPulseCharge2 = 0.0;
    double hrppd10Percent2 = 0.0;
    double hrppd50Percent2 = 0.0;
    double hrppd90Percent2 = 0.0;
    //double aFPD = 0.;
    //double bFPD = 0.;

    if(hrppdBottomIndex2 > -1) // Only do if Pulse Position is Reasonable 
      {
	// Define leading edge as between 10% and 90% of amplitude
	double hrppdThresh012 = hrppdBaseline2 - 0.01*hrppdAmplitude2;
	double hrppdThresh102 = hrppdBaseline2 - 0.1*hrppdAmplitude2;
	double hrppdThresh902 = hrppdBaseline2 - 0.9*hrppdAmplitude2;

	hrppdEdgeEndIndex2 = hrppd2.getLeadingEdgeIndex(hrppdBottomIndex2,hrppdThresh902,_HRPPD_EDGE_SEARCH_LIMIT_);
	hrppdEdgeBeginIndex2 = hrppd2.getLeadingEdgeIndex(hrppdBottomIndex2,hrppdThresh102,_HRPPD_EDGE_SEARCH_LIMIT_);
	hrppdBeginningIndex2 = hrppd2.getLeadingEdgeIndex(hrppdBottomIndex2,hrppdThresh012,_HRPPD_EDGE_SEARCH_LIMIT_+100);
	hrppdTrailingIndex2 = hrppd2.getTrailingEdgeIndex(hrppdBottomIndex2,hrppdThresh012,_HRPPD_EDGE_SEARCH_LIMIT_+100); // Trailing edge is extended

	// Width of the Leading Edge
	pointsInHRPPDFit2 = hrppdEdgeEndIndex2 - hrppdEdgeBeginIndex2 + 1;

	// Width of Pulse
	hrppdPulseWidth2 = hrppdTrailingIndex2 - hrppdBeginningIndex2 + 1;

	// Calculate Integrated Charge
	double q2 = 0.0;
	if(hrppdTrailingIndex2 != -1)
	  {
	    for(unsigned i=hrppdBeginningIndex2; i<=hrppdTrailingIndex2; i++)
	      {
		q2 += (hrppdBaseline2 - hrppd2.getValue(i));//*20E-12;
	      }
	    q2 /= 50.0;
	  }
	hrppdPulseCharge2 = q2;

	// Reference Histos
	hHRPPDPointsInFit2->Fill(pointsInHRPPDFit2);
	hHRPPDEdgeEndVsBeginIndex2->Fill(hrppdEdgeBeginIndex2,hrppdEdgeEndIndex2);
	hHRPPDPulseWidth2->Fill(hrppdPulseWidth2);
	hHRPPDPulseCharge2->Fill(q2);

	// Do Linear Fit on Pulse Edge
	if(hrppdEdgeBeginIndex2 > -1 && hrppdEdgeEndIndex2 > -1) // Make sure ranges are defined
	  {
	    double workingpoint = 0.5; // Get time at this percentage of the amplitude
	    hrppd10Percent2 = hrppd2.fitLeadingEdge(hrppdEdgeBeginIndex2,hrppdEdgeEndIndex2,hrppdAmplitude2,hrppdBaseline2,0.10);
	    hrppd50Percent2 = hrppd2.fitLeadingEdge(hrppdEdgeBeginIndex2,hrppdEdgeEndIndex2,hrppdAmplitude2,hrppdBaseline2,workingpoint);
	    hrppd90Percent2 = hrppd2.fitLeadingEdge(hrppdEdgeBeginIndex2,hrppdEdgeEndIndex2,hrppdAmplitude2,hrppdBaseline2,0.90);
	  }	
      }

    // Set HRPPD Tree Variables
    if(hrppdBottomIndex2 > -1) hrppdOk2 = 1;
    hrppdPeakIndex2 = hrppdBottomIndex2;
    hrppdPoints2 = pointsInHRPPDFit2;
    hrppdBase2 = hrppdBaseline2;
    hrppdAmp2 = hrppdAmplitude2;
    hrppdWidth2 = hrppdPulseWidth2;
    hrppdCharge2 = hrppdPulseCharge2;
    hrppd10Time2 = hrppd10Percent2;
    hrppd50Time2 = hrppd50Percent2;
    hrppd90Time2 = hrppd90Percent2;
    */

    
    /*
    //==================================================
    //             Signal (HRPPD) Pulse 3
    //==================================================
    // 3. Search for Pulse and Find Baseline
    double hrppdBottom3 = 1000.;
    double hrppdBaseline3 = 0.;
    double hrppdAmplitude3 = 0.;
    int hrppdBottomIndex3 = -1;

    hrppdOk3 = 0;

    if(trgTriggerIndex > -1) // Only look for HRPPD pulse if there was a trigger
      {
	// Find Peak Position and Value
	hrppdBottomIndex3 = hrppd3.findMinimum(trgTriggerIndex + SIGNAL_OFFSET3 - _HRPPD_PULSE_WINDOW_,trgTriggerIndex + SIGNAL_OFFSET3 + _HRPPD_PULSE_WINDOW_);
	hrppdBottom3 = hrppd3.getValue(hrppdBottomIndex3);

	if(hrppdBottomIndex3 > -1) // Proceed only if pulse position is reasonable
	  {
	    // Find Baseline
	    unsigned baselineRangeLo3 = (hrppdBottomIndex3 - _HRPPD_BASELINE_WINDOW_OFFSET_ > 1) ? hrppdBottomIndex3 - _HRPPD_BASELINE_WINDOW_OFFSET_ : 1;
	    unsigned baselineRangeHi3 = baselineRangeLo3 + _HRPPD_BASELINE_WINDOW_WIDTH_;
	    hrppdBaseline3 = hrppd3.getBaseline(baselineRangeLo3,baselineRangeHi3);

	    //cout << fpdTriggerIndex << " " << baselineRangeLo << " " << baselineRangeHi << endl;

	    // Amplitude = Baseline - Bottom
	    hrppdAmplitude3 = hrppdBaseline3 - hrppdBottom3;

	    // Reference Histos
	    hHRPPDBottom3->Fill(hrppdBottom3);
	    hHRPPDBottomIndex3->Fill(hrppdBottomIndex3);
	    hHRPPDBaseline3->Fill(hrppdBaseline3);
	    hHRPPDAmplitude3->Fill(hrppdAmplitude3);
	    hHRPPDAmplitudeVsBottomIndex3->Fill(hrppdBottomIndex3,hrppdAmplitude3);
	  }
      }

    // 4. Define Limits of Leading Edge and Fit
    int hrppdEdgeBeginIndex3 = -1;
    int hrppdEdgeEndIndex3 = -1;
    int hrppdBeginningIndex3 = -1;
    int hrppdTrailingIndex3 = -1;
    int pointsInHRPPDFit3 = 0;
    int hrppdPulseWidth3 = 0;
    double hrppdPulseCharge3 = 0.0;
    double hrppd10Percent3 = 0.0;
    double hrppd50Percent3 = 0.0;
    double hrppd90Percent3 = 0.0;
    //double aFPD = 0.;
    //double bFPD = 0.;

    if(hrppdBottomIndex3 > -1) // Only do if Pulse Position is Reasonable 
      {
	// Define leading edge as between 10% and 90% of amplitude
	double hrppdThresh013 = hrppdBaseline3 - 0.01*hrppdAmplitude3;
	double hrppdThresh103 = hrppdBaseline3 - 0.1*hrppdAmplitude3;
	double hrppdThresh903 = hrppdBaseline3 - 0.9*hrppdAmplitude3;

	hrppdEdgeEndIndex3 = hrppd3.getLeadingEdgeIndex(hrppdBottomIndex3,hrppdThresh903,_HRPPD_EDGE_SEARCH_LIMIT_);
	hrppdEdgeBeginIndex3 = hrppd3.getLeadingEdgeIndex(hrppdBottomIndex3,hrppdThresh103,_HRPPD_EDGE_SEARCH_LIMIT_);
	hrppdBeginningIndex3 = hrppd3.getLeadingEdgeIndex(hrppdBottomIndex3,hrppdThresh013,_HRPPD_EDGE_SEARCH_LIMIT_+100);
	hrppdTrailingIndex3 = hrppd3.getTrailingEdgeIndex(hrppdBottomIndex3,hrppdThresh013,_HRPPD_EDGE_SEARCH_LIMIT_+100); // Trailing edge is extended

	// Width of the Leading Edge
	pointsInHRPPDFit3 = hrppdEdgeEndIndex3 - hrppdEdgeBeginIndex3 + 1;

	// Width of Pulse
	hrppdPulseWidth3 = hrppdTrailingIndex3 - hrppdBeginningIndex3 + 1;

	// Calculate Integrated Charge
	double q3 = 0.0;
	if(hrppdTrailingIndex3 != -1)
	  {
	    for(unsigned i=hrppdBeginningIndex3; i<=hrppdTrailingIndex3; i++)
	      {
		q3 += (hrppdBaseline3 - hrppd3.getValue(i));//*20E-12;
	      }
	    q3 /= 50.0;
	  }
	hrppdPulseCharge3 = q3;

	// Reference Histos
	hHRPPDPointsInFit3->Fill(pointsInHRPPDFit3);
	hHRPPDEdgeEndVsBeginIndex3->Fill(hrppdEdgeBeginIndex3,hrppdEdgeEndIndex3);
	hHRPPDPulseWidth3->Fill(hrppdPulseWidth3);
	hHRPPDPulseCharge3->Fill(q3);

	// Do Linear Fit on Pulse Edge
	if(hrppdEdgeBeginIndex3 > -1 && hrppdEdgeEndIndex3 > -1) // Make sure ranges are defined
	  {
	    double workingpoint = 0.5; // Get time at this percentage of the amplitude
	    hrppd10Percent3 = hrppd3.fitLeadingEdge(hrppdEdgeBeginIndex3,hrppdEdgeEndIndex3,hrppdAmplitude3,hrppdBaseline3,0.10);
	    hrppd50Percent3 = hrppd3.fitLeadingEdge(hrppdEdgeBeginIndex3,hrppdEdgeEndIndex3,hrppdAmplitude3,hrppdBaseline3,workingpoint);
	    hrppd90Percent3 = hrppd3.fitLeadingEdge(hrppdEdgeBeginIndex3,hrppdEdgeEndIndex3,hrppdAmplitude3,hrppdBaseline3,0.90);
	  }	
      }

    // Set HRPPD Tree Variables
    if(hrppdBottomIndex3 > -1) hrppdOk3 = 1;
    hrppdPeakIndex3 = hrppdBottomIndex3;
    hrppdPoints3 = pointsInHRPPDFit3;
    hrppdBase3 = hrppdBaseline3;
    hrppdAmp3 = hrppdAmplitude3;
    hrppdWidth3 = hrppdPulseWidth3;
    hrppdCharge3 = hrppdPulseCharge3;
    hrppd10Time3 = hrppd10Percent3;
    hrppd50Time3 = hrppd50Percent3;
    hrppd90Time3 = hrppd90Percent3;
    */

    /*
    //==================================================
    //             Signal (HRPPD) Pulse 4
    //==================================================
    // 3. Search for Pulse and Find Baseline
    double hrppdBottom4 = 1000.;
    double hrppdBaseline4 = 0.;
    double hrppdAmplitude4 = 0.;
    int hrppdBottomIndex4 = -1;

    hrppdOk4 = 0;

    if(trgTriggerIndex > -1) // Only look for HRPPD pulse if there was a trigger
      {
	// Find Peak Position and Value
	hrppdBottomIndex4 = hrppd4.findMinimum(trgTriggerIndex + SIGNAL_OFFSET4 - _HRPPD_PULSE_WINDOW_,trgTriggerIndex + SIGNAL_OFFSET4 + _HRPPD_PULSE_WINDOW_);
	hrppdBottom4 = hrppd4.getValue(hrppdBottomIndex4);

	if(hrppdBottomIndex4 > -1) // Proceed only if pulse position is reasonable
	  {
	    // Find Baseline
	    unsigned baselineRangeLo4 = (hrppdBottomIndex4 - _HRPPD_BASELINE_WINDOW_OFFSET_ > 1) ? hrppdBottomIndex4 - _HRPPD_BASELINE_WINDOW_OFFSET_ : 1;
	    unsigned baselineRangeHi4 = baselineRangeLo4 + _HRPPD_BASELINE_WINDOW_WIDTH_;
	    hrppdBaseline4 = hrppd4.getBaseline(baselineRangeLo4,baselineRangeHi4);

	    //cout << fpdTriggerIndex << " " << baselineRangeLo << " " << baselineRangeHi << endl;

	    // Amplitude = Baseline - Bottom
	    hrppdAmplitude4 = hrppdBaseline4 - hrppdBottom4;

	    // Reference Histos
	    hHRPPDBottom4->Fill(hrppdBottom4);
	    hHRPPDBottomIndex4->Fill(hrppdBottomIndex4);
	    hHRPPDBaseline4->Fill(hrppdBaseline4);
	    hHRPPDAmplitude4->Fill(hrppdAmplitude4);
	    hHRPPDAmplitudeVsBottomIndex4->Fill(hrppdBottomIndex4,hrppdAmplitude4);
	  }
      }

    // 4. Define Limits of Leading Edge and Fit
    int hrppdEdgeBeginIndex4 = -1;
    int hrppdEdgeEndIndex4 = -1;
    int hrppdBeginningIndex4 = -1;
    int hrppdTrailingIndex4 = -1;
    int pointsInHRPPDFit4 = 0;
    int hrppdPulseWidth4 = 0;
    double hrppdPulseCharge4 = 0.0;
    double hrppd10Percent4 = 0.0;
    double hrppd50Percent4 = 0.0;
    double hrppd90Percent4 = 0.0;
    //double aFPD = 0.;
    //double bFPD = 0.;

    if(hrppdBottomIndex4 > -1) // Only do if Pulse Position is Reasonable 
      {
	// Define leading edge as between 10% and 90% of amplitude
	double hrppdThresh014 = hrppdBaseline4 - 0.01*hrppdAmplitude4;
	double hrppdThresh104 = hrppdBaseline4 - 0.1*hrppdAmplitude4;
	double hrppdThresh904 = hrppdBaseline4 - 0.9*hrppdAmplitude4;

	hrppdEdgeEndIndex4 = hrppd4.getLeadingEdgeIndex(hrppdBottomIndex4,hrppdThresh904,_HRPPD_EDGE_SEARCH_LIMIT_);
	hrppdEdgeBeginIndex4 = hrppd4.getLeadingEdgeIndex(hrppdBottomIndex4,hrppdThresh104,_HRPPD_EDGE_SEARCH_LIMIT_);
	hrppdBeginningIndex4 = hrppd4.getLeadingEdgeIndex(hrppdBottomIndex4,hrppdThresh014,_HRPPD_EDGE_SEARCH_LIMIT_+100);
	hrppdTrailingIndex4 = hrppd4.getTrailingEdgeIndex(hrppdBottomIndex4,hrppdThresh014,_HRPPD_EDGE_SEARCH_LIMIT_+100); // Trailing edge is extended

	// Width of the Leading Edge
	pointsInHRPPDFit4 = hrppdEdgeEndIndex4 - hrppdEdgeBeginIndex4 + 1;

	// Width of Pulse
	hrppdPulseWidth4 = hrppdTrailingIndex4 - hrppdBeginningIndex4 + 1;

	// Calculate Integrated Charge
	double q4 = 0.0;
	if(hrppdTrailingIndex4 != -1)
	  {
	    for(unsigned i=hrppdBeginningIndex4; i<=hrppdTrailingIndex4; i++)
	      {
		q4 += (hrppdBaseline4 - hrppd4.getValue(i));//*20E-12;
	      }
	    q4 /= 50.0;
	  }
	hrppdPulseCharge4 = q4;

	// Reference Histos
	hHRPPDPointsInFit4->Fill(pointsInHRPPDFit4);
	hHRPPDEdgeEndVsBeginIndex4->Fill(hrppdEdgeBeginIndex4,hrppdEdgeEndIndex4);
	hHRPPDPulseWidth4->Fill(hrppdPulseWidth4);
	hHRPPDPulseCharge4->Fill(q4);

	// Do Linear Fit on Pulse Edge
	if(hrppdEdgeBeginIndex4 > -1 && hrppdEdgeEndIndex4 > -1) // Make sure ranges are defined
	  {
	    double workingpoint = 0.5; // Get time at this percentage of the amplitude
	    hrppd10Percent4 = hrppd4.fitLeadingEdge(hrppdEdgeBeginIndex4,hrppdEdgeEndIndex4,hrppdAmplitude4,hrppdBaseline4,0.10);
	    hrppd50Percent4 = hrppd4.fitLeadingEdge(hrppdEdgeBeginIndex4,hrppdEdgeEndIndex4,hrppdAmplitude4,hrppdBaseline4,workingpoint);
	    hrppd90Percent4 = hrppd4.fitLeadingEdge(hrppdEdgeBeginIndex4,hrppdEdgeEndIndex4,hrppdAmplitude4,hrppdBaseline4,0.90);
	  }	
      }

    // Set HRPPD Tree Variables
    if(hrppdBottomIndex4 > -1) hrppdOk4 = 1;
    hrppdPeakIndex4 = hrppdBottomIndex4;
    hrppdPoints4 = pointsInHRPPDFit4;
    hrppdBase4 = hrppdBaseline4;
    hrppdAmp4 = hrppdAmplitude4;
    hrppdWidth4 = hrppdPulseWidth4;
    hrppdCharge4 = hrppdPulseCharge4;
    hrppd10Time4 = hrppd10Percent4;
    hrppd50Time4 = hrppd50Percent4;
    hrppd90Time4 = hrppd90Percent4;
    */

    /*
    //==================================================
    //             Signal (HRPPD) Pulse 5
    //==================================================
    // 3. Search for Pulse and Find Baseline
    double hrppdBottom5 = 1000.;
    double hrppdBaseline5 = 0.;
    double hrppdAmplitude5 = 0.;
    int hrppdBottomIndex5 = -1;

    hrppdOk5 = 0;

    if(trgTriggerIndex > -1) // Only look for HRPPD pulse if there was a trigger
      {
	// Find Peak Position and Value
	hrppdBottomIndex5 = hrppd5.findMinimum(trgTriggerIndex + SIGNAL_OFFSET5 - _HRPPD_PULSE_WINDOW_,trgTriggerIndex + SIGNAL_OFFSET5 + _HRPPD_PULSE_WINDOW_);
	hrppdBottom5 = hrppd5.getValue(hrppdBottomIndex5);

	if(hrppdBottomIndex5 > -1) // Proceed only if pulse position is reasonable
	  {
	    // Find Baseline
	    unsigned baselineRangeLo5 = (hrppdBottomIndex5 - _HRPPD_BASELINE_WINDOW_OFFSET_ > 1) ? hrppdBottomIndex5 - _HRPPD_BASELINE_WINDOW_OFFSET_ : 1;
	    unsigned baselineRangeHi5 = baselineRangeLo5 + _HRPPD_BASELINE_WINDOW_WIDTH_;
	    hrppdBaseline5 = hrppd5.getBaseline(baselineRangeLo5,baselineRangeHi5);

	    //cout << fpdTriggerIndex << " " << baselineRangeLo << " " << baselineRangeHi << endl;

	    // Amplitude = Baseline - Bottom
	    hrppdAmplitude5 = hrppdBaseline5 - hrppdBottom5;

	    // Reference Histos
	    hHRPPDBottom5->Fill(hrppdBottom5);
	    hHRPPDBottomIndex5->Fill(hrppdBottomIndex5);
	    hHRPPDBaseline5->Fill(hrppdBaseline5);
	    hHRPPDAmplitude5->Fill(hrppdAmplitude5);
	    hHRPPDAmplitudeVsBottomIndex5->Fill(hrppdBottomIndex5,hrppdAmplitude5);
	  }
      }

    // 4. Define Limits of Leading Edge and Fit
    int hrppdEdgeBeginIndex5 = -1;
    int hrppdEdgeEndIndex5 = -1;
    int hrppdBeginningIndex5 = -1;
    int hrppdTrailingIndex5 = -1;
    int pointsInHRPPDFit5 = 0;
    int hrppdPulseWidth5 = 0;
    double hrppdPulseCharge5 = 0.0;
    double hrppd10Percent5 = 0.0;
    double hrppd50Percent5 = 0.0;
    double hrppd90Percent5 = 0.0;
    //double aFPD = 0.;
    //double bFPD = 0.;

    if(hrppdBottomIndex5 > -1) // Only do if Pulse Position is Reasonable 
      {
	// Define leading edge as between 10% and 90% of amplitude
	double hrppdThresh015 = hrppdBaseline5 - 0.01*hrppdAmplitude5;
	double hrppdThresh105 = hrppdBaseline5 - 0.1*hrppdAmplitude5;
	double hrppdThresh905 = hrppdBaseline5 - 0.9*hrppdAmplitude5;

	hrppdEdgeEndIndex5 = hrppd5.getLeadingEdgeIndex(hrppdBottomIndex5,hrppdThresh905,_HRPPD_EDGE_SEARCH_LIMIT_);
	hrppdEdgeBeginIndex5 = hrppd5.getLeadingEdgeIndex(hrppdBottomIndex5,hrppdThresh105,_HRPPD_EDGE_SEARCH_LIMIT_);
	hrppdBeginningIndex5 = hrppd5.getLeadingEdgeIndex(hrppdBottomIndex5,hrppdThresh015,_HRPPD_EDGE_SEARCH_LIMIT_+100);
	hrppdTrailingIndex5 = hrppd5.getTrailingEdgeIndex(hrppdBottomIndex5,hrppdThresh015,_HRPPD_EDGE_SEARCH_LIMIT_+100); // Trailing edge is extended

	// Width of the Leading Edge
	pointsInHRPPDFit5 = hrppdEdgeEndIndex5 - hrppdEdgeBeginIndex5 + 1;

	// Width of Pulse
	hrppdPulseWidth5 = hrppdTrailingIndex5 - hrppdBeginningIndex5 + 1;

	// Calculate Integrated Charge
	double q5 = 0.0;
	if(hrppdTrailingIndex5 != -1)
	  {
	    for(unsigned i=hrppdBeginningIndex5; i<=hrppdTrailingIndex5; i++)
	      {
		q5 += (hrppdBaseline5 - hrppd5.getValue(i));//*20E-12;
	      }
	    q5 /= 50.0;
	  }
	hrppdPulseCharge5 = q5;

	// Reference Histos
	hHRPPDPointsInFit5->Fill(pointsInHRPPDFit5);
	hHRPPDEdgeEndVsBeginIndex5->Fill(hrppdEdgeBeginIndex5,hrppdEdgeEndIndex5);
	hHRPPDPulseWidth5->Fill(hrppdPulseWidth5);
	hHRPPDPulseCharge5->Fill(q5);

	// Do Linear Fit on Pulse Edge
	if(hrppdEdgeBeginIndex5 > -1 && hrppdEdgeEndIndex5 > -1) // Make sure ranges are defined
	  {
	    double workingpoint = 0.5; // Get time at this percentage of the amplitude
	    hrppd10Percent5 = hrppd5.fitLeadingEdge(hrppdEdgeBeginIndex5,hrppdEdgeEndIndex5,hrppdAmplitude5,hrppdBaseline5,0.10);
	    hrppd50Percent5 = hrppd5.fitLeadingEdge(hrppdEdgeBeginIndex5,hrppdEdgeEndIndex5,hrppdAmplitude5,hrppdBaseline5,workingpoint);
	    hrppd90Percent5 = hrppd5.fitLeadingEdge(hrppdEdgeBeginIndex5,hrppdEdgeEndIndex5,hrppdAmplitude5,hrppdBaseline5,0.90);
	  }	
      }

    // Set HRPPD Tree Variables
    if(hrppdBottomIndex5 > -1) hrppdOk5 = 1;
    hrppdPeakIndex5 = hrppdBottomIndex5;
    hrppdPoints5 = pointsInHRPPDFit5;
    hrppdBase5 = hrppdBaseline5;
    hrppdAmp5 = hrppdAmplitude5;
    hrppdWidth5 = hrppdPulseWidth5;
    hrppdCharge5 = hrppdPulseCharge5;
    hrppd10Time5 = hrppd10Percent5;
    hrppd50Time5 = hrppd50Percent5;
    hrppd90Time5 = hrppd90Percent5;
    */

    //==================================================
    //                HRPPD - FPD Timing
    //==================================================

    if(trgTriggerIndex > -1 && hrppdBottomIndex1 > -1 && pointsInHRPPDFit1 > 2)
      {
	double hrppdTRGTimeDiff1 = hrppd50Percent1 - trg50Percent;
	hHRPPDFPDTimeDiffVsAmp1->Fill(hrppdAmplitude1,hrppdTRGTimeDiff1);
      }

    /*
    if(trgTriggerIndex > -1 && hrppdBottomIndex2 > -1 && pointsInHRPPDFit2 > 2)
      {
	double hrppdTRGTimeDiff2 = hrppd50Percent2 - trg50Percent;
	hHRPPDFPDTimeDiffVsAmp2->Fill(hrppdAmplitude2,hrppdTRGTimeDiff2);
      }

    if(trgTriggerIndex > -1 && hrppdBottomIndex3 > -1 && pointsInHRPPDFit3 > 2)
      {
	double hrppdTRGTimeDiff3 = hrppd50Percent3 - trg50Percent;
	hHRPPDFPDTimeDiffVsAmp3->Fill(hrppdAmplitude3,hrppdTRGTimeDiff3);
      }

    if(trgTriggerIndex > -1 && hrppdBottomIndex4 > -1 && pointsInHRPPDFit4 > 2)
      {
	double hrppdTRGTimeDiff4 = hrppd50Percent4 - trg50Percent;
	hHRPPDFPDTimeDiffVsAmp4->Fill(hrppdAmplitude4,hrppdTRGTimeDiff4);
      }

    if(trgTriggerIndex > -1 && hrppdBottomIndex5 > -1 && pointsInHRPPDFit5 > 2)
      {
	double hrppdTRGTimeDiff5 = hrppd50Percent5 - trg50Percent;
	hHRPPDFPDTimeDiffVsAmp5->Fill(hrppdAmplitude5,hrppdTRGTimeDiff5);
      }
    */

    //tout->Fill();
    NEVENTS++;
  }

  //tout->Write();
  ofile->Write();
  ofile->Close();

  cout << "Number of Events = " << NEVENTS << endl;

}
