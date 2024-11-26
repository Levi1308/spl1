#include "Facility.h"
#include "iostream"
#include <string>
#include <vector>
using std::string;
using std::vector;
using namespace std;

// Constructor of Facility (inherits from FacilityType)
Facility::Facility(const string &Fname, const string &FsettlementName, const FacilityCategory Fcategory, const int Fprice, const int FlifeQuality_score, const int Feconomy_score, const int Fenvironment_score)
    : FacilityType(Fname, Fcategory, Fprice, FlifeQuality_score, Feconomy_score, Fenvironment_score), settlementName(FsettlementName), status(FacilityStatus::UNDER_CONSTRUCTIONS), timeLeft(price){}

// Constructor for Facility using FacilityType
Facility::Facility(const FacilityType &type, const string &settlementName)
    : FacilityType(type), settlementName(settlementName), status(FacilityStatus::UNDER_CONSTRUCTIONS), timeLeft(type.getCost()){}


// Copy Constructor for Facility
Facility::Facility(const Facility &other)
:FacilityType(other), settlementName(other.settlementName), status(other.status), timeLeft(other.timeLeft){}


// Getter for settlement name
const string &Facility::getSettlementName() const {
    return settlementName;
}

// Getter for time left
const int Facility::getTimeLeft() const {
    return timeLeft;
}



// Function to progress the status of the Facility
FacilityStatus Facility::step() {
    // Logic for advancing the status of the facility
    if (status == FacilityStatus::UNDER_CONSTRUCTIONS) {
        --timeLeft;
        if (timeLeft == 0) {
            status = FacilityStatus::OPERATIONAL;
        }
    }
    
    return status;
}

// Setter for status
void Facility::setStatus(FacilityStatus newStatus) {
    status = newStatus;
}

// Getter for status
const FacilityStatus& Facility::getStatus() const {
    return status;
}

// String representation of the Facility
const string Facility::toString() const {
    return "Facility: " + name + ", " + settlementName + ", Status: " + (status == FacilityStatus::OPERATIONAL ? "Operational" : "Under Construction");
}
Facility* Facility::clone() {
    return new Facility(*this);
}


