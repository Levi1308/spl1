#include "SelectionPolicy.h"
#include "Facility.h"
#include "iostream"
#include <string>
#include <vector>
#include <Simulation.h>
#include <cstdlib> 
#include <algorithm> 
using std::vector;
using std::string;


//Constructor of NaiveSelection
NaiveSelection:: NaiveSelection()
:lastSelectedIndex(-1){}


// Copy Constructor for NaiveSelection
NaiveSelection:: NaiveSelection(const NaiveSelection &other):lastSelectedIndex(other.lastSelectedIndex){}

// other methods for NaiveSelection
const string NaiveSelection::toString() const {
return "nve";}

NaiveSelection* NaiveSelection::clone() const {
return new NaiveSelection(*this);}

const FacilityType& NaiveSelection::selectFacility (const vector<FacilityType>& facilitiesOptions) {
lastSelectedIndex++;
return facilitiesOptions[lastSelectedIndex];};

const string NaiveSelection::Nickname() const {
    return "nve";
}



//Constructor of BalancedSelection
BalancedSelection:: BalancedSelection(int BLifeQualityScore, int BEconomyScore, int BEnvironmentScore)
: LifeQualityScore(BLifeQualityScore), EconomyScore(BEconomyScore), EnvironmentScore(BEnvironmentScore){}

// Copy Constructor for BalancedSelection
BalancedSelection::BalancedSelection(const BalancedSelection &other)
: LifeQualityScore(other.LifeQualityScore), EconomyScore(other.EconomyScore), EnvironmentScore(other.EnvironmentScore) {}

// other methods for BalancedSelection
const string BalancedSelection::toString() const{
return "bal";}

BalancedSelection* BalancedSelection::clone() const {
return new BalancedSelection(*this);}

const FacilityType& BalancedSelection::selectFacility(const vector<FacilityType>& facilitiesOptions){
int IBselection = 0;
int Bdistance;

for (int i = 0; i < int (facilitiesOptions.size()); i++ ){
    int Lscore = facilitiesOptions[i].getLifeQualityScore()+ LifeQualityScore;
    int Ecscore = facilitiesOptions[i].getEconomyScore()+ EconomyScore;
    int Envscore = facilitiesOptions[i].getEnvironmentScore()+ EnvironmentScore;
    int Idistance =  CloseDistance(Lscore,Ecscore,Envscore);
    if( Idistance == 0 )
        return facilitiesOptions[i];
    if (i == 0){
        Bdistance = Idistance;
    }
    else{
        if(Bdistance > Idistance){
            Bdistance = Idistance;
            IBselection = i;
        }
    }
}
LifeQualityScore = facilitiesOptions[IBselection].getLifeQualityScore() + LifeQualityScore;
EconomyScore = facilitiesOptions[IBselection].getEconomyScore() + EconomyScore;
EnvironmentScore = facilitiesOptions[IBselection].getEnvironmentScore() + EnvironmentScore;
return facilitiesOptions[IBselection];
};
int SelectionPolicy::CloseDistance(int x,int y,int z){
    int diff1 = std::abs(x - y);
    int diff2 = std::abs(y - z);
    int diff3 = std::abs(z - x);
    return std::max({diff1, diff2, diff3});
}
const string BalancedSelection::Nickname() const {
    return "bal";
}



//Constructor of EconomySelection
EconomySelection:: EconomySelection()
:lastSelectedIndex(-1){}

// Copy Constructor for EconomySelection
EconomySelection::EconomySelection(const EconomySelection &other)
:lastSelectedIndex(other.lastSelectedIndex){}

// other methods for EconomySelection
const string EconomySelection::toString() const{
return "eco";}

EconomySelection* EconomySelection :: clone() const{
return new EconomySelection(*this);}

const FacilityType& EconomySelection:: selectFacility(const vector<FacilityType>& facilitiesOptions){
for(int i = lastSelectedIndex + 1 ; i < int (facilitiesOptions.size()); i++){
    if(facilitiesOptions[i].getCategory() == FacilityCategory::ECONOMY){
         lastSelectedIndex = i;
         return facilitiesOptions[i];
    }    
}
return facilitiesOptions[lastSelectedIndex];

};


const string EconomySelection::Nickname() const {
    return "eco";
}

//Constructor of SustainabilitySelection
SustainabilitySelection::SustainabilitySelection()
:lastSelectedIndex(-1){}

// Copy Constructor for SustainabilitySelection
SustainabilitySelection::SustainabilitySelection(const SustainabilitySelection &other)
:lastSelectedIndex(other.lastSelectedIndex){}

// other methods for SustainabilitySelection
const string SustainabilitySelection::toString() const{
return "env";}


SustainabilitySelection* SustainabilitySelection:: clone() const {
return new SustainabilitySelection(*this);
}

const FacilityType& SustainabilitySelection::selectFacility(const vector<FacilityType>& facilitiesOptions){
for(int i = lastSelectedIndex + 1 ; i < int (facilitiesOptions.size()); i++){
    if(facilitiesOptions[i].getCategory() == FacilityCategory::ENVIRONMENT){
         lastSelectedIndex = i;
         return facilitiesOptions[i];
    }    
}
return facilitiesOptions[lastSelectedIndex];
}
const string SustainabilitySelection::Nickname() const {
    return "env";
}

