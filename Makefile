# Define the build directory and the binary directory
BUILD_DIR = build 
BIN_DIR = bin
LOG_DIR = logs

# OPTIONS
CMAKE_MODE = Debug # Options: Release, Debug, MinSizeRel
EXECUTABLE_NAME = zuper


all: build

cmake:
	@echo "[Configuring with Ninja for $(CMAKE_MODE) mode]"
	@cmake -S . -B $(BUILD_DIR) -G Ninja -DCMAKE_BUILD_TYPE=$(CMAKE_MODE) -DEXECUTABLE_NAME=$(EXECUTABLE_NAME)

build: cmake
	@echo "[Building project in $(CMAKE_MODE) mode]"
	@cmake --build $(BUILD_DIR)

clean:
	@echo "[Cleaning bin directory]"
	@rm -rf $(BIN_DIR)
	@echo "[Cleaning log directory]"
	@rm -rf $(LOG_DIR)

wipe: clean
	@echo "[Cleaning build directory]"
	@rm -rf $(BUILD_DIR)

fresh: wipe all 

# Run the latest executable (stat -c '%Y' to get the last modified time)
run: all
	@echo "[Running the executable]"
	@./$(BIN_DIR)/$(EXECUTABLE_NAME)

log:
	@echo "[printing latest log file]"
	@latest_file=$$(find $(LOG_DIR) -type f -printf '%T@ %p\n' | sort -k1,1nr | head -n 1 | cut -d' ' -f2); \
		if [ -n "$$latest_file" ]; then \
			echo "[Found log file: $$latest_file]"; \
			cat $$latest_file; \
		fi

check:
	@echo "[Running cppcheck]"
	@cppcheck --enable=all --inconclusive --std=c++23 .

test: 
	@echo "[Running tests]"
	@ctest -B $(BUILD_DIR) 
	@ninja -C build test


lint:
	@files=$$(find include src -type f \( -name '*.hpp' -o -name '*.cpp' \)); \
		echo "[Running clang-format (1/2)]"; \
		clang-format -i -verbose $$files; \
		echo "[Running clang-tidy (2/2)]"; \
		clang-tidy $$files -- -std=c++23
	
valgrind:
	@echo "[Checking for memory leaks]"
	@mkdir -p $(LOG_DIR)
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=$(LOG_DIR)/valgrind.log $(BIN_DIR)/$(EXECUTABLE_NAME)

.PHONY: all cmake build clean wipe fresh run log check lint valgrind
