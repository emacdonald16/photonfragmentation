#include "labelCMS.h"
#include <TChain.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TH1D.h>
#include <TCut.h>
#include <TColor.h>
#include <iostream>
#include "analysisTools.h"


//TString year = "2016";
//TString year = "2017";
TString year = "_com";


bool allBs = true;

void madMinPhotonDeltaR() {

  const TString sigdir = "/eos/uscms/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/tree_signal/";
  const TString dir = "/eos/uscms/store/user/lpcsusyhad/SusyRA2Analysis2015/Skims/Run2ProductionV16/tree_GJet_CleanVars/";

  TChain * chain_ZJetsToNuNu = new TChain("tree");
  TChain * chain_GJets = new TChain("tree");
  TChain * chain_QCD = new TChain("tree");

  if (year.Contains("16")) {
    chain_ZJetsToNuNu->Add(sigdir + "tree_ZJetsToNuNu_HT-100to200_MC2016.root");
    chain_ZJetsToNuNu->Add(sigdir + "tree_ZJetsToNuNu_HT-200to400_MC2016.root");
    chain_ZJetsToNuNu->Add(sigdir + "tree_ZJetsToNuNu_HT-400to600_MC2016.root");
    chain_ZJetsToNuNu->Add(sigdir + "tree_ZJetsToNuNu_HT-600to800_MC2016.root");
    chain_ZJetsToNuNu->Add(sigdir + "tree_ZJetsToNuNu_HT-800to1200_MC2016.root");
    chain_ZJetsToNuNu->Add(sigdir + "tree_ZJetsToNuNu_HT-1200to2500_MC2016.root");
    chain_ZJetsToNuNu->Add(sigdir + "tree_ZJetsToNuNu_HT-2500toInf_MC2016.root");

    chain_GJets->Add(dir + "tree_GJets_HT-100to200_MC2016.root");
    chain_GJets->Add(dir + "tree_GJets_HT-200to400_MC2016.root");
    chain_GJets->Add(dir + "tree_GJets_HT-400to600_MC2016.root");
    chain_GJets->Add(dir + "tree_GJets_HT-600toInf_MC2016.root");

    chain_QCD->Add(dir + "tree_QCD_HT-200to300_MC2016.root");
    chain_QCD->Add(dir + "tree_QCD_HT-300to500_MC2016.root");
    chain_QCD->Add(dir + "tree_QCD_HT-500to700_MC2016.root");
    chain_QCD->Add(dir + "tree_QCD_HT-700to1000_MC2016.root");
    //chain_QCD->Add(dir + "tree_QCD_HT-700to1000_MC2017.root");
    chain_QCD->Add(dir + "tree_QCD_HT-1000to1500_MC2016.root");
    chain_QCD->Add(dir + "tree_QCD_HT-1500to2000_MC2016.root");
    chain_QCD->Add(dir + "tree_QCD_HT-2000toInf_MC2016.root");
  }
  else if (year.Contains("17")) {
    chain_ZJetsToNuNu->Add(sigdir + "tree_ZJetsToNuNu_HT-100to200_MC2017.root");
    chain_ZJetsToNuNu->Add(sigdir + "tree_ZJetsToNuNu_HT-200to400_MC2017.root");
    chain_ZJetsToNuNu->Add(sigdir + "tree_ZJetsToNuNu_HT-400to600_MC2017.root");
    chain_ZJetsToNuNu->Add(sigdir + "tree_ZJetsToNuNu_HT-600to800_MC2017.root");
    chain_ZJetsToNuNu->Add(sigdir + "tree_ZJetsToNuNu_HT-800to1200_MC2017.root");
    chain_ZJetsToNuNu->Add(sigdir + "tree_ZJetsToNuNu_HT-1200to2500_MC2017.root");
    chain_ZJetsToNuNu->Add(sigdir + "tree_ZJetsToNuNu_HT-2500toInf_MC2017.root");

    chain_GJets->Add(dir + "tree_GJets_HT-100to200_MC2017.root");
    chain_GJets->Add(dir + "tree_GJets_HT-200to400_MC2017.root");
    chain_GJets->Add(dir + "tree_GJets_HT-400to600_MC2017.root");
    chain_GJets->Add(dir + "tree_GJets_HT-600toInf_MC2017.root");

    chain_QCD->Add(dir + "tree_QCD_HT-200to300_MC2017.root");
    chain_QCD->Add(dir + "tree_QCD_HT-300to500_MC2017.root");
    chain_QCD->Add(dir + "tree_QCD_HT-500to700_MC2017.root");
    chain_QCD->Add(dir + "tree_QCD_HT-700to1000_MC2017.root");
    chain_QCD->Add(dir + "tree_QCD_HT-1000to1500_MC2017.root");
    chain_QCD->Add(dir + "tree_QCD_HT-1500to2000_MC2017.root");
    chain_QCD->Add(dir + "tree_QCD_HT-2000toInf_MC2017.root");
  }

  else if (year.Contains("com")) {
    chain_ZJetsToNuNu->Add(sigdir + "tree_ZJetsToNuNu_HT-100to200_MC2016.root");
    chain_ZJetsToNuNu->Add(sigdir + "tree_ZJetsToNuNu_HT-200to400_MC2016.root");
    chain_ZJetsToNuNu->Add(sigdir + "tree_ZJetsToNuNu_HT-400to600_MC2016.root");
    chain_ZJetsToNuNu->Add(sigdir + "tree_ZJetsToNuNu_HT-600to800_MC2016.root");
    chain_ZJetsToNuNu->Add(sigdir + "tree_ZJetsToNuNu_HT-800to1200_MC2016.root");
    chain_ZJetsToNuNu->Add(sigdir + "tree_ZJetsToNuNu_HT-1200to2500_MC2016.root");
    chain_ZJetsToNuNu->Add(sigdir + "tree_ZJetsToNuNu_HT-2500toInf_MC2016.root");

    chain_GJets->Add(dir + "tree_GJets_HT-100to200_MC2016.root");
    chain_GJets->Add(dir + "tree_GJets_HT-200to400_MC2016.root");
    chain_GJets->Add(dir + "tree_GJets_HT-400to600_MC2016.root");
    chain_GJets->Add(dir + "tree_GJets_HT-600toInf_MC2016.root");

    chain_QCD->Add(dir + "tree_QCD_HT-200to300_MC2016.root");
    chain_QCD->Add(dir + "tree_QCD_HT-300to500_MC2016.root");
    chain_QCD->Add(dir + "tree_QCD_HT-500to700_MC2016.root");
    chain_QCD->Add(dir + "tree_QCD_HT-700to1000_MC2016.root");
    //chain_QCD->Add(dir + "tree_QCD_HT-700to1000_MC2017.root");
    chain_QCD->Add(dir + "tree_QCD_HT-1000to1500_MC2016.root");
    chain_QCD->Add(dir + "tree_QCD_HT-1500to2000_MC2016.root");
    chain_QCD->Add(dir + "tree_QCD_HT-2000toInf_MC2016.root");

    chain_ZJetsToNuNu->Add(sigdir + "tree_ZJetsToNuNu_HT-100to200_MC2017.root");
    chain_ZJetsToNuNu->Add(sigdir + "tree_ZJetsToNuNu_HT-200to400_MC2017.root");
    chain_ZJetsToNuNu->Add(sigdir + "tree_ZJetsToNuNu_HT-400to600_MC2017.root");
    chain_ZJetsToNuNu->Add(sigdir + "tree_ZJetsToNuNu_HT-600to800_MC2017.root");
    chain_ZJetsToNuNu->Add(sigdir + "tree_ZJetsToNuNu_HT-800to1200_MC2017.root");
    chain_ZJetsToNuNu->Add(sigdir + "tree_ZJetsToNuNu_HT-1200to2500_MC2017.root");
    chain_ZJetsToNuNu->Add(sigdir + "tree_ZJetsToNuNu_HT-2500toInf_MC2017.root");

    chain_GJets->Add(dir + "tree_GJets_HT-100to200_MC2017.root");
    chain_GJets->Add(dir + "tree_GJets_HT-200to400_MC2017.root");
    chain_GJets->Add(dir + "tree_GJets_HT-400to600_MC2017.root");
    chain_GJets->Add(dir + "tree_GJets_HT-600toInf_MC2017.root");

    chain_QCD->Add(dir + "tree_QCD_HT-200to300_MC2017.root");
    chain_QCD->Add(dir + "tree_QCD_HT-300to500_MC2017.root");
    chain_QCD->Add(dir + "tree_QCD_HT-500to700_MC2017.root");
    chain_QCD->Add(dir + "tree_QCD_HT-700to1000_MC2017.root");
    chain_QCD->Add(dir + "tree_QCD_HT-1000to1500_MC2017.root");
    chain_QCD->Add(dir + "tree_QCD_HT-1500to2000_MC2017.root");
    chain_QCD->Add(dir + "tree_QCD_HT-2000toInf_MC2017.root");


  }

  // TChain * chain_GJets_DR0p4 = new TChain("tree");
  // chain_GJets_DR0p4->Add(dir + "tree_GJets_DR-0p4_HT-100to200.root");
  // chain_GJets_DR0p4->Add(dir + "tree_GJets_DR-0p4_HT-200to400.root");
  // chain_GJets_DR0p4->Add(dir + "tree_GJets_DR-0p4_HT-400to600.root");
  // chain_GJets_DR0p4->Add(dir + "tree_GJets_DR-0p4_HT-600toInf.root");



  // TH1D * h = new TH1D("h", ";min #DeltaR (#gamma, hard partons);Events / 0.1", 40, 0., 4.);
  // const double max = 16000.;
  // const TString savetag = "widerange";

  TH1D * h = new TH1D("h", ";min #DeltaR(#gamma, hard partons);Events / 0.05", 16, 0., 0.8);
  const double max = 4000.;
  const TString savetag = "narrowrange";
  //

  h->SetLineWidth(2);
  h->SetStats(0);
  h->Sumw2();
  TH1D * h_ZJetsToNuNu = (TH1D*)h->Clone("h_ZJetsToNuNu");
  TH1D * h_GJets = (TH1D*)h->Clone("h_GJets");
  //TH1D * h_GJets_DR0p4 = (TH1D*)h->Clone("h_GJets_DR0p4");
  TH1D * h_QCD = (TH1D*)h->Clone("h_QCD");

  const TCut cut_photon = "@Photons->size()==1 && Photons[0].Pt()>=200. && Photons_fullID[0]==1";
  const TCut cut_leptons = "@Electrons->size()==0 && @Muons->size()==0";
  const TCut cut_tracks = "isoElectronTracks==0 && isoMuonTracks==0 && isoPionTracks==0";
  const TCut cut_dphi = "DeltaPhi1>=0.5 && DeltaPhi2>=0.5 && DeltaPhi3>=0.3 && DeltaPhi4>=0.3";
  TCut cut_baseline = "";
  if (allBs) cut_baseline = "NJets>=2 && HT>=300. && MHT>=300. && JetID==1";
  else cut_baseline = "NJets>=2 && HT>=300. && MHT>=300. && JetID==1 && BTags==0";
  cut_baseline = cut_leptons && cut_tracks && cut_dphi && cut_baseline;

  //TString which_file = chain->GetFile()->GetName();

  char cut_ZJetsToNuNu[2000];
  if (year.Contains("16") || year.Contains("com")) sprintf(cut_ZJetsToNuNu, "Weight * 35862.824 * (%s)", TString(cut_baseline).Data());
  else if (year.Contains("17")) sprintf(cut_ZJetsToNuNu, "Weight * 41529.000 * (%s)", TString(cut_baseline).Data());
  std::cout << "filling from ZJetsToNuNu..." << std::endl;
  chain_ZJetsToNuNu->Project("h_ZJetsToNuNu", "madMinPhotonDeltaR", cut_ZJetsToNuNu);

  char cut_GJets[2000];
  if (year.Contains("16") || year.Contains("com")) sprintf(cut_GJets, "Weight * 35862.824 * (%s)", TString(cut_baseline && cut_photon).Data());
  else if (year.Contains("17"))  sprintf(cut_GJets, "Weight * 41529.000 * (%s)", TString(cut_baseline && cut_photon).Data());
  std::cout << "filling from GJets..." << std::endl;
  chain_GJets->Project("h_GJets", "madMinPhotonDeltaR", cut_GJets);
  //std::cout << "filling from GJets_DR-0p4..." << std::endl;
  //chain_GJets_DR0p4->Project("h_GJets_DR0p4", "madMinPhotonDeltaR", cut_GJets);

  char cut_QCD[2000];
  if (year.Contains("16") || year.Contains("com")) sprintf(cut_QCD, "Weight * 35862.824 * (%s && madMinDeltaRStatus==1)", TString(cut_baseline && cut_photon).Data());
  else if (year.Contains("17")) sprintf(cut_QCD, "Weight * 41529.000 * (%s && madMinDeltaRStatus==1)", TString(cut_baseline && cut_photon).Data());
  std::cout << "filling from QCD..." << std::endl;
  chain_QCD->Project("h_QCD", "madMinPhotonDeltaR", cut_QCD);

  //TCanvas * can_h = new TCanvas("can_h", "", 400., 400.);
  h_GJets->SetLineColor(kBlue);
  //h_GJets_DR0p4->SetLineColor(7);
  h_QCD->SetLineColor(2001);
  h_ZJetsToNuNu->SetLineColor(2002);
  h_ZJetsToNuNu->SetLineStyle(2);
  h_GJets->SetMinimum(0.);
  h_GJets->SetMaximum(max);
  h_GJets->SetStats(0);

  //setup canvas and pads
  double W = 800;
  double H = 600;
  double T = 0.08*H;
  double B = 0.12*H;
  double L = 0.12*W;
  double R = 0.04*W;
  TCanvas * can_h = new TCanvas("canvName","canvName", 50, 50, W, H);
  can_h->SetFillColor(0);
  can_h->SetBorderMode(0);
  can_h->SetFrameFillStyle(0);
  can_h->SetFrameBorderMode(0);
  can_h->SetLeftMargin( L/W );
  can_h->SetRightMargin( R/W );
  can_h->SetTopMargin( T/H );
  can_h->SetBottomMargin( B/H );
  can_h->SetTickx(0);
  can_h->SetTicky(0);


  h_GJets->Draw("HIST, E");
  //h_GJets_DR0p4->Draw("HIST, E, SAME");
  h_QCD->Draw("HIST, E, SAME");
  h_ZJetsToNuNu->Draw("HIST, E, SAME");

  TLegend * leg_h = new TLegend(0.225, 0.75, 0.865, 0.89);
  leg_h->SetNColumns(3);
  leg_h->SetBorderSize(0);
  leg_h->AddEntry(h_GJets, "#gamma+Jets", "L");
  //leg_h->AddEntry(h_GJets_DR0p4, "GJets_DR-0p4", "L");
  leg_h->AddEntry(h_QCD, "QCD", "L");
  leg_h->AddEntry(h_ZJetsToNuNu, "Z#rightarrow#nu#bar{#nu}", "L");
  leg_h->Draw();


  CMS_lumi(year,can_h, 0, 0);
  if (allBs){
    can_h->SaveAs("./allBs/plots"+year+"/madMinPhotonDeltaR."+savetag+".pdf");
    can_h->SaveAs("./allBs/plots"+year+"/madMinPhotonDeltaR.root");
  }
  else {
    can_h->SaveAs("./plots"+year+"/madMinPhotonDeltaR."+savetag+".pdf");
    can_h->SaveAs("./plots"+year+"/madMinPhotonDeltaR.root");
  }

  /*
  TH1D * r_GJets = (TH1D*)h_ZJetsToNuNu->Clone("r_GJets");
  r_GJets->Divide(h_GJets);

  TH1D * r_GJets_DR0p4 = (TH1D*)h_ZJetsToNuNu->Clone("r_GJets_DR0p4");
  r_GJets_DR0p4->Divide(h_GJets_DR0p4);

  TH1D * r_QCD = (TH1D*)h_ZJetsToNuNu->Clone("r_QCD");
  r_QCD->Divide(h_QCD);

  TCanvas * can_r = new TCanvas("can_r", "", 400, 400);
  r_GJets->SetMarkerColor(8);
  r_GJets->SetLineColor(8);
  r_GJets->SetMarkerStyle(20);
  r_GJets_DR0p4->SetMarkerColor(7);
  r_GJets_DR0p4->SetLineColor(7);
  r_GJets_DR0p4->SetMarkerStyle(20);
  r_QCD->SetMarkerColor(6);
  r_QCD->SetLineColor(6);
  r_QCD->SetMarkerStyle(20);

  r_GJets->Draw("PE");
  r_GJets->SetTitle(";min #DeltaR (#gamma, hard partons);ZJetsToNuNu ratio");
  r_GJets_DR0p4->Draw("PE, SAME");
  r_QCD->Draw("PE, SAME");
  r_GJets->SetMinimum(0.01);
  r_GJets->SetMaximum(10.);
  can_r->SetLogy();

  TLegend * leg_r = new TLegend(0.225, 0.15, 0.865, 0.34);
  leg_r->SetNColumns(3);
  leg_r->SetBorderSize(0);
  leg_r->AddEntry(r_GJets, "GJets", "P");
  leg_r->AddEntry(r_GJets_DR0p4, "GJets_DR-0p4", "P");
  leg_r->AddEntry(r_QCD, "QCD", "P");
  leg_r->Draw();

  labelCMS();
  can_r->SaveAs("./plots"+year+"/madMinPhotonDeltaR.ratio."+savetag+".pdf");
  can_r->SaveAs("./plots"+year+"/madMinPhotonDeltaR.ratio.root");
  */
}
