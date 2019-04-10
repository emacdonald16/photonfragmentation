#include <TFile.h>
#include <iostream>
#include "analysisTools.h"
#include <TChain.h>
#include <TLorentzVector.h>
#include <TGraphAsymmErrors.h>
#include <TH1D.h>

//TString year = "2016";
//TString year = "2017";
TString year = "_com";

bool bin65 = false;


class fragmentation {
public:
  fragmentation(){};
  void run(double sp, TString spTag);
private:
  bool passBaseline();
  void initChain(TChain * chain);
  void fillHists(TChain * chain, const int hid, const double sp);

  double HT, MHT;
  int NJets, JetID, BTags;
  int isoElectronTracks, isoMuonTracks, isoPionTracks;
  double Weight;
  std::vector<TLorentzVector> *Electrons, *Muons, *Photons;
  std::vector<bool> *Photons_fullID;
  double madMinPhotonDeltaR;
  int madMinDeltaRStatus;

  TH1D *h_inc[3];
  TH1D *h_HT[3], *h_MHT[3], *h_NJets[3];
  TH1D *h_bin50[3], *h_bin50_NJets8910[3];
  TH1D *h_bin65[3], *h_bin65_NJets8910[3];
};

void fragmentation::initChain(TChain * chain) {
  chain->SetBranchAddress("HT", &HT);
  chain->SetBranchAddress("MHT", &MHT);
  chain->SetBranchAddress("NJets", &NJets);
  chain->SetBranchAddress("BTags", &BTags);
  chain->SetBranchAddress("isoElectronTracks", &isoElectronTracks);
  chain->SetBranchAddress("isoMuonTracks", &isoMuonTracks);
  chain->SetBranchAddress("isoPionTracks", &isoPionTracks);
  chain->SetBranchAddress("Weight", &Weight);
  chain->SetBranchAddress("JetID", &JetID);
  chain->SetBranchAddress("madMinPhotonDeltaR", &madMinPhotonDeltaR);
  chain->SetBranchAddress("madMinDeltaRStatus", &madMinDeltaRStatus);
  chain->SetBranchAddress("Electrons", &Electrons);
  chain->SetBranchAddress("Muons", &Muons);
  chain->SetBranchAddress("Photons", &Photons);
  chain->SetBranchAddress("Photons_fullID", &Photons_fullID);
  Electrons = Muons = Photons = 0;
  Photons_fullID = 0;
}

bool fragmentation::passBaseline() {
  if (NJets>=2 && HT>=300. && MHT>=250. && JetID==1) {
  //if (NJets>=2 && HT>=300. && MHT>=250. && JetID==1 && BTags==0) {
    if (isoElectronTracks==0 && isoMuonTracks==0 && isoPionTracks==0) {
      if (Electrons->size()==0 && Muons->size()==0 && Photons->size()==1) {
        if (Photons->at(0).Pt()>=200. && Photons_fullID->at(0)==1) {
          if (whichBin_HTMHT13(HT, MHT, NJets)>0) {
            return true;
          }
        }
      }
    }
  }
  return false;
}

void fragmentation::fillHists(TChain * chain, const int hid, const double sp) {
  for (int i = 0; i < chain->GetEntries(); ++i) {
    TString which_file = chain->GetFile()->GetName();
    //cout<<"File name: "<<which_file<<endl;
    chain->GetEntry(i);
    if (!passBaseline()) continue;

    // QCD
    if (hid==0) {
      if (madMinDeltaRStatus!=1) continue;
      if (madMinPhotonDeltaR>=sp) continue;
    }
    // GJets
    if (hid==1 && madMinPhotonDeltaR<0.4) continue;
    if (hid==2 && madMinPhotonDeltaR<sp) continue;

    if (which_file.Contains("MC2016")) {
      //cout<<"Found file (2016) correctly!"<<endl;
      Weight = Weight * 35922.000;
    }
    else if (which_file.Contains("MC2017")) {
      //cout<<"Found file (2017) correctly!"<<endl;
      Weight = Weight * 41529.000;
    }
    else if (which_file.Contains("MC2018")) {
      //cout<<"Found file (2018) correctly!"<<endl;
      Weight = Weight * 59740.000;
    }


    if (bin65) {
      h_bin65[hid]->Fill(whichBin_65(HT, MHT, NJets), Weight);
      for (int j = 1; j <= 65; ++j) {
        if (whichBin_65_NJets8910(HT, MHT, NJets, j)) {
          h_bin65_NJets8910[hid]->Fill(j, Weight);
        }
      }
    }


    h_MHT[hid]->Fill(MHT, Weight);
    if (MHT<300.) continue;
    h_inc[hid]->Fill(1., Weight);
    h_HT[hid]->Fill(HT, Weight);
    h_NJets[hid]->Fill(NJets, Weight);
    h_bin50[hid]->Fill(whichBin_50(HT, MHT, NJets), Weight);
    for (int j = 1; j <= 50; ++j) {
      if (whichBin_50_NJets8910(HT, MHT, NJets, j)) {
        h_bin50_NJets8910[hid]->Fill(j, Weight);
      }
    }
  }
}

