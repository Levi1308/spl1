#pragma once
#include <vector>
#include "Facility.h"
using std::vector;

class SelectionPolicy {
    public:
        virtual const FacilityType& selectFacility(const vector<FacilityType>& facilitiesOptions) = 0;
        virtual const string toString() const = 0;
        virtual const string Nickname() const = 0;
        virtual SelectionPolicy* clone() const = 0;
        virtual ~SelectionPolicy() = default;
        int CloseDistance(int x,int y,int z);
        void setScores(int LifeQualityScore, int EconomyScore, int EnvironmentScore);
};

class NaiveSelection: public SelectionPolicy {
    public:
        NaiveSelection();
        NaiveSelection(const NaiveSelection &other);
        const FacilityType& selectFacility(const vector<FacilityType>& facilitiesOptions) override;
        const string toString() const override;
        const string Nickname() const override;
        NaiveSelection *clone() const override;
    private:
        int lastSelectedIndex;
};

class BalancedSelection: public SelectionPolicy {
    public:
        BalancedSelection(int LifeQualityScore, int EconomyScore, int EnvironmentScore);
        BalancedSelection(const BalancedSelection &other);
        const FacilityType& selectFacility(const vector<FacilityType>& facilitiesOptions) override;
        const string toString() const override;
        const string Nickname() const override;
        BalancedSelection *clone() const override;
        void setScores(int LifeQualityScore, int EconomyScore, int EnvironmentScore);
    private:
        int LifeQualityScore;
        int EconomyScore;
        int EnvironmentScore;
};

class EconomySelection: public SelectionPolicy {
    public:
        EconomySelection();
        EconomySelection(const EconomySelection &other);
        const FacilityType& selectFacility(const vector<FacilityType>& facilitiesOptions) override;
        const string toString() const override;
        const string Nickname() const override;
        EconomySelection *clone() const override;
    private:
        int lastSelectedIndex;

};

class SustainabilitySelection: public SelectionPolicy {
    public:
        SustainabilitySelection();
        SustainabilitySelection(const SustainabilitySelection &other);
        const FacilityType& selectFacility(const vector<FacilityType>& facilitiesOptions) override;
        const string toString() const override;
        const string Nickname() const ;
        SustainabilitySelection *clone() const override;
    private:
        int lastSelectedIndex;
};
