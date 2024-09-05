GCC=g++ --std=c++11 -Wall
SFML=SFML-2.6.1
BUILD=build
EXEC_NAME=raysnake.exe

all: compile

$(BUILD)/SplashState.o: view/state/SplashState.cpp view/state/SplashState.hpp view/State.hpp
	$(GCC) -c view/state/SplashState.cpp -o $(BUILD)/SplashState.o -I $(SFML)/include




$(BUILD)/StateMachine.o: view/StateMachine.cpp view/StateMachine.hpp view/State.hpp
	$(GCC) -c view/StateMachine.cpp -o $(BUILD)/StateMachine.o -I $(SFML)/include

$(BUILD)/ResourceManager.o: view/ResourceManager.cpp view/ResourceManager.hpp
	$(GCC) -c view/ResourceManager.cpp -o $(BUILD)/ResourceManager.o -I $(SFML)/include

$(BUILD)/Controller.o: controller/Controller.cpp controller/Controller.hpp
	$(GCC) -c controller/Controller.cpp -o $(BUILD)/Controller.o -I $(SFML)/include

$(BUILD)/main.o: main.cpp
	$(GCC) -c main.cpp -o $(BUILD)/main.o -I $(SFML)/include

main: $(BUILD)/main.o $(BUILD)/Controller.o $(BUILD)/ResourceManager.o $(BUILD)/StateMachine.o $(BUILD)/SplashState.o
	$(GCC) $(BUILD)/main.o $(BUILD)/Controller.o $(BUILD)/ResourceManager.o $(BUILD)/StateMachine.o $(BUILD)/SplashState.o -o $(EXEC_NAME) -L $(SFML)/lib -lsfml-graphics -lsfml-window -lsfml-system

compile: main

run:
	export LD_LIBRARY_PATH=$(SFML)/lib && ./$(EXEC_NAME)

clean:
	rm $(BUILD)/*.o


#g++ -c main.cpp -I SFML/include
#
#g++ main.o -o sfml-app -L SFML/lib -lsfml-graphics -lsfml-window -lsfml-system
#export LD_LIBRARY_PATH=SFML/lib && ./sfml-app
