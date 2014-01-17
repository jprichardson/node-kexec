
.PHONY: build test demo demovp

build:
	node-gyp clean
	node-gyp configure
	node-gyp build

test:
	$(MAKE) build
	mocha

demo:
	$(MAKE) build
	cd demo && node demo.js

demovp:
	$(MAKE) build
	cd demo && node demovp.js

