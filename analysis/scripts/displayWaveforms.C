// Display Sample Waveforms

int displayWaveforms(TString rootHistFname)
{
  gStyle->SetOptStat(0);
  gStyle->SetPalette(50);

  TFile *fa = new TFile(rootHistFname);
  assert(fa->IsOpen());

  TH2D *h[3][10];
  for(int i=0; i<10; i++)
    {
      h[0][i] = (TH2D *)fa->Get(Form("hWFLo_%d",i));
      h[1][i] = (TH2D *)fa->Get(Form("hWFMid_%d",i));
      h[2][i] = (TH2D *)fa->Get(Form("hWFHi_%d",i));
    }

  // Draw
  TCanvas *c[3];
  c[0] = new TCanvas("c0","Waveforms: 0.01 < Amplitude < 0.02",800,600);
  c[1] = new TCanvas("c1","Waveforms: 0.02 < Amplitude < 0.03",800,600);
  c[2] = new TCanvas("c2","Waveforms: Amplitude > 0.03",800,600);

  for(int i=0; i<3; i++)
    {
      c[i]->Clear();
      c[i]->Divide(5,2);
    }

  for(int i=0; i<3; i++)
    {
      for(int j=0; j<10; j++)
	{
	  c[i]->cd(j+1);
	  h[i][j]->Draw("COL");
	  h[i][j]->GetXaxis()->SetRangeUser(5800,6200); // 290015
	  //h[i]->GetXaxis()->SetRangeUser(6100,6500); // 290014
	  //h[i]->GetXaxis()->SetRangeUser(5900,6300); // 290024 290026
	  h[i][j]->GetYaxis()->SetRangeUser(-0.1,0.05);
	}
    }

  return 0;
}
