CXXFLAGS += -Wall -Wextra -std=c++14 -MMD

-include main.d

main: main.o
	$(CXX) $^ -o $@

clean:
	@$(RM) main.d main.o main

