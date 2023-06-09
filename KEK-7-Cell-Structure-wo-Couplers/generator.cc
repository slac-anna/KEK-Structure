#include <iostream>
#include <fstream>
#include <string>

#include "generator.hh"

using namespace std;

MyPrimaryGenerator::MyPrimaryGenerator()
{
      fParticleGun = new G4ParticleGun(1);
      G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
      G4String particleName="electrons";
      G4ParticleDefinition *particle = particleTable->FindParticle("e-");

      G4ThreeVector pos(10*mm, 0*mm, 16*mm);
      G4ThreeVector mom(0, 0, 0);
      fParticleGun->SetParticlePosition(pos);
      fParticleGun->SetParticleMomentumDirection(mom);
      fParticleGun->SetParticleMomentum(100*MeV);
      fParticleGun->SetParticleDefinition(particle);
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
    delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
    fParticleGun->GeneratePrimaryVertex(anEvent);
}





