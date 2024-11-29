#pragma once
#include <string>
#include <vector>
using std::string;
using std::vector;

class Facility;

enum class SettlementType {
    VILLAGE=1,
    CITY=2,
    METROPOLIS=3,
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