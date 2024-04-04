.phony: clean

all: bin/main
debug: bin/main-debug

FILES = $(wildcard src/**/*.cpp src/main.cpp)

bin/main: $(FILES)
	@echo "[make]Compiling..."
	g++ $^ -O3 --std=c++20 -o $@

bin/main-debug: $(FILES)
	g++ $^ -g --std=c++20 -o $@

run: bin/main
	@make -C bin/ run

clean:
	@make -C bin/ clean