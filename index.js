module.exports = function (opts) {
  if (!opts) opts = {};
  var display = opts.display || 0,
      filetype = opts.filetype || 'png';
  return require('bindings')('xshot')(display, filetype);
};