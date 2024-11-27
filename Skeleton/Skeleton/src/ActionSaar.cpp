#include "Action.h"
#include "iostream"
#include "Auxiliary.h"
ActionStatus BaseAction::getStatus() const {
	return status;
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
AddSettlement::~AddSettlement() {

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
	return "Printing Status of a Plan";
}
ChangePlanPolicy::ChangePlanPolicy(const int planId, const string& newPolicy)
	:planId(planId), newPolicy(newPolicy)
{

};
void ChangePlanPolicy::act(Simulation& simulation) {
	Plan p = simulation.getPlan(planId);
	if (p.getId() != -1 && p.CheckPolicy(newPolicy))
	{
		simulation.setPlanPolicy(planId, newPolicy);
		complete();
	}
	error("Cannot change selection policy");
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
BackupSimulation* BackupSimulationclone() {
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