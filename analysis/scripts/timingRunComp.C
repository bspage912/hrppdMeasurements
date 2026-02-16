// Compare timing curves from different runs

void timingRunComp()
{
  gStyle->SetOptStat(0);

  TFile *fa[3];
  fa[0] = new TFile("/gpfs02/eic/bpage/home/HRPPD/BFieldStudies/scope/processedTrees/run290026Tree.hist.root");
  fa[1] = new TFile("/gpfs02/eic/bpage/home/HRPPD/BFieldStudies/scope/processedTrees/run290027Tree.hist.root");
  fa[2] = new TFile("/gpfs02/eic/bpage/home/HRPPD/BFieldStudies/scope/processedTrees/run290028Tree.hist.root");
  assert(fa[0]->IsOpen());
  assert(fa[1]->IsOpen());
  assert(fa[2]->IsOpen());

  TTree *t[3];
  for(int i=0; i<3; i++)
    {
      t[i] = (TTree *)fa[i]->Get("t");
    }

  double hrppdAmp1[3] = {0.0};
  double hrppd50Time1[3] = {0.0};

  for(int i=0; i<3; i++)
    {
      t[i]->SetBranchAddress("hrppdAmp1", &hrppdAmp1[i]);
      t[i]->SetBranchAddress("hrppd50Time1", &hrppd50Time1[i]);
    }

  // Histograms
  TH1D *timing[3];
  TH2D *timingVsAmp[3];
  for(int i=0; i<3; i++)
    {
      timing[i] = new TH1D(Form("timing_%d",i),"",600,102000.0,108000.0);
      timingVsAmp[i] = new TH2D(Form("timingVsAmp_%d",i),"",1000,0.,0.5,600,102000.0,108000.0);
    }


  // Loop Through Events
  for(int run=0; run<3; run++)
    {
      Int_t nentries = (Int_t)t[run]->GetEntries();
      for(int i=0; i<nentries; i++)
	{
	  t[run]->GetEntry(i);
	  timingVsAmp[run]->Fill(hrppdAmp1[run],hrppd50Time1[run]);
	  if(hrppdAmp1[run] > 0.005)
	    timing[run]->Fill(hrppd50Time1[run]);
	}
    }

  // Plot
  TCanvas *c1 = new TCanvas("c1","Raw Timing Spectra",800,600);
  c1->Clear();
  c1->Divide(1,1);
  c1->cd(1);

  timing[0]->Draw("HIST");
  timing[0]->SetLineColor(kBlue);

  timing[1]->Draw("HISTSAME");
  timing[1]->SetLineColor(kRed);

  timing[2]->Draw("HISTSAME");
  timing[2]->SetLineColor(kGreen+2);


  TF1 *fit[3];
  double amp[3] = {0.0};
  double mean[3] = {0.0};
  double sigma[3] = {0.0};
  double alpha[3] = {0.0};
  double n[3] = {0.0};
  for(int i=0; i<3; i++)
    {
      fit[i] = new TF1(Form("fit_%d",i),"crystalball",102000.0,108000.0);

      amp[i] = timing[i]->GetMaximum();
      mean[i] = timing[i]->GetBinCenter(timing[i]->GetMaximumBin());
      sigma[i] = 35.0;
      alpha[i] = -0.9;
      n[i] = 1.5;

      fit[i]->SetParameters(amp[i],mean[i],sigma[i],alpha[i],n[i]);

      timing[i]->Fit(fit[i]);
    }


  TCanvas *c2 = new TCanvas("c2","Crystal Ball Fits",800,600);
  c2->Clear();
  c2->Divide(1,1);
  c2->cd(1);

  TF1 *fitA = new TF1("fitA","gaus",102000.0,108000.0);
  fitA->SetParameters(fit[0]->GetParameter(0),fit[0]->GetParameter(1),fit[0]->GetParameter(2));
  fitA->SetLineColor(kBlue);
  fitA->SetNpx(1000);
  fitA->Draw();
  //fit[0]->SetLineColor(kBlue);
  //fit[0]->Draw();

  TF1 *fitB = new TF1("fitB","gaus",102000.0,108000.0);
  fitB->SetParameters(fit[1]->GetParameter(0),fit[1]->GetParameter(1),fit[1]->GetParameter(2));
  fitB->SetLineColor(kRed);
  fitB->SetNpx(1000);
  fitB->Draw("SAME");
  //fit[1]->SetLineColor(kRed);
  //fit[1]->Draw("SAME");

  TF1 *fitC = new TF1("fitC","gaus",102000.0,108000.0);
  fitC->SetParameters(fit[2]->GetParameter(0),fit[2]->GetParameter(1),fit[2]->GetParameter(2));
  fitC->SetLineColor(kGreen+2);
  fitC->SetNpx(1000);
  fitC->Draw("SAME");
  //fit[2]->SetLineColor(kGreen+2);
  //fit[2]->Draw("SAME");

  TCanvas *c3 = new TCanvas("c3","Timing Vs Amp",2400,600);
  c3->Clear();
  c3->Divide(3,1);

  c3->cd(1);
  timingVsAmp[0]->Draw("COLZ");
  timingVsAmp[0]->GetXaxis()->SetRangeUser(0.,0.15);
  timingVsAmp[0]->GetYaxis()->SetRangeUser(103000,107000);

  c3->cd(2);
  timingVsAmp[1]->Draw("COLZ");
  timingVsAmp[1]->GetXaxis()->SetRangeUser(0.,0.15);
  timingVsAmp[1]->GetYaxis()->SetRangeUser(103000,107000);

  c3->cd(3);
  timingVsAmp[2]->Draw("COLZ");
  timingVsAmp[2]->GetXaxis()->SetRangeUser(0.,0.15);
  timingVsAmp[2]->GetYaxis()->SetRangeUser(103000,107000);
}
