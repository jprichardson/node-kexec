Node.js - kexec
===============

[![npm Package](https://img.shields.io/npm/v/kexec.svg?style=flat-square)](https://www.npmjs.org/package/kexec)
[![build status](https://api.travis-ci.org/jprichardson/node-kexec.svg)](http://travis-ci.org/jprichardson/node-kexec)
[![JavaScript Style Guide](https://img.shields.io/badge/code%20style-standard-brightgreen.svg)](http://standardjs.com/)

This module causes your current Node.js process to be replaced by the process invoked by the parameter of this function. It's like the Ruby exec function. It currently does not work on Windows.


Usage
-----

```js
var kexec = require('kexec')

kexec('top') //your process now becomes top, can also accept parameters in one string
```

```javascript
var kexec = require('kexec')

kexec('du', [ '-sh', '/etc/fstab' ]) //your process now becomes du, with the arguments indicated
```


Details
-------

`kexec` can be called in either of two ways, as indicated by the examples, above.

With one argument `arg`, that argument must be a string.  The resulting system
call is:

    execvp("/bin/sh", [ "/bin/sh", "-c", arg, 0 ]);

With two arguments, the first (`cmd`) must be a string, and the second (`args`) an array of strings.  The resulting
system call is:

    execvp(cmd, [ cmd, args[0], args[1], ..., 0 ]);

In the first case, the command is subject to shell parsing, and shell meta
characters retain their special meanings.  In the second case, the arguments
are passed directly to `execvp`, without an intervening shell.


License
-------

(The MIT License)

Copyright (c) 2011-2015 JP Richardson
