Node.js - kexec
===============

This module causes your current Node.js process to be replaced by the process invoked by the parameter of this function. It's like the Ruby exec function. It currently does not work on Windows.

Fully compatible with Node.js version v0.6 and v0.8.


Installation Node v0.6 and v0.8
------------

    npm install kexec@latest



Installation Node v0.4
-------------

    npm install kexec@0.0.3




Usage
-----

```javascript
var kexec = require('kexec');

kexec('top'); //your process now becomes top, can also accept parameters in one string
```

```javascript
var kexec = require('kexec');

kexec('du', [ '-sh', '/etc/fstab' ]); //your process now becomes du, with the arguments indicated
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

Copyright (c) 2011-2012 JP Richardson

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files 
(the 'Software'), to deal in the Software without restriction, including without limitation the rights to use, copy, modify,
 merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE 
WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS 
OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


