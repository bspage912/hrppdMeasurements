// Plot and fit timing curve - place a cut on HRPPD amplitude

int timingCurve(TString rootHistFname, double aCut = 0.0)
{
  gStyle->SetOptStat();

  TFile *fa = new TFile(rootHistFname);
  assert(fa->IsOpen());

  TTree *t = (TTree *)fa->Get("t");

  int fpdOk = 0, hrppdOk = 0, fpdPeakIndex = 0, hrppdPeakIndex = 0, fpdPoints = 0, hrppdPoints = 0;
  double fpdBase = 0.0, hrppdBase = 0.0, fpdAmp = 0.0, hrppdAmp = 0.0, fpd50Time = 0.0, hrppd50Time = 0.0;
  t->SetBranchAddress("fpdOk", &fpdOk);
  t->SetBranchAddress("fpdPeakIndex", &fpdPeakIndex);
  t->SetBranchAddress("fpdPoints", &fpdPoints);
  t->SetBranchAddress("fpdBase", &fpdBase);
  t->SetBranchAddress("fpdAmp", &fpdAmp);
  t->SetBranchAddress("fpd50Time", &fpd50Time);
  t->SetBranchAddress("hrppdOk", &hrppdOk);
  t->SetBranchAddress("hrppdPeakIndex", &hrppdPeakIndex);
  t->SetBranchAddress("hrppdPoints", &hrppdPoints);
  t->SetBranchAddress("hrppdBase", &hrppdBase);
  t->SetBranchAddress("hrppdAmp", &hrppdAmp);
  t->SetBranchAddress("hrppd50Time", &hrppd50Time);

  TH1D *hAmplitude = new TH1D("hAmplitude","",500,0.,0.5);
  TH1D *hNumPoints = new TH1D("hNumPoints","",50,0.,50.);
  TH1D *hNumPointsCut = new TH1D("hNumPointsCut","",50,0.,50.);
  TH1D *hTimingCurve = new TH1D("hTimingCurve","",30000,15000.,45000.);
  TH1D *hTimingCurveCut = new TH1D("hTimingCurveCut","",30000,15000.,45000.);
  TH2D *hTimingCurveVsAmplitude = new TH2D("hTimingCurveVsAmplitude","",500,0.,0.5,10000,20000.,30000.);
  TH2D *hTimingCurveVsNumPoints = new TH2D("hTimingCurveVsNumPoints","",50,0.,50.,10000,20000.,30000.);
  TH2D *hTimingCurveVsNumPointsCut = new TH2D("hTimingCurveVsNumPointsCut","",50,0.,50.,10000,20000.,30000.);

  Int_t nentries = (Int_t)t->GetEntries();
  for(int i=0; i<nentries; i++)
    {
      t->GetEntry(i);

      hAmplitude->Fill(hrppdAmp);
      hNumPoints->Fill(hrppdPoints);
      hTimingCurve->Fill(hrppd50Time - fpd50Time);
      hTimingCurveVsAmplitude->Fill(hrppdAmp,hrppd50Time - fpd50Time);
      hTimingCurveVsNumPoints->Fill(hrppdPoints,hrppd50Time - fpd50Time);

      if(hrppdAmp > aCut)
	{
	  hNumPointsCut->Fill(hrppdPoints);
	  hTimingCurveCut->Fill(hrppd50Time - fpd50Time);
	  hTimingCurveVsNumPointsCut->Fill(hrppdPoints,hrppd50Time - fpd50Time);
	}
    }

  // Draw Result
  TCanvas *c1 = new TCanvas("c1","Timing Curve",800,600);
  c1->Clear();
  c1->Divide(1,1);

  c1->cd(1);
  hTimingCurveCut->Draw("HIST");

  double amp = hTimingCurveCut->GetMaximum();
  double mean = hTimingCurveCut->GetBinCenter(hTimingCurveCut->GetMaximumBin());
  double sigma = 15.0;
  double alpha = -0.9;
  double n = 1.5;

  TF1 *f1 = new TF1("f1","crystalball",24000,26000);
  f1->SetParameters(amp,mean,sigma,alpha,n);

  hTimingCurveCut->Fit(f1);
  f1->Draw("SAME");

  TCanvas *c2 = new TCanvas("c2","HRPPD Amplitude",800,600);
  c2->Clear();
  c2->Divide(1,1);

  c2->cd(1);
  hAmplitude->Draw("HIST");
  double ulimit = 1.5*hAmplitude->GetMaximum();
  TLine *plAmp = new TLine(aCut,0.0,aCut,ulimit);
  plAmp->SetLineColor(kRed);
  plAmp->Draw("SAME");

  TCanvas *c3 = new TCanvas("c3","Number of Points",800,600);
  c3->Clear();
  c3->Divide(1,1);

  c3->cd(1);
  hNumPoints->SetLineColor(kBlue);
  hNumPoints->Draw("HIST");
  hNumPointsCut->SetLineColor(kRed);
  hNumPointsCut->Draw("HISTSAME");

  TCanvas *c4 = new TCanvas("c4","Raw Timing Curve",800,600);
  c4->Clear();
  c4->Divide(1,1);

  c4->cd(1);
  hTimingCurve->SetLineColor(kBlue);
  hTimingCurve->Draw("HIST");

  TCanvas *c5 = new TCanvas("c5","Raw Timing Curve Vs Amplitude",800,600);
  c5->Clear();
  c5->Divide(1,1);

  c5->cd(1);
  hTimingCurveVsAmplitude->Draw("COLZ");
  TLine *plAmp5 = new TLine(aCut,20000.0,aCut,30000.0);
  plAmp5->SetLineColor(kRed);
  plAmp5->Draw("SAME");

  TCanvas *c6 = new TCanvas("c6","Raw Timing Curve Vs Numbrer of HRPPD fit Points",800,600);
  c6->Clear();
  c6->Divide(1,1);

  c6->cd(1);
  hTimingCurveVsNumPoints->Draw("COLZ");

  TCanvas *c7 = new TCanvas("c7","Raw Timing Curve Vs Numbrer of HRPPD fit Points after Amp Cut",800,600);
  c7->Clear();
  c7->Divide(1,1);

  c7->cd(1);
  hTimingCurveVsNumPointsCut->Draw("COLZ");

  return 0;
}
