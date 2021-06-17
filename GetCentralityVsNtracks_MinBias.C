
float hfBin[201] = {0, 10.5072, 11.2099, 11.8364, 12.478, 13.1194, 13.7623, 14.4081, 15.0709, 15.7532, 16.4673, 17.1881, 17.923, 18.673, 19.4865, 20.3033, 21.1536, 22.0086, 22.9046, 23.8196, 24.7924, 25.8082, 26.8714, 27.9481, 29.0828, 30.2757, 31.5043, 32.8044, 34.1572, 35.6142, 37.1211, 38.6798, 40.3116, 42.0398, 43.8572, 45.6977, 47.6312, 49.6899, 51.815, 54.028, 56.3037, 58.7091, 61.2024, 63.8353, 66.5926, 69.3617, 72.2068, 75.2459, 78.3873, 81.5916, 84.9419, 88.498, 92.1789, 95.9582, 99.8431, 103.739, 107.78, 111.97, 116.312, 120.806, 125.46, 130.269, 135.247, 140.389, 145.713, 151.212, 156.871, 162.729, 168.762, 174.998, 181.424, 188.063, 194.907, 201.942, 209.19, 216.683, 224.37, 232.291, 240.43, 248.807, 257.416, 266.256, 275.348, 284.668, 294.216, 304.053, 314.142, 324.488, 335.101, 345.974, 357.116, 368.547, 380.283, 392.29, 404.564, 417.122, 429.968, 443.116, 456.577, 470.357, 484.422, 498.78, 513.473, 528.479, 543.813, 559.445, 575.411, 591.724, 608.352, 625.344, 642.686, 660.361, 678.371, 696.749, 715.485, 734.608, 754.068, 773.846, 794.046, 814.649, 835.608, 856.972, 878.719, 900.887, 923.409, 946.374, 969.674, 993.435, 1017.62, 1042.21, 1067.28, 1092.72, 1118.64, 1144.96, 1171.71, 1198.98, 1226.67, 1254.82, 1283.46, 1312.65, 1342.21, 1372.27, 1402.85, 1433.93, 1465.49, 1497.62, 1530.29, 1563.49, 1597.22, 1631.49, 1666.37, 1701.8, 1737.75, 1774.35, 1811.51, 1849.29, 1887.75, 1926.79, 1966.6, 2006.97, 2047.99, 2089.71, 2132.1, 2175.23, 2219.17, 2263.72, 2309.2, 2355.43, 2402.47, 2450.33, 2499.05, 2548.66, 2599.16, 2650.59, 2703.03, 2756.32, 2810.75, 2866.27, 2922.91, 2980.54, 3039.47, 3099.53, 3160.98, 3223.66, 3287.71, 3353.18, 3420.34, 3489.13, 3559.72, 3632.06, 3706.18, 3782.42, 3860.78, 3941.42, 4024.52, 4110.27, 4199.4, 4292.8, 4394.49, 4519.52, 5199.95};

