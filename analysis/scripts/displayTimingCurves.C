// Plot Timing Results
// Number Come from timingCurve.C Script

void displayTimingCurves()
{
  gStyle->SetOptStat(0);

  double tile27X2Y2H1PC[7] = {25.0, 50.0, 75.0, 100.0, 200.0, 300.0, 400.0};
  double tile27X4Y4PC[1] = {200.0};

  double testGainVals1[3] = {0.0009, 0.0052, 0.0075};
  double testGainVals2[4] = {0.0025, 0.0085, 0.0258, 0.0322};
  double testGainVals3[3] = {0.0264, 0.0444, 0.0884}; // 0.0544
  double testGainVals4[4] = {0.0481, 0.0388, 0.0423, 0.0468};
  
  double tile16X4Y1D4MPC1PC[3] = {100.0, 300.0, 400.0};
  double tile16X4Y1D4MPC2PC[4] = {30.0, 100.0, 300.0, 400.0};
  double tile16X4Y1D4MPC3PC[3] = {30.0, 100.0, 300.0};
  double tile16X1Y3MPC1PC1[1] = {400.0};
  double tile16X1Y3MPC2PC2[1] = {300.0};

  double tile27X2Y2H1Sigma[7] = {50.94, 44.08, 36.91, 33.87, 27.84, 23.59, 20.89}; // run80005 - run80011
  double tile27X4Y4E4Sigma[1] = {29.67}; // run80012
  double tile27X4Y4B6Sigma[1] = {26.68}; // run80013
  double tile27X4Y4F6Sigma[1] = {29.20}; // run80014
  double tile27X4Y4D2Sigma[1] = {26.40}; // run80015
  double tile27X4Y4G3Sigma[1] = {27.70}; // run80016
  double tile27X4Y4G3Asym25Sigma[1] = {31.28}; // run80017
  double tile27X4Y4G3Asym50Sigma[1] = {44.68}; // run80018

  double tile16X4Y1D4MPC1Sigma[3] = {27.69, 19.90, 16.16}; // run80019 - run80021
  double tile16X4Y1D4MPC2Sigma[4] = {41.27, 22.65, 14.27, 13.27}; // run80022 - run80025
  double tile16X4Y1D4MPC3Sigma[3] = {39.83, 20.17, 12.91}; // run80026 - run80028

  double tile16X1Y3H6MPC1Sigma1[1] = {14.26}; // run80029 (ROP at nominal scope settings)
  double tile16X1Y3H6MPC1Sigma2[1] = {15.23}; // run80030 (ROP with CH5 at 20 mV/div)
  double tile16X1Y3H6MPC1Sigma3[1] = {13.72}; // run80031 (Repeat)
  double tile16X1Y3H6MPC1Sigma4[1] = {14.22}; // run80032 (Repeat)
  double tile16X1Y3H6MPC1Sigma5[1] = {15.41}; // run80033 (Repeat)
  double tile16X1Y3H6MPC1Sigma6[1] = {14.54}; // run80030 - run80033 combined
  double tile16X1Y3H6MPC2Sigma7[1] = {17.30}; // run80034 (MPC 675 PC 300 at nominal scope settings)
  double tile16X1Y3H6MPC2Sigma8[1] = {14.95}; // run80035 (MPC 675 PC 300 with CH5 at 20 mV/div)
  double tile16X1Y3H6MPC2Sigma9[1] = {15.55}; // run80036 (Repeat)
  double tile16X1Y3H6MPC2Sigma10[1] = {15.59}; // run80037 (Repeat)
  double tile16X1Y3H6MPC2Sigma11[1] = {15.54}; // run80038 (Repeat)
  double tile16X1Y3H6MPC2Sigma12[1] = {15.15}; // run80035 - run80038 combined
  double tile16X1Y3B4Sigma[1] = {18.98}; // run80039
  double tile16X1Y3E5Sigma[1] = {14.07}; // run80040
  double tile16X1Y3C7Sigma[1] = {16.82}; // run80041
  double tile16X1Y3C7Asym25Sigma[1] = {18.17}; // run80042
  double tile16X1Y3C7Asym50Sigma[1] = {19.59}; // run80043

  double testSigma[4] = {14.26, 18.98, 14.07, 16.82};

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
  TGraph *g16X1Y3H6MPC2Sigma = new TGraph(1,tile16X1Y3MPC1PC1,tile16X1Y3H6MPC1Sigma1);
  TGraph *g16X1Y3B4MPC2Sigma = new TGraph(1,tile16X1Y3MPC1PC1,tile16X1Y3B4Sigma);
  TGraph *g16X1Y3E5MPC2Sigma = new TGraph(1,tile16X1Y3MPC1PC1,tile16X1Y3E5Sigma);
  TGraph *g16X1Y3C7MPC2Sigma = new TGraph(1,tile16X1Y3MPC1PC1,tile16X1Y3C7Sigma);
  TGraph *g16X1Y3C7MPC2Asym25Sigma = new TGraph(1,tile16X1Y3MPC1PC1,tile16X1Y3C7Asym25Sigma);
  TGraph *g16X1Y3C7MPC2Asym50Sigma = new TGraph(1,tile16X1Y3MPC1PC1,tile16X1Y3C7Asym50Sigma);

  TGraph *g16X1Y3H6MPC1Sigma1 = new TGraph(1,tile16X1Y3MPC1PC1,tile16X1Y3H6MPC1Sigma1);
  TGraph *g16X1Y3H6MPC1Sigma2 = new TGraph(1,tile16X1Y3MPC1PC1,tile16X1Y3H6MPC1Sigma2);
  TGraph *g16X1Y3H6MPC1Sigma3 = new TGraph(1,tile16X1Y3MPC1PC1,tile16X1Y3H6MPC1Sigma3);
  TGraph *g16X1Y3H6MPC1Sigma4 = new TGraph(1,tile16X1Y3MPC1PC1,tile16X1Y3H6MPC1Sigma4);
  TGraph *g16X1Y3H6MPC1Sigma5 = new TGraph(1,tile16X1Y3MPC1PC1,tile16X1Y3H6MPC1Sigma5);
  TGraph *g16X1Y3H6MPC1Sigma6 = new TGraph(1,tile16X1Y3MPC1PC1,tile16X1Y3H6MPC1Sigma6);
  TGraph *g16X1Y3H6MPC2Sigma7 = new TGraph(1,tile16X1Y3MPC2PC2,tile16X1Y3H6MPC2Sigma7);
  TGraph *g16X1Y3H6MPC2Sigma8 = new TGraph(1,tile16X1Y3MPC2PC2,tile16X1Y3H6MPC2Sigma8);
  TGraph *g16X1Y3H6MPC2Sigma9 = new TGraph(1,tile16X1Y3MPC2PC2,tile16X1Y3H6MPC2Sigma9);
  TGraph *g16X1Y3H6MPC2Sigma10 = new TGraph(1,tile16X1Y3MPC2PC2,tile16X1Y3H6MPC2Sigma10);
  TGraph *g16X1Y3H6MPC2Sigma11 = new TGraph(1,tile16X1Y3MPC2PC2,tile16X1Y3H6MPC2Sigma11);
  TGraph *g16X1Y3H6MPC2Sigma12 = new TGraph(1,tile16X1Y3MPC2PC2,tile16X1Y3H6MPC2Sigma12);

  TGraph *g27X2Y2H1Mean = new TGraph(7,tile27X2Y2H1PC,tile27X2Y2H1Mean);
  TGraph *g27X4Y4E4Mean = new TGraph(1,tile27X4Y4PC,tile27X4Y4E4Mean);
  TGraph *g27X4Y4B6Mean = new TGraph(1,tile27X4Y4PC,tile27X4Y4B6Mean);
  TGraph *g27X4Y4F6Mean = new TGraph(1,tile27X4Y4PC,tile27X4Y4F6Mean);
  TGraph *g27X4Y4D2Mean = new TGraph(1,tile27X4Y4PC,tile27X4Y4D2Mean);
  TGraph *g27X4Y4G3Mean = new TGraph(1,tile27X4Y4PC,tile27X4Y4G3Mean);
  TGraph *g27X4Y4G3Asym25Mean = new TGraph(1,tile27X4Y4PC,tile27X4Y4G3Asym25Mean);
  TGraph *g27X4Y4G3Asym50Mean = new TGraph(1,tile27X4Y4PC,tile27X4Y4G3Asym50Mean);

  TGraph *gTestGains1 = new TGraph(3,testGainVals1,tile16X4Y1D4MPC1Sigma);
  TGraph *gTestGains2 = new TGraph(4,testGainVals2,tile16X4Y1D4MPC2Sigma);
  TGraph *gTestGains3 = new TGraph(3,testGainVals3,tile16X4Y1D4MPC3Sigma);
  TGraph *gTestGains4 = new TGraph(4,testGainVals4,testSigma);

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
  TH2D *h3 = new TH2D("h3","",1,0.,450.,1,10.,25.); // 10 60
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

  g16X1Y3H6MPC2Sigma->Draw("*");
  g16X1Y3H6MPC2Sigma->SetMarkerStyle(21);
  g16X1Y3H6MPC2Sigma->SetMarkerColor(kBlue);

  g16X1Y3B4MPC2Sigma->Draw("*");
  g16X1Y3B4MPC2Sigma->SetMarkerStyle(22);
  g16X1Y3B4MPC2Sigma->SetMarkerColor(kBlue);

  g16X1Y3E5MPC2Sigma->Draw("*");
  g16X1Y3E5MPC2Sigma->SetMarkerStyle(23);
  g16X1Y3E5MPC2Sigma->SetMarkerColor(kBlue);

  g16X1Y3C7MPC2Sigma->Draw("*");
  g16X1Y3C7MPC2Sigma->SetMarkerStyle(34);
  g16X1Y3C7MPC2Sigma->SetMarkerColor(kBlue);

  g16X1Y3C7MPC2Asym25Sigma->Draw("*");
  g16X1Y3C7MPC2Asym25Sigma->SetMarkerStyle(24);
  g16X1Y3C7MPC2Asym25Sigma->SetMarkerColor(kBlue);

  g16X1Y3C7MPC2Asym50Sigma->Draw("*");
  g16X1Y3C7MPC2Asym50Sigma->SetMarkerStyle(25);
  g16X1Y3C7MPC2Asym50Sigma->SetMarkerColor(kBlue);


  TCanvas *c4 = new TCanvas("c4","Tile 16 Clipping Study",800,600);
  c4->Clear();
  c4->Divide(1,1);
  c4->cd(1);
  TH2D *h4 = new TH2D("h4","",1,250.,450.,1,10.,20.);
  h4->Draw();

  g16X1Y3H6MPC1Sigma1->Draw("*");
  g16X1Y3H6MPC1Sigma1->SetMarkerStyle(21);
  g16X1Y3H6MPC1Sigma1->SetMarkerColor(kRed);

  g16X1Y3H6MPC1Sigma2->Draw("*");
  g16X1Y3H6MPC1Sigma2->SetMarkerStyle(24);
  g16X1Y3H6MPC1Sigma2->SetMarkerColor(kBlue);

  g16X1Y3H6MPC1Sigma3->Draw("*");
  g16X1Y3H6MPC1Sigma3->SetMarkerStyle(24);
  g16X1Y3H6MPC1Sigma3->SetMarkerColor(kGreen+2);

  g16X1Y3H6MPC1Sigma4->Draw("*");
  g16X1Y3H6MPC1Sigma4->SetMarkerStyle(24);
  g16X1Y3H6MPC1Sigma4->SetMarkerColor(kMagenta+1);

  g16X1Y3H6MPC1Sigma5->Draw("*");
  g16X1Y3H6MPC1Sigma5->SetMarkerStyle(24);
  g16X1Y3H6MPC1Sigma5->SetMarkerColor(kCyan+1);

  g16X1Y3H6MPC1Sigma6->Draw("*");
  g16X1Y3H6MPC1Sigma6->SetMarkerStyle(20);
  g16X1Y3H6MPC1Sigma6->SetMarkerColor(kOrange-3);

  g16X1Y3H6MPC2Sigma7->Draw("*");
  g16X1Y3H6MPC2Sigma7->SetMarkerStyle(21);
  g16X1Y3H6MPC2Sigma7->SetMarkerColor(kRed);

  g16X1Y3H6MPC2Sigma8->Draw("*");
  g16X1Y3H6MPC2Sigma8->SetMarkerStyle(24);
  g16X1Y3H6MPC2Sigma8->SetMarkerColor(kBlue);

  g16X1Y3H6MPC2Sigma9->Draw("*");
  g16X1Y3H6MPC2Sigma9->SetMarkerStyle(24);
  g16X1Y3H6MPC2Sigma9->SetMarkerColor(kGreen+2);

  g16X1Y3H6MPC2Sigma10->Draw("*");
  g16X1Y3H6MPC2Sigma10->SetMarkerStyle(24);
  g16X1Y3H6MPC2Sigma10->SetMarkerColor(kMagenta+1);

  g16X1Y3H6MPC2Sigma11->Draw("*");
  g16X1Y3H6MPC2Sigma11->SetMarkerStyle(24);
  g16X1Y3H6MPC2Sigma11->SetMarkerColor(kCyan+1);

  g16X1Y3H6MPC2Sigma12->Draw("*");
  g16X1Y3H6MPC2Sigma12->SetMarkerStyle(20);
  g16X1Y3H6MPC2Sigma12->SetMarkerColor(kOrange-3);


  TCanvas *c5 = new TCanvas("c5","Gain Test",800,600);
  c5->Clear();
  c5->Divide(1,1);
  c5->cd(1);
  TH2D *h5 = new TH2D("h5","",1,0.,0.1,1,10.,60.);
  h5->Draw();

  gTestGains1->Draw("L*");
  gTestGains1->SetMarkerStyle(21);
  gTestGains1->SetMarkerColor(kBlue);
  gTestGains1->SetLineColor(kBlue);

  gTestGains2->Draw("L*");
  gTestGains2->SetMarkerStyle(21);
  gTestGains2->SetMarkerColor(kRed);
  gTestGains2->SetLineColor(kRed);

  gTestGains3->Draw("L*");
  gTestGains3->SetMarkerStyle(21);
  gTestGains3->SetMarkerColor(kGreen+2);
  gTestGains3->SetLineColor(kGreen+2);

  gTestGains4->Draw("L*");
  gTestGains4->SetMarkerStyle(25);
  gTestGains4->SetMarkerColor(kRed);
  gTestGains4->SetLineColor(kRed);


  /*
  TGraph *g16X1Y3H6MPC1Sigma1 = new TGraph(1,tile16X1Y3MPC1PC1,tile16X1Y3H6MPC1Sigma1);
  TGraph *g16X1Y3H6MPC1Sigma2 = new TGraph(1,tile16X1Y3MPC1PC1,tile16X1Y3H6MPC1Sigma2);
  TGraph *g16X1Y3H6MPC1Sigma3 = new TGraph(1,tile16X1Y3MPC1PC1,tile16X1Y3H6MPC1Sigma3);
  TGraph *g16X1Y3H6MPC1Sigma4 = new TGraph(1,tile16X1Y3MPC1PC1,tile16X1Y3H6MPC1Sigma4);
  TGraph *g16X1Y3H6MPC1Sigma5 = new TGraph(1,tile16X1Y3MPC1PC1,tile16X1Y3H6MPC1Sigma5);
  TGraph *g16X1Y3H6MPC1Sigma6 = new TGraph(1,tile16X1Y3MPC1PC1,tile16X1Y3H6MPC1Sigma6);
  TGraph *g16X1Y3H6MPC2Sigma7 = new TGraph(1,tile16X1Y3MPC2PC2,tile16X1Y3H6MPC2Sigma7);
  TGraph *g16X1Y3H6MPC2Sigma8 = new TGraph(1,tile16X1Y3MPC2PC2,tile16X1Y3H6MPC2Sigma8);
  TGraph *g16X1Y3H6MPC2Sigma9 = new TGraph(1,tile16X1Y3MPC2PC2,tile16X1Y3H6MPC2Sigma9);
  TGraph *g16X1Y3H6MPC2Sigma10 = new TGraph(1,tile16X1Y3MPC2PC2,tile16X1Y3H6MPC2Sigma10);
  TGraph *g16X1Y3H6MPC2Sigma11 = new TGraph(1,tile16X1Y3MPC2PC2,tile16X1Y3H6MPC2Sigma11);
  TGraph *g16X1Y3H6MPC2Sigma12 = new TGraph(1,tile16X1Y3MPC2PC2,tile16X1Y3H6MPC2Sigma12);
  */
}
