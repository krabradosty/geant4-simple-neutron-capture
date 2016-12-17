
#ifndef STORAGE_HH
#define STORAGE_HH

#include <iostream>
#include <vector>
#include <map>
#include <G4String.hh>
#include <G4ios.hh>

using namespace std;

struct Nucleus {
    G4int z, a;

    bool operator==(const Nucleus &o) const {
        return z == o.z && a == o.a;
    }

    bool operator<(const Nucleus &o) const {
        return z < o.z || a < o.a;
    }
};

struct NeutronCaptureGammas {
    G4double         probability;
    vector<G4double> gammaEnergies;
};

class Storage {
public:
    const G4String NEUTRON_CAPTURE_DIR = "/home/krab/workdir/simulation/B1/data/neutron_capture/";
    const G4String NEUTRON_CAPTURE_FILES[1] = {
            "Ni59.mac"
    };
private:
    Storage();
    virtual ~Storage() {}
    static Storage* me;

    void ReadNeutronCaptureData(G4String);
    void ReadAllNeutronData();


public:
    static Storage* Get();
    bool CheckNeutronCaptureData(G4int z, G4int a) {
        return neutronCaptureData.count(Nucleus{z, a}) > 0;
    };
    vector<NeutronCaptureGammas> GetNeutronCaptureData(G4int z, G4int a) { return neutronCaptureData[Nucleus{z, a}]; };

private:
    map<Nucleus, vector<NeutronCaptureGammas> > neutronCaptureData;
};

#endif //STORAGE_HH
