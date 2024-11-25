#include "Plan.h"
#include <iostream>
#include <algorithm> // For std::find
#include <string>

Plan::Plan(const int planId, const Settlement& settlement,
    SelectionPolicy* selectionPolicy, const std::vector<FacilityType>& facilityOptions)
    : plan_id(planId), settlement(settlement),
    selectionPolicy(selectionPolicy->clone()),
    status(PlanStatus::AVALIABLE), facilityOptions(facilityOptions),
    life_quality_score(0), economy_score(0), environment_score(0) {
}

Plan::Plan(const Plan& other)
    : plan_id(other.plan_id), settlement(other.settlement),
    selectionPolicy(other.selectionPolicy->clone()),
    status(other.status), facilityOptions(other.facilityOptions),
    life_quality_score(other.life_quality_score),
    economy_score(other.economy_score),
    environment_score(other.environment_score) {
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
}

Plan& Plan::operator=(const Plan& other) {
    if (this != &other) {
        // Clean up existing resources
        delete selectionPolicy;
        for (Facility* f : facilities) {
            delete f;
        }
        for (Facility* f : underConstruction) {
            delete f;
        }

        // Copy simple data members
        plan_id = other.plan_id;
        settlement = other.settlement;
        status = other.status;
        facilityOptions = other.facilityOptions;
        life_quality_score = other.life_quality_score;
        economy_score = other.economy_score;
        environment_score = other.environment_score;

        // Copy selection policy
        selectionPolicy = other.selectionPolicy ? other.selectionPolicy->clone() : nullptr;

        // Deep copy facilities
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
}


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
    std::cout << "Plan ID: " << plan_id << ", Settlement Name: " << settlement.getName() << std::endl;
    std::cout << "Plan Status: " << getStringStatus() << std::endl;
    std::cout << "Selection Policy: " << selectionPolicy->toString() << std::endl;
    std::cout << "Life Quality Score: " << getlifeQualityScore() << std::endl;
    std::cout << "Economy Score: " << getEconomyScore() << std::endl;
    std::cout << "Environment Score: " << getEnvironmentScore() << std::endl;

    for (Facility* f : facilities) {
        if (std::find(underConstruction.begin(), underConstruction.end(), f) != underConstruction.end()) {
            std::cout << f->getName() << " facilityStatus: UnderConstruction" << std::endl;
        }
        else {
            std::cout << f->getName() << " facilityStatus: Operational" << std::endl;
        }
    }
}

void Plan::step() {
    // Implementation for advancing the state of the plan
}

const std::string Plan::toString() const {
    return "Plan ID: " + std::to_string(plan_id) + ", Settlement: " + settlement.getName();
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
