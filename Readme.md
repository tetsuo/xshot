# xshot

takes screenshots on osx.

# example

```js
var xshot = require('xshot');
var fs = require('fs');
fs.writeFileSync('out.png', xshot());
```

# api

## xshot(opts={})

Returns an image containing the contents of the specified display.

`opts` object can have following properties:

* `display` is the unit number of the display for which an image is being created. (default, 0)
* `filetype` can be either `png` or `jpeg`. (default, png)

# usage

```
  usage: xshot filename [options]

  options:

    -d, --display       specify the display id
    -f, --filetype      specify the output filetype, png or jpeg
    -v, --version       show the version number
```

# license

mit