// Plot Timing Results

void displayTiming()
{
  gStyle->SetOptStat(0);

  double modAmpX[10] = {0.0, 350.0, 400.0, 450.0, 1150.0, 1200.0, 1250.0, 1550.0, 1600.0, 1650.0};
  double modBTot[10] = {0.0, 0.324, 0.374, 0.424, 1.088, 1.138, 1.188, 1.459, 1.509, 1.559};

  double rawSigma[10] = {38.3, 54.3, 44.7, 42.8, 46.7, 45.8, 41.2, 50.3, 48.8, 45.7};
  double corSigma[10] = {32.3, 51.0, 42.3, 41.0, 47.2, 45.5, 48.2, 49.2, 48.2, 46.9};
  double rawSigmaCut[10] = {36.1, 40.6, 39.0, 38.4, 42.8, 44.6, 45.6, 46.8, 51.1, 43.8};
  double corSigmaCut[10] = {32.4, 41.5, 36.5, 35.6, 41.1, 45.0, 46.0, 45.9, 48.2, 40.8};
  //double rawSigmaOneGaus[10] = {49.4, 60.6, 51.0, 48.5, 51.6, 51.9, 53.7, 60.7, 55.4, 52.5};
  //double rawSigmaCutOneGaus[10] = {41.6, 44.1, 42.3, 42.5, 48.4, 49.1, 50.0, 54.6, 57.6, 45.6};
  double rawSigmaCrystalBall[10] = {41.2, 58.5, 50.0, 45.3, 46.0, 49.2, 47.7, 50.0, 50.6, 50.4};
  double corSigmaCrystalBall[10] = {39.5, 53.6, 46.4, 44.8, 49.2, 48.5, 47.6, 49.8, 50.0, 50.5};
  double rawSigmaCutCrystalBall[10] = {39.3, 43.1, 42.1, 41.0, 47.6, 46.9, 45.2, 47.4, 53.5, 44.9};
  double corSigmaCutCrystalBall[10] = {35.7, 46.2, 39.2, 38.2, 46.2, 47.9, 48.1, 47.7, 49.7, 44.9};
  // Numbers = 25, 26, 27, 28, 29, 30, 31, 32, 33, 34
  // Cut Values = 0.07, 0.04, 0.04, 0.055, 0.0175, 0.0175, 0.022, 0.0075, 0.01, 0.015
  // Correction Values = {-900.0, 2128.16, 1000.0, -592.765, -438.25, -1361.4, -1000.0, -2800.0, -2054.73, -2000.0};
  
  // These numbers taken with restricted search window on HRPPD signal
  //double rawSigma[10] = {38.3, 61.1, 44.9, 37.7, 46.0, 46.2, 50.5, 49.4, 46.7, 45.2};
  //double corSigma[10] = {39.5, 64.4, 40.2, 40.2, 46.5, 45.6, 54.7, 46.6, 46.3, 48.2};
  //double rawSigmaCut[10] = {38.8, 46.3, 38.7, 34.9, 44.5, 45.1, 45.0, 44.2, 45.3, 46.4};
  //double corSigmaCut[10] = {36.5, 44.1, 34.2, 36.6, 45.1, 44.9, 46.7, 42.8, 43.6, 40.4};


  TGraph *gRawSigmaModAmpX = new TGraph(10,modAmpX,rawSigma);
  TGraph *gCorSigmaModAmpX = new TGraph(10,modAmpX,corSigma);
  TGraph *gRawSigmaCutModAmpX = new TGraph(10,modAmpX,rawSigmaCut);
  TGraph *gCorSigmaCutModAmpX = new TGraph(10,modAmpX,corSigmaCut);
  //TGraph *gRawSigmaModAmpXOneGaus = new TGraph(10,modAmpX, rawSigmaOneGaus);
  //TGraph *gRawSigmaCutModAmpXOneGaus = new TGraph(10,modAmpX, rawSigmaCutOneGaus);
  TGraph *gRawSigmaModAmpXCB = new TGraph(10,modAmpX,rawSigmaCrystalBall);
  TGraph *gCorSigmaModAmpXCB = new TGraph(10,modAmpX,corSigmaCrystalBall);
  TGraph *gRawSigmaCutModAmpXCB = new TGraph(10,modAmpX,rawSigmaCutCrystalBall);
  TGraph *gCorSigmaCutModAmpXCB = new TGraph(10,modAmpX,corSigmaCutCrystalBall);

  TCanvas *c1 = new TCanvas("c1","Timing Resolution",800,600);
  c1->Clear();
  c1->Divide(1,1);
  c1->cd(1);
  TH2D *h1 = new TH2D("h1","Time Resolution Vs Magnet Current and HV Settings;Magnet Current [A];Timing Resolution [ps]",1,-100.,1700.0,1,20.,80.);
  h1->Draw();

  gRawSigmaModAmpX->Draw("*");
  gRawSigmaModAmpX->SetMarkerStyle(20);
  gRawSigmaModAmpX->SetMarkerColor(kBlue);

  gCorSigmaModAmpX->Draw("*");
  gCorSigmaModAmpX->SetMarkerStyle(24);
  gCorSigmaModAmpX->SetMarkerColor(kBlue);

  gRawSigmaModAmpXCB->Draw("*");
  gRawSigmaModAmpXCB->SetMarkerStyle(21);
  gRawSigmaModAmpXCB->SetMarkerColor(kRed);

  gCorSigmaModAmpXCB->Draw("*");
  gCorSigmaModAmpXCB->SetMarkerStyle(25);
  gCorSigmaModAmpXCB->SetMarkerColor(kRed);

  TLegend *leg1 = new TLegend(0.15,0.88,0.55,0.68);
  leg1->SetBorderSize(1);
  leg1->AddEntry(gRawSigmaModAmpX,"Raw Timing Resolution: Two Gaussian Fit","p");
  leg1->AddEntry(gCorSigmaModAmpX,"Corrected Timing Resolution: Two Gaussian Fit","p");
  leg1->AddEntry(gRawSigmaModAmpXCB,"Raw Timing Resolution: Crystal Ball Fit","p");
  leg1->AddEntry(gCorSigmaModAmpXCB,"Corrected Timing Resolution: Crystal Ball Fit","p");
  leg1->Draw();


  TCanvas *c2 = new TCanvas("c2","Timing Resolution (Amplitude Cut)",800,600);
  c2->Clear();
  c2->Divide(1,1);
  c2->cd(1);
  TH2D *h2 = new TH2D("h2","Time Resolution Vs Magnet Current and HV Settings (Amplitude Cut);Magnet Current [A];Timing Resolution [ps]",1,-100.,1700.0,1,20.,80.);
  h2->Draw();

  gRawSigmaCutModAmpX->Draw("*");
  gRawSigmaCutModAmpX->SetMarkerStyle(20);
  gRawSigmaCutModAmpX->SetMarkerColor(kBlue);

  gCorSigmaCutModAmpX->Draw("*");
  gCorSigmaCutModAmpX->SetMarkerStyle(24);
  gCorSigmaCutModAmpX->SetMarkerColor(kBlue);

  gRawSigmaCutModAmpXCB->Draw("*");
  gRawSigmaCutModAmpXCB->SetMarkerStyle(21);
  gRawSigmaCutModAmpXCB->SetMarkerColor(kRed);

  gCorSigmaCutModAmpXCB->Draw("*");
  gCorSigmaCutModAmpXCB->SetMarkerStyle(25);
  gCorSigmaCutModAmpXCB->SetMarkerColor(kRed);

  TLegend *leg2 = new TLegend(0.15,0.88,0.55,0.68);
  leg2->SetBorderSize(1);
  leg2->AddEntry(gRawSigmaCutModAmpX,"Raw Timing Resolution: Two Gaussian Fit","p");
  leg2->AddEntry(gCorSigmaCutModAmpX,"Corrected Timing Resolution: Two Gaussian Fit","p");
  leg2->AddEntry(gRawSigmaCutModAmpXCB,"Raw Timing Resolution: Crystal Ball Fit","p");
  leg2->AddEntry(gCorSigmaCutModAmpXCB,"Corrected Timing Resolution: Crystal Ball Fit","p");
  leg2->Draw();


  // B-Field
  TGraph *gRawSigmaModBTot = new TGraph(10,modBTot,rawSigma);
  TGraph *gCorSigmaModBTot = new TGraph(10,modBTot,corSigma);
  TGraph *gRawSigmaCutModBTot = new TGraph(10,modBTot,rawSigmaCut);
  TGraph *gCorSigmaCutModBTot = new TGraph(10,modBTot,corSigmaCut);
  //TGraph *gRawSigmaModBTotOneGaus = new TGraph(10,modBTot, rawSigmaOneGaus);
  //TGraph *gRawSigmaCutModBTotOneGaus = new TGraph(10,modBTot, rawSigmaCutOneGaus);
  TGraph *gRawSigmaModBTotCB = new TGraph(10,modBTot,rawSigmaCrystalBall);
  TGraph *gCorSigmaModBTotCB = new TGraph(10,modBTot,corSigmaCrystalBall);
  TGraph *gRawSigmaCutModBTotCB = new TGraph(10,modBTot,rawSigmaCutCrystalBall);
  TGraph *gCorSigmaCutModBTotCB = new TGraph(10,modBTot,corSigmaCutCrystalBall);

  TCanvas *c3 = new TCanvas("c3","Timing Resolution",800,600);
  c3->Clear();
  c3->Divide(1,1);
  c3->cd(1);
  TH2D *h3 = new TH2D("h3","Time Resolution Vs B-Field and HV Settings;B-Field [T];Timing Resolution [ps]",1,-0.25,2.0,1,20.,80.);
  h3->Draw();

  gRawSigmaModBTot->Draw("*");
  gRawSigmaModBTot->SetMarkerStyle(20);
  gRawSigmaModBTot->SetMarkerColor(kBlue);

  gCorSigmaModBTot->Draw("*");
  gCorSigmaModBTot->SetMarkerStyle(24);
  gCorSigmaModBTot->SetMarkerColor(kBlue);

  gRawSigmaModBTotCB->Draw("*");
  gRawSigmaModBTotCB->SetMarkerStyle(21);
  gRawSigmaModBTotCB->SetMarkerColor(kRed);

  gCorSigmaModBTotCB->Draw("*");
  gCorSigmaModBTotCB->SetMarkerStyle(25);
  gCorSigmaModBTotCB->SetMarkerColor(kRed);

  TLegend *leg3 = new TLegend(0.15,0.88,0.55,0.68);
  leg3->SetBorderSize(1);
  leg3->AddEntry(gRawSigmaModBTot,"Raw Timing Resolution: Two Gaussian Fit","p");
  leg3->AddEntry(gCorSigmaModBTot,"Corrected Timing Resolution: Two Gaussian Fit","p");
  leg3->AddEntry(gRawSigmaModBTotCB,"Raw Timing Resolution: Crystal Ball Fit","p");
  leg3->AddEntry(gCorSigmaModBTotCB,"Corrected Timing Resolution: Crystal Ball Fit","p");
  leg3->Draw();


  TCanvas *c4 = new TCanvas("c4","Timing Resolution (Amplitude Cut)",800,600);
  c4->Clear();
  c4->Divide(1,1);
  c4->cd(1);
  TH2D *h4 = new TH2D("h4","Time Resolution Vs B-Field and HV Settings (Amplitude Cut);B-Field [T];Timing Resolution [ps]",1,-0.25,2.0,1,20.,80.);
  h4->Draw();

  gRawSigmaCutModBTot->Draw("*");
  gRawSigmaCutModBTot->SetMarkerStyle(20);
  gRawSigmaCutModBTot->SetMarkerColor(kBlue);

  gCorSigmaCutModBTot->Draw("*");
  gCorSigmaCutModBTot->SetMarkerStyle(24);
  gCorSigmaCutModBTot->SetMarkerColor(kBlue);

  gRawSigmaCutModBTotCB->Draw("*");
  gRawSigmaCutModBTotCB->SetMarkerStyle(21);
  gRawSigmaCutModBTotCB->SetMarkerColor(kRed);

  gCorSigmaCutModBTotCB->Draw("*");
  gCorSigmaCutModBTotCB->SetMarkerStyle(25);
  gCorSigmaCutModBTotCB->SetMarkerColor(kRed);

  TLegend *leg4 = new TLegend(0.15,0.88,0.55,0.68);
  leg4->SetBorderSize(1);
  leg4->AddEntry(gRawSigmaCutModBTot,"Raw Timing Resolution: Two Gaussian Fit","p");
  leg4->AddEntry(gCorSigmaCutModBTot,"Corrected Timing Resolution: Two Gaussian Fit","p");
  leg4->AddEntry(gRawSigmaCutModBTotCB,"Raw Timing Resolution: Crystal Ball Fit","p");
  leg4->AddEntry(gCorSigmaCutModBTotCB,"Corrected Timing Resolution: Crystal Ball Fit","p");
  leg4->Draw();
}
