
.PHONY: build test testvp

build:
	node-gyp clean
	node-gyp configure
	node-gyp build

test:
	$(MAKE) build
	indir demo node demo.js

testvp:
	$(MAKE) build
	indir demo node demovp.js

