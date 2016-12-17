
#include "Storage.hh"
#include <iostream>
#include <fstream>
#include <G4String.hh>
#include <G4SIunits.hh>

using namespace std;

Storage* Storage::me = 0;

// singleton
Storage::Storage() {
    ReadAllNeutronData();
}

Storage* Storage::Get() {
    if (!me)
        me = new Storage();
    return me;
}

void Storage::ReadAllNeutronData() {
    for(int i = 0; i < sizeof(NEUTRON_CAPTURE_FILES)/sizeof(G4String); i++) {
        ReadNeutronCaptureData(NEUTRON_CAPTURE_FILES[i]);
    }
}

void Storage::ReadNeutronCaptureData(G4String fileName) {

    ifstream inFile(NEUTRON_CAPTURE_DIR + fileName);

    G4int z, a;
    inFile >> z >> a;
    Nucleus nucleus = {z, a};

    G4double probability, energy;
    G4int n;
    vector<NeutronCaptureGammas> neutronCaptureGammas;
    vector<G4double> gammaEnergies;
    while (inFile >> probability >> n) {
        gammaEnergies.clear();
        for(int i = 0; i < n; i++) {
            inFile >> energy;
            gammaEnergies.push_back(energy);
        }
        neutronCaptureGammas.push_back(NeutronCaptureGammas{probability, gammaEnergies});
    }

    pair<Nucleus, vector<NeutronCaptureGammas> > p(nucleus, neutronCaptureGammas);
    neutronCaptureData.insert(p);
}
