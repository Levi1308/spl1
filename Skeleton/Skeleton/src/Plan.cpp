#include "Plan.h"
#include "iostream"

Plan::Plan(const int planId, const Settlement &settlement,
 SelectionPolicy *selectionPolicy, const vector<FacilityType> &facilityOptions){
    plan_id=planId;
    
 };
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
 void Plan::printStatus(){
    std::cout<<"status"<<std::endl;
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
        