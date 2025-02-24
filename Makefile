# Define the build directory and the binary directory
BUILD_DIR = build 
BIN_DIR = bin
LOG_DIR = logs

# OPTIONS
# Options: Debug, Release, MinSizeRel, RelWithDebInfo
DEFAULT_BUILD_TYPE = RelWithDebInfo
MODE = RelWithDebInfo
EXENAME = rw_sync

# Find all source files and save to a variable
FILES := $(shell find include src -type f \( -name '*.hpp' -o -name '*.cpp' \))

all: build

all-modes:
	@echo "\n[Building all modes]\n"
	@make MODE=Debug
	@make MODE=Release
	@make MODE=MinSizeRel
	@make MODE=RelWithDebInfo

cmake:
	@echo "\n[Configuring with Ninja for $(MODE) mode]\n"
	@cmake -S . -B $(BUILD_DIR) -G Ninja -DCMAKE_BUILD_TYPE=$(MODE) -DDEFAULT_BUILD_TYPE=$(DEFAULT_BUILD_TYPE) -DEXECUTABLE_NAME=$(EXENAME)

build: cmake
	@echo "\n[Building project in $(MODE) mode]\n"
	@cmake --build $(BUILD_DIR)

test: 
	@echo "\n[Running tests]\n"
	@ctest --test-dir $(BUILD_DIR) -C $(MODE)
	
check: build
	@echo "\n[Running cppcheck]\n"
	@cppcheck --enable=all --inconclusive --suppress=missingIncludeSystem --suppress=unmatchedSuppression --std=c++23 --cppcheck-build-dir=$(BUILD_DIR) src/*.cpp

lint:
	@echo "\n[Running clang-format]\n"
	@clang-format -i -verbose $(FILES)
	@echo "\n[Running clang-tidy]\n"
	@clang-tidy $(FILES) -- -std=c++23

valgrind:
	@echo "\n[Checking for memory leaks in $(DEFAULT_BUILD_TYPE) mode]\n"
	@mkdir -p $(LOG_DIR)
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=$(LOG_DIR)/valgrind.log $(BIN_DIR)/$(EXENAME)

log:
	@echo "\n[Printing all log files]\n"
	@for file in $(LOG_DIR)/*; do \
		echo "\n[Filename: $$file]\n"; \
		cat $$file; \
	done

# remove runtime files
clean:
	@echo "[Cleaning bin directory]"
	@rm -rf $(BIN_DIR)
	@echo "[Cleaning log directory]"
	@rm -rf $(LOG_DIR)

# remove build files
del: 
	@echo "[Cleaning build directory]"
	@rm -rf $(BUILD_DIR)

# remove all generated files
wipe : clean del

# remove all generated files and rebuild (reboot the project)
fresh: wipe all 

run: all
	@echo "\n[Running $(EXENAME) in $(DEFAULT_BUILD_TYPE) mode]\n"
	@./$(BIN_DIR)/$(EXENAME)

precommit: lint check test

.PHONY: all all-modes cmake build test check lint valgrind log clean del wipe fresh run precommit
