// Plot and fit timing curve - place a cut on HRPPD amplitude

int timingMultiFit(TString rootHistFname, double corRangeLo = 0.005, double corRangeHi = 0.5, double fitCut = 0.005, double byHandCor = 0.0)
{
  gStyle->SetOptStat(0);

  TFile *fa = new TFile(rootHistFname);
  assert(fa->IsOpen());

  TTree *t = (TTree *)fa->Get("t");

  double hrppdAmp1 = 0;
  double hrppd50Time1 = 0;
  t->SetBranchAddress("hrppdAmp1", &hrppdAmp1);
  t->SetBranchAddress("hrppd50Time1", &hrppd50Time1);

  const double limitLo = 102000.0; //102000
  const double limitHi = 108000.0; //108000

  // Histograms
  TH2D *timingVsAmpRaw = new TH2D("timingVsAmpRaw","Trig-Sig Time Difference Vs Signal Amplitude;Amplitude [V];Time Difference [ps]",1000,0.,0.5,6000,limitLo,limitHi);
  TH2D *timingVsAmpCor = new TH2D("timingVsAmpCor","Trig-Sig Time Difference Vs Signal Amplitude (Corrected);Amplitude [V];Time Difference [ps]",1000,0.,0.5,6000,limitLo,limitHi);
  TH1D *timingRaw = new TH1D("timingRaw",Form("Raw Trig-Sig Timing Difference (Amp > %f);Timing Difference [ps]",fitCut),600,limitLo,limitHi);
  TH1D *timingRaw1 = new TH1D("timingRaw1",Form("Raw Trig-Sig Timing Difference (Amp > %f);Timing Difference [ps]",fitCut),600,limitLo,limitHi);
  TH1D *timingRaw2 = new TH1D("timingRaw2",Form("Raw Trig-Sig Timing Difference (Amp > %f);Timing Difference [ps]",fitCut),600,limitLo,limitHi);
  TH1D *timingRaw3 = new TH1D("timingRaw3",Form("Raw Trig-Sig Timing Difference (Amp > %f);Timing Difference [ps]",fitCut),600,limitLo,limitHi);
  TH1D *timingCor = new TH1D("timingCor",Form("Corrected Trig-Sig Timing Difference (Amp > %f);Timing Difference [ps]",fitCut),600,limitLo,limitHi);
  TH1D *timingCor1 = new TH1D("timingCor1",Form("Corrected Trig-Sig Timing Difference (Amp > %f);Timing Difference [ps]",fitCut),600,limitLo,limitHi);
  TH1D *timingCor2 = new TH1D("timingCor2",Form("Corrected Trig-Sig Timing Difference (Amp > %f);Timing Difference [ps]",fitCut),600,limitLo,limitHi);
  TH1D *timingCor3 = new TH1D("timingCor3",Form("Corrected Trig-Sig Timing Difference (Amp > %f);Timing Difference [ps]",fitCut),600,limitLo,limitHi);
  
  //TH2D *optCurve = new TH2D("optCurve","",200,0.,200.,10000.,0.,1000.);

  // Do Minimization
  Int_t nentries = (Int_t)t->GetEntries();
  Double_t initialSlope = 0.;
  Double_t initialIntercept = 0.;
  Double_t bestSlope = 1000000.;
  Double_t bestIntercept = 0.;
  Double_t correctionFactor[2] = { 0.0, 0.0 };
  
  for(int slp=0; slp<2; slp++)
    {
      // Fit Points
      double sumX = 0.;
      double sumX2 = 0.;
      double sumVal = 0.;
      double sumXVal = 0.;
      unsigned N = 0;
      
      for(int i=0; i<nentries; i++)
	{
	  t->GetEntry(i);
	  
	  double modY = 0.0;
	  modY = hrppd50Time1 - correctionFactor[slp]*hrppdAmp1; 

	  if(slp == 0) // slp = 0 -> No correction for time diff vs slope
	    {
	      timingVsAmpRaw->Fill(hrppdAmp1,modY);

	      if(hrppdAmp1 > 0.005) // 0.005
		{
		  timingRaw->Fill(modY);
		  if(hrppdAmp1 > fitCut) 
		    {
		      timingRaw1->Fill(modY);
		      timingRaw2->Fill(modY);
		      timingRaw3->Fill(modY);
		    }
		}
	    }

	  if(slp == 1) // slp = 1 -> Correction for time diff vs slope applied
	    {
	      if(TMath::Abs(byHandCor) > 0.0) // Replace calculated correction factor with user input
		{
		  modY = hrppd50Time1 - byHandCor*hrppdAmp1;
		}

	      timingVsAmpCor->Fill(hrppdAmp1,modY);

	      if(hrppdAmp1 > 0.005) // 0.005
		{
		  timingCor->Fill(modY);
		  if(hrppdAmp1 > fitCut) 
		    {
		      timingCor1->Fill(modY);
		      timingCor2->Fill(modY);
		      timingCor3->Fill(modY);
		    }
		}
	    }
	  
	  if(std::isfinite(hrppdAmp1) && std::isfinite(hrppd50Time1))
	    {
	      if(hrppdAmp1 > corRangeLo && hrppdAmp1 < corRangeHi && hrppd50Time1 < 105000.0 && hrppd50Time1 > 104000.0)
		{
		  sumX += hrppdAmp1;
		  sumX2 += hrppdAmp1*hrppdAmp1;
		  sumVal += modY;//hrppd50Time1;
		  sumXVal += hrppdAmp1*modY;//hrppdAmp1*hrppd50Time1;
		  N++;
		}
	    }
	}
      
      double delta = N*sumX2 - sumX*sumX;
      double a = (sumX2*sumVal - sumX*sumXVal)/delta;
      double b = (N*sumXVal - sumX*sumVal)/delta;

      if(slp == 0)
	{
	  initialSlope = b;
	  initialIntercept = a;

	  correctionFactor[1] = initialSlope;
	}

      if(slp == 1)
	{
	  bestSlope = b;
	  bestIntercept = a;
	}
    }

  /*
  if(TMath::Abs(byHandCor) > 0.0) // Replace calculated correction factor with user input
    {
      correctionFactor[1] = byHandCor;
    } 
  */

  /*
  for(int i=0; i<nentries; i++)
    {
      t->GetEntry(i);
      
      timingVsAmpCor->Fill(hrppdAmp1,hrppd50Time1 - correctionFactor[1]*hrppdAmp1);
      if(hrppdAmp1 > 0.005) // 0.005
	{
	  timingCor->Fill(hrppd50Time1 - correctionFactor[1]*hrppdAmp1);
	  if(hrppdAmp1 > fitCut) timingCor1->Fill(hrppd50Time1 - correctionFactor[1]*hrppdAmp1);
	}
    }
  */
  
  cout << "Initial Slope = " << initialSlope << endl;
  cout << "Initial Intercept = " << initialIntercept << endl;
  cout << "Best Slope = " << bestSlope << endl;
  cout << "Best Intercept = " << bestIntercept << endl;
  cout << "Correction Factor = " << correctionFactor[1] << endl;

  TCanvas *c1 = new TCanvas("c1","Raw",800,600);
  c1->Clear();
  c1->Divide(1,1);

  c1->cd(1);
  timingVsAmpRaw->Draw("COLZ");

  
  TCanvas *c2 = new TCanvas("c2","Corrected",800,600);
  c2->Clear();
  c2->Divide(1,1);

  c2->cd(1);
  timingVsAmpCor->Draw("COLZ");

  TCanvas *c3 = new TCanvas("c3","Timing",800,600);
  c3->Clear();
  c3->Divide(1,1);

  c3->cd(1);
  timingRaw->SetLineColor(kBlue);
  timingRaw->Draw("HIST");
  timingCor->SetLineColor(kRed);
  timingCor->Draw("HISTSAME");

  
  TCanvas *c4 = new TCanvas("c4","Raw Time Fit",800,600);
  c4->Clear();
  c4->Divide(1,1);

  c4->cd(1);
  timingRaw1->Draw("HIST");
  timingRaw1->GetXaxis()->SetRangeUser(104000,106000);

  // Fit
  TF1 *fitRaw = new TF1("fitRaw","gaus(0)+gaus(3)",limitLo,limitHi);
  TF1 *fitRaw1 = new TF1("fitRaw1","gaus",limitLo,limitHi);
  TF1 *fitRaw2 = new TF1("fitRaw2","gaus",limitLo,limitHi);
  double ampRaw1 = timingRaw1->GetMaximum();
  double meanRaw1 = timingRaw1->GetBinCenter(timingRaw1->GetMaximumBin());
  double sigmaRaw1 = 35.0;
  double ampRaw2 = 0.1*ampRaw1;
  double meanRaw2 = meanRaw1 + 100.0;
  double sigmaRaw2 = 60.0;
  fitRaw->SetParameters(ampRaw1,meanRaw1,sigmaRaw1,ampRaw2,meanRaw2,sigmaRaw2);

  timingRaw1->Fit(fitRaw);
  fitRaw->SetLineColor(kAzure+8);
  fitRaw->Draw("SAME");
  fitRaw1->SetParameters(fitRaw->GetParameter(0),fitRaw->GetParameter(1),fitRaw->GetParameter(2));
  fitRaw2->SetParameters(fitRaw->GetParameter(3),fitRaw->GetParameter(4),fitRaw->GetParameter(5));
  fitRaw1->SetLineColor(kRed);
  fitRaw1->Draw("SAME");
  fitRaw2->SetLineColor(kGreen+2);
  fitRaw2->Draw("SAME");


  TCanvas *c5 = new TCanvas("c5","Corrected Time Fit",800,600);
  c5->Clear();
  c5->Divide(1,1);

  c5->cd(1);
  timingCor1->Draw("HIST");
  timingCor1->GetXaxis()->SetRangeUser(104000,106000);

  // Fit
  TF1 *fitCor = new TF1("fitCor","gaus(0)+gaus(3)",limitLo,limitHi);
  TF1 *fitCor1 = new TF1("fitCor1","gaus",limitLo,limitHi);
  TF1 *fitCor2 = new TF1("fitCor2","gaus",limitLo,limitHi);
  double ampCor1 = timingCor1->GetMaximum();
  double meanCor1 = timingCor1->GetBinCenter(timingCor1->GetMaximumBin());
  double sigmaCor1 = 35.0;
  double ampCor2 = 0.1*ampCor1;
  double meanCor2 = meanCor1 + 100.0;
  double sigmaCor2 = 60.0;
  fitCor->SetParameters(ampCor1,meanCor1,sigmaCor1,ampCor2,meanCor2,sigmaCor2);

  timingCor1->Fit(fitCor);
  fitCor->SetLineColor(kAzure+8);
  fitCor->Draw("SAME");
  fitCor1->SetParameters(fitCor->GetParameter(0),fitCor->GetParameter(1),fitCor->GetParameter(2));
  fitCor2->SetParameters(fitCor->GetParameter(3),fitCor->GetParameter(4),fitCor->GetParameter(5));
  fitCor1->SetLineColor(kRed);
  fitCor1->Draw("SAME");
  fitCor2->SetLineColor(kGreen+2);
  fitCor2->Draw("SAME");


  TCanvas *c6 = new TCanvas("c6","Raw Time Fit - Single Gaus",800,600);
  c6->Clear();
  c6->Divide(1,1);

  c6->cd(1);
  timingRaw2->Draw("HIST");
  timingRaw2->GetXaxis()->SetRangeUser(104000,106000);

  // Fit
  TF1 *fitRawSingle = new TF1("fitRawSingle","gaus(0)",limitLo,limitHi);
  double ampRawSingle = timingRaw2->GetMaximum();
  double meanRawSingle = timingRaw2->GetBinCenter(timingRaw2->GetMaximumBin());
  double sigmaRawSingle = 35.0;
  fitRawSingle->SetParameters(ampRawSingle,meanRawSingle,sigmaRawSingle);

  timingRaw2->Fit(fitRawSingle);
  fitRawSingle->SetLineColor(kRed);
  fitRawSingle->Draw("SAME");


  TCanvas *c7 = new TCanvas("c7","Corrected Time Fit - Single Gaus",800,600);
  c7->Clear();
  c7->Divide(1,1);

  c7->cd(1);
  timingCor2->Draw("HIST");
  timingCor2->GetXaxis()->SetRangeUser(104000,106000);

  // Fit
  TF1 *fitCorSingle = new TF1("fitCorSingle","gaus(0)",limitLo,limitHi);
  double ampCorSingle = timingCor2->GetMaximum();
  double meanCorSingle = timingCor2->GetBinCenter(timingCor2->GetMaximumBin());
  double sigmaCorSingle = 35.0;
  fitCorSingle->SetParameters(ampCorSingle,meanCorSingle,sigmaCorSingle);

  timingCor2->Fit(fitCorSingle);
  fitCorSingle->SetLineColor(kRed);
  fitCorSingle->Draw("SAME");


  TCanvas *c8 = new TCanvas("c8","Raw Time Fit - Crystal Ball",800,600);
  c8->Clear();
  c8->Divide(1,1);

  c8->cd(1);
  timingRaw3->Draw("HIST");
  timingRaw3->GetXaxis()->SetRangeUser(104000,106000);

  // Fit
  TF1 *fitRawCB = new TF1("fitRawCB","crystalball",limitLo,limitHi);
  TF1 *fitRawCB1 = new TF1("fitRawCB1","gaus(0)",limitLo,limitHi);
  double ampRawCB = timingRaw3->GetMaximum();
  double meanRawCB = timingRaw3->GetBinCenter(timingRaw3->GetMaximumBin());
  double sigmaRawCB = 35.0;
  double alphaRawCB = -0.9;
  double nRawCB = 1.5;
  fitRawCB->SetParameters(ampRawCB,meanRawCB,sigmaRawCB,alphaRawCB,nRawCB);

  timingRaw3->Fit(fitRawCB);
  fitRawCB->SetLineColor(kAzure+8);
  fitRawCB->Draw("SAME");
  fitRawCB1->SetParameters(fitRawCB->GetParameter(0),fitRawCB->GetParameter(1),fitRawCB->GetParameter(2));
  fitRawCB1->SetLineColor(kRed);
  fitRawCB1->Draw("SAME");


  TCanvas *c9 = new TCanvas("c9","Corrected Time Fit - Crystal Ball",800,600);
  c9->Clear();
  c9->Divide(1,1);

  c9->cd(1);
  timingCor3->Draw("HIST");
  timingCor3->GetXaxis()->SetRangeUser(104000,106000);

  // Fit
  TF1 *fitCorCB = new TF1("fitCorCB","crystalball",limitLo,limitHi);
  TF1 *fitCorCB1 = new TF1("fitCorCB1","gaus(0)",limitLo,limitHi);
  double ampCorCB = timingCor3->GetMaximum();
  double meanCorCB = timingCor3->GetBinCenter(timingCor3->GetMaximumBin());
  double sigmaCorCB = 35.0;
  double alphaCorCB = -0.9;
  double nCorCB = 1.5;
  fitCorCB->SetParameters(ampCorCB,meanCorCB,sigmaCorCB,alphaCorCB,nCorCB);

  timingCor3->Fit(fitCorCB);
  fitCorCB->SetLineColor(kAzure+8);
  //fitCorCB->SetLineColor(kMagenta);
  fitCorCB->Draw("SAME");
  fitCorCB1->SetParameters(fitCorCB->GetParameter(0),fitCorCB->GetParameter(1),fitCorCB->GetParameter(2));
  fitCorCB1->SetLineColor(kRed);
  fitCorCB1->Draw("SAME");
  
  
  return 0;
}
