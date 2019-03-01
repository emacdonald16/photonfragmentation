#include <TH1D.h>
#include <TStyle.h>
#include "labelCMS.h"
#include <TPaveStats.h>
#include <TFile.h>
#include <TH1D.h>
#include <TCanvas.h>
#include "analysisTools.h"

//TString year = "2016";
TString year = "2017";

void scatter() {
  TFile * f_0p4 = TFile::Open("fragmentation.hdp.sp0p4.2016.root");
  TFile * f_0p3 = TFile::Open("fragmentation.hdp.sp0p3.2016.root");
  TFile * f_0p2 = TFile::Open("fragmentation.hdp.sp0p2.2016.root");

  if (year.Contains("17")) {
    f_0p4 = TFile::Open("fragmentation.hdp.sp0p4.2017.root");
    f_0p3 = TFile::Open("fragmentation.hdp.sp0p3.2017.root");
    f_0p2 = TFile::Open("fragmentation.hdp.sp0p2.2017.root");
  }

  TGraphAsymmErrors * g_0p4 = (TGraphAsymmErrors*)f_0p4->Get("bin46_NJets8910");
  TGraphAsymmErrors * g_0p3 = (TGraphAsymmErrors*)f_0p3->Get("bin46_NJets8910");
  TGraphAsymmErrors * g_0p2 = (TGraphAsymmErrors*)f_0p2->Get("bin46_NJets8910");

  TH1D * h3 = new TH1D("h3", ";#DeltaF_{dir} / (1 - F_{dir});Bins", 20, -1., 1.);
  h3->SetLineWidth(2);
  h3->SetLineColor(kBlue);
  TH1D * h2 = new TH1D("h2", ";#DeltaF_{dir} / (1 - F_{dir});Bins;", 20, -1., 1.);
  h2->SetLineWidth(2);
  h2->SetLineColor(2001);

  for (int i = 0; i < 38; ++i) {

    double x0, y0;
    g_0p4->GetPoint(i, x0, y0);
    double y0err = g_0p4->GetErrorY(i);

    double x1, y1;
    g_0p3->GetPoint(i, x1, y1);
    double y1err = g_0p3->GetErrorY(i);

    double x2, y2;
    g_0p2->GetPoint(i, x2, y2);
    double y2err = g_0p2->GetErrorY(i);

    double val1 = (y1-y0)/(1.-y0);
    h3->Fill(val1);

    double val2 = (y2-y0)/(1.-y0);
    h2->Fill(val2);
  }

  gStyle->SetOptStat("mr");

  // c1 is a hack to get the stats boxes
  TCanvas c1("c1", "", 800., 400.);
  c1.Divide(2, 1);
  c1.cd(1);
  h3->Draw();
  c1.cd(2);
  h2->Draw();
  c1.Update();
  gPad->Update();
  TPaveStats *st21 = (TPaveStats*)h3->FindObject("stats");
  st21->SetLineColor(kBlue);
  st21->SetTextColor(kBlue);
  TPaveStats *st22 = (TPaveStats*)h2->FindObject("stats");
  st22->SetLineColor(2001);
  st22->SetTextColor(2001);

  TCanvas * c2 = new TCanvas("c2", "", 500., 400.);
  h3->SetMaximum(18.);
  h3->Draw();
  h2->Draw("SAME");

  TLegend * l = new TLegend(0.20, 0.77, 0.62, 0.89);
  l->SetBorderSize(0);
  l->SetNColumns(2);
  l->AddEntry(h2, "#DeltaR = 0.2", "L");
  l->AddEntry(h3, "#DeltaR = 0.3", "L");
  l->Draw("same");


  double height = st22->GetY2NDC()-st22->GetY1NDC();
  double width = st22->GetX2NDC()-st22->GetX1NDC();
  st21->SetY2NDC(0.89);
  st21->SetY1NDC(0.89-height);
  st21->SetX2NDC(0.89);
  st21->SetX1NDC(0.89-width);
  st22->SetY2NDC(st21->GetY1NDC()-.005);
  st22->SetY1NDC(st22->GetY2NDC()-height);

  st22->SetX2NDC(st21->GetX2NDC());
  st22->SetX1NDC(st21->GetX1NDC());
  st21->Draw("same");
  st22->Draw("same");

  labelCMS(year);
  c2->SaveAs("plots"+year+"/fragSystematics46Scatter.pdf");
}
