#include "Facility.h"
#include "iostream"
#include <string>
#include <vector>
using std::string;
using std::vector;
using namespace std;

// Constructor of FacilityType
FacilityType::FacilityType(const string &FTname, const FacilityCategory FTcategory, const int FTprice, const int FTlifeQuality_score, const int FTeconomy_score, const int FTenvironment_score)
    : name(FTname), category(FTcategory), price(FTprice), lifeQuality_score(FTlifeQuality_score), economy_score(FTeconomy_score), environment_score(FTenvironment_score) {}

// Destructor of FacilityType
FacilityType::~FacilityType() {}

// Copy Constructor for FacilityType
FacilityType::FacilityType(const FacilityType &other)
    : name(other.name), category(other.category), price(other.price),
      lifeQuality_score(other.lifeQuality_score), economy_score(other.economy_score), environment_score(other.environment_score) {}

// Assignment Operator for FacilityType
FacilityType& FacilityType::operator=(const FacilityType &other) {
    return *this;
}

// Getter methods for FacilityType
const string &FacilityType::getName() const { return name; }
int FacilityType::getCost() const { return price; }
int FacilityType::getLifeQualityScore() const { return lifeQuality_score; }
int FacilityType::getEnvironmentScore() const { return environment_score; }
int FacilityType::getEconomyScore() const { return economy_score; }
FacilityCategory FacilityType::getCategory() const { return category; }