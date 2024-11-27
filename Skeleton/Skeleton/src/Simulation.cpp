#include "Simulation.h"
#include "iostream"
#include "Auxiliary.h" 
#include "Settlement.h"
#include "Facility.h"  
#include <fstream>
#include <iostream>
#include <string>
#include "Action.h"
#include <iostream>
#include <algorithm> 

Simulation::Simulation(const string& configFilePath)
    : isRunning(false), planCounter(0), actionsLog(), plans(), settlements(), facilitiesOptions() {

    std::ifstream configFile(configFilePath);
    if (!configFile.is_open()) {
        throw std::runtime_error("Failed to open config file: " + configFilePath);
    }

    std::string line;
    while (std::getline(configFile, line)) {
        std::vector<std::string> args = Auxiliary::parseArguments(line);

        if (args.empty() || args[0][0] == '#') {
            continue; 
        }

        const std::string& command = args[0];

        if (command == "settlement") {
            const std::string& name = args[1];
            SettlementType type = static_cast<SettlementType>(std::stoi(args[2]));
            settlements.push_back(new Settlement(name, type));
        } else if (command == "facility") {
            const std::string& name = args[1];
            FacilityCategory category = static_cast<FacilityCategory>(std::stoi(args[2]));
            int price = std::stoi(args[3]);
            int lifeQuality  = std::stoi(args[4]);
            int economy = std::stoi(args[5]);
            int environment  = std::stoi(args[6]);

             facilitiesOptions.emplace_back(name, category, price, lifeQuality, economy, environment);
        } else if (command == "plan") {
            const std::string& settlementName = args[1];
            const std::string& policy = args[2];

            Settlement& settlement = getSettlement(settlementName);
            SelectionPolicy* selectionPolicy = nullptr;

            if (policy == "eco") {
                selectionPolicy = new EconomySelection();
            } else if (policy == "bal") {
                selectionPolicy = new BalancedSelection(10,10,10);
            } else if (policy == "env") {
                selectionPolicy = new SustainabilitySelection();
            } else if (policy == "nve") {
                selectionPolicy = new NaiveSelection();
            }

             if (selectionPolicy) {
                addPlan(settlement, selectionPolicy);
            }
        }
    }

    configFile.close();
}

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
Simulation::Simulation(const Simulation&& other) noexcept
	: isRunning(other.isRunning),
	planCounter(other.planCounter),
	plans(std::move(other.plans)),
	facilitiesOptions(std::move(other.facilitiesOptions)),
	actionsLog(std::move(other.actionsLog)),
	settlements(std::move(other.settlements)) {
	
}
Simulation::~Simulation() {
	for (BaseAction* b : actionsLog) {
		delete b;
	}
	for (Settlement* s : settlements) {
		delete s;
	}

}

Simulation& Simulation::operator=(const Simulation& other) noexcept {
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

Simulation& Simulation::operator=(const Simulation&& other) noexcept {
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

    }
    return *this;
}


void Simulation::addPlan(const Settlement& settlement, SelectionPolicy* selectionPolicy) {
	plans.emplace_back(planCounter++, settlement, selectionPolicy, facilitiesOptions);
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

Settlement& Simulation::getSettlement(const std::string& settlementName) {
    for (Settlement* settlement : settlements) {
        if (settlement->getName() == settlementName) {
            return *settlement;
        }
    }
    throw std::runtime_error("Settlement not found: " + settlementName);
}

Plan& Simulation::getPlan(int planID) {
    for (Plan& plan : plans) {
        if (plan.getId() == planID) {
            return plan;
        }
    }
    throw std::runtime_error("Plan not found with ID: " + std::to_string(planID));
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
	open(); 

	while (isRunning) {
			std::string userInput;
			std::getline(std::cin, userInput);
			vector<string> parseArgs = Auxiliary::parseArguments(userInput);

			if(userInput == "close"){
				close();
			}
			else{
				if(userInput == "step"){
					step();
				}
			}

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