#pragma once
#include <string>
#include <vector>
#include "Facility.h"
#include "Plan.h"
#include "Settlement.h"
using std::string;
using std::vector;
#include <memory>


class BaseAction;
class SelectionPolicy;

class Simulation {
public:
    Simulation(const string& configFilePath);
    Simulation(const Simulation& other);
    ~Simulation();
    Simulation& operator=(const Simulation& other);
    Simulation(Simulation&& other) noexcept;
    Simulation& operator=(Simulation&& other) noexcept;
    void start();
    void addPlan(const Settlement& settlement, SelectionPolicy* selectionPolicy);
    void addAction(BaseAction* action);
    bool addSettlement(Settlement* settlement);
    bool addFacility(FacilityType facility);
    bool isSettlementExists(const string& settlementName);
    Settlement& getSettlement(const string& settlementName);
    Plan& getPlan(const int planID);
    void setPlanPolicy(int planId, const string& newPolicy);
    const vector<BaseAction*>& getActionLog() const;
    const vector<Plan>& getPlans() const;
    void BackUp();
    void Restore();
    void step();
    void close();
    void open();
    Simulation* getBackup();
    void print();

private:
    bool isRunning;
    int planCounter; //For assigning unique plan IDs
    vector<BaseAction*> actionsLog;
    vector<Plan> plans;
    vector<Settlement*> settlements;
    std::vector<FacilityType> facilitiesOptions;
    Settlement falseSettlement;
    Plan falsePlan;
     
};
    extern Simulation* backup;
