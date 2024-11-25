#include "Simulation.h"
#include "iostream"

Simulation::Simulation(const string& configFilePath)
	:isRunning(true), planCounter(0)
{

};
Simulation::Simulation(const Simulation& other)
{
	isRunning = other.isRunning;
	planCounter = other.planCounter;
	plans = other.plans;
	settlements = other.settlements;
	facilitiesOptions = other.facilitiesOptions;
	for (BaseAction* b : other.actionsLog)
	{
		actionsLog.push_back(b);
	}
};
Simulation::~Simulation()
{
	for (BaseAction* b : actionsLog)
	{
		delete b;
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

void Simulation::addPlan(const Settlement& settlement, SelectionPolicy* selectionPolicy) {
	Plan* p = new Plan(planCounter, settlement, selectionPolicy, facilitiesOptions);
	plans.push_back(*p);
	planCounter++;
	//delete p;
	//delete selectionPolicy;
};

bool Simulation::addSettlement(Settlement *settlement) {
	Settlement s(*settlement);
	settlements.push_back(s);
	return true;
};

bool Simulation::isSettlementExists(const string& settlementName) {
	for (Settlement s : settlements)
	{
		if (s.getName()._Equal(settlementName))
			return true;
	}
	return false;
};
Settlement& Simulation::getSettlement(const string& settlementName) {
	for (Settlement s : settlements)
	{
		if (s.getName()._Equal(settlementName))
			return s;
	}
};
Plan& Simulation::getPlan(const int planID) {
	for (Plan p : plans)
	{
		if (p.getId() == planID)
			return p;
	}
}

