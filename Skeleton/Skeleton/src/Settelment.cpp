#include "Settlement.h"
#include "iostream"
//Constructor
Settlement::Settlement(const string &settelementName, SettlementType settelementType)
:name(settelementName),type(settelementType){};

const string &Settlement::getName() const{ return name;}

SettlementType Settlement::getType() const{return type;}

const string Settlement::toString() const {
 switch (type)
 {
 case SettlementType::VILLAGE: "Settelment name: "+name+"Settelment type:Villge";
 case SettlementType::CITY:return "Settelment name: "+name+"Settelment type:City";
 case SettlementType::METROPOLIS:return "Settelment name: "+name+"Settelment type:Metropolis";
 default:
    return "Unknown settlment type";
 }

};