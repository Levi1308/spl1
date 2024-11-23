#include "Plan.h"
#include "iostream"
#include "Settlement.h"
    Plan::Plan(const int planId, const Settlement& settlement,
        SelectionPolicy* selectionPolicy, const vector<FacilityType>& facilityOptions)
        :plan_id(plan_id), settlement(settlement),
        selectionPolicy(selectionPolicy->clone()),
        status(status), facilityOptions(facilityOptions),
        life_quality_score(0),
        economy_score(0),
        environment_score(0)
    {
    };
Plan::Plan(const Plan& other)
    :plan_id(other.plan_id), settlement(other.settlement),
    selectionPolicy(other.selectionPolicy->clone()),
    status(other.status), facilityOptions(other.facilityOptions),
    life_quality_score(other.life_quality_score),
    economy_score(other.economy_score),
    environment_score(other.environment_score) {
    for (Facility* f : facilities)
    {
        facilities.push_back(f->clone());
    }
    for (Facility* f : underConstruction)
    {
        underConstruction.push_back(f->clone());
    }
}
Plan::~Plan(){
    delete selectionPolicy;
    for (Facility* f : facilities)
    {
        delete f;
    }
    for (Facility* f : underConstruction)
    {
        delete f;
    }
}
Plan Plan::operator= (const Plan& other){
    if (this != &other)
    {
        plan_id = other.plan_id;
        life_quality_score = other.life_quality_score;
        economy_score = other.economy_score;
        environment_score = other.environment_score;
        settlement = other.settlement;
        selectionPolicy = other.selectionPolicy->clone();
        facilities.clear();
        underConstruction.clear();
        for (Facility* f : other.facilities)
        {
            facilities.push_back(f);
        }
        for (Facility* f : other.underConstruction)
        {
            underConstruction.push_back(f);
        }
    }
    return *this;
}
 const int Plan::getEconomyScore() const{
    return economy_score;
 }
 const int Plan::getEnvironmentScore() const{
    return environment_score;
 }
 const int Plan::getlifeQualityScore() const{
    return life_quality_score;
 }
 const vector<Facility*> &Plan::getFacilities() const{
    return facilities;
 }
 const string Plan::getStringStatus() const {
     if (status == PlanStatus::AVALIABLE)
     {
         return "AVALIABLE";
     }
     else
         return "BUSY";
 }
 void Plan::printStatus(){
    std::cout<<"planID "+plan_id<<" settlementName: "+settlement.getName() << std::endl;
    std::cout << "planStatus" +getStringStatus() << std::endl;
    std::cout << "planStatus" + getStringStatus() << std::endl;
 }
 void Plan::step(){

 }
 const string Plan::toString() const{
    return "something";
 }
 void Plan::setSelectionPolicy(SelectionPolicy *newSelectionPolicy){
    selectionPolicy=newSelectionPolicy;
 }
 void Plan::addFacility(Facility* facility){
    facilities.push_back(facility);
 }
 const int Plan::getId() const {
     return plan_id;
 }