void GetCentralityVsNtracks_MinBias() {

  gStyle->SetOptStat(0);

  int centBins[8] = {0,10,20,30,40,50,60,100};
  int hiBins[8] = {0,20,40,60,80,100,120,200};
  float hiBinsFloat[8] = {0,20,40,60,80,100,120,200};
  //int centBins[9] = {0,5,10,20,30,40,50,75,100};
  //int hiBins[9] = {0,10,20,40,60,80,100,150,200};
  //float hiBinsFloat[9] = {0,10,20,40,60,80,100,150,200};
  //int centBins[7] = {0,10,20,30,40,50,100};
  //int hiBins[7] = {0,20,40,60,80,100,200};
  //float hiBinsFloat[7] = {0,20,40,60,80,100,200};
  //int centBins[4] = {0,20,40,100};
  //int hiBins[4] = {0,40,80,200};
  //float hiBinsFloat[4] = {0,40,80,200};

  const int numBins = (int)sizeof(hiBins)/sizeof(int)-1;

  int NtracksMax = 3500;
  int NtracksMin = 0;
  int numNtracksBins = 100;
  int numFiles = 72;//72

  TString directory = "/eos/cms/store/group/phys_heavyions/dileptons/jjay/NtracksData/Ntracks_HIRun2018A_PromptReco_v3_AOD_20200702_PbPb_nomask/HIMinimumBiasReducedFormat1/crab_Ntracks_HIRun2018A_PromptReco_v3_AOD_20200702_PbPb_nomask/200702_171850/0000/";
  TString ntracksTag = "recoCentrality_hiCentrality__RECO.obj.trackMultiplicity_";
  TString HFplusTag = "recoCentrality_hiCentrality__RECO.obj.etHFtowerSumPlus_";
  TString HFminusTag = "recoCentrality_hiCentrality__RECO.obj.etHFtowerSumMinus_";

  TH1F* HF2Hist = new TH1F("HF2Hist","HF2Hist",200,0,5000);

  TH1F* ntracksHist[numBins];
  TString histLabel[numBins];
  TCanvas* c[numBins];

  for(int i=0; i<numBins; i++) {
    ntracksHist[i] = new TH1F(Form("ntracksHist[%i]",i),Form("ntracksHist[%i]",i),numNtracksBins,NtracksMin,NtracksMax);
    ntracksHist[i]->SetLineColor(i+2);
    ntracksHist[i]->SetFillColor(i+2);
    ntracksHist[i]->SetFillColorAlpha(i+2, 0.25);
  }

  TCanvas* c1 = new TCanvas("c1","c1",40,40,400,400);
  TCanvas* ctemp = new TCanvas("ctemp","ctemp",440,40,400,400);
  c1->cd();
  gPad->SetLogy();

  cout << "Creating ntracks integrated histogram..." << endl;
  TH1F* ntracksIntHist = new TH1F("ntracksIntHist","ntracksIntHist",numNtracksBins,NtracksMin,NtracksMax);
  ctemp->cd();
  ntracksIntHist->SetTitle("");
  ntracksIntHist->GetXaxis()->SetTitle("N_{tracks}");
  ntracksIntHist->SetMaximum(1e7);
  ntracksIntHist->SetMinimum(100);

  for(int i=0; i<numBins; i++) {
    for (int fileNum=1; fileNum<=numFiles; fileNum++) {
      TString fileName = Form("%sntrack_AAMinBias_5TeV_AOD_%i.root", directory.Data(), fileNum);
      //cout << "Reading file " << fileName << endl;
      TFile* inFile = TFile::Open(fileName,"READ");
      TTree* myTree = (TTree*)inFile->Get("Events");
      TString centCut = Form("(%s+%s)>=%f && (%s+%s)<%f", HFplusTag.Data(), HFminusTag.Data(), hfBin[200-hiBins[i+1]], HFplusTag.Data(), HFminusTag.Data(), hfBin[200-hiBins[i]]);
      //cout << centCut << endl;

      TH1F* hInttmp = new TH1F("hInttmp","hInttmp",numNtracksBins,NtracksMin,NtracksMax);
      if (i==0) {
        ctemp->cd();
        myTree->Draw(Form("%s>>hInttmp",ntracksTag.Data()));
        ntracksIntHist->Add(hInttmp);
      }

      TH1F* htmp = new TH1F("htmp","htmp",numNtracksBins,NtracksMin,NtracksMax);
      ctemp->cd();
      myTree->Draw(Form("%s>>htmp",ntracksTag.Data()),centCut.Data());
      ntracksHist[i]->Add(htmp);

      delete hInttmp;
      delete htmp;
      delete myTree;
      inFile->Close();
      delete inFile;
    }
    c1->cd();
    if (i==0) {
      ntracksIntHist->Draw();
    }
    ntracksHist[i]->Draw("same");
    histLabel[i] = Form("%i-%i%: avg=%i",centBins[i],centBins[i+1],(int)ntracksHist[i]->GetMean());
cout << histLabel[i] << " +/- " << ntracksHist[i]->GetRMS() << endl;
    //cout << histLabel[i] << " +/- " << (ntracksHist[i]->GetRMS()/sqrt(ntracksHist[i]->GetEntries())) << endl;
  }

//  cout << "Creating HF histogram..." << endl;
//  TCanvas* c0 = new TCanvas("c0","c0",40,400,400,400);
//  TH1F* HF2Hist = new TH1F("HF2Hist","HF2Hist",200,0,5000);
//  myTree->Draw(Form("(%s+%s)>>HF2Hist",HFplusTag.Data(),HFminusTag.Data()));

  c1->cd();

  TLegend* fitleg = new TLegend(0.6,0.65,0.9,0.9); fitleg->SetTextSize(10);
  fitleg->SetTextFont(43);
  //fitleg->SetBorderSize(0);
  for(int i=0; i<numBins; i++) {
    fitleg->AddEntry(ntracksHist[i],histLabel[i],"l");
  }
  fitleg->Draw("same");

  TString outfName = "NtracksInCentralityBins_MinBias_fromCrab_2020_11_03";
  c1->SaveAs(Form("%s.pdf",outfName.Data()));
  c1->SaveAs(Form("%s.png",outfName.Data()));

  cout << endl << "Here's what's in memory: " << endl;
  gDirectory->ls("-m");

  TFile* outf = new TFile(Form("%s.root",outfName.Data()),"recreate");
  ntracksIntHist->Write();
  for(int i=0; i<numBins; i++) {
    ntracksHist[i]->Write();
  }
  c1->Write();
  outf->Close();

}
