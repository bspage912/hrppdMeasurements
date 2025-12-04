// Fit Amplitude Spectrum to Extract Gain

int gainAnalysis(TString rootHistFname, int number)
{
  gStyle->SetOptStat(0);

  TFile *fa = new TFile(rootHistFname);
  assert(fa->IsOpen());

  TTree *t = (TTree *)fa->Get("t");

  //int fpdOk = 0, hrppdOk = 0, fpdPeakIndex = 0, hrppdPeakIndex = 0, fpdPoints = 0, hrppdPoints = 0;
  int hrppdWidth = 0;
  double hrppdCharge = 0.0;
  t->SetBranchAddress("hrppdWidth", &hrppdWidth);
  t->SetBranchAddress("hrppdCharge", &hrppdCharge);

  TH1D *hHRPPDCharge = new TH1D("hHRPPDCharge","",600,-0.05,0.25);

  Int_t nentries = (Int_t)t->GetEntries();
  for(int i=0; i<nentries; i++)
    {
      t->GetEntry(i);

      hHRPPDCharge->Fill(hrppdCharge);
    }

  // Draw Results
  TCanvas *c1 = new TCanvas("c1","Pulse Charge",800,600);
  c1->Clear();
  c1->Divide(1,1);

  c1->cd(1);
  hHRPPDCharge->Draw("HIST");
  gPad->SetLogy();

  double amp = 50000.0;
  double mean = 0.0002;
  double sigma = 0.00005;
  double alpha = -0.9;
  double n = 2.0;
  double amp1 = 30.0;
  double mean1 = 0.03;
  double sigma1 = 0.01;

  TF1 *f1 = new TF1("f1","crystalball(0)+gaus(5)",-0.001,0.1);
  f1->SetParameters(amp,mean,sigma,alpha,n,amp1,mean1,sigma1);

  hHRPPDCharge->Fit(f1);
  f1->Draw("SAME");

  TF1 *f2 = new TF1("f2","crystalball(0)",-0.001,0.1);
  f2->SetParameters(f1->GetParameter(0),f1->GetParameter(1),f1->GetParameter(2),f1->GetParameter(3),f1->GetParameter(4));
  f2->SetLineColor(kBlue);
  f2->Draw("SAME");

  TF1 *f3 = new TF1("f3","gaus(0)",-0.001,0.1);
  f3->SetParameters(f1->GetParameter(5),f1->GetParameter(6),f1->GetParameter(7));
  f3->SetLineColor(kGreen+2);
  f3->Draw("SAME");

  cout << endl;
  cout << "######################" << endl;
  cout << "##       Gain       ##" << endl;
  cout << "######################" << endl;
  cout << endl;
  cout << "Gain = " << f1->GetParameter(6) << " x (20*10^-12)*10^19/1.602 = " << f1->GetParameter(6)*124843945.0 << endl;
  
  /*
  double amp1 = hHRPPDCharge->GetMaximum();
  double mean1 = 0.0001;
  double sigma1 = 0.00001;
  double expoA = 3.0;
  double expoB = -1000.0;
  double amp2 = 30.0;
  double mean2 = 0.03;
  double sigma2 = 0.01;

  TF1 *f1 = new TF1("f1","gaus(0)+expo(3)+gaus(5)",-0.001,0.1);
  f1->SetParameters(amp1,mean1,sigma1,expoA,expoB,amp2,mean2,sigma2);

  hHRPPDCharge->Fit(f1);
  f1->Draw("SAME");

  TF1 *f2 = new TF1("f1","gaus(0)",-0.001,0.1);
  f2->SetParameters(f1->GetParameter(0),f1->GetParameter(1),f1->GetParameter(2));
  f2->SetLineColor(kBlue);
  f2->Draw("SAME");

  TF1 *f3 = new TF1("f3","expo(0)",-0.001,0.1);
  f3->SetParameters(f1->GetParameter(3),f1->GetParameter(4));
  f3->SetLineColor(kCyan+1);
  f3->Draw("SAME");

  TF1 *f4 = new TF1("f4","gaus(0)",-0.001,0.1);
  f4->SetParameters(f1->GetParameter(5),f1->GetParameter(6),f1->GetParameter(7));
  f4->SetLineColor(kGreen+2);
  f4->Draw("SAME");
  */

  return 0;
}
