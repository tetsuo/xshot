var xshot = require('./');
var assert = require('assert');

assert.equal('PNG', xshot().slice(1, 4).toString());
assert.equal('JFIF', xshot({ filetype: 'jpeg' }).slice(6, 10).toString());