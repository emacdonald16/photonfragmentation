#include <TH1D.h>
#include <TLine.h>
#include <TColor.h>

TColor *uscb_gold = new TColor(2001, 255/255.,200/255.,47/255);
TColor *penn_red = new TColor(2002, 255/255.,0/255.,43/255.);
TColor *grayed_jade = new TColor(2006, 105/255.,166/255., 202/255.);
TColor *dusk_blue = new TColor(2007, 133/255.,189/255., 164/255.);

void drawLines46(const double min, const double max) {
   TLine * line[4];
   line[0] = new TLine(10.5, min, 10.5, max);
   line[1] = new TLine(20.5, min, 20.5, max);
   line[2] = new TLine(30.5, min, 30.5, max);
   line[3] = new TLine(38.5, min, 38.5, max);
   for (int i = 0; i < 4; ++i) {
      line[i]->SetLineStyle(2);
      line[i]->SetLineColor(kBlack);
      line[i]->Draw();
   }
}

TH1D * binShifts46(TH1D * inHist, const TString name)
{
   TH1D * hist = new TH1D(name, ";46-bin NJets-HT-MHT plane;", 46, 0.5, 46.5);
   int wB = 1;
   for (int i = 1; i <= 50; ++i) {
      double c = inHist->GetBinContent(i);
      double e = inHist->GetBinError(i);
      if (i!=31 && i!=34 && i!=41 && i!=44) {
         hist->SetBinContent(wB, c);
         hist->SetBinError(wB, e);
         ++wB;
      }
   }
   return hist;
}

TH1D * binShifts59(TH1D * inHist, const TString name)
{
   TH1D * hist = new TH1D(name, ";59-bin NJets-HT-MHT plane;", 59, 0.5, 59.5);
   int wB = 1;
   for (int i = 1; i <= 65; ++i) {
      double c = inHist->GetBinContent(i);
      double e = inHist->GetBinError(i);
      if (i!=40 && i!=43 && i!=46 && i!=53 && i!=56 && i!=59) {
         hist->SetBinContent(wB, c);
         hist->SetBinError(wB, e);
         ++wB;
      }
   }
   return hist;
}

int whichBin_HTMHT13(const double HT, const double MHT, const int NJets)
{
   // 250 <= MHT < 300
   if (HT>=300.  && HT<600.  && MHT>=250. && MHT<300.) return 1;
   if (HT>=600.  && HT<1200. && MHT>=250. && MHT<300.) return 2;
   if (HT>=1200.             && MHT>=250. && MHT<300.) return 3;
   // 300 <= MHT < 350
   if (HT>=300.  && HT<600.  && MHT>=300. && MHT<350.) return 4;
   //if (HT>=300.  && HT<500.  && MHT>=300. && MHT<350.) if (NJets<7) return 4;
   if (HT>=600.  && HT<1200. && MHT>=300. && MHT<350.) return 5;
   if (HT>=1200.             && MHT>=300. && MHT<350.) return 6;
   // 350 <= MHT < 600
   if (HT>=350.  && HT<600.  && MHT>=350. && MHT<600.) return 7;
   if (HT>=600.  && HT<1200. && MHT>=350. && MHT<600.) return 8;
   if (HT>=1200.             && MHT>=350. && MHT<600.) return 9;
   // 500 <= MHT < 850
   if (HT>=600.  && HT<1200. && MHT>=600. && MHT<850.) return 10;
   if (HT>=1200.             && MHT>=600. && MHT<850.) return 11;
    // 850 <= MHT
   if (HT>=850.  && HT<1700. && MHT>=850.            ) return 12;
   if (HT>=1700.             && MHT>=850.            ) return 13;
   return 0;
}

int whichBin_HTMHT(const double HT, const double MHT, const int NJets)
{
   // 300 < MHT < 350
   if (HT>=300.  && HT<600.  && MHT>=300. && MHT<350.) return 1;
   if (HT>=600.  && HT<1200. && MHT>=300. && MHT<350.) return 2;
   if (HT>=1200.             && MHT>=300. && MHT<350.) return 3;
   // 350 < MHT < 600
   if (HT>=350.  && HT<600.  && MHT>=350. && MHT<600.) return 4;
   if (HT>=600.  && HT<1200. && MHT>=350. && MHT<600.) return 5;
   if (HT>=1200.             && MHT>=350. && MHT<600.) return 6;
   // 600 < MHT < 850
   if (HT>=600.  && HT<1200. && MHT>=600. && MHT<850.) return 7;
   if (HT>=1200.             && MHT>=600. && MHT<850.) return 8;
    // 850 < MHT
   if (HT>=850.  && HT<1700. && MHT>=850.            ) return 9;
   if (HT>=1700.             && MHT>=850.            ) return 10;
   return 0;
}

int whichBin_NJets(const int NJets)
{
   if (NJets==2||NJets==3) return 1;
   if (NJets==4||NJets==5) return 2;
   if (NJets==6||NJets==7) return 3;
   if (NJets==8||NJets==9) return 4;
   if (NJets>=10) return 5;
   return 0;
}

std::vector<int> whichBin_NJets8910(const int NJets)
{
   std::vector<int> vec;
   if (NJets==2||NJets==3) vec.push_back(1);
   if (NJets==4||NJets==5) vec.push_back(2);
   if (NJets==6||NJets==7) vec.push_back(3);
   if (NJets>=8) vec.push_back(4);
   if (NJets>=8) vec.push_back(5);
   return vec;
}

int whichBin_50(const double HT, const double MHT, const int NJets)
{
   const int NJetsBin = whichBin_NJets(NJets);
   const int HTMHTBin = whichBin_HTMHT(HT, MHT, NJets);
   return 10*(NJetsBin-1) + HTMHTBin;
}

int whichBin_65(const double HT, const double MHT, const int NJets)
{
   const int NJetsBin = whichBin_NJets(NJets);
   const int HTMHT13Bin = whichBin_HTMHT13(HT, MHT, NJets);
   return 13*(NJetsBin-1) + HTMHT13Bin;
}

bool whichBin_50_NJets8910(const double HT, const double MHT, const int NJets, const int bin)
{
   const int HTMHTBin = whichBin_HTMHT(HT, MHT, NJets);
   std::vector<int> NJetsbins = whichBin_NJets8910(NJets);
   for (unsigned int i = 0; i < NJetsbins.size(); ++i) {
      int tempBin = 10*(NJetsbins.at(i)-1) + HTMHTBin;
      if (tempBin == bin) return true;
   }
   return false;
}

bool whichBin_65_NJets8910(const double HT, const double MHT, const int NJets, const int bin)
{
   const int HTMHT13Bin = whichBin_HTMHT13(HT, MHT, NJets);
   std::vector<int> NJetsbins = whichBin_NJets8910(NJets);
   for (unsigned int i = 0; i < NJetsbins.size(); ++i) {
      int tempBin = 13*(NJetsbins.at(i)-1) + HTMHT13Bin;
      if (tempBin == bin) return true;
   }
   return false;
}
