.PHONY: clean

clean: main
	rm main

prepare: main
	@cp ../src/data/tokens.txt .
	@cp ../src/data/input.txt .

run: main prepare
	@./$<