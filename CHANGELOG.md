4.0.0 / 2020-04-10
------------------
- add support for node 12 and node 13
- drop support for all node versions before 8
- port from NaN to node-addon-api
- throw JS errors for all system call failures

3.0.0 / 2016-09-11
------------------
- port to NaN [#31]
- change JS style to Standard
- dropped official support for Node v0.10

2.0.2 / 2015-11-27
------------------
- fix build in Make: See: https://github.com/jprichardson/node-kexec/pull/28
- compatible for Node v5 See: https://github.com/jprichardson/node-kexec/pull/29

2.0.1 / 2015-11-25
------------------
- removed incorrect references to `node-gyp`: See: https://github.com/jprichardson/node-kexec/pull/27

2.0.0 / 2015-11-24
------------------
- removed `node-gyp` dep. In case this breaks anything, bumped major. See: https://github.com/jprichardson/node-kexec/pull/24

1.3.0 / 2015-10-20
------------------
- Node.js v4 support https://github.com/jprichardson/node-kexec/pull/21

1.2.0 / 2015-02-09
------------------
- Node.js v0.12 support https://github.com/jprichardson/node-kexec/pull/18

1.1.1 / 2015-01-26
------------------
- move `pangyp` to dependencies

1.1.0 / 20145-01-20
------------------
- dropped `node-gyp` for `pangyp`
- `io.js` support https://github.com/jprichardson/node-kexec/issues/13

1.0.0 / 2014-12-29
------------------
- added Node 0.11 support https://github.com/jprichardson/node-kexec/pull/11

0.2.0 / 2014-01-25
------------------
* API extensions, kexec(cmnd,[args]) now execvps cmd with args directly.

0.1.1 / 2012-09-19
------------------
* kexec now returns `exevp` error code if it fails.

0.1.0 / 2012-09-19
------------------
* Made Node v0.8 compatible.

0.0.3 / 2012-01-09
------------------
* Fixed typo in index.js (Matt Insler)

0.0.2 / 2012-01-06
------------------
* Node.js v0.6 support (Matt Insler)

0.0.1 / 2011-12-05
------------------
* Initial release
