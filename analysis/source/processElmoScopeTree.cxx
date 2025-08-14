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

  // Noise Characterization
  TH1D *hNoiseTotal = new TH1D("hNoiseTotal","",2000,-0.1,0.1);
  TH1D *hNoise100_1 = new TH1D("hNoise100_1","",2000,-0.1,0.1);
  TH1D *hNoise100_2 = new TH1D("hNoise100_2","",2000,-0.1,0.1);
  TH1D *hNoise100_3 = new TH1D("hNoise100_3","",2000,-0.1,0.1);
  TH1D *hNoise100_4 = new TH1D("hNoise100_4","",2000,-0.1,0.1);
  TH1D *hNoise100_5 = new TH1D("hNoise100_5","",2000,-0.1,0.1);
  TH1D *hNoise50_1 = new TH1D("hNoise50_1","",2000,-0.1,0.1);
  TH1D *hNoise50_2 = new TH1D("hNoise50_2","",2000,-0.1,0.1);
  TH1D *hNoise50_3 = new TH1D("hNoise50_3","",2000,-0.1,0.1);
  TH1D *hNoise50_4 = new TH1D("hNoise50_4","",2000,-0.1,0.1);
  TH1D *hNoise50_5 = new TH1D("hNoise50_5","",2000,-0.1,0.1);
  TH1D *hNoiseStdDev = new TH1D("hNoiseStdDev","",2000,0.,0.02);

  // FPD Signal
  TH1D *hFPDBottom = new TH1D("hFPDBottom","",200,-1.,1.);
  TH1D *hFPDBottomIndex = new TH1D("hFPDBottomIndex","",5000,0.,5000.);
  TH1D *hFPDBaseline = new TH1D("hFPDBaseline","",2000,-0.1,0.1);
  TH1D *hFPDAmplitude = new TH1D("hFPDAmplitude","",200,0.,1.);
  TH2D *hFPDTrgPointVsBottomPoint = new TH2D("hFPDTrgPointVsBottomPoint","",2000,0.,2000,2000,0.,2000);

  TH1D *hFPDPointsInFit = new TH1D("hFPDPointsInFit","",20,0.,20.);
  TH2D *hFPDEdgeEndVsBeginIndex = new TH2D("hFPDEdgeEndVsBeginIndex","",2000,0.,2000.,2000,0.,2000.);

  TH1D *hFPDa = new TH1D("hFPDa","",50000,0.,50000.);
  TH1D *hFPDb = new TH1D("hFPDb","",5000,-0.5,0.0);

  TH1D *hFPD50PercentTime = new TH1D("hFPD50PercentTime","",20000,-100.,100.);
  //TH2D *hFPD50PercentTimeVsBottom = new TH2D("hFPD50PercentTimeVsBottom","",200,-1.,1.,20000,-100.,100.);

  // HRPPD Signal
  TH1D *hHRPPDTestBottom = new TH1D("hHRPPDTestBottom","",200,-0.1,0.1);
  TH1D *hHRPPDTestBottomIndex = new TH1D("hHRPPDTestBottomIndex","",5000,0.,5000.);

  TH1D *hHRPPDBottom = new TH1D("hHRPPDBottom","",200,-0.1,0.1);
  TH1D *hHRPPDBaseline = new TH1D("hHRPPDBaseline","",2000,-0.1,0.1);
  TH1D *hHRPPDAmplitude = new TH1D("hHRPPDAmplitude","",1000,0.,0.5);

  TH2D *hHRPPDAmplitudeVsBottomIndex = new TH2D("hHRPPDAmplitudeVsBottomIndex","",5000,0.,5000.,200,-1.,1.);

  TH1D *hHRPPDPointsInFit = new TH1D("hHRPPDPointsInFit","",100,0.,100.);
  TH2D *hHRPPDPointsInFitVsAmplitude = new TH2D("hHRPPDPointsInFitVsAmplitude","",1000,0.,0.5,100,0.,100.);
  TH2D *hHRPPDEdgeEndVsBeginIndex = new TH2D("hHRPPDEdgeEndVsBeginIndex","",2000,0.,2000.,2000,0.,2000.);
  //TH1D *hHRPPDEdgeEndBeginTimeDiff = new TH1D("hHRPPDEdgeEndBeginTimeDiff","",1000,0.,1000.);
  //TH2D *hHRPPDEdgeEndBeginTimeDiffVsAmplitude = new TH2D("hHRPPDEdgeEndBeginTimeDiffVsAmplitude","",1000,0.,0.5,1000,0.,1000.);

  TH1D *hHRPPDa = new TH1D("hHRPPDa","",50000,0.,50000.);
  TH1D *hHRPPDb = new TH1D("hHRPPDb","",5000,-0.5,0.0);

  TH1D *hHRPPD50PercentTime = new TH1D("hHRPPD50PercentTime","",20000,-100.,100.);
  //TH2D *hHRPPD50PercentTimeVsBottom = new TH2D("hHRPPD50PercentTimeVsBottom","",200,-1.,1.,20000,-100.,100.);

  // FPD - HRPPD Timing
  TH1D *hHRPPDFPDTimeDiff = new TH1D("hHRPPDFPDTimeDiff","",30000,15000.,45000.);
  TH1D *hHRPPDFPDTimeDiff15 = new TH1D("hHRPPDFPDTimeDiff15","",10000,15000.,25000.);
  TH1D *hHRPPDFPDTimeDiff20 = new TH1D("hHRPPDFPDTimeDiff20","",10000,15000.,25000.);
  TH2D *hHRPPDFPDTimeDiffVsAmp = new TH2D("hHRPPDFPDTimeDiffVsAmp","",1000,0.,0.5,30000,15000.,45000.);
  TH2D *hHRPPDVsFPDTime = new TH2D("hHRPPDVsFPDTime","",2000,0.,20000.,2000,0.,20000.);

  //TH2D *sigVsTime4708 = new TH2D("sigVsTime4708","",2000,50.,150.,100,-0.5,0.5);

  //TH1D *numSignal = new TH1D("numSignal","",20,0.,20.);
  //TH2D *numSignalVsTime = new TH2D("numSignalVsTime","",4000,-100.,300.,5,0.,5.);

  //TH2D *sigVsTrigTime = new TH2D("sigVsTrigTime","",8000,-100.,300.,8000,-100.,300.);

  // Constants (hardwire for now)
  //const double TRIGGERVAL = -0.005;//-0.004;
  //const double LASERTRIGGERVAL = -0.2;
  //const int LOWWINDOWWIDTH = 90;
  //const int WINDOWOFFSET = 350;
  //const int WINDOWWIDTH = 250;
  const double SIGNALTHRESH = -0.06;//-0.065; // -0.038
  const int SIGNALOFFSET = 200;
  const int SIGNALWIDTH = 100;
  const double TRIGGERTHRESH = -0.1; //-0.158; // Set Trigger Thresh on Scope
  const int TRIGGEROFFSET = 100;
  const int TRIGGERWIDTH = 50;

  cout << "Define Everything" << endl;
  cout << setprecision(10);

  // Loop Over Events
  int NEVENTS = 0;
  int NUMTRIG = 0;
  int NUMSIG = 0;
  while(tree_reader.Next()) {
    //NEVENTS++;

    if(NEVENTS%1000 == 0)
      cout << "Processed " << NEVENTS << " Events" << endl;

    bool kill = false;

    /*
    if(NEVENTS == 10)
      {
	for(unsigned int i=0; i<signalTime.GetSize(); i++)
	  {
	    cout << i << " " << signalTime[i] << endl;
	  }
      }
    */

    //cout << NEVENTS << endl; //" / " << tree_reader.GetSize() << endl;
    //cout << eventTime.GetSize() << " " << signalTime.GetSize() << " " << trigger.GetSize() << " " << signal.GetSize() << endl;

    // Look at Noise Spectrum - useful only for runs taken with no signal
    int numNoise = 0;
    double totalNoise = 0.;
    double totalNoise2 = 0.;
    double noise100_1 = 0.;
    double noise100_2 = 0.;
    double noise100_3 = 0.;
    double noise100_4 = 0.;
    double noise100_5 = 0.;
    double noise50_1 = 0.;
    double noise50_2 = 0.;
    double noise50_3 = 0.;
    double noise50_4 = 0.;
    double noise50_5 = 0.;
    for(unsigned int i=0; i<signal.GetSize(); i++)
      {
	totalNoise += signal[i];
	totalNoise2 += signal[i]*signal[i];
	numNoise++;

	if(i>99 && i<200)
	  {
	    noise100_1 += signal[i];
	    if(i>124 && i<175)
	      noise50_1 += signal[i];
	  }
	if(i>599 && i<700)
	  {
	    noise100_2 += signal[i];
	    if(i>624 && i<675)
	      noise50_2 += signal[i];
	  }
	if(i>1099 && i<1200)
	  {
	    noise100_3 += signal[i];
	    if(i>1124 && i<1175)
	      noise50_3 += signal[i];
	  }
	if(i>1499 && i<1600)
	  {
	    noise100_4 += signal[i];
	    if(i>1524 && i<1575)
	      noise50_4 += signal[i];
	  }
	if(i>1799 && i<1900)
	  {
	    noise100_5 += signal[i];
	    if(i>1824 && i<1875)
	      noise50_5 += signal[i];
	  }
      }
    double EX2 = totalNoise2/(1.0*numNoise);
    double mean = totalNoise/(1.0*numNoise);
    double var = EX2 - mean*mean;
    
    hNoiseTotal->Fill(totalNoise/(1.0*numNoise));
    hNoise100_1->Fill(noise100_1/100.0);
    hNoise100_2->Fill(noise100_2/100.0);
    hNoise100_3->Fill(noise100_3/100.0);
    hNoise100_4->Fill(noise100_4/100.0);
    hNoise100_5->Fill(noise100_5/100.0);
    hNoise50_1->Fill(noise50_1/50.0);
    hNoise50_2->Fill(noise50_2/50.0);
    hNoise50_3->Fill(noise50_3/50.0);
    hNoise50_4->Fill(noise50_4/50.0);
    hNoise50_5->Fill(noise50_5/50.0);

    hNoiseStdDev->Fill(TMath::Sqrt(var));

    // Trigger (FPD) Pulse
    // 1. Search for Pulse and Find Baseline
    double fpdBottom = 1000.;
    double fpdBaseline = 0.;
    double fpdAmplitude = 0.;
    int fpdBottomIndex = -1;
    int fpdTriggerIndex = -1;
    bool fpdTriggerFlag = true;
    for(unsigned int i=0; i<trigger.GetSize(); i++)
      {
	if(trigger[i] < TRIGGERTHRESH && fpdTriggerFlag)
	  {
	    fpdTriggerIndex = i;
	    fpdTriggerFlag = false;
	  }
      }
    if(fpdTriggerIndex > -1)
      {
	for(int i=fpdTriggerIndex; i<fpdTriggerIndex+TRIGGEROFFSET; i++)
	  {
	    if(trigger[i] < fpdBottom)
	      {
		fpdBottom = trigger[i];
		fpdBottomIndex = i;
	      }
	  }

	int numFPDBaselinePoints = 0;
	double fpdBaselineTotal = 0.;
	int limit = fpdTriggerIndex-TRIGGEROFFSET-TRIGGERWIDTH;
	if(limit < 1) limit = 1; 
	for(int i=fpdTriggerIndex-TRIGGEROFFSET; i>=limit; i--)
	  {
	    //cout << NEVENTS << " " << i << endl;
	    fpdBaselineTotal += trigger[i];
	    numFPDBaselinePoints++;
	  }
	fpdBaseline = fpdBaselineTotal/(1.0*numFPDBaselinePoints);
	fpdAmplitude = fpdBaseline - fpdBottom;

	hFPDBottom->Fill(fpdBottom);
	hFPDBottomIndex->Fill(fpdBottomIndex);
	hFPDBaseline->Fill(fpdBaseline);
	hFPDAmplitude->Fill(fpdAmplitude);
	hFPDTrgPointVsBottomPoint->Fill(fpdBottomIndex,fpdTriggerIndex);

	NUMTRIG++;
      }

    //cout << "Finish 1" << endl;

    // 2. Define Limits of Leading Edge and Fit
    int fpdEdgeBeginIndex = -1;
    int fpdMidIndex = -1;
    int fpdEdgeEndIndex = -1;
    int pointsInFPDFit = 0;
    double fpd50Percent = 0.0; 
    double aFPD = 0.;
    double bFPD = 0.;

    if(fpdTriggerIndex > -1)
      {
	double fpdThresh10 = fpdBaseline - 0.1*fpdAmplitude;
	double fpdThresh50 = fpdBaseline - 0.5*fpdAmplitude;
	double fpdThresh90 = fpdBaseline - 0.9*fpdAmplitude;
	for(int i=fpdBottomIndex; i>=fpdBottomIndex-TRIGGEROFFSET; i--)
	  {
	    if(trigger[i] > fpdThresh90)
	      {
		fpdEdgeEndIndex = i;// - 1;
		break;
	      }

	    //cout << NEVENTS << " " << i << endl;
	  }
	for(int i=fpdBottomIndex; i>=fpdBottomIndex-TRIGGEROFFSET; i--)
	  {
	    if(trigger[i] > fpdThresh10)
	      {
		fpdEdgeBeginIndex = i;// - 1;
		break;
	      }
	  }
	for(int i=fpdBottomIndex; i>=fpdBottomIndex-TRIGGEROFFSET; i--)
	  {
	    if(trigger[i] > fpdThresh50)
	      {
		fpdMidIndex = i;// - 1;
		break;
	      }
	  }
	
	pointsInFPDFit = fpdEdgeEndIndex - fpdEdgeBeginIndex + 1;
	
	hFPDPointsInFit->Fill(pointsInFPDFit);
	hFPDEdgeEndVsBeginIndex->Fill(fpdEdgeBeginIndex,fpdEdgeEndIndex);
	
	double sumXFPD = 0.;
	double sumX2FPD = 0.;
	double sumFPDVal = 0.;
	double sumXFPDVal = 0.;
	int NFPD = 0;
	if(fpdEdgeBeginIndex > -1 && fpdEdgeEndIndex > -1)
	  {
	    for(int i=fpdEdgeBeginIndex; i<fpdEdgeEndIndex+1; i++)
	      {
		double time = signalTime[i]*1000000000000.0;
		
		sumXFPD += time;
		sumX2FPD += time*time;
		sumFPDVal += trigger[i];
		sumXFPDVal += time*trigger[i];
		NFPD++;
	      }
	  }

	if(fpdEdgeBeginIndex == -1 || fpdEdgeEndIndex == -1)
	  kill = true;
	
	double deltaFPD = NFPD*sumX2FPD - sumXFPD*sumXFPD;
	aFPD = (sumX2FPD*sumFPDVal - sumXFPD*sumXFPDVal)/deltaFPD;
	bFPD = (NFPD*sumXFPDVal - sumXFPD*sumFPDVal)/deltaFPD;

	hFPDa->Fill(aFPD);
	hFPDb->Fill(bFPD);

	fpd50Percent = ((fpdBaseline - 0.5*fpdAmplitude) - aFPD)/bFPD;

	hFPD50PercentTime->Fill(fpd50Percent);
	//hFPD50PercentTimeVsBottom->Fill(signalTime[fpdBottomIndex],fpd50Percent);
      }

    //cout << "Finish 2" << endl;

    double hrppdTestBottom = 1000.;
    int hrppdTestBottomIndex = -1;
    for(int i=0; i<signal.GetSize(); i++)
      {
	if(signal[i] < hrppdTestBottom)
	  {
	    hrppdTestBottom = signal[i];
	    hrppdTestBottomIndex = i;
	  }
      }
    hHRPPDTestBottom->Fill(hrppdTestBottom);
    hHRPPDTestBottomIndex->Fill(hrppdTestBottomIndex);

    // HRPPD Pulse
    // 3. Search for Lowest Point in Pulse and Find Baseline
    double hrppdBottom = 1000.;
    double hrppdBaseline = 0.;
    double hrppdAmplitude = 0.;
    int hrppdBottomIndex = -1;
    //if(NEVENTS > 20000)
    //cout << NEVENTS << " " << signal.GetSize() << endl;
    //for(int i=0; i<signal.GetSize(); i++) // HRPPD Signals Are Small - Do Global Search: Restrict range to avoid "double-signals" in elmo 300 450
    // Offsets Between FPD and HRPPD Pulse for Each Run
    // Python Test = 1381
    // BP Run07 = 1390
    // BP Run12 = 1390
    // BP Run13 = 1385
    // BP Run15 = 1375
    // BP Run16 = 1378
    // BP Run17 = 1381
    // BP Run18 = 1380
    // BP Run19 = 1374
    // BP Run20 = 690 (2500 RL)
    // BP Run21 = 690 (2500 RL)
    // BP Run22 = 687 (2500 RL)
    // BP Run23 = 345 (1250 RL)
    // BP Run24 = 345 (1250 RL)
    // BP Run25 = 344 (1250 RL)
    // BP Run26 = 172 (1000 RL)
    // BP Run27 = 173 (1000 RL)
    // BP Run28 = 173 (1000 RL)
    // BP Run29 = 173 (1000 RL)
    // BP Run30 = 172 (1000 RL)
    // BP Run31 = 1381
    // BP Run32 = 1377
    // BP Run33 = 690 (2500 RL)
    // BP Run34 = 689 (2500 RL)
    // BP Run35 = 345 (1250 RL)
    // BP Run36 = 344 (1250 RL)
    // BP Run37 = 1380
    // run80001 = 1232
    // AYK Run09 = 1420
    // AYK Run10 = 1420
    // AYK Run11 = 1425
    // AYK Run12 = 1429
    // AYK Run13 = 1432
    // AYK Run14 = 1437
    // AYK Run52 = 1380
    if(fpdTriggerIndex > -1)
      {
	for(int i=fpdBottomIndex+1232-25; i<fpdBottomIndex+1232+25; i++) // ; 1384 = run09
	  {
	    //if(signal[i] < hrppdBottom && signal[i] < SIGNALTHRESH)
	    if(signal[i] < hrppdBottom)
	      {
		hrppdBottom = signal[i];
		hrppdBottomIndex = i;
	      }
	  }
      }
    //if(NEVENTS > 20950)
    //cout << "!!! " << hrppdBottom << " " << hrppdBottomIndex << endl;
    if(hrppdBottomIndex > -1)
      {
	int numHRPPDBaselinePoints = 0;
	double hrppdBaselineTotal = 0.;
	//int limit = hrppdBottomIndex-SIGNALOFFSET-SIGNALWIDTH;
	//if(limit < 1) limit = 1; 
	//for(int i=hrppdBottomIndex; i>=limit; i--)
	for(int i=hrppdBottomIndex-50; i>=hrppdBottomIndex-100; i--)
	  {
	    //cout << NEVENTS << " " << i << endl;
	    
	    hrppdBaselineTotal += signal[i];
	    numHRPPDBaselinePoints++;
	  }

	//cout << hrppdBottomIndex << " " << numHRPPDBaselinePoints << " " << hrppdBaselineTotal << " " << hrppdBottomIndex-SIGNALOFFSET-SIGNALWIDTH << endl;
	
	hrppdBaseline = hrppdBaselineTotal/(1.0*numHRPPDBaselinePoints);
	hrppdAmplitude = hrppdBaseline - hrppdBottom;
	
	hHRPPDBottom->Fill(hrppdBottom);
	hHRPPDBaseline->Fill(hrppdBaseline);
	hHRPPDAmplitude->Fill(hrppdAmplitude);
	hHRPPDAmplitudeVsBottomIndex->Fill(hrppdBottomIndex,hrppdAmplitude);
	//hHRPPDTrgPointVsBottomPoint->Fill(hrppdBottomIndex,fpdTriggerIndex);

	NUMSIG++;
      }

    //if(hrppdAmplitude > 0.04)
    //cout << setprecision(20) << hrppdAmplitude << " " << hrppdBottom << " " << NEVENTS << " " << eventTime[0] << endl;

    //cout << "Finish 3" << endl;

    // 4. Define Limits of Leading Edge and Fit
    int hrppdEdgeBeginIndex = -1;
    int hrppdMidIndex = -1;
    int hrppdEdgeEndIndex = -1;
    int pointsInHRPPDFit = 0;
    double hrppd50Percent = 0.0; 
    double aHRPPD = 0.;
    double bHRPPD = 0.;

    if(hrppdBottomIndex > -1)
      {
	double hrppdThresh10 = hrppdBaseline - 0.1*hrppdAmplitude;
	double hrppdThresh50 = hrppdBaseline - 0.5*hrppdAmplitude;
	double hrppdThresh90 = hrppdBaseline - 0.9*hrppdAmplitude;
	for(int i=hrppdBottomIndex; i>=hrppdBottomIndex-SIGNALOFFSET; i--)
	  {
	    if(signal[i] > hrppdThresh90)
	      {
		hrppdEdgeEndIndex = i;// - 1;
		break;
	      }
	    //cout << setprecision(20) << endl;
	    //cout << NEVENTS << " " << i << " " << eventTime[i] << endl;
	  }
	for(int i=hrppdBottomIndex; i>=hrppdBottomIndex-SIGNALOFFSET; i--)
	  {
	    if(signal[i] > hrppdThresh10)
	      {
		hrppdEdgeBeginIndex = i;// - 1;
		break;
	      }
	  }
	for(int i=hrppdBottomIndex; i>=hrppdBottomIndex-SIGNALOFFSET; i--)
	  {
	    if(signal[i] > hrppdThresh50)
	      {
		hrppdMidIndex = i;// - 1;
		break;
	      }
	  }
	
	pointsInHRPPDFit = hrppdEdgeEndIndex - hrppdEdgeBeginIndex + 1;
	
	hHRPPDPointsInFit->Fill(pointsInHRPPDFit);
	hHRPPDPointsInFitVsAmplitude->Fill(hrppdAmplitude,pointsInHRPPDFit);
	hHRPPDEdgeEndVsBeginIndex->Fill(hrppdEdgeBeginIndex,hrppdEdgeEndIndex);
	//hHRPPDEdgeEndBeginTimeDiff->Fill((signalTime[hrppdEdgeEndIndex]-signalTime[hrppdEdgeBeginIndex])*1000000000000.0);
	//hHRPPDEdgeEndBeginTimeDiffVsAmplitude->Fill(hrppdAmplitude,(signalTime[hrppdEdgeEndIndex]-signalTime[hrppdEdgeBeginIndex])*1000000000000.0);

	double sumXHRPPD = 0.;
	double sumX2HRPPD = 0.;
	double sumHRPPDVal = 0.;
	double sumXHRPPDVal = 0.;
	int NHRPPD = 0;
	if(hrppdEdgeBeginIndex > -1 && hrppdEdgeEndIndex > -1)
	  {
	    for(int i=hrppdEdgeBeginIndex; i<hrppdEdgeEndIndex+1; i++)
	      {
		double time = signalTime[i]*1000000000000.0;
		
		sumXHRPPD += time;
		sumX2HRPPD += time*time;
		sumHRPPDVal += signal[i];
		sumXHRPPDVal += time*signal[i];
		NHRPPD++;
	      }
	  }

	if(hrppdEdgeBeginIndex == -1 || hrppdEdgeEndIndex == -1)
	  kill = true;
	
	double deltaHRPPD = NHRPPD*sumX2HRPPD - sumXHRPPD*sumXHRPPD;
	aHRPPD = (sumX2HRPPD*sumHRPPDVal - sumXHRPPD*sumXHRPPDVal)/deltaHRPPD;
	bHRPPD = (NHRPPD*sumXHRPPDVal - sumXHRPPD*sumHRPPDVal)/deltaHRPPD;

	hHRPPDa->Fill(aHRPPD);
	hHRPPDb->Fill(bHRPPD);

	hrppd50Percent = ((hrppdBaseline - 0.5*hrppdAmplitude) - aHRPPD)/bHRPPD;

	hHRPPD50PercentTime->Fill(hrppd50Percent);
	//hHRPPD50PercentTimeVsBottom->Fill(signalTime[hrppdBottomIndex],hrppd50Percent);
      }

    //cout << "Finish 4" << endl;

    // Look at HRPPD - FPD Timing
    if(fpdTriggerIndex > -1 && hrppdBottomIndex > -1 && pointsInHRPPDFit > 2 && !kill)
      {
	double hrppdFPDTimeDiff = hrppd50Percent - fpd50Percent;
	//double hrppdFPDTimeDiffWrap = (hrppdFPDTimeDiff > 0.0) ? hrppdFPDTimeDiff : hrppdFPDTimeDiff + 204800.0;
	
	hHRPPDFPDTimeDiff->Fill(hrppdFPDTimeDiff);
	hHRPPDFPDTimeDiffVsAmp->Fill(hrppdAmplitude,hrppdFPDTimeDiff);
	hHRPPDVsFPDTime->Fill(fpd50Percent,hrppd50Percent);

	if(hrppdAmplitude > 0.015)
	  hHRPPDFPDTimeDiff15->Fill(hrppdFPDTimeDiff);

	if(hrppdAmplitude > 0.020)
	  hHRPPDFPDTimeDiff20->Fill(hrppdFPDTimeDiff);

	/*
	hHRPPDVsFPDMidIndex->Fill(fpdMidIndex,hrppdMidIndex);
	hHRPPDFPDMidDiff->Fill(hrppdMidIndex - fpdMidIndex);

	if(hrppdAmplitude > 20.0)
	  {
	    hHRPPDFPDTimeDiff20->Fill(hrppdFPDTimeDiff);
	    hHRPPDFPDTimeDiffWrap20->Fill(hrppdFPDTimeDiffWrap);
	  }

	if(hrppdAmplitude > 25.0)
	  {
	    hHRPPDFPDTimeDiff25->Fill(hrppdFPDTimeDiff);
	    hHRPPDFPDTimeDiffWrap25->Fill(hrppdFPDTimeDiffWrap);
	  }

	hHRPPDFPDTimeDiffWrap->Fill(hrppdFPDTimeDiffWrap);
	hHRPPDFPDTimeDiffWrapVsAmp->Fill(hrppdAmplitude,hrppdFPDTimeDiffWrap);

	if(time[fpdBottomIndex] < 1000.0)
	  hHRPPDFPDTimeDiffWrapTimeCut->Fill(hrppdFPDTimeDiffWrap);

	if(pointsInHRPPDFit > 2)
	  hHRPPDFPDTimeDiffFitPoints->Fill(hrppdFPDTimeDiff);

	if(fpdBottom < -277.5)
	  {
	    hHRPPDFPDTimeDiffLowBottom->Fill(hrppdFPDTimeDiff);
	  }
	if(fpdBottom > -277.5)
	  {
	    hHRPPDFPDTimeDiffHighBottom->Fill(hrppdFPDTimeDiff);
	  }

	// Test Cut on hrppd50Percent vs fpd50Percent for Run 27764
	if(hrppd50Percent > 70000.0 || fpd50Percent > 140000.0)
	  {
	    hHRPPDVsFPDTimeTestCut->Fill(fpd50Percent,hrppd50Percent);
	    hHRPPDFPDTimeDiffWrapTestCut->Fill(hrppdFPDTimeDiffWrap);
	    hHRPPDFPDTimeDiffWrapVsAmpTestCut->Fill(hrppdAmplitude,hrppdFPDTimeDiffWrap);

	    if(hrppdAmplitude > 30.0 && hrppdAmplitude < 40.0 && hrppdFPDTimeDiffWrap > 66000.0 && hrppdFPDTimeDiffWrap < 66500.0)
	      {
		//std::cout << NEVENTS << " " << aHRPPD << " " << bHRPPD << " " << aFPD << " " << bFPD << std::endl;
	      }
	  }
	*/
      }


    NEVENTS++;
} //while

  //tout->Write();
  //hb1->Write();
  //hb4->Write();
  ofile->Write();
  ofile->Close();

  cout << "Number of Events = " << NEVENTS << endl;
  cout << "Number of Triggers = " << NUMTRIG << endl;
  cout << "Number of Signals = " << NUMSIG << endl;
}
