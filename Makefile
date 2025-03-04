GCC=g++ --std=c++11 -Wall
SFML=SFML-2.6.1
BUILD=build
EXEC_NAME=raysnake.exe

STATES=$(BUILD)/SplashState.o
MODEL=$(BUILD)/World.o $(BUILD)/Direction.o $(BUILD)/Snake.o $(BUILD)/SnakePart.o $(BUILD)/Bound.o
VIEW=$(BUILD)/StateMachine.o $(BUILD)/ResourceManager.o $(BUILD)/AnimatedSprite.o
ADAPTER=$(BUILD)/SnakeAdapter.o

all: compile

# States compilation rule
$(BUILD)/SplashState.o: src/view/state/SplashState.cpp src/view/state/SplashState.hpp src/view/State.hpp
	$(GCC) -c src/view/state/SplashState.cpp -o $(BUILD)/SplashState.o -I $(SFML)/include

# Model compilation rules
$(BUILD)/SnakePart.o: src/model/SnakePart.cpp src/model/SnakePart.hpp
	$(GCC) -c src/model/SnakePart.cpp -o $(BUILD)/SnakePart.o -I $(SFML)/include
$(BUILD)/Snake.o: src/model/Snake.cpp src/model/Snake.hpp src/model/SnakePart.hpp
	$(GCC) -c src/model/Snake.cpp -o $(BUILD)/Snake.o -I $(SFML)/include
$(BUILD)/World.o: src/model/terrain/World.cpp src/model/terrain/World.hpp src/model/Snake.hpp
	$(GCC) -c src/model/terrain/World.cpp -o $(BUILD)/World.o -I $(SFML)/include
$(BUILD)/Bound.o: src/model/Bound.cpp src/model/Bound.hpp
	$(GCC) -c src/model/Bound.cpp -o $(BUILD)/Bound.o -I $(SFML)/include
$(BUILD)/Direction.o: src/model/Direction.cpp src/model/Direction.hpp
	$(GCC) -c src/model/Direction.cpp -o $(BUILD)/Direction.o -I $(SFML)/include

# View compilation rules
$(BUILD)/StateMachine.o: src/view/StateMachine.cpp src/view/StateMachine.hpp src/view/State.hpp
	$(GCC) -c src/view/StateMachine.cpp -o $(BUILD)/StateMachine.o -I $(SFML)/include
$(BUILD)/ResourceManager.o: src/view/ResourceManager.cpp src/view/ResourceManager.hpp
	$(GCC) -c src/view/ResourceManager.cpp -o $(BUILD)/ResourceManager.o -I $(SFML)/include
$(BUILD)/AnimatedSprite.o: src/view/AnimatedSprite.cpp src/view/AnimatedSprite.hpp
	$(GCC) -c src/view/AnimatedSprite.cpp -o $(BUILD)/AnimatedSprite.o -I $(SFML)/include

# Adapter compilation rules
$(BUILD)/SnakeAdapter.o: src/adapter/SnakeAdapter.cpp src/adapter/SnakeAdapter.hpp
	$(GCC) -c src/adapter/SnakeAdapter.cpp -o $(BUILD)/SnakeAdapter.o -I $(SFML)/include
$(BUILD)/SnakeOptAdapter.o: src/adapter/SnakeOptAdapter.cpp src/adapter/SnakeOptAdapter.hpp
	$(GCC) -c src/adapter/SnakeOptAdapter.cpp -o $(BUILD)/SnakeOptAdapter.o -I $(SFML)/include


$(BUILD)/Controller.o: src/controller/Controller.cpp src/controller/Controller.hpp
	$(GCC) -c src/controller/Controller.cpp -o $(BUILD)/Controller.o -I $(SFML)/include

$(BUILD)/main.o: main.cpp
	$(GCC) -c main.cpp -o $(BUILD)/main.o -I $(SFML)/include

main: $(BUILD)/main.o $(BUILD)/Controller.o $(VIEW) $(STATES) $(MODEL) $(ADAPTER)
	$(GCC) $(BUILD)/main.o $(BUILD)/Controller.o $(VIEW) $(STATES) $(MODEL) $(ADAPTER) -o $(EXEC_NAME) -L $(SFML)/lib -lsfml-graphics -lsfml-window -lsfml-system

compile: main

run:
	export LD_LIBRARY_PATH=$(SFML)/lib && ./$(EXEC_NAME)

clean:
	rm $(BUILD)/*.o


#g++ -c main.cpp -I SFML/include
#
#g++ main.o -o sfml-app -L SFML/lib -lsfml-graphics -lsfml-window -lsfml-system
#export LD_LIBRARY_PATH=SFML/lib && ./sfml-app
