
.PHONY: build test testvp

build:
	node-gyp clean
	node-gyp configure
	node-gyp build

test:
	$(MAKE) build
	cd demo && node demo.js

testvp:
	$(MAKE) build
	cd demo && node demovp.js

