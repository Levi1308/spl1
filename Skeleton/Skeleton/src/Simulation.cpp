#include "Simulation.h"
#include "iostream"

Simulation::Simulation(const string& configFilePath)
	:isRunning(true), planCounter(0)
{

};
//Rule of 5
Simulation::Simulation(const Simulation& other)
{
	isRunning = other.isRunning;
	planCounter = other.planCounter;
	plans = other.plans;
	facilitiesOptions = other.facilitiesOptions;
	for (BaseAction* b : other.actionsLog)
	{
		actionsLog.push_back(b);
	}
	for (Settlement* s : settlements)
	{
		settlements.push_back(s);
	}
};
Simulation::~Simulation()
{
	for (BaseAction* b : actionsLog)
	{
		delete b;
	}
	for (Settlement* s : settlements)
	{
		delete s;
	}
};
Simulation& Simulation::operator=(const Simulation& other) {
	if (this != &other)
	{
		isRunning = other.isRunning;
		planCounter = other.planCounter;
		plans = other.plans;
		settlements = other.settlements;
		facilitiesOptions = other.facilitiesOptions;
		actionsLog.clear();
		for (BaseAction* b : other.actionsLog)
		{
			actionsLog.push_back(b);
		}
	}
	return *this;
}

Simulation::Simulation(const Simulation&& other) {
	isRunning = other.isRunning;
	planCounter = other.planCounter;
	plans = other.plans;
	facilitiesOptions = other.facilitiesOptions;
	for (BaseAction* b : other.actionsLog)
	{
		actionsLog.push_back(b);
	}
	for (Settlement* s : settlements)
	{
		settlements.push_back(s);
	}
}

Simulation& Simulation::operator=(const Simulation&& other) {
	if (this != &other)
	{
		isRunning = other.isRunning;
		planCounter = other.planCounter;
		plans = other.plans;
		settlements = other.settlements;
		facilitiesOptions = other.facilitiesOptions;
		actionsLog.clear();
		for (BaseAction* b : other.actionsLog)
		{
			actionsLog.push_back(b);
		}
	}
	return *this;
}
void Simulation::addPlan(const Settlement& settlement, SelectionPolicy* selectionPolicy) {
	Plan* p = new Plan(planCounter, settlement, selectionPolicy, facilitiesOptions);
	plans.push_back(*p);
	planCounter++;
	//delete p;
	//delete selectionPolicy;
};
bool Simulation::addSettlement(Settlement* settlement) {
	Settlement* s(settlement);
	if (isSettlementExists((*settlement).getName()))
	{
		settlements.push_back(s);
		return true;
	}
	return false;
};

bool Simulation::isSettlementExists(const string& settlementName) {
	for (Settlement* s : settlements)
	{
		if (s->getName()._Equal(settlementName))
			return true;
	}
	return false;
};
Settlement& Simulation::getSettlement(const string& settlementName) {
	for (Settlement* s : settlements)
	{
		if (s->getName()._Equal(settlementName))
			return *s;
	}
	return Settlement("", SettlementType::CITY);
};
Plan& Simulation::getPlan(const int planID) {
	for (Plan p : plans)
	{
		if (p.getId() == planID)
			return p;
	}
	return Plan(-1);
}
void Simulation::setPlanPolicy(int planId, const string& newPolicy) {
	Plan& p = getPlan(planId);
	if (newPolicy == "nve") {
		p.setSelectionPolicy(new NaiveSelection());
	}
	else if (newPolicy == "bal") {
		p.setSelectionPolicy(new BalancedSelection(p.getlifeQualityScore(),p.getEconomyScore(),p.getEnvironmentScore()));
	}
	else if (newPolicy == "eco") {
		p.setSelectionPolicy(new EconomySelection());
	}
	else if (newPolicy == "env") {
		p.setSelectionPolicy(new SustainabilitySelection());
	}
}

