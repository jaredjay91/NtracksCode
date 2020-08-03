

void PlotMinBiasDists() {

  int centMax = 200;
  int centMin = 0;
  int numcentBins = 100;
  int HFMax = 10000;
  int HFMin = 0;
  int numHFBins = 100;
  int NtracksMax = 4000;
  int NtracksMin = 0;
  int numNtracksBins = 100;

  TFile* inFile = TFile::Open("MinBias_PbPb2018_centrality_Ntracks_complete.root","read");
  TTree* myTree = (TTree*)inFile->Get("newTree");

  //2.11e+8 events
  //int Nevents = 1e6;
  int Nevents = myTree->GetEntries();

  TCanvas* c1 = new TCanvas("c1","c1",40,40,1200,400);
  c1->Divide(3);

  c1->cd(1);
  gPad->SetLogy();
  TH1F* centHist = new TH1F("centHist","centHist",numcentBins,centMin,centMax);
  myTree->Draw("hiBin>>centHist","","",Nevents);
  centHist->SetTitle("Centrality Bin");
  centHist->GetXaxis()->SetTitle("Centrality Bin");

  c1->cd(2);
  gPad->SetLogy();
  TH1F* hfHist = new TH1F("hfHist","hfHist",numHFBins,HFMin,HFMax);
  myTree->Draw("hiHF>>hfHist","","",Nevents);
  hfHist->SetTitle("HF");
  hfHist->GetXaxis()->SetTitle("HF");

  c1->cd(3);
  gPad->SetLogy();
  TH1F* ntracksHist = new TH1F("ntracksHist","ntracksHist",numNtracksBins,NtracksMin,NtracksMax);
  myTree->Draw("hiNtracks>>ntracksHist","","",Nevents);
  ntracksHist->SetTitle("Ntracks");
  ntracksHist->GetXaxis()->SetTitle("Ntracks");

  c1->SaveAs("CentralityDistributions_MinBias.pdf");
  c1->SaveAs("CentralityDistributions_MinBias.png");

}
