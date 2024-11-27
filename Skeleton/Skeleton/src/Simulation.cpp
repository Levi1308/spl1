#include "Simulation.h"
#include "iostream"
#include "Auxiliary.h" 
#include <fstream>
#include <iostream>
#include <string>
#include "Action.h"
#include <iostream>
#include <algorithm> 

Simulation::Simulation(const string& configFilePath)
	:isRunning(false), planCounter(0)
{
	std::ifstream configFile(configFilePath); 
	if (!configFile.is_open()) {
		throw std::runtime_error("Failed to open config file: " + configFilePath);
	}

	std::string line;
	while (std::getline(configFile, line)) {
		std::cout << "Read line: " << line << std::endl; 
	}

	configFile.close();
};
//Rule of 5
Simulation::Simulation(const Simulation& other)
	: isRunning(other.isRunning),
	planCounter(other.planCounter),
	plans(other.plans),
	facilitiesOptions(other.facilitiesOptions) {
	// Deep copy of actionsLog
	for (BaseAction* b : other.actionsLog) {
		actionsLog.push_back(b->clone()); // Assuming BaseAction has a virtual clone() method
	}

	// Deep copy of settlements
	for (Settlement* s : other.settlements) {
		settlements.push_back(new Settlement(*s)); // Assuming Settlement has a copy constructor
	}
}

Simulation::~Simulation() {
	// Free dynamically allocated memory
	for (BaseAction* b : actionsLog) {
		delete b;
	}
	for (Settlement* s : settlements) {
		delete s;
	}
}

Simulation& Simulation::operator=(const Simulation& other) {
	if (this != &other) {
		// Clean up existing resources
		for (BaseAction* b : actionsLog) {
			delete b;
		}
		actionsLog.clear();
		for (Settlement* s : settlements) {
			delete s;
		}
		settlements.clear();

		// Copy resources
		isRunning = other.isRunning;
		planCounter = other.planCounter;
		plans = other.plans;
		facilitiesOptions = other.facilitiesOptions;

		for (BaseAction* b : other.actionsLog) {
			actionsLog.push_back(b->clone()); // Deep copy of actions
		}

		for (Settlement* s : other.settlements) {
			settlements.push_back(new Settlement(*s)); // Deep copy of settlements
		}
	}
	return *this;
}

Simulation::Simulation(Simulation&& other) noexcept
	: isRunning(other.isRunning),
	planCounter(other.planCounter),
	plans(std::move(other.plans)),
	facilitiesOptions(std::move(other.facilitiesOptions)),
	actionsLog(std::move(other.actionsLog)),
	settlements(std::move(other.settlements)) {
	// Nullify pointers in the source object
	other.actionsLog.clear();
	other.settlements.clear();
}

Simulation& Simulation::operator=(Simulation&& other) noexcept {
	if (this != &other) {
		// Clean up existing resources
		for (BaseAction* b : actionsLog) {
			delete b;
		}
		actionsLog.clear();
		for (Settlement* s : settlements) {
			delete s;
		}
		settlements.clear();

		// Transfer ownership
		isRunning = other.isRunning;
		planCounter = other.planCounter;
		plans = std::move(other.plans);
		facilitiesOptions = std::move(other.facilitiesOptions);
		actionsLog = std::move(other.actionsLog);
		settlements = std::move(other.settlements);

		// Nullify pointers in the source object
		other.actionsLog.clear();
		other.settlements.clear();
	}
	return *this;
}

void Simulation::addPlan(const Settlement& settlement, SelectionPolicy* selectionPolicy) {
	Plan* p = new Plan(planCounter++, settlement, selectionPolicy, facilitiesOptions);
	plans.emplace_back(*p); // Copy the Plan object
	delete p; // Free the dynamically allocated memory
}


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
	for (Settlement* s : settlements) {
		if (s->getName() == settlementName) {
			return true;
		}
	}
	return false;
}

Settlement& Simulation::getSettlement(const string& settlementName) {
	for (Settlement* s : settlements) {
		if (s->getName() == settlementName) {
			return *s;
		}
	}
}

Plan& Simulation::getPlan(const int planID) {
	for (Plan& p : plans) { // Use reference to avoid copying
		if (p.getId() == planID) {
			return p;
		}
	}
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
bool Simulation::addFacility(FacilityType facility) {
	if (std::find(facilitiesOptions.begin(), facilitiesOptions.end(), facility) != facilitiesOptions.end()) {
		return false; // Facility already exists
	}
	facilitiesOptions.push_back(facility);
	return true;
}


void Simulation::addAction(BaseAction* action) {
	if (action != nullptr) {
		actionsLog.push_back(action);
	}
}

void Simulation::close() {
	std::cout << "The simulation has finished" << std::endl;
	isRunning = false;

}
void Simulation::step() {
	for (Plan& p : plans) {
		p.step();
	}
}

void Simulation::open() {
	std::cout << "The simulation has started" << std::endl;
	isRunning = true;
}

void Simulation::start() {
	open(); // Initialize or prepare the simulation

	while (isRunning) {
			string userInput;
			std::getline(std::cin, userInput);
			vector<string> parseArgs = Auxiliary::parseArguments(userInput);
	}
}

const vector<BaseAction*>& Simulation::getActionLog() const {
	return actionsLog;
}

const vector<Plan>& Simulation::getPlans() const {
	return plans;
}

void Simulation::BackUp() {
	backup = new Simulation(*this);
};
void Simulation::Restore() {
	*this = *backup;
}