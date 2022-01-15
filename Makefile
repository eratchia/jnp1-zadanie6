GCC = /usr/bin/g++-11
FLAGS = -Wall -Wextra -std=c++20

compile: direction.cc state.cc Sensor.cc Instruction.cc rover.cc rover_example.cpp
	${GCC} ${FLAGS} -fmodules-ts -c $^

link:
	${GCC} -fmodules-ts *.o -o main

modules: compile link

clean:
	rm -r *.o main gcm.cache