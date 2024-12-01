#pragma once
#include <vector>
#include "Facility.h"
#include "Settlement.h"
#include "SelectionPolicy.h"
using std::vector;

enum class PlanStatus {
    AVALIABLE,
    BUSY,
};

class Plan {
    public:
        Plan(const int planId, const Settlement &settlement, SelectionPolicy *selectionPolicy, const vector<FacilityType> &facilityOptions);
        Plan(const Plan& other);
        Plan& operator= (const Plan& other);
        Plan& operator=( Plan&& other) = delete;
        Plan(Plan&& other) = delete;
        Plan(int plan_id);
        Plan();
        ~Plan();
        const int getlifeQualityScore() const;
        const int getEconomyScore() const;
        const int getEnvironmentScore() const;
        const int getId() const;
        bool CheckPolicy(string selectionPolicy);
        const string getStringStatus() const;
        void setSelectionPolicy(SelectionPolicy *selectionPolicy);
        void step();
        void printStatus();
        const vector<Facility*> &getFacilities() const;
        void addFacility(Facility* facility);
        const string toString() const;
        SelectionPolicy* getSelectionPolicy() const;
        void setPlanStatus(PlanStatus p);
        PlanStatus getPlanStatus();
        const int getUnderunderConstructionLQS() const;
        const int getUnderunderConstructionECS() const;
        const int getUnderunderConstructionENS() const;

    private:
        int plan_id;
        const Settlement &settlement;
        SelectionPolicy *selectionPolicy; //What happens if we change this to a reference?
        PlanStatus status;
        vector<Facility*> facilities;
        vector<Facility*> underConstruction;
        const vector<FacilityType> &facilityOptions;
        int life_quality_score, economy_score, environment_score;
};