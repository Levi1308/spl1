#include "Plan.h"
#include <iostream>
#include <algorithm> // For std::find
#include <string>

Plan::Plan(const int planId, const Settlement& settlement,
    SelectionPolicy* selectionPolicy, const std::vector<FacilityType>& facilityOptions)
    : plan_id(planId), settlement(settlement),
    selectionPolicy(selectionPolicy->clone()),
    status(PlanStatus::AVALIABLE), 
    facilities(vector<Facility*>()),
    underConstruction(vector<Facility*>()),
    facilityOptions(facilityOptions),
    life_quality_score(0), economy_score(0), environment_score(0) {
}
//Rule of 5
Plan::Plan(const Plan& other)
    : plan_id(other.plan_id), settlement(other.settlement),
    selectionPolicy(other.selectionPolicy->clone()),
    status(other.status),
    facilities(), underConstruction(), facilityOptions(other.facilityOptions),
    life_quality_score(other.life_quality_score),
    economy_score(other.economy_score),
    environment_score(other.environment_score){
    for (Facility* f : other.facilities) {
        facilities.push_back(f->clone());
    }
    for (Facility* f : other.underConstruction) {
        underConstruction.push_back(f->clone());
    }
}

Plan::~Plan() {
    delete selectionPolicy;
    for (Facility* f : facilities) {
        delete f;
    }
    for (Facility* f : underConstruction) {
        delete f;
    }
    facilities.clear();
    underConstruction.clear();
}

Plan& Plan::operator=(const Plan& other) {
    if (this != &other) {
        delete selectionPolicy;
        for (Facility* f : facilities) {
            delete f;
        }
        for (Facility* f : underConstruction) {
            delete f;
        }
        plan_id = other.plan_id;
        status = other.status;
        life_quality_score = other.life_quality_score;
        economy_score = other.economy_score;
        environment_score = other.environment_score;
        selectionPolicy = other.selectionPolicy->clone();
        facilities.clear();
        for (Facility* f : other.facilities) {
            facilities.push_back(f->clone());
        }
        underConstruction.clear();
        for (Facility* f : other.underConstruction) {
            underConstruction.push_back(f->clone());
        }
    }
    return *this;
};



const int Plan::getEconomyScore() const {
    return economy_score;
}

const int Plan::getEnvironmentScore() const {
    return environment_score;
}

const int Plan::getlifeQualityScore() const {
    return life_quality_score;
}

const std::vector<Facility*>& Plan::getFacilities() const {
    return facilities;
}

const std::string Plan::getStringStatus() const {
    if (status == PlanStatus::AVALIABLE) {
        return "AVALIABLE";
    }
    return "BUSY";
}

void Plan::printStatus() {
    std::cout << "Plan ID: " << plan_id <<std::endl;
    std::cout<<"Settlement Name: " << settlement.getName() << std::endl;
    std::cout << "PlanStatus: " << getStringStatus() << std::endl;
    std::cout << "SelectionPolicy: " << selectionPolicy->toString()<< std::endl;
    std::cout << "LifeQualityScore: " << getlifeQualityScore() << std::endl;
    std::cout << "EconomyScore: " << getEconomyScore() << std::endl;
    std::cout << "EnvironmentScore: " << getEnvironmentScore() << std::endl;
    for (Facility* f : facilities) {
            std::cout << f->toString() << std::endl;
            }
    for (Facility* f : underConstruction) {    
            std::cout << f->toString() << std::endl;  
    }
}

