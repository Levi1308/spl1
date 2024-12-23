#pragma once
#include <string>
#include <vector>
using std::string;
using std::vector;

class Facility;

enum class SettlementType {
    VILLAGE,
    CITY,
    METROPOLIS
};

class Settlement {
    public:
        Settlement(const string &name, SettlementType type);
        Settlement() =default;
        Settlement(const Settlement& other);
        ~Settlement() = default;
        Settlement& operator= (const Settlement& other);
        const string &getName() const;
        SettlementType getType() const;
        const string toString() const;

        private:
            const string name;
            SettlementType type;
};