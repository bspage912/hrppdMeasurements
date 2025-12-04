// Display Sample Waveforms

int displayWaveforms(TString rootHistFname)
{
  gStyle->SetOptStat(0);
  gStyle->SetPalette(50);

  TFile *fa = new TFile(rootHistFname);
  assert(fa->IsOpen());

  TH2D *h[10];
  for(int i=0; i<10; i++)
    {
      h[i] = (TH2D *)fa->Get(Form("hWF_%d",i));
    }

  // Draw
  TCanvas *c = new TCanvas("c","Waveforms",800,600);
  c->Clear();
  c->Divide(5,2);
  for(int i=0; i<10; i++)
    {
      c->cd(i+1);
      h[i]->Draw("COL");
      h[i]->GetXaxis()->SetRangeUser(5800,6200); // 290015
      //h[i]->GetXaxis()->SetRangeUser(6100,6500); // 290014
      //h[i]->GetXaxis()->SetRangeUser(5900,6300); // 290024 290026
      h[i]->GetYaxis()->SetRangeUser(-0.1,0.05);
    }

  return 0;
}
