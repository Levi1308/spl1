
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
    : isRunning(false), planCounter(0), actionsLog(), plans(), settlements(), facilitiesOptions()
    ,falseSettlement("",SettlementType::CITY),falsePlan(-1) {

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
            if(isSettlementExists(settlementName)){
                Settlement settlement = getSettlement(settlementName);
                std::cout<<settlement.toString()<<std::endl;
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
            std::cout<<selectionPolicy->toString()<<std::endl;
            if (selectionPolicy!=nullptr) {
                addPlan(settlement, selectionPolicy);
                }
            }
        }
    }
    configFile.close();
}

//Rule of 5
Simulation::Simulation(const Simulation& other)
	: isRunning(other.isRunning),
	planCounter(other.planCounter),
    actionsLog(),
	plans(other.plans),
    settlements(),
    facilitiesOptions(other.facilitiesOptions),  
    falseSettlement("",SettlementType::CITY),
    falsePlan(-1)
    {
	for (BaseAction* b : other.actionsLog)
		actionsLog.push_back(b->clone());
	for (Settlement* s : other.settlements) 
		settlements.push_back(new Settlement(*s)); 
}
Simulation::Simulation(Simulation&& other) noexcept
	: isRunning(other.isRunning),
	planCounter(other.planCounter),
    actionsLog(std::move(other.actionsLog)),
	plans(std::move(other.plans)),
    settlements(std::move(other.settlements)),
	facilitiesOptions(std::move(other.facilitiesOptions)),
	falseSettlement("",SettlementType::CITY),
    falsePlan(-1){
	
};
Simulation::~Simulation(){
    for (BaseAction* action : actionsLog) {
        delete action;
    }
    for (Settlement* settlement : settlements) {
        delete settlement;
    }
}


Simulation& Simulation::operator=(const Simulation& other) {
    if (this != &other) {
        for (BaseAction* b : actionsLog) {
            delete b;
        }
        actionsLog.clear();
        for (Settlement* s : settlements) {
            delete s;
        }
        settlements.clear();
        facilitiesOptions.clear();
        isRunning = other.isRunning;
        planCounter = other.planCounter;
        plans = other.plans;
        for (const auto& F : other.facilitiesOptions) {
            facilitiesOptions.push_back(F);
        }
        for (BaseAction* b : other.actionsLog) {
            actionsLog.push_back(b->clone()); 
        }
        for (Settlement* s : other.settlements) {
            settlements.push_back(new Settlement(*s)); 
        }
    }
    return *this;
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

    }
    return *this;
}


void Simulation::addPlan(const Settlement& settlement, SelectionPolicy* selectionPolicy) {
	Plan p (planCounter,settlement,selectionPolicy,facilitiesOptions);
    plans.push_back(p);
    std::cout<<p.toString()<<std::endl;
    planCounter++;

}


bool Simulation::addSettlement(Settlement* settlement) {
	settlements.push_back(settlement);
	return true;
}

bool Simulation::isSettlementExists(const string& settlementName) {
	for (Settlement* s : settlements) {
		if (s->getName() == settlementName) {
			return true;
		}
	}
	return false;
}

Settlement Simulation::getSettlement(const std::string& settlementName) {
    for (Settlement* settlement : settlements) {
        if (settlement->getName() == settlementName) {
            return *settlement;
        }
    }
   return falseSettlement;
}

