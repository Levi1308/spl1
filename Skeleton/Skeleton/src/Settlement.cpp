#include "Settlement.h"
#include "iostream"
#include "string"
    //Constructor
    Settlement::Settlement(const string& settelementName, SettlementType settelementType)
        :name(settelementName), type(settelementType),valid(true) {
    };

    Settlement::Settlement(const string &settelementName, SettlementType settelementType,bool notvalid)
    :name(settelementName), type(settelementType),valid(false) {

    };
    Settlement::Settlement(const Settlement& other)
        :name(other.name), type(other.type),valid(other.valid) {
    };
    Settlement& Settlement::operator= (const Settlement& other){
        if(this!=&other)
        {
            type=other.type;
            valid=other.valid;
        }
        return *this;
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

    };
    bool Settlement::Valid(){
        return valid;
    }
