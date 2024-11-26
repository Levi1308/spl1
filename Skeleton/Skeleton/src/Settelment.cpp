#include "Settlement.h"
#include "iostream"
#include "string"
class Settlement {
private:
    std::string name;
    SettlementType type;
public:
    //Constructor
    Settlement::Settlement(const string& settelementName, SettlementType settelementType)
        :name(settelementName), type(settelementType) {
    };

    Settlement::Settlement(const Settlement& other)
        :name(other.name), type(other.type) {
    };
    Settlement::~Settlement() {}
    Settlement& Settlement::operator=(const Settlement& other) {
        if (this != &other) { // Check for self-assignment
            name = other.name; // Copy the name
            type = other.type; // Copy the type
        }
        return *this; // Return a non-const reference to support chained assignments
    }

    const string& Settlement::getName() const { return name; }

    SettlementType Settlement::getType() const { return type; }

    const string Settlement::toString() const {
        switch (type)
        {
        case SettlementType::VILLAGE: "Settelment name: " + name + "Settelment type:Villge";
        case SettlementType::CITY:return "Settelment name: " + name + "Settelment type:City";
        case SettlementType::METROPOLIS:return "Settelment name: " + name + "Settelment type:Metropolis";
        default:
            return "Unknown settlment type";
        }

    }
};