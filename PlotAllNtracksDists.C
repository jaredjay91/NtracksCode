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

//original colors:
//int colorAA5 = 1;
//int colorPA8 = 2;
//int colorPA5 = kGreen+3;
//int colorPP5 = 4;
//int colorAA5cent20 = 6;

//Colors to match the efficiency plots.
int colorAA5 = kRed;
int colorPA8 = kBlue;
int colorPA5 = kGreen+1;
int colorPP5 = kBlack;
int colorAA5cent20 = 6;

int linewidth = 1;

void PlotAllNtracksDists() {

  gStyle->SetOptStat(0);

  //PbPb 5.02TeV
  TFile* fAA5 = TFile::Open("Ntracks_MinBias_PbPb_5TeV_ManyFiles_prettyBins.root","READ");
  //TFile* fAA5 = TFile::Open("Ntracks_MinBias_PbPb_5TeV_ManyFilesMoreBins.root","READ");
  TH1F* hAA5 = (TH1F*)fAA5->Get("ntracksHist");
  hAA5->SetLineColor(colorAA5);
  hAA5->SetLineWidth(linewidth);
  int nAA5 = hAA5->GetEntries();
  hAA5->Scale(1.0/((double)nAA5));
  cout << "nAA5 = " << nAA5 << endl;

  //pPb 8.16TeV
  TFile* fPA8 = TFile::Open("Ntracks_MinBias_pPb_8TeV_ManyFiles_prettyBins.root","READ");
  TH1F* hPA8 = (TH1F*)fPA8->Get("ntracksHist");
  hPA8->SetLineColor(colorPA8);
  hPA8->SetLineWidth(linewidth);
  int nPA8 = hPA8->GetEntries();
  hPA8->Scale(1.0/((double)nPA8));
  cout << "nPA8 = " << nPA8 << endl;
  //hPA8->GetXaxis()->SetRange(1,65);//for lower limit of 2e-5

  //pPb 5.02TeV
  TFile* fPA5 = TFile::Open("Ntracks_MinBias_pPb_5TeV_ManyFiles_prettyBins.root","READ");
  TH1F* hPA5 = (TH1F*)fPA5->Get("ntracksHist");
  //hPA5->SetLineColor(3);
  hPA5->SetLineColor(colorPA5);
  hPA5->SetLineWidth(linewidth);
  int nPA5 = hPA5->GetEntries();
  hPA5->Scale(1.0/((double)nPA5));
  cout << "nPA5 = " << nPA5 << endl;
  //hPA5->GetXaxis()->SetRange(1,54);//for lower limit of 2e-5

  //pp 5.02TeV
  //TFile* fPP5 = TFile::Open("Ntracks_MinBias_pp_5TeV_ManyFiles.root","READ");
  TFile* fPP5 = TFile::Open("Ntracks_ZeroBias_pp_5TeV_ManyFiles_prettyBins.root","READ");
  TH1F* hPP5 = (TH1F*)fPP5->Get("ntracksHist");
  hPP5->SetLineColor(colorPP5);
  hPP5->SetLineWidth(linewidth);
  //hPP5->Rebin(2);
  int nPP5 = hPP5->GetEntries();
  hPP5->Scale(1.0/((double)nPP5));
  //hPP5->GetXaxis()->SetRange(1,60);//for lower limit of 2e-5
  cout << "nPP5 = " << nPP5 << endl;

  //PbPb 5.02TeV 0-10% centrality
  TFile* fAA5cent10 = TFile::Open("NtracksInCentralityBins_MinBias_fromCrab.root","READ");
  TH1F* hAA5cent10 = (TH1F*)fAA5cent10->Get("ntracksHist[0]");
  TH1F* hAA5cent20 = (TH1F*)fAA5cent10->Get("ntracksHist[1]");
  hAA5cent20->Add(hAA5cent10);
  hAA5cent20->SetLineColor(colorAA5cent20);
  hAA5cent20->SetLineWidth(linewidth);
  //hAA5cent20->SetFillColor(6);
  hAA5cent20->Scale(1.0/((double)nAA5*34));//hAA5 (variablebins) has bins of size 36, while hAA5cent10 has bins of size 20
  //hAA5cent20->GetXaxis()->SetLimits(1000,4000);
  hAA5cent20->GetXaxis()->SetRange(2,155);//for lower limit of 2e-5

  //Make them all start at the same value.
  float AA5bin1 = hAA5->GetBinContent(6);
  float PA8bin1 = hPA8->GetBinContent(6);
  float PA5bin1 = hPA5->GetBinContent(6);
  float PP5bin1 = hPP5->GetBinContent(6);
  cout << "AA5bin1 = " << AA5bin1 << endl;
  cout << "PA8bin1 = " << PA8bin1 << endl;
  cout << "PA5bin1 = " << PA5bin1 << endl;
  cout << "PP5bin1 = " << PP5bin1 << endl;
  float scalefactor = 8;
  hPA8->Scale(scalefactor*AA5bin1/PA8bin1);
  hPA5->Scale(scalefactor*AA5bin1/PA5bin1);
  hPP5->Scale(scalefactor*AA5bin1/PP5bin1);
  hAA5->Scale(scalefactor);
  hAA5cent20->Scale(scalefactor);

  TCanvas* c1 = new TCanvas("c1","c1",40,40,400,400);
  c1->cd(1);
  gPad->SetLogy();
  gPad->SetLogx();
  hAA5->SetTitle("");
  //hAA5->SetMaximum(4);
  hAA5->SetMaximum(1);
  hAA5->SetMinimum(2e-5);
  //hAA5->GetXaxis()->SetLimits(40,4000);
  hAA5->GetXaxis()->SetRange(6,200);
  //hAA5->GetXaxis()->SetRangeUser(1000,4000);
  hAA5->GetXaxis()->SetTitle("N_{tracks}");
  hAA5->GetXaxis()->SetTitleSize(0.04);
  //hAA5->GetYaxis()->SetTitleOffset(1.43);
  hAA5->GetYaxis()->CenterTitle(kFALSE);
  //hAA5->GetYaxis()->SetTitleSize(0.058);
  hAA5->GetYaxis()->SetTitle("A.U.");
  hAA5->GetYaxis()->SetLabelSize(0.04);
  hAA5->GetXaxis()->SetLabelSize(0.04);
  //hAA5->GetXaxis()->SetTitleSize(0);

  c1->cd();
  cout << "Plotting ntracks distribution..." << endl;
  hAA5->Draw("hist");
  hPA8->Draw("same hist");
  hPA5->Draw("same hist");
  hPP5->Draw("same hist");
  hAA5cent20->Draw("same hist");
  c1->RedrawAxis();
  c1->SetTickx();
  c1->SetTicky();

  //TLegend* leg = new TLegend(0.58,0.5,0.89,0.72); leg->SetTextSize(12);
  TLegend* leg = new TLegend(0.55,0.57,0.85,0.85); leg->SetTextSize(12);
  //leg->SetTextFont(43);
  leg->SetTextFont(43);
  leg->SetBorderSize(0);
  leg->AddEntry(hPP5,"pp, #sqrt{s}=5TeV","l");
  leg->AddEntry(hPA5,"pPb, #sqrt{s_{NN}}=5TeV","l");
  leg->AddEntry(hPA8,"pPb, #sqrt{s_{NN}}=8TeV","l");
  leg->AddEntry(hAA5,"PbPb, #sqrt{s_{NN}}=5TeV","l");
  leg->AddEntry(hAA5cent20,"PbPb, #sqrt{s_{NN}}=5TeV","l");
  leg->AddEntry(hAA5cent20,Form("0-20%s Centrality","%"),"");
  leg->Draw("same");

  TLatex *cmstex = new TLatex(0.15,0.15,"CMS");
  cmstex->SetTextFont(61);
  cmstex->SetTextSize(0.08);
  cmstex->SetNDC();
  cmstex->Draw();

  //TLatex *extratex = new TLatex(0.62,0.73,"Preliminary");
  //extratex->SetTextFont(52);
  //extratex->SetTextSize(0.06);
  //extratex->SetNDC();
  //extratex->Draw();

  /*float xpos = 0.78;//0.77
  float ypos = 0.18;
  float ystep = 0.03;
  float textsize = 0.03;
  int textfont = 41;
  TLatex *centtex0 = new TLatex(xpos,ypos+ystep,"PbPb");
  centtex0->SetTextFont(textfont);
  centtex0->SetTextSize(textsize);
  centtex0->SetNDC();
  centtex0->Draw();
  TLatex *centtex = new TLatex(xpos,ypos,"0-20%");
  centtex->SetTextFont(textfont);
  centtex->SetTextSize(textsize);
  centtex->SetNDC();
  centtex->Draw();
  TLatex *centtex2 = new TLatex(xpos-0.01,ypos-ystep,"centrality");
  centtex2->SetTextFont(textfont);
  centtex2->SetTextSize(textsize);
  centtex2->SetNDC();
  centtex2->Draw();
  //TLatex *centtex3 = new TLatex(xpos-0.02,ypos-ystep,Form("avg=%.0f",hAA5cent20->GetMean()));
  //centtex3->SetTextFont(textfont);
  //centtex3->SetTextSize(textsize);
  //centtex3->SetNDC();
  //centtex3->Draw();
*/

  //Print averages:
  cout << "hAA5 avg = " << hAA5->GetMean() << endl;
  cout << "hPA8 avg = " << hPA8->GetMean() << endl;
  cout << "hPA5 avg = " << hPA5->GetMean() << endl;
  cout << "hPP5 avg = " << hPP5->GetMean() << endl;
  cout << "hAA5cent20 avg = " << hAA5cent20->GetMean() << endl;

  TString outfName = "Ntracks_AllSystems";
  c1->SaveAs(Form("%s.pdf",outfName.Data() ));
  c1->SaveAs(Form("%s.png",outfName.Data() ));
  c1->SaveAs(Form("%s.C",outfName.Data() ));

  cout << endl << "Here's what's in memory: " << endl;
  gDirectory->ls("-m");

}