bool Simulation::addFacility(FacilityType facility) {
	for(FacilityType facilitytype:facilitiesOptions) {
        if(facilitytype==facility)
		   return false;
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
    for(BaseAction* BA: actionsLog){
        delete BA;
    }
    for(Settlement* s:settlements){
        delete s;
    }
    delete backup;
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
			vector<string> args = Auxiliary::parseArguments(userInput);
            if (args.empty()) {
              continue; 
            }
        
        const std::string& command = args[0];
		if(command == "close"){
			Close c = Close();
            c.act(*this);
		}
		else if(command == "step"){
            const std::string& stringNum = args[1];
            SimulateStep* simS = new SimulateStep(std::stoi(stringNum));
            simS->act(*this);
            actionsLog.push_back(simS);
		}
	    else if(command == "planStatus"){
          const std::string& stringNum = args[1];
          PrintPlanStatus* PPS = new PrintPlanStatus(std::stoi(stringNum));
          PPS->act(*this);
          actionsLog.push_back(PPS);
        }
        else if(command == "log"){
            PrintActionsLog PAL = PrintActionsLog();
            PAL.act(*this);
        }
        else if(command == "backup"){
            BackupSimulation* BS = new BackupSimulation();
            BS->act(*this);
            actionsLog.push_back(BS);
        }
        else if(command == "restore"){
            RestoreSimulation* RS = new RestoreSimulation();
            RS->act(*this);
            actionsLog.push_back(RS);
        }
        else if(command == "plan"){
            const std::string& settlementName = args[1];
            const std::string& policyName = args[2];
            AddPlan* AP = new AddPlan(settlementName, policyName);
            AP->act(*this);
            actionsLog.push_back(AP);
        }
        else if(command == "settlement"){
            const std::string& settlementName = args[1];
            SettlementType type = static_cast<SettlementType>(std::stoi(args[2]));
            AddSettlement* AS = new AddSettlement(settlementName, type);
            AS->act(*this);
            actionsLog.push_back(AS);
        }
        else if(command == "facility"){
            const std::string& facilityName = args[1];
            FacilityCategory category = static_cast<FacilityCategory>(std::stoi(args[2]));
            int price = std::stoi(args[3]);
            int lifeQualityScore = std::stoi(args[4]);
            int economyScore = std::stoi(args[5]);
            int environmentScore = std::stoi(args[6]);
            AddFacility* AF = new AddFacility(facilityName, category, price, lifeQualityScore, economyScore, environmentScore);
            AF->act(*this);
            actionsLog.push_back(AF);
        }
        else if(command == "changePolicy"){
            int planId = std::stoi(args[1]);
            const std::string& newPolicy = args[2];
            ChangePlanPolicy* CPP = new ChangePlanPolicy(planId, newPolicy);
            CPP->act(*this);
            actionsLog.push_back(CPP);
        }

    
	}
};

const vector<BaseAction*>& Simulation::getActionLog() const {
	return actionsLog;
}

const vector<Plan>& Simulation::getPlans() const {
	return plans;
}

void Simulation::BackUp() {
	backup = new Simulation(*this);
}
void Simulation::Restore() {
	if (backup!=nullptr) {
        *this = *backup;
    } 
}
Plan& Simulation::getPlan(int planID) {
    for (Plan& plan : plans) {
        if (plan.getId() == planID) {
            return plan;
        }
    }
   return falsePlan;
};

void Simulation::setPlanPolicy(Plan p,string newPolicy){
    if(p.getId()!=-1)
    {
	if (newPolicy == "nve") {
		p.setSelectionPolicy(new NaiveSelection());
	}
	else if (newPolicy == "bal") {
		p.setSelectionPolicy(new BalancedSelection(p.getlifeQualityScore() + p.getUnderunderConstructionLQS() ,p.getEconomyScore() + p.getUnderunderConstructionECS(),p.getEnvironmentScore()+ p.getUnderunderConstructionENS()));
	}
	else if (newPolicy == "eco") {
		p.setSelectionPolicy(new EconomySelection());
	}
	else if (newPolicy == "env") {
		p.setSelectionPolicy(new SustainabilitySelection());
	}
    }
};

Simulation* Simulation::getBackup(){
    return backup;
};
void Simulation::print(){
    for(Settlement* s:settlements)
    {
        std::cout<<s->toString()<<std::endl;
    }
    for(Plan p:plans)
    {
       p.printStatus();
    }
    for(FacilityType f:facilitiesOptions)
    {
        std::cout<<f.getName()<<std::endl;
    }
}