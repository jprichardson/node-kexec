
.PHONY: build test demo demovp demovp-pids demos

REALPATH := $(shell which realpath || echo "readlink -f")
NPM_PATH := $(shell $(REALPATH) `which npm`)
NPM_DIR := $(shell dirname $(NPM_PATH))
NPM_NODE_GYP := $(NPM_DIR)/node-gyp-bin/node-gyp

build:
	$(NPM_NODE_GYP) clean
	$(NPM_NODE_GYP) configure
	$(NPM_NODE_GYP) build

test:
	$(MAKE) build
	./node_modules/.bin/mocha

demo:
	$(MAKE) build
	cd demo && node demo.js

demovp:
	$(MAKE) build
	cd demo && node demovp.js

demovp-pids:
	$(MAKE) build
	cd demo && node demovp-pids.js

demos:
	$(MAKE) build
	cd demo && node demo.js
	cd demo && node demovp.js
	cd demo && node demovp-pids.js
