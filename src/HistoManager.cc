/*
 * @Author: Lingteng Kong 
 * @Date: 2020-07-15 15:11:11 
 * @Last Modified by: Lingteng Kong
 * @Last Modified time: 2020-07-17 02:07:14
 */

#include "HistoManager.hh"
#include "G4UnitsTable.hh"

HistoManager::HistoManager()
  : fFileName("data")
{
  Book();
}

HistoManager::~HistoManager()
{
  delete G4AnalysisManager::Instance();
}

//define what histos to plot
void HistoManager::Book()
{
  // Create or get analysis manager
  // The choice of analysis technology is done via selection of a namespace
  // in HistoManager.hh
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetFileName(fFileName);
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetActivation(true);     //enable inactivation of histograms
  
  // Define histograms start values
  //do not forget to change StackingAction.cc
  const G4int kMaxHisto = 11;
  const G4String id[] = {"0","1","2","3","4","5","6","7","8","9","10"};
  const G4String title[] = 
          { //scintillation photon info
            "distribution along x: scintillation photon",              //0
            "energy spectrum: scintillation photon",                   //1
            "wavelength(nm): scintillation photon",                    //2
            //distribution of other particles
            "distribution along x: gamma",                             //3
            "distribution along x: electron",                          //4
            "distribution along x: alpha",                             //5
            "distribution along x: ions",                              //6
            //kinetic energy spectrum of other particles
            "energy spectrum: gamma",                                  //7
            "energy spectrum: electron",                               //8
            "energy spectrum: alpha",                                  //9
            "energy spectrum: ions",     //charge > 2                  //10
          };

  // Default values (to be reset via /analysis/h1/set command)               
  G4int nbins = 100;
  G4double vmin = 0.;
  G4double vmax = 100.;

  // Create all histograms as inactivated 
  // as we have not yet set nbins, vmin, vmax
  for (G4int k=0; k<kMaxHisto; k++) {
    G4int ih = analysisManager->CreateH1(id[k], title[k], nbins, vmin, vmax);
    analysisManager->SetH1Activation(ih, false);
  }
}
