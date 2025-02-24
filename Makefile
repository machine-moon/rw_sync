# Define the build directory and the binary directory
BUILD_DIR = build 
BIN_DIR = bin
LOG_DIR = logs

# OPTIONS
# Options: Debug, Release, MinSizeRel, RelWithDebInfo
DEFAULT_BUILD_TYPE = RelWithDebInfo 
MODE = RelWithDebInfo
EXENAME = zuper

# Find all source files and save to a variable
FILES := $(shell find include src -type f \( -name '*.hpp' -o -name '*.cpp' \))

all: build

all-modes:
	@echo "[Building all modes]"
	@make MODE=RelWithDebInfo
	@make MODE=Debug
	@make MODE=Release
	@make MODE=MinSizeRel

cmake:
	@echo "[Configuring with Ninja for $(MODE) mode]"
	@cmake -S . -B $(BUILD_DIR) -G Ninja -DCMAKE_BUILD_TYPE=$(MODE) -DDEFAULT_BUILD_TYPE=$(DEFAULT_BUILD_TYPE) -DEXECUTABLE_NAME=$(EXENAME)

build: cmake
	@echo "\n[Building project in $(MODE) mode]\n"
	@cmake --build $(BUILD_DIR)

test: 
	@echo "[Running tests]"
	@ctest --test-dir $(BUILD_DIR) -C $(MODE)
	
check:
	@echo "[Running cppcheck]"
	@cppcheck --enable=all --inconclusive --std=c++23 $(FILES)

lint:
	@echo "[Running clang-format (1/2)]"
	@clang-format -i -verbose $(FILES)
	@echo "[Running clang-tidy (2/2)]"
	@clang-tidy $(FILES) -- -std=c++23

valgrind:
	@echo "[Checking for memory leaks]"
	@mkdir -p $(LOG_DIR)
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=$(LOG_DIR)/valgrind.log $(BIN_DIR)/$(EXENAME)

log:
	@echo "[Printing all log files]"
	@for file in $(LOG_DIR)/*; do \
		echo "[Filename: $$file]"; \
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
	@echo "[Running the executable]"
	@./$(BIN_DIR)/$(EXENAME)

.PHONY: all cmake build clean wipe fresh run log check test lint valgrind
