#include <string>
#include <vector>
#include "Simulation.h"
#include "Settlement.h"
#include "Action.h"
#include "Plan.h"
#include "Facility.h"
#include <sstream>
#include <iostream>


class Simulation;
//BaseAction Class
BaseAction::BaseAction()
:errorMsg(""),status()
{}

ActionStatus BaseAction::getStatus() const {
	return status;
}

void BaseAction::complete() {
	status = ActionStatus::COMPLETED;
}
void BaseAction::error(string errorMsg) {
	status = ActionStatus::ERROR;
	std::cout << "ERROR: " + errorMsg << std::endl;
}
const string& BaseAction::getErrorMsg() const {
	return errorMsg;
}

std::string actionStatusToString(ActionStatus status) {
    if (status == ActionStatus::COMPLETED) {
        return "COMPLETED";
    } else if (status == ActionStatus::ERROR) {
        return "ERROR";
    } else {
        return "UNKNOWN";
    }
}
std::string facilityCategoryToString(FacilityCategory category) {
    if (category == FacilityCategory::LIFE_QUALITY) {
        return "1";
    } else if (category == FacilityCategory::ECONOMY) {
        return "2";
    } else if (category == FacilityCategory::ENVIRONMENT) {
        return "3";
    } else {
        return "0"; // Default value for unknown categories
    }
}
std::string settlementTypeToNumberString(SettlementType type) {
    switch (type) {
        case SettlementType::VILLAGE:
            return "1";
        case SettlementType::CITY:
            return "2";
        case SettlementType::METROPOLIS:
            return "3";
        default:
            return "0"; // Default value for unknown types
    }
}




// SimulateStep Class
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



const string SimulateStep::toString() const {
    return "SimulationStep " + std::to_string(numOfSteps)+" "+ actionStatusToString(getStatus());
}


SimulateStep* SimulateStep::clone() const {
	return new SimulateStep(*this);
}

//AddFacility Class
AddFacility::AddFacility(const string& AfacilityName, const FacilityCategory AfacilityCategory, const int Aprice, const int AlifeQualityScore, const int AeconomyScore, const int AenvironmentScore)
    :facilityName(AfacilityName), facilityCategory(AfacilityCategory), price(Aprice), lifeQualityScore(AlifeQualityScore), economyScore(AeconomyScore), environmentScore(AenvironmentScore){}


void AddFacility::act(Simulation& simulation) {
    FacilityType F(facilityName, facilityCategory, price, lifeQualityScore, economyScore, environmentScore);
    if (simulation.addFacility(F) == false) {
        error("Facility already exists");
    }
    else {
        complete();
    }
     
}

AddFacility* AddFacility::clone() const {
    return new AddFacility(*this);
}

const string AddFacility::toString() const {
    return "Facility " + facilityName + facilityCategoryToString (facilityCategory) + " " +
	 std::to_string(price) + " " + std::to_string(lifeQualityScore) + " " +
	 std::to_string(economyScore) + " " + std::to_string(environmentScore) + " " + actionStatusToString(getStatus());
}


//PrintActionLog Class
    PrintActionsLog::PrintActionsLog() {}

    void PrintActionsLog::act(Simulation& simulation) {
        const auto& actionLog = simulation.getActionLog();

        if (actionLog.empty()) {
            std::cout << "No actions logged yet." << std::endl;
            return;
        }

        for (BaseAction* action : actionLog) {
            if (action != nullptr) { 
                std::cout << action->toString() << std::endl;
            }
        }
    }

    PrintActionsLog* PrintActionsLog::clone() const {
        return new PrintActionsLog();
    }

    const string PrintActionsLog::toString() const {
        return "PrintActionsLog";
    }
//Close Class
    Close::Close(){}

    void Close::act(Simulation& simulation) {
        const auto& plans = simulation.getPlans();

        if (plans.empty()) {
            std::cout << "No plans logged yet." << std::endl;
        }
        for (Plan p : plans) {
             p.printStatus();
        }
        simulation.close();
        complete();
    }
    Close* Close::clone() const {
        return new Close();
    }
    const string Close::toString() const {
        return "Close ";
    }


//AddSettlement Class
void AddSettlement::act(Simulation& simulation) {
	if (!simulation.isSettlementExists(settlementName))
	{
		Settlement* s = new Settlement(settlementName, settlementType);
		simulation.addSettlement(s);
		complete();
	}
	else
		error("Settlement already Exist");
}
const string AddSettlement::toString() const {
	return "Settlement " + settlementName + " " +settlementTypeToNumberString(settlementType) + " " + actionStatusToString(getStatus());
}
AddSettlement* AddSettlement::clone() const{
	return new AddSettlement(settlementName, settlementType);
}
AddSettlement::AddSettlement(const string& settlementName, SettlementType settlementType)
	:settlementName(settlementName), settlementType(settlementType)
{
};


//AddPlan Class
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
		return "Plan " + settlementName + " " + selectionPolicy + " " + actionStatusToString(getStatus()) ;
	};
AddPlan* AddPlan::clone() const {
	return new AddPlan(settlementName, selectionPolicy);
}


//PringPlanStatus Class
PrintPlanStatus::PrintPlanStatus(int planId)
	:planId(planId)
{

};
void PrintPlanStatus::act(Simulation& simulation) {
	Plan p = simulation.getPlan(planId);
		if (p.getId() != -1)
		{
		p.printStatus();
		complete();
		}
	else
		error("Plan doesn't exist");
};
PrintPlanStatus* PrintPlanStatus::clone() const {
	return new PrintPlanStatus(planId);
}
const string PrintPlanStatus::toString() const {
	return "PrintPlanStatus "+ std::to_string(planId) + " " + actionStatusToString(getStatus());
}


//ChangePlanPolicy Class
ChangePlanPolicy::ChangePlanPolicy(const int planId, const string& newPolicy)
	:planId(planId), newPolicy(newPolicy)
{

};
void ChangePlanPolicy::act(Simulation& simulation) {
	Plan p = simulation.getPlan(planId);
		if (p.getId() != -1)
	{
	if (p.getId() != -1 && p.CheckPolicy(newPolicy))
	{
		simulation.setPlanPolicy(planId, newPolicy);
		std::cout<<"planID: " + std::to_string(p.getId())<< std::endl;
		std::cout<<"prviousPolicy: " + p.getSelectionPolicy()->toString()<<std::endl;
		std::cout<<"newPolicy: " + newPolicy;
		complete();
	}
	}
	error("Cannot change selection policy");
};
ChangePlanPolicy* ChangePlanPolicy::clone() const {
	return new ChangePlanPolicy(planId, newPolicy);
};
const string ChangePlanPolicy::toString() const {
	return "ChangePlanPolicy " + std::to_string(planId) +  " " + newPolicy + " " + actionStatusToString(getStatus());
};


//BackupSimulation Class
BackupSimulation::BackupSimulation() {
	
}

void BackupSimulation::act(Simulation& simulation) {
	simulation.BackUp();
}
BackupSimulation* BackupSimulation::clone() const{
	return new BackupSimulation();
}
const string BackupSimulation::toString() const {
	return "BackupSimulation " + actionStatusToString(getStatus());
}

RestoreSimulation::RestoreSimulation() {
	
}
void RestoreSimulation::act(Simulation& simulation) {
	if (simulation.getBackup() == nullptr){
		error("No backup available");
	}
	else{
		simulation.Restore();
	}
}
RestoreSimulation* RestoreSimulation::clone() const {
	return new RestoreSimulation();
}
const string RestoreSimulation::toString() const {
	return "Restore Simulation" + actionStatusToString(getStatus());
};