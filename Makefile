all: compile

clean: _clean compile

_clean:
	rm -rf build && mkdir build && cd build && cmake ..

compile:

	cd build && cmake .. && cmake --build .
	cd build && ./test-blockchain
	cd build && ./test-http
	cd build && ./test-contract-lang
