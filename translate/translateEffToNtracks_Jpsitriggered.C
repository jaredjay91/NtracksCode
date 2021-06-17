void PrintRooDataSet(RooDataSet* rds) {
  int nBins = rds->numEntries();
  cout << "nBins = " << nBins << endl;
  for (int i=0; i<nBins; i++) {
    const RooArgSet *set0 = rds->get(i);
    if (i==0) set0->Print();
    RooRealVar *eta = (RooRealVar*)set0->find("eta");
    RooRealVar *pt = (RooRealVar*)set0->find("pt");
    RooRealVar *tag_hiBin = (RooRealVar*)set0->find("tag_hiBin");
    RooRealVar *tag_hiNtracks = (RooRealVar*)set0->find("tag_hiNtracks");
    RooRealVar *Glb = (RooRealVar*)set0->find("Glb");
    RooRealVar *PF = (RooRealVar*)set0->find("PF");
    RooRealVar *eff = (RooRealVar*)set0->find("efficiency");
    double efflo = eff->getAsymErrorLo();
    double effhi = eff->getAsymErrorHi();
    cout << "RooArgSet:: = (";
    if (eta != NULL) cout << eta->getVal() << ",";
    if (pt != NULL) cout << pt->getVal() << ",";
    if (tag_hiBin != NULL) cout << tag_hiBin->getVal() << ",";
    if (tag_hiNtracks != NULL) cout << tag_hiNtracks->getVal() << ",";
    if (Glb != NULL) cout << Glb->getVal() << ",";
    if (PF != NULL) cout << PF->getVal() << ",";
    if (eff != NULL) cout << eff->getVal() << " + " << effhi << " - " << efflo;
    else cout << "NULL";
    cout << ")" << endl;
  }
}

void centToNtracks(float hiBin, double* ntracksvalptr, double* ntrackserrloptr, double* ntrackserrhiptr) {

  if (hiBin<20) {
    *ntracksvalptr = 2398;
    *ntrackserrloptr = 273;
    *ntrackserrhiptr = 273;
  }
  else if (hiBin<40) {
    *ntracksvalptr = 1780;
    *ntrackserrloptr = 202;
    *ntrackserrhiptr = 202;
  }
  else if (hiBin<60) {
    *ntracksvalptr = 1270;
    *ntrackserrloptr = 162;
    *ntrackserrhiptr = 162;
  }
  else if (hiBin<80) {
    *ntracksvalptr = 871;
    *ntrackserrloptr = 128;
    *ntrackserrhiptr = 128;
  }
  else if (hiBin<100) {
    *ntracksvalptr = 547;
    *ntrackserrloptr = 95;
    *ntrackserrhiptr = 95;
  }
  else if (hiBin<130) {
    *ntracksvalptr = 291;
    *ntrackserrloptr = 77;
    *ntrackserrhiptr = 77;
  }
  else if (hiBin<200) {
    *ntracksvalptr = 95;
    *ntrackserrloptr = 40;
    *ntrackserrhiptr = 40;
  }

}

