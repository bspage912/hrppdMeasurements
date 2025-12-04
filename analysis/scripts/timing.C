// Plot and fit timing curve - place a cut on HRPPD amplitude

int timing(TString rootHistFname)
{
  gStyle->SetOptStat(0);

  TFile *fa = new TFile(rootHistFname);
  assert(fa->IsOpen());

  TTree *t = (TTree *)fa->Get("t");

  double hrppdAmp1 = 0;
  double hrppd50Time1 = 0;
  t->SetBranchAddress("hrppdAmp1", &hrppdAmp1);
  t->SetBranchAddress("hrppd50Time1", &hrppd50Time1);

  /*
  Int_t nentries = (Int_t)t->GetEntries();
  double sum = 0.0;
  for(int i=0; i<nentries; ++i)
    {
      t->GetEntry(i);

      if(std::isfinite(hrppdAmp1)) sum += hrppdAmp1;
      else
	cout << i << " Bad Entry" << endl;
    }

  cout << sum << endl;
  */

  // Histograms
  TH2D *timingVsAmpRaw = new TH2D("timingVsAmpRaw","",1000,0.,0.5,6000,117000.,123000.);
  TH2D *timingVsAmpCor = new TH2D("timingVsAmpCor","",1000,0.,0.5,6000,117000.,123000.);
  TH1D *timingRaw = new TH1D("timingRaw","",600,117000.,123000.);
  TH1D *timingCor = new TH1D("timingCor","",600,117000.,123000.);
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

	  if(slp == 0)
	    {
	      timingVsAmpRaw->Fill(hrppdAmp1,modY);

	      if(hrppdAmp1 > 0.005)
		timingRaw->Fill(modY);
	    }
	  
	  if(std::isfinite(hrppdAmp1) && std::isfinite(hrppd50Time1))
	    {
	      if(hrppdAmp1 > 0.005 && hrppdAmp1 < 0.08 && hrppd50Time1 < 121000.0)
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

      /*
      optCurve->Fill(slp,TMath::Abs(b));

      if(TMath::Abs(b) < TMath::Abs(bestSlope))
	{
	  bestSlope = b;
	  bestIntercept = a;
	  bestCorrection = slp;
	}
      */
      
      //cout << a << " " << b << endl;
    }

  /*
  // Do Minimization
  Int_t nentries = (Int_t)t->GetEntries();
  int bestSlope = 0;
  Double_t initialMean = 0.;
  Double_t bestMean = 0.;
  Double_t bestResidual = 1e12;
  for(int slp=0; slp<50; slp++)
    {
      int n = 0;
      Double_t valSum = 0.0;
      Double_t mean = 0.0;
      for(int i=0; i<nentries; i++)
	{
	  t->GetEntry(i);

	  if(slp == 0)
	    timingVsAmpRaw->Fill(hrppdAmp1,hrppd50Time1);

	  if(std::isfinite(hrppdAmp1) && std::isfinite(hrppd50Time1))
	    {
	      if(hrppdAmp1 > 0.005)
		{
		  valSum += (hrppd50Time1 + (100.0*slp)*hrppdAmp1);
		  n++;
		}
	    }
	}

      mean = valSum/(n*1.0);
      if(slp == 0) initialMean = mean;

      double residual2 = 0.0;
      double rms = 0.0;
      for(int i=0; i<nentries; i++)
	{
	  t->GetEntry(i);

	  if(std::isfinite(hrppdAmp1) && std::isfinite(hrppd50Time1))
	    {
	      if(hrppdAmp1 > 0.005)
		{
		  residual2 += (hrppd50Time1+(100.0*slp)*hrppdAmp1 - mean)*(hrppd50Time1+(100.0*slp)*hrppdAmp1 - mean);
		}
	    }
	}

      rms = TMath::Sqrt(residual2/(1.0*n));

      cout << slp << " " << rms << endl;

      if(rms < bestResidual)
	{
	  bestResidual = rms;
	  bestMean = mean;
	  bestSlope = slp;
	}
    }

  cout << "Initial Mean = " << initialMean << endl;
  cout << "Best Mean = " << bestMean << endl;
  cout << "Best Slope = " << bestSlope << endl;
  cout << "Best Residual = " << bestResidual << endl;

  for(int i=0; i<nentries; i++)
    {
      t->GetEntry(i);

      timingVsAmpCor->Fill(hrppdAmp1,hrppd50Time1+(100.0*bestSlope)*hrppdAmp1);
    }
  */

  for(int i=0; i<nentries; i++)
    {
      t->GetEntry(i);
      
      timingVsAmpCor->Fill(hrppdAmp1,hrppd50Time1 - correctionFactor[1]*hrppdAmp1);
      if(hrppdAmp1 > 0.005)
	timingCor->Fill(hrppd50Time1 - correctionFactor[1]*hrppdAmp1);
    }
  
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

  /*
  TCanvas *c4 = new TCanvas("c4","Optimization",800,600);
  c4->Clear();
  c4->Divide(1,1);

  c4->cd(1);
  optCurve->Draw("COLZ");
  */
  
  return 0;
}
