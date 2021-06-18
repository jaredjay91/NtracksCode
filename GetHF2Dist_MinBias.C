
void GetHF2Dist_MinBias() {

  gStyle->SetOptStat(0);

  int HF2Max = 5000;
  int HF2Min = 0;
  int numHF2Bins = 100;
  int numFiles = 72;//72

  TString directory = "/eos/cms/store/group/phys_heavyions/dileptons/jjay/NtracksData/Ntracks_HIRun2018A_PromptReco_v3_AOD_20200702_PbPb_nomask/HIMinimumBiasReducedFormat1/crab_Ntracks_HIRun2018A_PromptReco_v3_AOD_20200702_PbPb_nomask/200702_171850/0000/";
  TString HFplusTag = "recoCentrality_hiCentrality__RECO.obj.etHFtowerSumPlus_";
  TString HFminusTag = "recoCentrality_hiCentrality__RECO.obj.etHFtowerSumMinus_";

  TCanvas* c1 = new TCanvas("c1","c1",40,40,400,400);
  TCanvas* ctemp = new TCanvas("ctemp","ctemp",440,40,400,400);
  c1->cd();
  gPad->SetLogy();

  cout << "Creating HF2 integrated histogram..." << endl;
  TH1F* HF2Hist = new TH1F("HF2Hist","HF2Hist",numHF2Bins,HF2Min,HF2Max);
  ctemp->cd();
  HF2Hist->SetTitle("");
  HF2Hist->GetXaxis()->SetTitle("N_{tracks}");
  HF2Hist->SetMaximum(1e7);
  HF2Hist->SetMinimum(100);

  for (int fileNum=1; fileNum<=numFiles; fileNum++) {
    TString fileName = Form("%sntrack_AAMinBias_5TeV_AOD_%i.root", directory.Data(), fileNum);
    //cout << "Reading file " << fileName << endl;
    TFile* inFile = TFile::Open(fileName,"READ");
    TTree* myTree = (TTree*)inFile->Get("Events");

    TH1F* hInttmp = new TH1F("hInttmp","hInttmp",numHF2Bins,HF2Min,HF2Max);
    ctemp->cd();
    myTree->Draw(Form("(%s+%s)>>hInttmp",HFplusTag.Data(),HFminusTag.Data()));
    HF2Hist->Add(hInttmp);

    delete hInttmp;
    delete myTree;
    inFile->Close();
    delete inFile;
  }
  c1->cd();
  HF2Hist->Draw();

  TString outfName = "HF2_PbPb_502TeV_MinBias_fromCrab_2020_11_03";
  c1->SaveAs(Form("%s.pdf",outfName.Data()));
  c1->SaveAs(Form("%s.png",outfName.Data()));

  cout << endl << "Here's what's in memory: " << endl;
  gDirectory->ls("-m");

  TFile* outf = new TFile(Form("%s.root",outfName.Data()),"recreate");
  HF2Hist->Write();
  c1->Write();
  outf->Close();

}
