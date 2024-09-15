GCC=g++ --std=c++11 -Wall
SFML=SFML-2.6.1
BUILD=build
EXEC_NAME=raysnake.exe

STATES=$(BUILD)/SplashState.o
MODEL=$(BUILD)/Snake.o $(BUILD)/SnakePart.o $(BUILD)/World.o
VIEW=$(BUILD)/StateMachine.o $(BUILD)/ResourceManager.o $(BUILD)/SnakeAdapter.o

all: compile

# States compilation rule
$(BUILD)/SplashState.o: src/view/state/SplashState.cpp src/view/state/SplashState.hpp src/view/State.hpp
	$(GCC) -c src/view/state/SplashState.cpp -o $(BUILD)/SplashState.o -I $(SFML)/include

# Model compilation rules
$(BUILD)/SnakePart.o: src/model/SnakePart.cpp src/model/SnakePart.hpp
	$(GCC) -c src/model/SnakePart.cpp -o $(BUILD)/SnakePart.o -I $(SFML)/include
$(BUILD)/Snake.o: src/model/Snake.cpp src/model/Snake.hpp src/model/SnakePart.hpp
	$(GCC) -c src/model/Snake.cpp -o $(BUILD)/Snake.o -I $(SFML)/include
$(BUILD)/World.o: src/model/World.cpp src/model/World.hpp src/model/Snake.hpp
	$(GCC) -c src/model/World.cpp -o $(BUILD)/World.o -I $(SFML)/include

# View compilation rules
$(BUILD)/StateMachine.o: src/view/StateMachine.cpp src/view/StateMachine.hpp src/view/State.hpp
	$(GCC) -c src/view/StateMachine.cpp -o $(BUILD)/StateMachine.o -I $(SFML)/include
$(BUILD)/ResourceManager.o: src/view/ResourceManager.cpp src/view/ResourceManager.hpp
	$(GCC) -c src/view/ResourceManager.cpp -o $(BUILD)/ResourceManager.o -I $(SFML)/include
$(BUILD)/SnakeAdapter.o: src/view/adapter/SnakeAdapter.cpp src/view/adapter/SnakeAdapter.hpp
	$(GCC) -c src/view/adapter/SnakeAdapter.cpp -o $(BUILD)/SnakeAdapter.o -I $(SFML)/include


$(BUILD)/Controller.o: src/controller/Controller.cpp src/controller/Controller.hpp
	$(GCC) -c src/controller/Controller.cpp -o $(BUILD)/Controller.o -I $(SFML)/include

$(BUILD)/main.o: main.cpp
	$(GCC) -c main.cpp -o $(BUILD)/main.o -I $(SFML)/include

main: $(BUILD)/main.o $(BUILD)/Controller.o $(VIEW) $(STATES) $(MODEL)
	$(GCC) $(BUILD)/main.o $(BUILD)/Controller.o $(VIEW) $(STATES) $(MODEL) -o $(EXEC_NAME) -L $(SFML)/lib -lsfml-graphics -lsfml-window -lsfml-system

compile: main

run:
	export LD_LIBRARY_PATH=$(SFML)/lib && ./$(EXEC_NAME)

clean:
	rm $(BUILD)/*.o


#g++ -c main.cpp -I SFML/include
#
#g++ main.o -o sfml-app -L SFML/lib -lsfml-graphics -lsfml-window -lsfml-system
#export LD_LIBRARY_PATH=SFML/lib && ./sfml-app
