var util = require('util');
var mod = require('./mod');
var kexec = require("../build/default/kexec.node");
var k = kexec.kexec;

k('node --version');