CXXFLAGS += -Wall -Wextra -std=c++14 -MMD

-include main.d

main: main.o
	$(CXX) $^ -o $@

clean:
	@$(RM) main.d main.o main

all: format $(BUILD_DIR)/$(TARGET)

format:
	@files=$$(ls *.cpp 2>/dev/null); \
	if [ -n "$$files" ]; then \
		clang-format -i $$files; \
	else \
		echo "Нет файлов для форматирования"; \
	fi

