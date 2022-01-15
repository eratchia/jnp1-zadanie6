GCC = /usr/bin/g++-11
FLAGS = -Wall -Wextra -std=c++20

precompilations:
	${GCC} -c -fmodules-ts -x c++-system-header -std=c++20 initializer_list vector list memory unordered_map utility string stdexcept iostream limits

modules: direction.cc state.cc Sensor.cc Instruction.cc rover.cc rover_example.cpp
	${GCC} ${FLAGS} -fmodules-ts -c $^

clean:
	rm -r *.o main gcm.cache