#pragma once
#include <string>
#include <vector>
#include "Simulation.h"
#include "Settlement.h"
#include "Action.h"
#include "Plan.h"
#include "Facility.h"
#include <sstream>
#include <iostream>




BaseAction::BaseAction()
:errorMsg(""),status()
{}

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

void BaseAction::error(string errorMsg) {
	status = ActionStatus::ERROR;
	errorMsg = errorMsg;
	std::cout << "ERROR: Action faild " + errorMsg << std::endl;
}
const string& BaseAction::getErrorMsg() const {
	return errorMsg;
}
void AddSettlement::act(Simulation& simulation) {
	if (!simulation.isSettlementExists(settlementName))
	{
		Settlement* s = new Settlement(settlementName, settlementType);
		simulation.addSettlement(s);
		complete();
	}
	else
		std::cout << "Settlement already Exist" << std::endl;
}
const string AddSettlement::toString() const {
	return "Adding Settlement";
}
AddSettlement* AddSettlement::clone() const{
	return new AddSettlement(settlementName, settlementType);
}
AddSettlement::AddSettlement(const string& settlementName, SettlementType settlementType)
	:settlementName(settlementName), settlementType(settlementType)
{
};


AddPlan::AddPlan(const string& settlementName, const string& selectionPolicy)
	:settlementName(settlementName), selectionPolicy(selectionPolicy)
{

}
void AddPlan::act(Simulation& simulation) {
	Settlement s = simulation.getSettlement(settlementName);
	if (s.getName() != "")
	{
		if (selectionPolicy == "nve") {
			simulation.addPlan(s, new NaiveSelection());
			complete();
		}
		else if (selectionPolicy == "bal") {
			simulation.addPlan(s, new BalancedSelection(0, 0, 0));

			complete();
		}
		else if (selectionPolicy == "eco") {
			simulation.addPlan(s, new EconomySelection());

			complete();
		}
		else if (selectionPolicy == "env") {
			simulation.addPlan(s, new SustainabilitySelection());
			complete();
		}
	}
	error("Cannot create this plan");
};
	const string AddPlan::toString() const {
		return "Add Plan";
	};
AddPlan* AddPlan::clone() const {
	return new AddPlan(settlementName, selectionPolicy);
}

PrintPlanStatus::PrintPlanStatus(int planId)
	:planId(planId)
{

};
void PrintPlanStatus::act(Simulation& simulation) {
	Plan* p = new Plan(simulation.getPlan(planId));
	if(p!=nullptr)
	{
		if (p->getId() != -1)
		{
		p->printStatus();
		complete();
		}
	}
	else
		error("Plan doesn't exist");
};
PrintPlanStatus* PrintPlanStatus::clone() const {
	return new PrintPlanStatus(planId);
}
const string PrintPlanStatus::toString() const {
	return "Printing Status of a Plan";
}
ChangePlanPolicy::ChangePlanPolicy(const int planId, const string& newPolicy)
	:planId(planId), newPolicy(newPolicy)
{

};
void ChangePlanPolicy::act(Simulation& simulation) {
	Plan* p = new Plan(simulation.getPlan(planId));
	if(p!=nullptr)
	{
	if (p->getId() != -1 && p->CheckPolicy(newPolicy))
	{
		simulation.setPlanPolicy(planId, newPolicy);
		complete();
		//delete p;
	}
	}
	error("Cannot change selection policy");
	delete p;
};
ChangePlanPolicy* ChangePlanPolicy::clone() const {
	return new ChangePlanPolicy(planId, newPolicy);
};
const string ChangePlanPolicy::toString() const {
	return "Changing Policy of a Plan";
};
BackupSimulation::BackupSimulation() {
	
}

void BackupSimulation::act(Simulation& simulation) {
	simulation.BackUp();
}
BackupSimulation* BackupSimulation::clone() const{
	return new BackupSimulation();
}
const string BackupSimulation::toString() const {
	return "Backup Simulation";
}

RestoreSimulation::RestoreSimulation() {
	
}
void RestoreSimulation::act(Simulation& simulation) {
	simulation.Restore();
}
RestoreSimulation* RestoreSimulation::clone() const {
	return new RestoreSimulation();
}
const string RestoreSimulation::toString() const {
	return "Restoring simulation";
};