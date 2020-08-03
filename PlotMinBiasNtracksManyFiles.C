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

void PlotMinBiasNtracksManyFiles() {

  gStyle->SetOptStat(0);
  
  int NtracksMin = 0;
  int numNtracksBins = 100;

  //PbPb 5.02TeV
/*  TString directory = "/eos/cms/store/group/phys_heavyions/dileptons/jjay/NtracksData/Ntracks_HIRun2018A_PromptReco_v3_AOD_20200702_PbPb_nomask/HIMinimumBiasReducedFormat1/crab_Ntracks_HIRun2018A_PromptReco_v3_AOD_20200702_PbPb_nomask/200702_171850/0000/";
  TString inFileName = "ntrack_AAMinBias_5TeV_AOD_";
  int nFiles = 72;//72;
  TString ntracksTag = "recoCentrality_hiCentrality__RECO.obj.trackMultiplicity_";
  int NtracksMax = 4000;
  TString plotTitle = "PbPb (5.02 TeV)";
  TString envTag = "PbPb_5TeV";
  TString outfName = Form("Ntracks_MinBias_%s_ManyFiles_prettyBins", envTag.Data());
  int arraySize = 201;
*/
/*  float NtracksBins[201]; //100 bins from 0 to 400, 100 bins from 400 to 4000
  for (int i=0; i<201; i++) {
    if (i<101) NtracksBins[i] = 4*i;
    else NtracksBins[i] = 400 + 36*(i-100);
  }
  numNtracksBins = sizeof(NtracksBins)/sizeof(float)-1;
*/
  //pPb 5.02TeV
  TString directory = "/eos/cms/store/group/phys_heavyions/dileptons/jjay/NtracksData/Ntracks_HIRun2016D_PromptReco_v5_AOD_20200625_pPb/PAMinimumBias1/crab_Ntracks_HIRun2016D_PromptReco_v5_AOD_20200625_pPb/200625_192742/0000/";
  TString inFileName = "ntrack_PAMinBias_5TeV_AOD_";
  int nFiles = 199;//199
  TString ntracksTag = "recoCentrality_hiCentrality__nTrack.obj.trackMultiplicity_";
  int NtracksMax = 400;
  TString plotTitle = "pPb (5.02 TeV)";
  TString envTag = "pPb_5TeV";
  TString outfName = Form("Ntracks_MinBias_%s_ManyFiles_prettyBins", envTag.Data());
  int arraySize = 140;

  //pPb 8.16TeV
/*  TString directory = "/eos/cms/store/group/phys_heavyions/dileptons/jjay/NtracksData/Ntracks_HIRun2016C_PromptReco_v5_AOD_20200625_pPb/PAMinimumBias7/crab_Ntracks_HIRun2016C_PromptReco_v5_AOD_20200625_pPb/200625_190444/0000/";
  TString inFileName = "ntrack_PAMinBias_8TeV_AOD_";
  int nFiles = 793;//793
  TString ntracksTag = "recoCentrality_hiCentrality__nTrack.obj.trackMultiplicity_";
  int NtracksMax = 400;
  TString plotTitle = "pPb (8.16 TeV)";
  TString envTag = "pPb_8TeV";
  TString outfName = Form("Ntracks_MinBias_%s_ManyFiles_prettyBins", envTag.Data());
  int arraySize = 140;
*/
  //pp
/*  TString directory = "/eos/cms/store/group/phys_heavyions/dileptons/jjay/NtracksData/Ntracks_Run2017G_AOD_20200729_1635_pp/HIZeroBias2/crab_Ntracks_Run2017G_AOD_20200729_1635_pp/200729_233525/0000/";
  TString inFileName = "ntrack_PPMinBias_5TeV_AOD_";
  int nFiles = 57;//57
  TString ntracksTag = "recoCentrality_hiCentrality__nTrack.obj.trackMultiplicity_";
  int NtracksMax = 400;
  TString plotTitle = "pp (5.02 TeV)";
  TString envTag = "pp_5TeV";
  TString outfName = Form("Ntracks_ZeroBias_%s_ManyFiles_prettyBins", envTag.Data());
  int arraySize = 101;
*/
  float NtracksBins[arraySize]; //make bins equally spaced on a log scale starting at 20, but 1 track per bin below 20. 
  cout << "NtracksBins[" << arraySize << "] = {";
  float M = NtracksMax;
  float N = (float)arraySize;
  float a = (M-N+1)/((N-1)*(N-2));
/*  for (int i=0; i<arraySize; i++) {
    if (i<20) NtracksBins[i] = i;
    else if (i<40) NtracksBins[i] = 4*(i-20)+20;
    else if (i<60) NtracksBins[i] = 100+8*(i-40);
    else NtracksBins[i] = 260*pow(M/260,(i-60)/(N-60));
    //NtracksBins[i] = pow(NtracksMax,(float)i/(float)arraySize);
    //NtracksBins[i] = i*( 1+39/((float)arraySize*2)*(i+1) );
    //NtracksBins[i] = (float)i * ((i-1)*a + 1);
    cout << NtracksBins[i] << ", ";
  }*/
/*  for (int i=0; i<arraySize; i++) {//pp
    if (i<30) NtracksBins[i] = i;
    else NtracksBins[i] = 30*pow(M/30,(i-30)/(N-30));
    cout << NtracksBins[i] << ", ";
  }*/
/*  for (int i=0; i<arraySize; i++) {//pPb
    if (i<30) NtracksBins[i] = i;
    else if (i<40) NtracksBins[i] = 30+2*(i-30);
    else NtracksBins[i] = 50*pow(M/50,(i-40)/(N-40));
    cout << NtracksBins[i] << ", ";
  }
*/
  float C = 100*(N-2)/(99*(N-1));//Don't use 100 bins, unless it's pp.
  float D = log10(M/(N-1))/((N-2)*log10(C));
  cout << "M = " << M << endl;
  cout << "N = " << N << endl;
  cout << "C = " << C << endl;
  cout << "D = " << D << endl;
  for (int i=0; i<arraySize; i++) {
    NtracksBins[i] = floor(i*pow(C,D*(i-1)));
    cout << NtracksBins[i] << ", ";
  }
  cout << "}" << endl;
  numNtracksBins = sizeof(NtracksBins)/sizeof(float)-1;

  TCanvas* c1 = new TCanvas("c1","c1",40,40,400,400);
  c1->cd(1);
  gPad->SetLogy();
  gPad->SetLogx();
  TH1F* ntracksHist = new TH1F("ntracksHist","ntracksHist",numNtracksBins,NtracksBins);//For PbPb
  ntracksHist->SetTitle(plotTitle);
  ntracksHist->GetXaxis()->SetTitle("Ntracks");
  ntracksHist->GetYaxis()->SetTitleOffset(1.43);
  ntracksHist->GetYaxis()->CenterTitle();
  //ntracksHist->GetYaxis()->SetTitleSize(0.058);
  ntracksHist->GetYaxis()->SetLabelSize(0.04);
  ntracksHist->GetXaxis()->SetLabelSize(0.04);
  //ntracksHist->GetXaxis()->SetRangeUser(0,1.1*NtracksMax);
  //ntracksHist->GetXaxis()->SetTitleSize(0);

  for (int i=1; i<nFiles+1; i++) {
    TString fnametmp = Form("%s%s%i.root",directory.Data(),inFileName.Data(),i);
    TFile* inFile = TFile::Open(fnametmp,"READ");
    cout << "Reading file " << fnametmp << endl;
    TTree* myTree = (TTree*)inFile->Get("Events");
    TH1F* htmp = new TH1F("htmp","htmp",numNtracksBins,NtracksBins);//For PbPb
    //2.11e+8 events
    //int Nevents = 1e5;
    int Nevents = myTree->GetEntries();
    myTree->Draw(Form("%s>>htmp",ntracksTag.Data()),"","",Nevents);
    ntracksHist->Add(htmp);
    delete htmp;
    delete myTree;
    inFile->Close();
    delete inFile;
  }

  //Rescale smaller PbPb bins from 0 to 400 Ntracks (The first 100 bins).
  //for (int i=0; i<100; i++) {
  //  int count = ntracksHist->GetBinContent(i+1);
  //  ntracksHist->SetBinContent(i+1,count*9);
  //}

  c1->cd();
  cout << "Plotting ntracks distribution..." << endl;
  ntracksHist->Scale(1,"width");
  ntracksHist->Draw();

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

  c1->SaveAs(Form("%s.pdf",outfName.Data() ));
  c1->SaveAs(Form("%s.png",outfName.Data() ));

  cout << endl << "Here's what's in memory: " << endl;
  gDirectory->ls("-m");

  TFile* outf = new TFile(Form("%s.root",outfName.Data()),"recreate");
  ntracksHist->Write();
  c1->Write();
  outf->Close();
}
