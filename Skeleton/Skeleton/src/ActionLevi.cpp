#pragma once
#include <string>
#include <vector>
#include "Simulation.h"
#include "Settlement.h"
#include "Action.h"
#include "plan.h"



BaseAction::BaseAction(){}

ActionStatus BaseAction::getStatus() const {
	return status;
}

void BaseAction::complete() {
	status = ActionStatus::COMPLETED;
}

SimulateStep::SimulateStep(const int numOFSteps) 
	:numOfSteps(numOFSteps){}

SimulateStep::SimulateStep(const SimulateStep& other)
	:numOfSteps(other.numOfSteps){}

void SimulateStep::act(Simulation& simulation) {
	for (int i = 1; i <= numOfSteps;i++) {
		simulation.step();
	}
}

std::string actionStatusToString(ActionStatus status) {
    switch (status) {
    case ActionStatus::COMPLETED:
        return "COMPLETED";
    case ActionStatus::ERROR:
        return "ERROR";
    default:
        return "UNKNOWN";
    }
}

const string SimulateStep::toString() const {
    return "Simulation Step numOfSteps: " + std::to_string(numOfSteps) +
        " Status: " + actionStatusToString(getStatus());
}


SimulateStep* SimulateStep::clone() const {
	return new SimulateStep(*this);
}