void Plan::step() {

    if (getPlanStatus()==PlanStatus::AVALIABLE) {
        while ( (int) (settlement.getType()) >= (int) (underConstruction.size()) ) {
            Facility* F = new Facility(getSelectionPolicy()->selectFacility(facilityOptions), settlement.getName());
            underConstruction.push_back(F);
        }
    }
    std::vector<Facility*> toRemove;

    for (Facility* facility : underConstruction) {
        if (facility->step() == FacilityStatus::OPERATIONAL) {
            addFacility(facility);
            setLifeQualityScore(facility->getLifeQualityScore());
            setEconomyScore(facility->getEconomyScore());
            setEnvironmentScore(facility->getEnvironmentScore());
            if (getSelectionPolicy()->Nickname() == "bal") {
                selectionPolicy->setScores(facility->getLifeQualityScore(), facility->getEconomyScore(), facility->getEnvironmentScore());
            }
            toRemove.push_back(facility);
            
        }
    }

    for (Facility* facility : toRemove) {
        underConstruction.erase(std::remove(underConstruction.begin(), underConstruction.end(), facility), underConstruction.end());
        delete facility;
    }

    if ( (int) (underConstruction.size()) <= (int) (settlement.getType()))
        setPlanStatus(PlanStatus::AVALIABLE);
    else{
        setPlanStatus(PlanStatus::BUSY);
    }
}

const std::string Plan::toString() const {
    std::string result = "Plan ID: " + std::to_string(plan_id) + "\n";
    result += "Settlement: " + settlement.getName() + "\n"; // Assuming Settlement has getName()
    result += "Life Quality Score: " + std::to_string(life_quality_score) + "\n";
    result += "Economy Score: " + std::to_string(economy_score) + "\n";
    result += "Environment Score: " + std::to_string(environment_score) + "\n";
    return result;
}


void Plan::setSelectionPolicy(SelectionPolicy* newSelectionPolicy) {
    if (selectionPolicy) {
        delete selectionPolicy;
    }
    selectionPolicy = newSelectionPolicy->clone();
}

void Plan::addFacility(Facility* facility) {
    facilities.push_back(facility);
}

const int Plan::getId() const {
    return plan_id;
}

SelectionPolicy* Plan::getSelectionPolicy() const {
    return selectionPolicy;
}

PlanStatus Plan::getPlanStatus() {
    return status;
}
void Plan::setPlanStatus(PlanStatus p) {
    status = p;
}

Plan::Plan(int plan_id)
    : plan_id(plan_id),
    settlement(Settlement("",SettlementType::CITY)),
    selectionPolicy(nullptr), 
    status(PlanStatus::AVALIABLE),
    facilities(vector<Facility*>()),
    underConstruction(vector<Facility*>()),
    facilityOptions(vector<FacilityType>()),
    life_quality_score(0),
    economy_score(0),
    environment_score(0) {
};
bool Plan::CheckPolicy(string newpolicy) {
    if ((newpolicy == selectionPolicy->Nickname()))
        return true;
    return false;
}

Plan::Plan()
    : plan_id(-1),settlement(Settlement("",SettlementType::CITY)),                
    selectionPolicy(nullptr),
    status(PlanStatus::AVALIABLE),       
    facilities(vector<Facility*>()),
    underConstruction(vector<Facility*>()),
    facilityOptions(vector<FacilityType>()),
    life_quality_score(0),economy_score(0),
    environment_score(0)
{
    
}const int Plan::getUnderunderConstructionLQS() const{
    int LQS = 0;
    for(Facility* F: underConstruction){
        LQS = LQS +F->getLifeQualityScore();
    }
    return LQS;
}

const int Plan::getUnderunderConstructionECS() const{
    int ECS = 0;
    for(Facility* F: underConstruction){
        ECS = ECS + F->getEconomyScore();
    }
    return ECS;
}

const int Plan::getUnderunderConstructionENS() const{
    int ENS = 0;
    for(Facility* F: underConstruction){
        ENS = ENS + F->getEnvironmentScore();
    }
    return ENS;
}

void Plan::setLifeQualityScore(int addL) {
    life_quality_score = life_quality_score + addL;
}

void Plan::setEconomyScore(int addEc) {
    economy_score = economy_score + addEc;
}

void Plan::setEnvironmentScore(int addEn) {
    environment_score = environment_score + addEn;
}
