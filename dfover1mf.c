#include <iostream>
#include <TLegend.h>
#include "labelCMS.h"
#include <TFile.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TAxis.h>
#include "analysisTools.h"
#include <TGraphErrors.h>

//TString year = "2016";
TString year = "2017";

void runHist(const TString histname, const bool isWide=false) {
  bool printText = false;
  TFile * f_0p4 = TFile::Open("fragmentation.hdp.sp0p4.2016.root");
  TFile * f_0p3 = TFile::Open("fragmentation.hdp.sp0p3.2016.root");
  TFile * f_0p2 = TFile::Open("fragmentation.hdp.sp0p2.2016.root");
  if (year.Contains("17")) {
    f_0p4 = TFile::Open("fragmentation.hdp.sp0p4.2017.root");
    f_0p3 = TFile::Open("fragmentation.hdp.sp0p3.2017.root");
    f_0p2 = TFile::Open("fragmentation.hdp.sp0p2.2017.root");
  }
  TGraphAsymmErrors * g_0p4 = (TGraphAsymmErrors*)f_0p4->Get(histname);
  TGraphAsymmErrors * g_0p3 = (TGraphAsymmErrors*)f_0p3->Get(histname);
  TGraphAsymmErrors * g_0p2 = (TGraphAsymmErrors*)f_0p2->Get(histname);

  const int n = g_0p4->GetN();
  TGraphErrors * df0p3 = new TGraphErrors(n);
  TGraphErrors * df0p2 = new TGraphErrors(n);
  char title[1000];
  sprintf(title, "%s;%s;%s", "", g_0p4->GetXaxis()->GetTitle(), "#DeltaF_{dir} / (1 - F_{dir})");
  df0p3->SetTitle(title);
  df0p2->SetTitle(title);

  for (int i = 0; i < n; ++i) {
    if (printText) std::cout << "point " << i << std::endl;

    double x4, y4;
    g_0p4->GetPoint(i, x4, y4);
    double y4err = g_0p4->GetErrorY(i);
    if (printText) std::cout << y4 << " " << y4err << std::endl;

    double x3, y3;
    g_0p3->GetPoint(i, x3, y3);
    double y3err = g_0p3->GetErrorY(i);
    if (printText) std::cout << y3 << " " << y3err << std::endl;

    double x2, y2;
    g_0p2->GetPoint(i, x2, y2);
    double y2err = g_0p2->GetErrorY(i);
    if (printText) std::cout << y2 << " " << y2err << std::endl;

    double val1 = (y3-y4)/(1.-y4);
    df0p3->SetPoint(i, x4, val1);
    double err1 = pow(1.-y4, 2)*pow(y3err, 2) + pow(1.-y3, 2)*pow(y4err, 2);
    err1 = sqrt(err1)/pow(1.-y4, 2);
    df0p3->SetPointError(i, 0., err1);
    if (printText) std::cout << val1 << " " << err1 << std::endl;

    double val2 = (y2-y4)/(1.-y4);
    df0p2->SetPoint(i, x4, val2);
    double err2 = pow(1.-y4, 2)*pow(y2err, 2) + pow(1.-y2, 2)*pow(y4err, 2);//possibly fix
    err2 = sqrt(err2)/pow(1.-y4, 2);
    df0p2->SetPointError(i, 0., err2);
    if (printText) {
      std::cout << val2 << " " << err2 << std::endl;
      std::cout << "" << std::endl;
    }

  }

  double width = 400.;
  if (isWide) width = 600.;

  double W = 800;
  double H = 600;
  double T = 0.10*H;
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

  df0p3->SetMarkerStyle(20);
  df0p3->SetMarkerColor(kBlue);
  df0p3->SetLineColor(kBlue);
  df0p3->Draw("APE");
  if (histname.Contains("8910")){
    df0p3->GetXaxis()->SetLimits(0.1,47.0);
    df0p3->SetMinimum(-2.);
    df0p3->SetMaximum(2.);
  }
  else {
    df0p3->SetMinimum(-1.5);
    df0p3->SetMaximum(1.5);
    df0p3->SetMarkerSize(1.2);
    df0p2->SetMarkerSize(1.2);
  }
  df0p3->Draw("APE");

  df0p2->SetMarkerStyle(20);
  df0p2->SetMarkerColor(2001);
  df0p2->SetLineColor(2001);
  df0p2->Draw("PE, SAME");

  TLegend * l1a = new TLegend(0.3, 0.77, 0.5, 0.89);
  TLegend * l1b = new TLegend(0.475, 0.77, 0.675, 0.89);
  l1a->SetBorderSize(0);
  l1b->SetBorderSize(0);
  l1a->AddEntry(df0p2, "#DeltaR = 0.2", "P");
  l1b->AddEntry(df0p3, "#DeltaR = 0.3", "P");
  l1a->Draw("same");
  l1b->Draw("same");

  if (isWide) drawLines46(-2., 2.);

  //Njet labels
  TLatex ttext_njet;
  if (histname.Contains("8910")){
    ttext_njet.SetTextFont(42);
    ttext_njet.SetTextSize(0.037);
    ttext_njet.SetTextAlign(22);
    ttext_njet.DrawLatex(5.8, -1.6 , "2 #leq N_{#scale[0.2]{ }jet} #leq 3");
    ttext_njet.DrawLatex(15.8, -1.6 , "4 #leq N_{#scale[0.2]{ }jet} #leq 5");
    ttext_njet.DrawLatex(25.8, -1.6, "6 #leq N_{#scale[0.2]{ }jet} #leq 7");
    ttext_njet.DrawLatex(34.8, -1.6, "N_{#scale[0.2]{ }jet} #geq 8");
    ttext_njet.DrawLatex(42.2, -1.6, "N_{#scale[0.2]{ }jet} #geq 8");
  }

  labelCMS(year);
  can_h->SaveAs("plots"+year+"/dfover1mf." + histname + ".pdf");
  delete can_h;

  TCanvas * c2 = new TCanvas("c2", "", width, 400.);
  c2->SetFillColor(0);
  c2->SetBorderMode(0);
  c2->SetFrameFillStyle(0);
  c2->SetFrameBorderMode(0);
  c2->SetLeftMargin( L/W );
  c2->SetRightMargin( R/W );
  c2->SetTopMargin( T/H );
  c2->SetBottomMargin( B/H );
  c2->SetTickx(0);
  c2->SetTicky(0);

  char title2[1000];
  sprintf(title2, "%s;%s;%s", "", g_0p3->GetXaxis()->GetTitle(), "Direct photon fraction");
  g_0p3->SetTitle(title2);
  g_0p3->SetMaximum(1.01);
  g_0p3->SetMarkerStyle(20);
  g_0p3->SetMarkerSize(0.7);
  g_0p3->SetMarkerColor(kBlue);
  g_0p3->SetLineColor(kBlue);
  g_0p3->Draw("APE");
  if (histname.Contains("NJets8910")){
    g_0p3->SetMinimum(0.6);
    g_0p3->GetXaxis()->SetLimits(0.1,47.0);
  }
  else if (histname.Contains("NJets")){
    g_0p3->SetMinimum(0.2);
  }
  else {
    g_0p3->SetMinimum(0.6);
    g_0p3->GetXaxis()->SetLimits(280,1320);
  }

  g_0p3->Draw("APE");
  g_0p2->SetMarkerStyle(20);
  g_0p2->SetMarkerSize(0.7);
  g_0p2->SetMarkerColor(2001);
  g_0p2->SetLineColor(2001);
  g_0p2->Draw("PE");
  g_0p4->SetMarkerStyle(20);
  g_0p4->SetMarkerSize(0.7);
  g_0p4->SetMarkerColor(2002);
  g_0p4->SetLineColor(2002);
  g_0p4->Draw("PE");

  TLegend * l2a = new TLegend(0.15, 0.27, 0.33, 0.39);
  TLegend * l2b = new TLegend(0.32, 0.27, 0.50, 0.39);
  TLegend * l2c = new TLegend(0.49, 0.27, 0.67, 0.39);

  l2a->SetBorderSize(0);
  l2b->SetBorderSize(0);
  l2c->SetBorderSize(0);
  l2a->AddEntry(g_0p2, "#DeltaR = 0.2", "P");
  l2b->AddEntry(g_0p3, "#DeltaR = 0.3", "P");
  l2c->AddEntry(g_0p4, "#DeltaR = 0.4", "P");
  l2a->Draw("same");
  l2b->Draw("same");
  l2c->Draw("same");

  if (isWide) drawLines46(0.6, 1.01);
  if (histname.Contains("8910")){
    g_0p4->GetXaxis()->SetLimits(0.1,47.0);
    ttext_njet.DrawLatex(5.8, 0.65 , "2 #leq N_{#scale[0.2]{ }jet} #leq 3");
    ttext_njet.DrawLatex(16., 0.65 , "4 #leq N_{#scale[0.2]{ }jet} #leq 5");
    ttext_njet.DrawLatex(25.8, 0.65, "6 #leq N_{#scale[0.2]{ }jet} #leq 7");
    ttext_njet.DrawLatex(34.8, 0.65, "N_{#scale[0.2]{ }jet} #geq 8");
    ttext_njet.DrawLatex(43.0, 0.65, "N_{#scale[0.2]{ }jet} #geq 8");
  }

  labelCMS(year);
  c2->Update();
  c2->SaveAs("plots"+year+"/frag." + histname + ".pdf");
  delete c2;
}

void dfover1mf() {
  runHist("HT");
  runHist("MHT");
  runHist("NJets");
  runHist("bin46_NJets8910", true);
}
