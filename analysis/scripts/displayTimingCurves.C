// Plot Timing Results
// Number Come from timingCurve.C Script

void displayTimingCurves()
{
  gStyle->SetOptStat(0);

  double tile27X2Y2H1PC[7] = {25.0, 50.0, 75.0, 100.0, 200.0, 300.0, 400.0};
  double tile27X4Y4PC[1] = {200.0};
  
  double tile16X4Y1D4MPC1PC[3] = {100.0, 300.0, 400.0};
  double tile16X4Y1D4MPC2PC[4] = {30.0, 100.0, 300.0, 400.0};
  double tile16X4Y1D4MPC3PC[3] = {30.0, 100.0, 300.0};

  double tile27X2Y2H1Sigma[7] = {50.94, 44.08, 36.91, 33.87, 27.84, 23.59, 20.89};
  double tile27X4Y4E4Sigma[1] = {29.67};
  double tile27X4Y4B6Sigma[1] = {26.68};
  double tile27X4Y4F6Sigma[1] = {29.20};
  double tile27X4Y4D2Sigma[1] = {26.40};
  double tile27X4Y4G3Sigma[1] = {27.70};
  double tile27X4Y4G3Asym25Sigma[1] = {31.28};
  double tile27X4Y4G3Asym50Sigma[1] = {44.68};

  double tile16X4Y1D4MPC1Sigma[3] = {27.69, 19.90, 16.16};
  double tile16X4Y1D4MPC2Sigma[4] = {41.27, 22.65, 14.27, 13.27};
  double tile16X4Y1D4MPC3Sigma[3] = {39.83, 20.17, 12.91};

  double tile27X2Y2H1Mean[7] = {25039.1, 24851.9, 24767.8, 24710.4, 24604.0, 24550.5, 24518.0};
  double tile27X4Y4E4Mean[1] = {24806.7};
  double tile27X4Y4B6Mean[1] = {24480.0};
  double tile27X4Y4F6Mean[1] = {24532.8};
  double tile27X4Y4D2Mean[1] = {24696.8};
  double tile27X4Y4G3Mean[1] = {24789.2};
  double tile27X4Y4G3Asym25Mean[1] = {24793.3};
  double tile27X4Y4G3Asym50Mean[1] = {24799.5};

  TGraph *g27X2Y2H1Sigma = new TGraph(7,tile27X2Y2H1PC,tile27X2Y2H1Sigma);
  TGraph *g27X4Y4E4Sigma = new TGraph(1,tile27X4Y4PC,tile27X4Y4E4Sigma);
  TGraph *g27X4Y4B6Sigma = new TGraph(1,tile27X4Y4PC,tile27X4Y4B6Sigma);
  TGraph *g27X4Y4F6Sigma = new TGraph(1,tile27X4Y4PC,tile27X4Y4F6Sigma);
  TGraph *g27X4Y4D2Sigma = new TGraph(1,tile27X4Y4PC,tile27X4Y4D2Sigma);
  TGraph *g27X4Y4G3Sigma = new TGraph(1,tile27X4Y4PC,tile27X4Y4G3Sigma);
  TGraph *g27X4Y4G3Asym25Sigma = new TGraph(1,tile27X4Y4PC,tile27X4Y4G3Asym25Sigma);
  TGraph *g27X4Y4G3Asym50Sigma = new TGraph(1,tile27X4Y4PC,tile27X4Y4G3Asym50Sigma);

  TGraph *g16X4Y1D4MPC1Sigma = new TGraph(3,tile16X4Y1D4MPC1PC,tile16X4Y1D4MPC1Sigma);
  TGraph *g16X4Y1D4MPC2Sigma = new TGraph(4,tile16X4Y1D4MPC2PC,tile16X4Y1D4MPC2Sigma);
  TGraph *g16X4Y1D4MPC3Sigma = new TGraph(3,tile16X4Y1D4MPC3PC,tile16X4Y1D4MPC3Sigma);

  TGraph *g27X2Y2H1Mean = new TGraph(7,tile27X2Y2H1PC,tile27X2Y2H1Mean);
  TGraph *g27X4Y4E4Mean = new TGraph(1,tile27X4Y4PC,tile27X4Y4E4Mean);
  TGraph *g27X4Y4B6Mean = new TGraph(1,tile27X4Y4PC,tile27X4Y4B6Mean);
  TGraph *g27X4Y4F6Mean = new TGraph(1,tile27X4Y4PC,tile27X4Y4F6Mean);
  TGraph *g27X4Y4D2Mean = new TGraph(1,tile27X4Y4PC,tile27X4Y4D2Mean);
  TGraph *g27X4Y4G3Mean = new TGraph(1,tile27X4Y4PC,tile27X4Y4G3Mean);
  TGraph *g27X4Y4G3Asym25Mean = new TGraph(1,tile27X4Y4PC,tile27X4Y4G3Asym25Mean);
  TGraph *g27X4Y4G3Asym50Mean = new TGraph(1,tile27X4Y4PC,tile27X4Y4G3Asym50Mean);

  TCanvas *c1 = new TCanvas("c1","Tile 27 Timing Sigma Vs PC",800,600);
  c1->Clear();
  c1->Divide(1,1);
  c1->cd(1);
  TH2D *h1 = new TH2D("h1","",1,0.,450.,1,10.,60.); // 10 60
  h1->Draw();

  g27X2Y2H1Sigma->Draw("L*");
  g27X2Y2H1Sigma->SetMarkerStyle(20);
  g27X2Y2H1Sigma->SetMarkerColor(kRed);
  g27X2Y2H1Sigma->SetLineColor(kRed);

  g27X4Y4E4Sigma->Draw("*");
  g27X4Y4E4Sigma->SetMarkerStyle(21);
  g27X4Y4E4Sigma->SetMarkerColor(kBlue);

  g27X4Y4B6Sigma->Draw("*");
  g27X4Y4B6Sigma->SetMarkerStyle(22);
  g27X4Y4B6Sigma->SetMarkerColor(kGreen+2);

  g27X4Y4F6Sigma->Draw("*");
  g27X4Y4F6Sigma->SetMarkerStyle(23);
  g27X4Y4F6Sigma->SetMarkerColor(kMagenta+1);

  g27X4Y4D2Sigma->Draw("*");
  g27X4Y4D2Sigma->SetMarkerStyle(33);
  g27X4Y4D2Sigma->SetMarkerColor(kCyan+1);

  g27X4Y4G3Sigma->Draw("*");
  g27X4Y4G3Sigma->SetMarkerStyle(34);
  g27X4Y4G3Sigma->SetMarkerColor(kOrange-3);

  g27X4Y4G3Asym25Sigma->Draw("*");
  g27X4Y4G3Asym25Sigma->SetMarkerStyle(24);
  g27X4Y4G3Asym25Sigma->SetMarkerColor(kBlack);

  g27X4Y4G3Asym50Sigma->Draw("*");
  g27X4Y4G3Asym50Sigma->SetMarkerStyle(25);
  g27X4Y4G3Asym50Sigma->SetMarkerColor(kGray+1);


  TCanvas *c2 = new TCanvas("c2","Tile 27 Timing Mean Vs PC",800,600);
  c2->Clear();
  c2->Divide(1,1);
  c2->cd(1);
  TH2D *h2 = new TH2D("h2","",1,0.,450.,1,24200.,25200.); // 10 60
  h2->Draw();

  g27X2Y2H1Mean->Draw("L*");
  g27X2Y2H1Mean->SetMarkerStyle(20);
  g27X2Y2H1Mean->SetMarkerColor(kRed);
  g27X2Y2H1Mean->SetLineColor(kRed);

  g27X4Y4E4Mean->Draw("*");
  g27X4Y4E4Mean->SetMarkerStyle(21);
  g27X4Y4E4Mean->SetMarkerColor(kBlue);

  g27X4Y4B6Mean->Draw("*");
  g27X4Y4B6Mean->SetMarkerStyle(22);
  g27X4Y4B6Mean->SetMarkerColor(kGreen+2);

  g27X4Y4F6Mean->Draw("*");
  g27X4Y4F6Mean->SetMarkerStyle(23);
  g27X4Y4F6Mean->SetMarkerColor(kMagenta+1);

  g27X4Y4D2Mean->Draw("*");
  g27X4Y4D2Mean->SetMarkerStyle(33);
  g27X4Y4D2Mean->SetMarkerColor(kCyan+1);

  g27X4Y4G3Mean->Draw("*");
  g27X4Y4G3Mean->SetMarkerStyle(34);
  g27X4Y4G3Mean->SetMarkerColor(kOrange-3);

  g27X4Y4G3Asym25Mean->Draw("*");
  g27X4Y4G3Asym25Mean->SetMarkerStyle(24);
  g27X4Y4G3Asym25Mean->SetMarkerColor(kBlack);

  g27X4Y4G3Asym50Mean->Draw("*");
  g27X4Y4G3Asym50Mean->SetMarkerStyle(25);
  g27X4Y4G3Asym50Mean->SetMarkerColor(kGray+1);


  TCanvas *c3 = new TCanvas("c3","Tile 16 Timing Sigma Vs PC",800,600);
  c3->Clear();
  c3->Divide(1,1);
  c3->cd(1);
  TH2D *h3 = new TH2D("h3","",1,0.,450.,1,10.,60.); // 10 60
  h3->Draw();

  g16X4Y1D4MPC1Sigma->Draw("L*");
  g16X4Y1D4MPC1Sigma->SetMarkerStyle(20);
  g16X4Y1D4MPC1Sigma->SetMarkerColor(kRed);
  g16X4Y1D4MPC1Sigma->SetLineColor(kRed);

  g16X4Y1D4MPC2Sigma->Draw("L*");
  g16X4Y1D4MPC2Sigma->SetMarkerStyle(20);
  g16X4Y1D4MPC2Sigma->SetMarkerColor(kBlue);
  g16X4Y1D4MPC2Sigma->SetLineColor(kBlue);

  g16X4Y1D4MPC3Sigma->Draw("L*");
  g16X4Y1D4MPC3Sigma->SetMarkerStyle(20);
  g16X4Y1D4MPC3Sigma->SetMarkerColor(kGreen+2);
  g16X4Y1D4MPC3Sigma->SetLineColor(kGreen+2);
}
