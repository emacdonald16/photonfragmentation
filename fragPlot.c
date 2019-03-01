#include <TH1D.h>
#include <TCanvas.h>
#include <TFile.h>
#include "labelCMS.h"
#include "analysisTools.h"
#include <TGraphAsymmErrors.h>


//TString year = "2016";
TString year = "2017";
//TString year = "_com";

void overlay();

void fragPlot() {
  TFile * f = TFile::Open("fragmentation.hdp.sp0p4.2016.root");
  if (year.Contains("17")) f = TFile::Open("fragmentation.hdp.sp0p4.2017.root");
  else if (year.Contains("com")) f = TFile::Open("fragmentation.hdp.sp0p4._com.root");

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

  float plotMin = 0.57; float plotMax = 1.01;

  TGraphAsymmErrors * g_bin46_NJets8910   = (TGraphAsymmErrors*)f ->Get("bin46_NJets8910");
  g_bin46_NJets8910->SetTitle(";46-bin NJets-HT-MHT plane;Direct photon fraction");
  g_bin46_NJets8910->SetMarkerStyle(20);
  g_bin46_NJets8910->SetMarkerSize(0.7);
  g_bin46_NJets8910->SetLineColor(kBlack);
  g_bin46_NJets8910->SetMarkerColor(kBlack);
  g_bin46_NJets8910->SetMinimum(plotMin);
  g_bin46_NJets8910->SetMaximum(plotMax);
  g_bin46_NJets8910->Draw("APE");
  g_bin46_NJets8910->GetXaxis()->SetLimits(0.1,47.0);
  g_bin46_NJets8910->Draw("APE");



  //CYA for when low stats makes empty bins
  int nbinsx = g_bin46_NJets8910->GetN();
  double ax[nbinsx],ay[nbinsx];
  for (int i=0; i< nbinsx; i++){
    g_bin46_NJets8910->GetPoint(i,ax[i],ay[i]);
    const int x0 = ax[i]; const int y0 = ay[i];
    if (ay[i] == 0){
      g_bin46_NJets8910->SetPoint(i,x0,0.95);
      g_bin46_NJets8910->SetPointEYlow(i,0.15);
      g_bin46_NJets8910->SetPointEYhigh(i,0.05);
    }
    if (g_bin46_NJets8910->GetErrorYlow(i) == 0) g_bin46_NJets8910->SetPointEYlow(i,0.1);
  }

  drawLines46(plotMin, plotMax);
  CMS_lumi(year,can_h, 0, 0);


  //Njet labels
  TLatex ttext_njet;
  ttext_njet.SetTextFont(42);
  ttext_njet.SetTextSize(0.035);
  ttext_njet.SetTextAlign(22);
  ttext_njet.DrawLatex(5.8, 0.62 , "2 #leq N_{#scale[0.2]{ }jet} #leq 3");
  ttext_njet.DrawLatex(15.5, 0.62 , "4 #leq N_{#scale[0.2]{ }jet} #leq 5");
  ttext_njet.DrawLatex(25.5, 0.62 , "6 #leq N_{#scale[0.2]{ }jet} #leq 7");
  ttext_njet.DrawLatex(34.5, 0.62, "N_{#scale[0.2]{ }jet} #geq 8");
  ttext_njet.DrawLatex(42.8, 0.62, "N_{#scale[0.2]{ }jet} #geq 8");

  can_h->Update();
  can_h->SaveAs("plots"+year+"/fragmentation.pdf");
  g_bin46_NJets8910->SaveAs("plots"+year+"/fragmentation.root");


  TCanvas * c2 = new TCanvas("c2","c2", 2400.,600.);
  c2->SetRightMargin(0.09);
  c2->SetLeftMargin(0.15);
  c2->SetBottomMargin(0.15);
  c2->Divide(3, 1);

  c2->cd(1);
  TGraphAsymmErrors * g_HT = (TGraphAsymmErrors*)f->Get("HT");
  g_HT->SetTitle(";H_{T} [GeV];Direct photon fraction");
  g_HT->GetXaxis()->SetLabelSize(0.033);
  g_HT->GetYaxis()->SetLabelSize(0.033);
  g_HT->GetXaxis()->SetTitleSize(0.04);
  g_HT->GetYaxis()->SetTitleSize(0.04);
  g_HT->SetMarkerStyle(20);
  g_HT->SetMarkerSize(1.3);
  g_HT->SetLineColor(kBlue);
  g_HT->SetMarkerColor(kBlue);
  g_HT->Draw("APE");
  g_HT->SetMinimum(0.8);
  g_HT->SetMaximum(1.01);
  labelCMS(year);


  c2->cd(2);
  TGraphAsymmErrors * g_MHT = (TGraphAsymmErrors*)f->Get("MHT");
  g_MHT->SetTitle(";H_{T}^{miss} [GeV];Direct photon fraction");
  g_MHT->GetXaxis()->SetLabelSize(0.033);
  g_MHT->GetYaxis()->SetLabelSize(0.033);
  g_MHT->GetXaxis()->SetTitleSize(0.04);
  g_MHT->GetYaxis()->SetTitleSize(0.04);
  g_MHT->SetMarkerStyle(20);
  g_MHT->SetMarkerSize(1.3);
  g_MHT->SetLineColor(kBlue);
  g_MHT->SetMarkerColor(kBlue);
  g_MHT->Draw("APE");
  g_MHT->SetMinimum(0.8);
  g_MHT->SetMaximum(1.01);
  labelCMS(year);

  c2->cd(3);
  TGraphAsymmErrors * g_NJets = (TGraphAsymmErrors*)f->Get("NJets");
  g_NJets->SetTitle(";N_{ jets};Direct photon fraction");
  g_NJets->GetXaxis()->SetLabelSize(0.033);
  g_NJets->GetYaxis()->SetLabelSize(0.033);
  g_NJets->GetXaxis()->SetTitleSize(0.04);
  g_NJets->GetYaxis()->SetTitleSize(0.04);
  g_NJets->SetMarkerStyle(20);
  g_NJets->SetMarkerSize(1.3);
  g_NJets->SetLineColor(kBlue);
  g_NJets->SetMarkerColor(kBlue);
  g_NJets->Draw("APE");
  g_NJets->SetMinimum(0.8);
  g_NJets->SetMaximum(1.01);
  labelCMS(year);

  c2->SaveAs("plots"+year+"/fragmentation.vars.pdf");

  //if com, plot 2016 and 2017 on same canvas
  if (year.Contains("com")) overlay();
}


