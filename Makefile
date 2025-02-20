# Define the build directory and the binary directory
BUILD_DIR = build 
BIN_DIR =   bin
CMAKE_MODE = Debug # Options: Release, Debug, MinSizeRel
ENABLE_TESTING = OFF # Options: ON, OFF

all: build

cmake:
	@echo "[Configuring with Ninja for $(CMAKE_MODE) mode]"
	@cmake -S . -B $(BUILD_DIR) -G Ninja -DCMAKE_BUILD_TYPE=$(CMAKE_MODE) -DENABLE_TESTING=$(ENABLE_TESTING)

build: cmake
	@echo "[Building project in $(CMAKE_MODE) mode]"
	@cmake --build $(BUILD_DIR)


clean:
	@echo "[Cleaning bin directory]"
	@rm -rf $(BIN_DIR)

wipe:
	@echo "[Cleaning bin directory]"
	@rm -rf $(BIN_DIR)
	@echo "[Cleaning build directory]"
	@rm -rf $(BUILD_DIR)

fresh: wipe all 

# Run the latest executable (stat -c '%Y' to get the last modified time)
run: all
	@latest_file=$$(find $(BIN_DIR) -type f -printf '%T@ %p\n' | sort -k1,1nr | head -n 1 | cut -d' ' -f2); \
    	if [ -n "$$latest_file" ]; then \
    		echo "[Found executable: $$latest_file]"; \
    		echo "[Running project $$latest_file]"; \
    		$$latest_file; \
    	fi

test: all
	@echo "[Running tests]"
	@cmake -S . -B $(BUILD_DIR) -G Ninja -DCMAKE_BUILD_TYPE=$(CMAKE_MODE) -DENABLE_TESTING=ON
	@ctest --test-dir $(BUILD_DIR)

.PHONY: all cmake compile format build wipe clean fresh run test