#!/usr/bin/env node

var path = require('path');
var fs = require('fs');
var minimist = require('minimist');
var argv = minimist(process.argv.slice(2), {
  alias: {
    d: 'display',
    f: 'filetype',
    v: 'version'
  },
  default: {
    display: 0,
    filetype: 'png'
  }
});

if (argv.version)
  return console.log(require('../package.json').version);

function usage () {
  var s = '\n  usage: xshot filename [options]\n\n'
    + '  options:\n\n'
    + '    -d, --display\tspecify the display id\n'
    + '    -f, --filetype\tspecify the output filetype, png or jpeg\n'
    + '    -v, --version\tshow the version number\n';
  console.log(s);
}

if (!argv._.length) return usage();

var filename = path.resolve(argv._[0]),
    opts = { display: argv.display, filetype: argv.filetype };

fs.writeFileSync(filename, require('..')(opts));
