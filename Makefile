
.PHONY: build test demo demovp demovp-pids demos

build:
	./node_modules/.bin/node-gyp clean
	./node_modules/.bin/node-gyp configure
	./node_modules/.bin/node-gyp build

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