void translateEffToNtracks_Jpsitriggered(){

  TString inFileName = "OtaFiles_2021_06_07/PbPbZ_tnp_Ana_MC_L3Mu12_PbPb_0_v5_paperFixedBWn.root";
  TString outFileName = "newFiles_triggered/PbPbZ_tnp_Ana_MC_L3Mu12_PbPb_0_v5_paperFixedBWn_Ntracks.root";
  TString treeTag = "tpTree";
  const static int numdirs = 1;
  TString centTag[numdirs] = {"Trg_centdep"};
  TString ntracksTag[numdirs] = {"Trg_ntracksdep"};
  TString selectionTag[numdirs] = {"tag_hiBin_PLOT_isTightMuon_true"};


  //Set up the output tree.
  TFile* outFile = new TFile(outFileName.Data(),"recreate");
  TDirectory *tpTreedir = outFile->mkdir(treeTag.Data());
  tpTreedir->cd();    // make the "tpTree" directory the current directory


  TFile* inFile = TFile::Open(inFileName.Data(),"read");
  for (int idir=0; idir<numdirs; idir++) {
    cout << "Converting " << centTag[idir] << " to " << ntracksTag[idir] << endl;
    TDirectory *ntracksdir = tpTreedir->mkdir(ntracksTag[idir]);

    //Get the graphs
    TCanvas* c1_orig = (TCanvas*)inFile->Get(treeTag + "/" + centTag[idir] + "/fit_eff_plots/" + selectionTag[idir] + ";1");
    c1_orig->Draw();
    //TCanvas* c1 = (TCanvas*)c1_orig->Clone();
    //cout << "c1's name is " << c1->GetName() << endl;
    //c1->SetName("tag_hiNtracks_PLOT_Glb_true_&_PF_true");
    //cout << "c1's name is " << c1->GetName() << endl;
    //TPad* pad1 = (TPad*)c1->GetPrimitive("pad1");

    //cout << endl;
    //c1->GetListOfPrimitives()->Print();

    cout << endl;
    cout << 0 << endl;
    c1_orig->GetListOfPrimitives()->At(0)->Print();
    cout << 1 << endl;
    c1_orig->GetListOfPrimitives()->At(1)->Print();
  
    TGraphAsymmErrors* Graph = (TGraphAsymmErrors*)c1_orig->GetListOfPrimitives()->At(1);
    Graph->SetMinimum(0);
    //delete c1_orig;

    //TH1F* hxy_fit_eff = c1->findObject("hxy_fit_eff");
    //TH1F* hxy_fit_eff = c1->GetHistogram();

    //TGraphAsymmErrors* GraphRD = (TGraphAsymmErrors*)c1->GetListOfPrimitives()->At(1);

    //GraphRD->Draw();
    //inFile->Close();

    RooDataSet* rds_cent = (RooDataSet*)inFile->Get(treeTag + "/" + centTag[idir] + "/fit_eff");

    cout << endl << "Printing out source dataset rds_cent:" << endl;
    PrintRooDataSet(rds_cent);

    cout << endl << "Starting translation..." << endl;
    int nBins = rds_cent->numEntries();
    cout << "nBins = " << nBins << endl;

    // Load efficiencies from the dataset
    //const RooArgSet *set = rds_cent->get();

    const RooArgSet *set0 = rds_cent->get(0);
    set0->Print();
    RooRealVar *eta = (RooRealVar*)set0->find("eta");
    RooRealVar *pt = (RooRealVar*)set0->find("pt");
    RooRealVar *tag_hiBin = (RooRealVar*)set0->find("tag_hiBin");//will be replaced by tag_hiNtracks
    RooRealVar *tag_hiNtracks = new RooRealVar("tag_hiNtracks","tag_hiNtracks",0,10000);
    RooRealVar *Glb = (RooRealVar*)set0->find("Glb");
    RooRealVar *PF = (RooRealVar*)set0->find("PF");
    RooRealVar *eff = (RooRealVar*)set0->find("efficiency");

    double ntracksval = 0;
    double ntrackserrlo = 0;
    double ntrackserrhi = 0;
    double* ntracksvalptr;
    double* ntrackserrloptr;
    double* ntrackserrhiptr;
    ntracksvalptr = &ntracksval;
    ntrackserrloptr = &ntrackserrlo;
    ntrackserrhiptr = &ntrackserrhi;
    centToNtracks(tag_hiBin->getVal(),ntracksvalptr,ntrackserrloptr,ntrackserrhiptr);
    tag_hiNtracks->setVal(*ntracksvalptr);
    tag_hiNtracks->setAttribute("StoreAsymError");
    tag_hiNtracks->setAsymError(*ntrackserrloptr,*ntrackserrhiptr);

    RooArgSet* argSet = new RooArgSet();
    cout << "argSet = ";
    argSet->Print();
    cout << "RooArgSet:: = (";
    if (eta != NULL) {
      argSet->add(*eta);
      cout << eta->getVal() << ",";
    }
    if (pt != NULL) {
      argSet->add(*pt);
      cout << pt->getVal() << ",";
    }
    if (tag_hiBin != NULL) {
      argSet->add(*tag_hiNtracks);
      cout << tag_hiNtracks->getVal() << ",";
    }
    if (Glb != NULL) {
      argSet->add(*Glb);
      cout << Glb->getVal() << ",";
    }
    if (PF != NULL) {
      argSet->add(*PF);
      cout << PF->getVal() << ",";
    }
    //if (eff != NULL) {
      argSet->add(*eff);
      cout << eff->getVal() << "";
    //}
    cout << ")" << endl << endl;

    cout << "argSet = ";
    argSet->Print();
    RooDataSet* rds_ntracks = new RooDataSet("fit_eff","Efficiency from unbinned ML fit",*argSet);
    rds_ntracks->add(*argSet);

    cout << "nBins = " << rds_ntracks->numEntries() << " so far." << endl;


    for (int i=1; i<nBins; i++) {
      cout << "merging entry #" << i << endl;
      rds_cent->get(i);//gets the ith entry in the dataset. The RooRealVars are automatically updated to the i-th entry.

      centToNtracks(tag_hiBin->getVal(),ntracksvalptr,ntrackserrloptr,ntrackserrhiptr);
      tag_hiNtracks->setVal(*ntracksvalptr);
      tag_hiNtracks->setAsymError(*ntrackserrloptr,*ntrackserrhiptr);

      cout << "RooArgSet:: = (";
      if (eta != NULL) {
        argSet->add(*eta);
        cout << eta->getVal() << ",";
      }
      if (pt != NULL) {
        argSet->add(*pt);
        cout << pt->getVal() << ",";
      }
      if (tag_hiBin != NULL) {
        argSet->add(*tag_hiNtracks);
        cout << tag_hiNtracks->getVal() << ",";
      }
      if (Glb != NULL) {
        argSet->add(*Glb);
        cout << Glb->getVal() << ",";
      }
      if (PF != NULL) {
        argSet->add(*PF);
        cout << PF->getVal() << ",";
      }
      //if (eff != NULL) {
        argSet->add(*eff);
        cout << eff->getVal() << "";
      //}
      cout << ")" << endl << endl;

      rds_ntracks->add(*argSet);

      cout << "nBins = " << rds_ntracks->numEntries() << " so far." << endl;
    }

    cout << endl;
    PrintRooDataSet(rds_ntracks);

    c1_orig->SetName(selectionTag[idir]+"_old");

    ntracksdir->cd();
    rds_ntracks->Write();

    //Plot dataset
    TDirectory *plotdir = ntracksdir->mkdir("fit_eff_plots");
    plotdir->cd();
    //TCanvas *c1 = new TCanvas("tag_hiNtracks_PLOT_Glb_true_&_PF_true", "",65,52,700,500);
    TCanvas *c1 = new TCanvas(selectionTag[idir], "",65,52,700,500);
    c1->cd();
    Graph->SetMinimum(0);
    Graph->GetXaxis()->SetTitle("tag_hiNtracks");
    for (int jBin=0; jBin<nBins; jBin++){
      double eyh = Graph->GetErrorYhigh(jBin);
      double eyl = Graph->GetErrorYhigh(jBin);
      double effY = 0;
      double effX = 0;
      ntracksval = 0;
      ntrackserrlo = 0;
      ntrackserrhi = 0;
      Graph->GetPoint(jBin,effX,effY);
      centToNtracks(effX,ntracksvalptr,ntrackserrloptr,ntrackserrhiptr);
      Graph->SetPoint(jBin,*ntracksvalptr,effY);
      double exh = *ntrackserrhiptr;
      double exl = *ntrackserrloptr;
      Graph->SetPointError(jBin, exl, exh, eyl, eyh);
    }
    Graph->Draw("AP");
    c1->SaveAs(Form("ntracksPlot[%i].png",idir));
    plotdir->cd();
    c1->Write();

    //delete c1;
    //delete c1_orig;
    //delete plotdir;
    //delete ntracksdir;
    //delete Graph;

    cout << "leftover in memory: " << endl;
    gDirectory->ls("-m");
    cout << endl;
  }//End of directory loop

  //Write everything to the output file
  cout << "Writing to File " << outFileName << endl;
  outFile->cd();
  tpTreedir->Write();
  outFile->Close();
  delete outFile;
}
