bool writeExtraText = false;
TString extraText   = "Preliminary";
float extraTextFont = 52;  // default is helvetica-italics

void drawText(const char *text, float xp, float yp, int textColor=kBlack, int textSize=18){
   TLatex *tex = new TLatex(xp,yp,text);
   //tex->SetTextFont(43);
   //   if(bold)tex->SetTextFont(43);
   tex->SetTextSize(textSize);
   tex->SetTextColor(textColor);
   tex->SetLineWidth(1);
   tex->SetNDC();
   tex->Draw();
}

void PlotMinBiasNtracks() {

  gStyle->SetOptStat(0);
  
  int centMax = 200;
  int centMin = 0;
  int numcentBins = 100;
  int HFMax = 10000;
  int HFMin = 0;
  int numHFBins = 100;
  int NtracksMin = 0;
  int numNtracksBins = 100;

  //PbPb
  //TFile* inFile = TFile::Open("MinBias_PbPb2018_centrality_Ntracks_complete.root","read");
  //TTree* myTree = (TTree*)inFile->Get("newTree");
  //TString ntracksTag = "hiNtracks";
  //int NtracksMax = 4000;
  //TString plotTitle = "PbPb (5.02 TeV)";

  //PbPb 5.02TeV
  TFile* inFile = TFile::Open("ntrack_AAMinBias_5TeV_AOD_merged.root","READ");
  TTree* myTree = (TTree*)inFile->Get("Events");
  TString ntracksTag = "recoCentrality_hiCentrality__RECO.obj.trackMultiplicity_";
  int NtracksMax = 4000;
  TString plotTitle = "PbPb (5.02 TeV)";
  TString envTag = "PbPb_5TeV";

  //pPb 5.02TeV
  //TFile* inFile = TFile::Open("ntrack_PAMinBias_5TeV_AOD_merged.root","READ");
  //TTree* myTree = (TTree*)inFile->Get("Events");
  //TString ntracksTag = "recoCentrality_hiCentrality__nTrack.obj.trackMultiplicity_";
  //int NtracksMax = 400;
  //TString plotTitle = "pPb (5.02 TeV)";

  //pPb 8.16TeV
  //TFile* inFile = TFile::Open("ntrack_PAMinBias_8TeV_AOD_merged.root","READ");
  //TTree* myTree = (TTree*)inFile->Get("Events");
  //TString ntracksTag = "recoCentrality_hiCentrality__nTrack.obj.trackMultiplicity_";
  //int NtracksMax = 400;
  //TString plotTitle = "pPb (8.16 TeV)";
  //TString envTag = "pPb_8TeV";

  //pp
  //TFile* inFile = TFile::Open("../../DataTrees/ppData2015/OniaTree_DoubleMu_PromptReco_262081_262273.root","read");
  //TTree* myTree = (TTree*)inFile->Get("myTree");
  //TString ntracksTag = "Ntracks";
  //int NtracksMax = 400;
  //TString plotTitle = "pPb (5.02 TeV)";

  //2.11e+8 events
  //int Nevents = 1e5;
  int Nevents = myTree->GetEntries();

  TCanvas* c1 = new TCanvas("c1","c1",40,40,400,400);
  c1->cd(1);
  gPad->SetLogy();
  TH1F* ntracksHist = new TH1F("ntracksHist","ntracksHist",numNtracksBins,NtracksMin,NtracksMax);
  ntracksHist->SetTitle(plotTitle);
  ntracksHist->GetXaxis()->SetTitle("Ntracks");
  ntracksHist->GetYaxis()->SetTitleOffset(1.43);
  ntracksHist->GetYaxis()->CenterTitle();
  //ntracksHist->GetYaxis()->SetTitleSize(0.058);
  ntracksHist->GetYaxis()->SetLabelSize(0.04);
  ntracksHist->GetXaxis()->SetLabelSize(0.04);
  //ntracksHist->GetXaxis()->SetRangeUser(0,1.1*NtracksMax);
  //ntracksHist->GetXaxis()->SetTitleSize(0);
  myTree->Draw(Form("%s>>ntracksHist",ntracksTag.Data()),"","",Nevents);

  TLatex *cmstex = new TLatex(0.72,0.8,"CMS");
  cmstex->SetTextFont(61);
  cmstex->SetTextSize(0.08);
  cmstex->SetNDC();
  cmstex->Draw();

  //TLatex *extratex = new TLatex(0.62,0.73,"Preliminary");
  //extratex->SetTextFont(52);
  //extratex->SetTextSize(0.06);
  //extratex->SetNDC();
  //extratex->Draw();

  c1->SaveAs(Form("Ntracks_MinBias_%s.pdf", envTag.Data() ));
  c1->SaveAs(Form("Ntracks_MinBias_%s.png", envTag.Data() ));

}
