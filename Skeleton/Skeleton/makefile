# Build all: clean, compile, and link
all: clean dirs compile link

# Linking Rule
link:
	@echo "Linking source files"
	g++ -o bin/skeleton bin/main.o bin/Settlement.o bin/Simulation.o bin/Facility.o bin/Auxiliary.o \
	bin/SelectionPolicy.o bin/Action.o

# Compile Rule
compile: main Settlement Simulation Facility Auxiliary SelectionPolicy Action

# Ensure bin directory exists
dirs:
	@mkdir -p bin

# Compile main
main: dirs
	@echo "Compile main"
	g++ -g -Wall -Weffc++ -std=c++11 -c -o bin/main.o src/main.cpp -Iinclude

# Compile Settlement
Settlement: dirs
	@echo "Compile Settlement"
	g++ -g -Wall -Weffc++ -std=c++11 -c -o bin/Settlement.o src/Settlement.cpp -Iinclude

# Compile Simulation
Simulation: dirs
	@echo "Compile Simulation"
	g++ -g -Wall -Weffc++ -std=c++11 -c -o bin/Simulation.o src/Simulation.cpp -Iinclude

# Compile Facility
Facility: dirs
	@echo "Compile Facility"
	g++ -g -Wall -Weffc++ -std=c++11 -c -o bin/Facility.o src/Facility.cpp -Iinclude

# Compile Auxiliary
Auxiliary: dirs
	@echo "Compile Auxiliary"
	g++ -g -Wall -Weffc++ -std=c++11 -c -o bin/Auxiliary.o src/Auxiliary.cpp -Iinclude

# Compile SelectionPolicy
SelectionPolicy: dirs
	@echo "Compile SelectionPolicy"
	g++ -g -Wall -Weffc++ -std=c++11 -c -o bin/SelectionPolicy.o src/SelectionPolicy.cpp -Iinclude

# Compile Action
Action: dirs
	@echo "Compile Action"
	g++ -g -Wall -Weffc++ -std=c++11 -c -o bin/Action.o src/Action.cpp -Iinclude

# Clean Rule
clean:
	@echo "Cleaning bin files"
	rm -rf bin/*
