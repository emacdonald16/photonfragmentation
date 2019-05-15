#include <TPaveText.h>
#include <TChain.h>
#include <TCanvas.h>
#include <TPad.h>
#include <TASImage.h>
#include <TLegend.h>
#include <TH1D.h>
#include <TCut.h>
#include <TColor.h>
#include <iostream>


const char * cmsText  = "CMS";
int cmsTextFont   = 61;

bool writeExtraText = true;
const char * extraText   = "Simulation";
int extraTextFont = 52;

float lumiTextSize     = 0.6;
float lumiTextOffset   = 0.2;

float cmsTextSize      = 0.75;
float cmsTextOffset    = 0.1;

float relPosX    = 0.045;
float relPosY    = 0.035;
float relExtraDY = 1.2;

float extraOverCmsTextSize  = 0.76;

string lumi_13TeV = "35.9 fb^{-1}";
string lumi_8TeV  = "19.7 fb^{-1}";
string lumi_7TeV  = "5.1 fb^{-1}";
string lumi_sqrtS = "";

bool drawLogo = false;


void labelCMS(TString year,const bool showlumi = true) {
  TLatex latex;
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack) ;

  float extraTextSize = extraOverCmsTextSize*cmsTextSize;
  latex.SetTextFont(cmsTextFont);
  latex.SetTextAlign(11);
  float t = 0.10;
  float l = 0.12;
  latex.SetTextSize(cmsTextSize*0.08);
  latex.DrawLatex(l,1-t+lumiTextOffset*t,cmsText);

  TPaveText * label0 = new TPaveText(0.3, .905, 0.85, .945, "NDC, NB");
  label0->SetFillColor(0);
  label0->SetTextAlign(25);
  label0->SetTextSize(0.044);
  if (showlumi) {
    if (year.Contains("2016"))      label0->AddText("Simulation                35.9 fb^{1} (13 TeV)");
    else if (year.Contains("2017")) label0->AddText("Simulation                41.5 fb^{1} (13 TeV)");
    else if (year.Contains("com") || year.Contains("V17")) label0->AddText("Simulation      2016+2017+2018 MC (13 TeV)");
  } else {
    label0->AddText("Simulation  #it{Preliminary}   (13 TeV)");
  }
  label0->Draw();
}



void CMS_lumi(TString year, TCanvas *pad, int iPeriod, float iPosX) {
  bool outOfFrame    = false;
  if(iPosX/10==0 ) outOfFrame = true;

  float alignY_=3.;
  float alignX_=2.;
  if( iPosX/10==0 ) alignX_=1.0;
  if( iPosX==0    ) alignY_=1.0;
  if( iPosX/10==1 ) alignX_=1.0;
  if( iPosX/10==2 ) alignX_=2.0;
  if( iPosX/10==3 ) alignX_=3.0;
  float align_ = 10.0*alignX_ + alignY_;

  float H = pad->GetWh();
  float W = pad->GetWw();
  float l = pad->GetLeftMargin();
  float t = pad->GetTopMargin();
  float r = pad->GetRightMargin();
  float b = pad->GetBottomMargin();
  float e = 0.025;

  pad->cd();

  const char * lumiText16 = "35.9 fb^{-1} (13 TeV)";
  const char * lumiText17 = "41.5 fb^{-1} (13 TeV)";
  const char * lumiTextcom = "2016+2017+2018 MC (13 TeV)";


  TLatex latex;
  latex.SetNDC();
  latex.SetTextAngle(0);
  latex.SetTextColor(kBlack) ;

  float extraTextSize = extraOverCmsTextSize*cmsTextSize;
  latex.SetTextFont(42);
  latex.SetTextAlign(31) ;
  latex.SetTextSize(lumiTextSize*t)  ;

  if (year.Contains("2016")) latex.DrawLatex(1-r,1-t+lumiTextOffset*t,lumiText16);
  else if (year.Contains("2017")) latex.DrawLatex(1-r,1-t+lumiTextOffset*t,lumiText17);
  else if (year.Contains("com") || year.Contains("V17") ) latex.DrawLatex(1-r,1-t+lumiTextOffset*t,lumiTextcom);

  if( outOfFrame ){
    latex.SetTextFont(cmsTextFont);
    latex.SetTextAlign(11);
    latex.SetTextSize(cmsTextSize*t);
    latex.DrawLatex(l,1-t+lumiTextOffset*t,cmsText);
  }
  pad->cd();

  float posX_ = 0;
  posX_ =   l + relPosX*(1-l-r);
  //if( iPosX%10<=1 ) posX_ =   l + relPosX*(1-l-r);
  //else if( iPosX%10==2 ) posX_ =  l + 0.5*(1-l-r);
  //else if( iPosX%10==3 )posX_ =  1-r - relPosX*(1-l-r);

  float posY_ = 1-t - relPosY*(1-t-b);

  if( !outOfFrame ){
    if( drawLogo ){
      posX_ =   l + 0.045*(1-l-r)*W/H;
      posY_ = 1-t - 0.045*(1-t-b);
      float xl_0 = posX_;
      float yl_0 = posY_ - 0.15;
      float xl_1 = posX_ + 0.15*H/W;
      float yl_1 = posY_;
      TASImage CMS_logo = TASImage("CMS-BW-label.png");
      TPad *pad_logo =  new TPad("logo","logo", xl_0, yl_0, xl_1, yl_1 );
      pad_logo->Draw();
      pad_logo->cd();
      CMS_logo.Draw("X");
      pad_logo->Modified();
      pad->cd();
    }
    else {
      latex.SetTextFont(cmsTextFont);
      latex.SetTextSize(cmsTextSize*t);
      latex.SetTextAlign(align_);
      latex.DrawLatex(posX_, posY_, cmsText);
      if( writeExtraText ) {
        latex.SetTextFont(extraTextFont);
        latex.SetTextAlign(align_);
        latex.SetTextSize(extraTextSize*t);
        latex.DrawLatex(posX_+3*r, posY_- relExtraDY*cmsTextSize*t, extraText);
      }
    }
  }
  else if( writeExtraText ){
    if( iPosX==0){
      posX_ =   l +  relPosX*(1-l-r);
      posY_ =   1-t+lumiTextOffset*t;
    }
    latex.SetTextFont(extraTextFont);
    latex.SetTextSize(extraTextSize*t);
    latex.SetTextAlign(align_);
    latex.DrawLatex(posX_+3*r, posY_, extraText) ;
  }
  pad->Update();

}