// to be used when weights are not used
TGraphAsymmErrors * divideHists(TH1D * hist[3], const TString name) {
  TH1D * num = (TH1D*)hist[1]->Clone("num_"+name);
  TH1D * denom = (TH1D*)hist[0]->Clone("denom_"+name);
  denom->Add(hist[2]);
  TGraphAsymmErrors * graph = new TGraphAsymmErrors(num, denom, "n");
  graph->SetName(name);
  char buffer[1000];
  sprintf(buffer, ";%s;fragmentation fraction", hist[0]->GetXaxis()->GetTitle());
  graph->SetTitle(buffer);
  return graph;
}


// TH1D * divideHists(TH1D * hist[3], const TString name)
// {
//   TH1D * num = (TH1D*)hist[1]->Clone("num");
//   num->SetName(name);
//   TH1D * denom = (TH1D*)hist[0]->Clone("denom");
//   denom->Add(hist[2]);
//   num->Divide(num, denom, 1, 1, "B");
//   char buffer[1000];
//   sprintf(buffer, ";%s;fragmentation fraction", hist[0]->GetXaxis()->GetTitle());
//   num->SetTitle(buffer);
//   return num;
// }

void fragmentation::run(double sp=0.4, TString spTag = "sp0p4") {
  if (sp==0.3) spTag = "sp0p3";
  else if (sp==0.2) spTag = "sp0p2";

  // nominal high-delta phi region
  const TString dir1 = "/eos/uscms/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/tree_GJet_CleanVars/";
  const TString dir2 = "/eos/uscms/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV17/tree_GJet_CleanVars/"; //for 2018 MC
  //const TString dirTag = "hdp";
  const TString dirTag = "allBs";

  // low-delta phi region for QCD estimate
  //const TString dir = "/eos/uscms/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/tree_GJetLDP_CleanVars/";
  //const TString dirTag = "ldp";


  TChain * cQCD = new TChain("tree");
  TChain * cGJets = new TChain("tree");

  if (year.Contains("16")) {
    cQCD->Add(dir1 + "tree_QCD_HT-200to300_MC2016.root");
    cQCD->Add(dir1 + "tree_QCD_HT-300to500_MC2016.root");
    cQCD->Add(dir1 + "tree_QCD_HT-500to700_MC2016.root");
    cQCD->Add(dir1 + "tree_QCD_HT-700to1000_MC2016.root");
    cQCD->Add(dir1 + "tree_QCD_HT-1000to1500_MC2016.root");
    cQCD->Add(dir1 + "tree_QCD_HT-1500to2000_MC2016.root");
    cQCD->Add(dir1 + "tree_QCD_HT-2000toInf_MC2016.root");
    initChain(cQCD);

    cGJets->Add(dir1 + "tree_GJets_HT-100to200_MC2016.root");
    cGJets->Add(dir1 + "tree_GJets_HT-200to400_MC2016.root");
    cGJets->Add(dir1 + "tree_GJets_HT-400to600_MC2016.root");
    cGJets->Add(dir1 + "tree_GJets_HT-600toInf_MC2016.root");
    initChain(cGJets);
  }

  else if (year.Contains("17")) {
    cQCD->Add(dir1 + "tree_QCD_HT-200to300_MC2017.root");
    cQCD->Add(dir1 + "tree_QCD_HT-300to500_MC2017.root");
    cQCD->Add(dir1 + "tree_QCD_HT-500to700_MC2017.root");
    cQCD->Add(dir1 + "tree_QCD_HT-700to1000_MC2017.root");
    cQCD->Add(dir1 + "tree_QCD_HT-1000to1500_MC2017.root");
    cQCD->Add(dir1 + "tree_QCD_HT-1500to2000_MC2017.root");
    cQCD->Add(dir1 + "tree_QCD_HT-2000toInf_MC2017.root");
    initChain(cQCD);

    cGJets->Add(dir1 + "tree_GJets_HT-100to200_MC2017.root");
    cGJets->Add(dir1 + "tree_GJets_HT-200to400_MC2017.root");
    cGJets->Add(dir1 + "tree_GJets_HT-400to600_MC2017.root");
    cGJets->Add(dir1 + "tree_GJets_HT-600toInf_MC2017.root");
    initChain(cGJets);
  }

  else if (year.Contains("com")) {
    cQCD->Add(dir1 + "tree_QCD_HT-200to300_MC2016.root");
    cQCD->Add(dir1 + "tree_QCD_HT-300to500_MC2016.root");
    cQCD->Add(dir1 + "tree_QCD_HT-500to700_MC2016.root");
    cQCD->Add(dir1 + "tree_QCD_HT-700to1000_MC2016.root");
    cQCD->Add(dir1 + "tree_QCD_HT-1000to1500_MC2016.root");
    cQCD->Add(dir1 + "tree_QCD_HT-1500to2000_MC2016.root");
    cQCD->Add(dir1 + "tree_QCD_HT-2000toInf_MC2016.root");

    cQCD->Add(dir1 + "tree_QCD_HT-200to300_MC2017.root");
    cQCD->Add(dir1 + "tree_QCD_HT-300to500_MC2017.root");
    cQCD->Add(dir1 + "tree_QCD_HT-500to700_MC2017.root");
    cQCD->Add(dir1 + "tree_QCD_HT-700to1000_MC2017.root");
    cQCD->Add(dir1 + "tree_QCD_HT-1000to1500_MC2017.root");
    cQCD->Add(dir1 + "tree_QCD_HT-1500to2000_MC2017.root");
    cQCD->Add(dir1 + "tree_QCD_HT-2000toInf_MC2017.root");

    cQCD->Add(dir2 + "tree_QCD_HT-200to300_MC2018.root");
    cQCD->Add(dir2 + "tree_QCD_HT-300to500_MC2018.root");
    cQCD->Add(dir2 + "tree_QCD_HT-500to700_MC2018.root");
    cQCD->Add(dir2 + "tree_QCD_HT-700to1000_MC2018.root");
    cQCD->Add(dir2 + "tree_QCD_HT-1000to1500_MC2018.root");
    cQCD->Add(dir2 + "tree_QCD_HT-1500to2000_MC2018.root");
    cQCD->Add(dir2 + "tree_QCD_HT-2000toInf_MC2018.root");
    initChain(cQCD);

    cGJets->Add(dir1 + "tree_GJets_HT-100to200_MC2016.root");
    cGJets->Add(dir1 + "tree_GJets_HT-200to400_MC2016.root");
    cGJets->Add(dir1 + "tree_GJets_HT-400to600_MC2016.root");
    cGJets->Add(dir1 + "tree_GJets_HT-600toInf_MC2016.root");

    cGJets->Add(dir1 + "tree_GJets_HT-100to200_MC2017.root");
    cGJets->Add(dir1 + "tree_GJets_HT-200to400_MC2017.root");
    cGJets->Add(dir1 + "tree_GJets_HT-400to600_MC2017.root");
    cGJets->Add(dir1 + "tree_GJets_HT-600toInf_MC2017.root");

    cGJets->Add(dir2 + "tree_GJets_HT-100to200_MC2018.root");
    cGJets->Add(dir2 + "tree_GJets_HT-200to400_MC2018.root");
    cGJets->Add(dir2 + "tree_GJets_HT-400to600_MC2018.root");
    cGJets->Add(dir2 + "tree_GJets_HT-600toInf_MC2018.root");
    initChain(cGJets);
  }

  TString l[3] = {"QCD_0tosp", "GJets_spto0p4", "GJets_gtsp"};
  for (int i = 0; i < 3; ++i) {
    h_inc[i] = new TH1D("h_inc_"+l[i], ";the unit bin;events", 1, 0.5, 1.5);
    h_HT[i] = new TH1D("h_HT_"+l[i], ";HT [GeV];events / 100 GeV", 10, 300., 1300.);
    h_MHT[i] = new TH1D("h_MHT_"+l[i], ";MHT [GeV];events / 100 GeV", 10, 300., 1300.);
    h_NJets[i] = new TH1D("h_NJets_"+l[i], ";NJets;events / 1", 10, 1.5, 11.5);
    h_bin50[i] = new TH1D("h_bin50_"+l[i], ";50-bin NJets-HT-MHT analysis plane;events / bin", 50, 0.5, 50.5);
    h_bin50_NJets8910[i] = new TH1D("h_bin50_NJets8910_"+l[i], ";50-bin NJets-HT-MHT analysis plane;events / bin", 50, 0.5, 50.5);
    h_bin65[i] = new TH1D("h_bin65_"+l[i], ";65-bin NJets-HT-MHT analysis plane;events / bin", 65, 0.5, 65.5);
    h_bin65_NJets8910[i] = new TH1D("h_bin65_NJets8910_"+l[i], ";65-bin NJets-HT-MHT analysis plane;events / bin", 65, 0.5, 65.5);
  }

  std::cout << "filling QCD hists..." << std::endl;
  fillHists(cQCD, 0, sp); // values less than sp
  std::cout << "filling GJets hists..." << std::endl;
  fillHists(cGJets, 1, sp); // values greater than 0p4
  std::cout << "filling GJets hists..." << std::endl;
  fillHists(cGJets, 2, sp); // values greater than sp

  TH1D *h_bin46[3], *h_bin46_NJets8910[3];
  TH1D *h_bin59_NJets8910[3], *h_bin59[3];
  for (int i = 0; i < 3; ++i) {
    h_bin46[i] = binShifts46(h_bin50[i], "h_bin46_"+l[i]);
    h_bin46_NJets8910[i] = binShifts46(h_bin50_NJets8910[i], "h_bin46_NJets8910_"+l[i]);
    if (bin65) {
      h_bin59[i] = binShifts59(h_bin65[i], "h_bin59_"+l[i]);
      h_bin59_NJets8910[i] = binShifts59(h_bin65_NJets8910[i], "h_bin59_NJets8910_"+l[i]);
    }
  }

  char buffer[200];
  sprintf(buffer, "fragmentation.%s.%s.%s.root", dirTag.Data(), spTag.Data(), year.Data());
  TFile * f = new TFile(buffer, "RECREATE");

  for (int i=0;i<3;i++){
    h_bin46_NJets8910[i]->Write();
  }

  TGraphAsymmErrors * g_inc = divideHists(h_inc, "inc");
  g_inc->Write();

  TGraphAsymmErrors * g_HT = divideHists(h_HT, "HT");
  g_HT->Write();

  TGraphAsymmErrors * g_MHT = divideHists(h_MHT, "MHT");
  g_MHT->Write();

  TGraphAsymmErrors * g_NJets = divideHists(h_NJets, "NJets");
  g_NJets->Write();

  TGraphAsymmErrors * g_bin46 = divideHists(h_bin46, "bin46");
  g_bin46->Write();

  TGraphAsymmErrors * g_bin46_NJets8910 = divideHists(h_bin46_NJets8910, "bin46_NJets8910");
  g_bin46_NJets8910->Write();

  if (bin65) {
    TGraphAsymmErrors * g_bin59 = divideHists(h_bin59, "bin59");
    g_bin59->Write();

    TGraphAsymmErrors * g_bin59_NJets8910 = divideHists(h_bin59_NJets8910, "bin59_NJets8910");
    g_bin59_NJets8910->Write();
  }

  f->Close();
}

void RunFragmentation() {
  cout<<"Trying 0.4 stitch point..."<<endl;
  fragmentation a;
  a.run(0.4);
  cout<<"Trying 0.3 stitch point..."<<endl;
  fragmentation b;
  b.run(0.3);
  cout<<"Trying 0.2 stitch point..."<<endl;
  fragmentation c;
  c.run(0.2);
}
