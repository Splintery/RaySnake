GCC=g++ --std=c++11 -Wall
SFML=SFML-2.6.1
BUILD=build
EXEC_NAME=raysnake.exe

all: compile

$(BUILD)/Controller.o: controller/Controller.cpp controller/Controller.hpp
	$(GCC) -c controller/Controller.cpp -o $(BUILD)/Controller.o -I $(SFML)/include

$(BUILD)/main.o: main.cpp
	$(GCC) -c main.cpp -o $(BUILD)/main.o -I $(SFML)/include

main: $(BUILD)/main.o $(BUILD)/Controller.o
	$(GCC) $(BUILD)/main.o $(BUILD)/Controller.o -o $(EXEC_NAME) -L $(SFML)/lib -lsfml-graphics -lsfml-window -lsfml-system

compile: main

run:
	export LD_LIBRARY_PATH=$(SFML)/lib && ./$(EXEC_NAME)

clean:
	rm $(BUILD)/*.o


#g++ -c main.cpp -I SFML/include
#
#g++ main.o -o sfml-app -L SFML/lib -lsfml-graphics -lsfml-window -lsfml-system
#export LD_LIBRARY_PATH=SFML/lib && ./sfml-app
