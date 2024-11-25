#include "Action.h"
#include "iostream"


void AddSettlement::act(Simulation& simulation) {
	Settlement* s=new Settlement(settlementName, settlementType);
	if (simulation.addSettlement(s))
		settlement = s;
	else
		std::cout << "Settlement already Exist" << std::endl;
}
const string AddSettlement::toString() const {
	//return settlement.toString();
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
	if (selectionPolicy == "nve") {
		//simulation.addPlan
	}
	else if (selectionPolicy == "bal") {
		// Handle the "bal" case
	}
	else if (selectionPolicy == "eco") {
		// Handle the "eco" case
	}
	else if (selectionPolicy == "env") {
		// Handle the "env" case
	}
};
	const string AddPlan::toString() const {
		return "Add plan was successful";
	};
AddPlan* AddPlan::clone() const {
	return new AddPlan(settlementName, selectionPolicy);
}

PrintPlanStatus::PrintPlanStatus(int planId)
	:planId(planId)
{

};
void PrintPlanStatus::act(Simulation& simulation) {
	simulation.getPlan(planId).printStatus();
}
PrintPlanStatus* PrintPlanStatus::clone() const {
	return new PrintPlanStatus(planId);
}
const string PrintPlanStatus::toString() const {
	return "PrintPlanStatus was successful";
}
ChangePlanPolicy::ChangePlanPolicy(const int planId, const string& newPolicy)
	:planId(planId), newPolicy(newPolicy)
{

};
void ChangePlanPolicy::act(Simulation& simulation) {
	simulation.setPlanPolicy(planId, newPolicy);
};
ChangePlanPolicy* ChangePlanPolicy::clone() const {
	return new ChangePlanPolicy(planId, newPolicy);
};
const string ChangePlanPolicy::toString() const {
	return "Success";
};

RestoreSimulation::RestoreSimulation() {

}
void RestoreSimulation::act(Simulation& simulation) {

}
RestoreSimulation* RestoreSimulation::clone() const {
	return new RestoreSimulation();
}
const string RestoreSimulation::toString() const {

};