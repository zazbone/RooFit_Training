#include "TString.h"
#include "TStopwatch.h"
#include "TFile.h"
#include "TH1D.h"
#include "TRandom3.h"
#include "TMath.h"

#include <iostream>
#include <filesystem>
#include <memory>
#include <string>

#include "sampling.hpp"
#include "fitting.hpp"


namespace fs = std::filesystem;
using UPtrTFile = std::unique_ptr<TFile>;
using UPtrTH1D = std::unique_ptr<TH1D>;


const TString GENERATE_COMMAND { "generate" };
const TString FIT_COMMAND { "fit" };


Int_t generate(fs::path file);
Int_t fit(fs::path file);
TString getPrompt();


int main() {
	
	return 0;
}


Int_t fit(fs::path file) {
	UPtrTFile data = UPtrTFile { TFile::Open(file.c_str()) };
	UPtrTH1D hist1 = UPtrTH1D{ data->Get<TH1D>("h1") };
	fitBump(*hist1);
	return 0;
}

Int_t generate(fs::path file) {
	UInt_t size = 1 << 25;
	Double32_t frac = 0.01;
	Int_t nBins = TMath::Power(size, .3);
	UPtrTFile data = UPtrTFile{ TFile::Open(file.c_str(), "RECREATE") };
	TRandom3 rng {1234};
	TH1D hist1 { "h1", "Gaussian in exp", nBins, 0., 20. };
	fillGaus(hist1, UInt_t(frac * size), 9., 0.2, rng);
	fillExp(hist1, UInt_t((1. - frac) * size), 6., rng);
	
	return data->Write();
}

TString getPrompt() {
	TString prompt;
	std::cout << ">>> " << std::flush;

	std::cin >> prompt;
	prompt.Strip();
	prompt.Clear();

	return prompt;
}