void overlay() {
  TFile * f  = TFile::Open("fragmentation.hdp.sp0p4.2016.root");
  TFile * f2 = TFile::Open("fragmentation.hdp.sp0p4.2017.root");

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

  TGraphAsymmErrors * g_bin46_NJets8910   = (TGraphAsymmErrors*)f ->Get("bin46_NJets8910");
  TGraphAsymmErrors * g_bin46_NJets8910_2 = (TGraphAsymmErrors*)f2->Get("bin46_NJets8910");

  //CYA for when low stats makes empty bins, or for 100% efficiency bins (gives zero error)
  int nbinsx = g_bin46_NJets8910->GetN();
  double ax[nbinsx],ay[nbinsx];
  double ax2[nbinsx],ay2[nbinsx];
  for (int i=0; i< nbinsx; i++){
    g_bin46_NJets8910  ->GetPoint(i,ax[i] ,ay[i]);
    g_bin46_NJets8910_2->GetPoint(i,ax2[i],ay2[i]);
    const int x0 = ax[i]; const int y0 = ay[i];
    const int x0_2 = ax2[i]; const int y0_2 = ay2[i];

    if (ay[i] == 0){
      g_bin46_NJets8910->SetPoint(i,x0,0.95);
      g_bin46_NJets8910->SetPointEYlow(i,0.15);
      g_bin46_NJets8910->SetPointEYhigh(i,0.05);
    }
    if (ay2[i] == 0){
      g_bin46_NJets8910_2->SetPoint(i,x0_2,0.95);
      g_bin46_NJets8910_2->SetPointEYlow(i,0.15);
      g_bin46_NJets8910_2->SetPointEYhigh(i,0.05);
    }
    if (g_bin46_NJets8910  ->GetErrorYlow(i) == 0) g_bin46_NJets8910  ->SetPointEYlow(i,0.1);
    if (g_bin46_NJets8910_2->GetErrorYlow(i) == 0) g_bin46_NJets8910_2->SetPointEYlow(i,0.1);
  }

  float plotMin = 0.57; float plotMax = 1.01;

  g_bin46_NJets8910->SetTitle(";46-bin NJets-HT-MHT plane;Direct photon fraction");
  g_bin46_NJets8910->SetMarkerStyle(20);
  g_bin46_NJets8910->SetMarkerSize(0.7);
  g_bin46_NJets8910->SetLineColor(kBlack);
  g_bin46_NJets8910->SetMarkerColor(kBlack);
  g_bin46_NJets8910->SetMinimum(plotMin);
  g_bin46_NJets8910->SetMaximum(plotMax);

  g_bin46_NJets8910_2->SetTitle(";46-bin NJets-HT-MHT plane;Direct photon fraction");
  g_bin46_NJets8910_2->SetMarkerStyle(20);
  g_bin46_NJets8910_2->SetMarkerSize(0.7);
  g_bin46_NJets8910_2->SetLineColor(kRed);
  g_bin46_NJets8910_2->SetMarkerColor(kRed);
  g_bin46_NJets8910_2->SetMinimum(plotMin);
  g_bin46_NJets8910_2->SetMaximum(plotMax);

  g_bin46_NJets8910_2->Draw("APE");
  g_bin46_NJets8910_2->GetXaxis()->SetLimits(0.1,47.0);
  g_bin46_NJets8910_2->Draw("APE");
  g_bin46_NJets8910->Draw("PE");


  double height = 0.15;
  double width = 0.2;
  double x_init = 0.32;
  double y_init = 0.27;

  TLegend * leg1 = new TLegend(x_init, y_init, x_init+width, y_init+height);
  leg1->SetTextSize(0.035);
  leg1->SetFillStyle(0);
  leg1->SetBorderSize(0);
  TLegend * leg2 = new TLegend(x_init, y_init+height-0.07, x_init+width, y_init+0.23);
  leg2->SetTextSize(0.035);
  leg2->SetFillStyle(0);
  leg2->SetBorderSize(0);

  leg1->AddEntry(g_bin46_NJets8910, "2016 MC", "pl");
  leg2->AddEntry(g_bin46_NJets8910_2, "2017 MC", "pl");
  leg1->Draw("same");
  leg2->Draw("same");

  drawLines46(plotMin, plotMax);
  CMS_lumi(year,can_h, 0, 0);

  //Njet labels
  TLatex ttext_njet;
  ttext_njet.SetTextFont(42);
  ttext_njet.SetTextSize(0.035);
  ttext_njet.SetTextAlign(22);
  ttext_njet.DrawLatex(5.8, 0.62 , "2 #leq N_{#scale[0.2]{ }jet} #leq 3");
  ttext_njet.DrawLatex(15.5, 0.62 , "4 #leq N_{#scale[0.2]{ }jet} #leq 5");
  ttext_njet.DrawLatex(25.5, 0.62 , "6 #leq N_{#scale[0.2]{ }jet} #leq 7");
  ttext_njet.DrawLatex(34.8, 0.62, "N_{#scale[0.2]{ }jet} #geq 8");
  ttext_njet.DrawLatex(42.8, 0.62, "N_{#scale[0.2]{ }jet} #geq 8");

  can_h->Update();
  can_h->SaveAs("plots"+year+"/fragBoth.pdf");
  g_bin46_NJets8910->SaveAs("plots"+year+"/fragBoth.root");
}
