#pragma once
#include <string>
#include <vector>
#include "Simulation.h"
#include "Settlement.h"
#include "Action.h"
#include "plan.h"
#include "Facility.h"
#include <sstream>
#include <iostream>




BaseAction::BaseAction(){}

ActionStatus BaseAction::getStatus() const {
	return status;
}

void BaseAction::complete() {
	status = ActionStatus::COMPLETED;
    std::cout << "Action completed succesfully!" << std::endl;
}

SimulateStep::SimulateStep(const int numOFSteps) 
	:numOfSteps(numOFSteps){}

SimulateStep::SimulateStep(const SimulateStep& other)
	:numOfSteps(other.numOfSteps){}

void SimulateStep::act(Simulation& simulation) {
	for (int i = 1; i <= numOfSteps;i++) {
		simulation.step();
	}
    complete();
}

std::string actionStatusToString(ActionStatus status) {
    switch (status) {
    case ActionStatus::COMPLETED:
        return "COMPLETED";
    case ActionStatus::ERROR:
        return "ERROR";
    default:
        return "UNKNOWN";
    }
}

const string SimulateStep::toString() const {
    return "Step " + std::to_string(numOfSteps) + actionStatusToString(getStatus());
}


SimulateStep* SimulateStep::clone() const {
	return new SimulateStep(*this);
}

AddFacility::AddFacility(const string& AfacilityName, const FacilityCategory AfacilityCategory, const int Aprice, const int AlifeQualityScore, const int AeconomyScore, const int AenvironmentScore)
    :facilityName(AfacilityName), facilityCategory(AfacilityCategory), price(Aprice), lifeQualityScore(AlifeQualityScore), economyScore(AeconomyScore), environmentScore(AenvironmentScore){}

AddFacility::AddFacility(const AddFacility& other)
    :facilityName(other.facilityName), facilityCategory(other.facilityCategory), price(other.price), lifeQualityScore(other.lifeQualityScore), economyScore(other.economyScore), environmentScore(other.environmentScore){}

void AddFacility::act(Simulation& simulation) {
    FacilityType F(facilityName, facilityCategory, price, lifeQualityScore, economyScore, environmentScore);
    if (simulation.addFacility(F) == false) {
        error(getErrorMsg());
    }
    else {
        complete();
    }
     
}

AddFacility* AddFacility::clone() const {
    return new AddFacility(*this);
}



const string AddFacility::toString() const {
    return "Add Facility: " + facilityName + actionStatusToString(getStatus());
}
            

    PrintActionsLog::PrintActionsLog() {}

    void PrintActionsLog::act(Simulation& simulation) {
        // Retrieve the action log from the simulation
        const auto& actionLog = simulation.getActionLog();

        if (actionLog.empty()) {
            std::cout << "No actions logged yet." << std::endl;
            return;
        }

        for (BaseAction* action : actionLog) {
            if (action != nullptr) { // Ensure the action pointer is valid
                std::cout << action->toString()  << std::endl;
            }
        }
    }

    PrintActionsLog* PrintActionsLog::clone() const {
        return new PrintActionsLog();
    }

    const string PrintActionsLog::toString() const {
        return "PrintActionsLog";
    }

    Close::Close(){}

    void Close::act(Simulation& simulation) {
        const auto& plans = simulation.getPlans();

        if (plans.empty()) {
            std::cout << "No plans logged yet." << std::endl;
        }

        for (Plan p : plans) {
            std::cout << p.toString() << std::endl;
        }

        simulation.close();
    }
    Close* Close::clone() const {
        return new Close();
    }
    const string Close::toString() const {
        return "Close ";
    }











