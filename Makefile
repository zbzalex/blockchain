all: _build

_build:
	cd build \
	&& cmake .. \
	&& cmake --build .

_clean:
	rm -rf build
	mkdir build

build: _build
clean: _clean _build
