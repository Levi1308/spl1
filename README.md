# Simulation Project - C++

Welcome to the **Simulation Project** – a C++ implementation of a simulation framework. This project demonstrates object-oriented design, modular programming, and various simulation concepts.

## Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [File Structure](#file-structure)
- [Testing](#testing)
- [Contributing](#contributing)
- [License](#license)

## Overview
This project simulates various processes using facilities, plans, and settlements. It uses different selection policies and actions to drive the simulation logic.

## Features
- **Modular Structure:** Clear separation between headers and source files.
- **Object-Oriented Design:** Encapsulation, inheritance, and polymorphism.
- **Configurable Policies:** Selection policies that influence simulation behavior.
- **Simulation Framework:** Facilities and settlements interact dynamically.

## Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/simulation-project.git
   ```
2. Navigate to the project directory:
   ```bash
   cd simulation-project
   ```
3. Build the project using the provided Makefile:
   ```bash
   make
   ```

## Usage
1. After building, run the simulation:
   ```bash
   ./bin/simulation
   ```
2. Modify the configuration in the `src/` or `include/` files to adjust the simulation logic.

## File Structure
```
simulation-project/
│
├── src/                  # Source files
│   ├── Action.cpp        # Implementation of actions
│   ├── Auxiliary.cpp     # Helper functions
│   ├── Facility.cpp      # Facility logic
│   ├── main.cpp          # Main entry point
│   ├── Plan.cpp          # Plan handling
│   ├── SelectionPolicy.cpp  # Selection policies
│   ├── Settlement.cpp    # Settlement logic
│   └── Simulation.cpp    # Core simulation logic
│
├── include/              # Header files
│   ├── Action.h          # Action definitions
│   ├── Auxiliary.h       # Helper definitions
│   ├── Facility.h        # Facility definitions
│   ├── Plan.h            # Plan definitions
│   ├── SelectionPolicy.h # Selection policy interface
│   ├── Settlement.h      # Settlement definitions
│   └── Simulation.h      # Simulation class definitions
│
├── bin/                  # Compiled binary and object files
│   ├── simulation        # Executable
│   └── *.o               # Object files
│
└── makefile              # Build instructions
```

## Testing
The project currently does not have a dedicated test suite. Testing is conducted manually by modifying and running different simulation scenarios.

## Contributing
Feel free to contribute to this project by submitting pull requests or opening issues.

## License
This project is licensed under the MIT License.

