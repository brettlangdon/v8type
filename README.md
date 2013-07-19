v8type
======

Module that uses V8 itself to check the type of a given object.

## Installing
```bash
npm install v8type
```

## API

### Constants
 * `ARRAY` - `'array'`
 * `BOOLEAN` - `'boolean'`
 * `BOOLEAN_OBJECT` - `'boolean_object'` (`new Boolean(false)`)
 * `DATE` - `'date'`
 * `FUNCTION` - `'function'`
 * `NULL` - `'null'`
 * `NUMBER` - `'number'`
 * `NUMBER_OBJECT` - `'number_object'` (`new Number(1)`)
 * `OBJECT` - `'object'`
 * `PRIMITIVE` - `'primitive'` (useful with `v8type.instance` function only)
 * `REGEXP` - `'regexp'`
 * `STRING` - `'string'`
 * `STRING_OBJECT` - `'string_object'` (`new String('v8type')`)
 * `UNDEFINED` - `'undefined'`

### Functions
 * `of(object)` - returns the type of `object` as a string defined in the corresponding constants above.
 * `is(object, type)` - returns `boolean` if `object` matches the string type `type` (string defined in the corresponding constants above).
 * `instance(object, type)` - returns `boolean` is `object` is of the type `type` or inherits from `type` (`type` is a string defined in the corresponding constants above).

## Examples

### of function
```javascript
var v8type = require('v8type');

console.log(v8type.of([1,2,3,4]));
// 'array'

console.log(v8type.of(undefined));
// 'undefined'

console.log(v8type.of(5));
// 'number'

console.log(v8type.of(new Number(5)))
// 'number_object'

console.log(v8type.of('v8type'));
// 'string'

console.log(v8type.of(new RegExp('v8type')));
// 'regexp'

console.log(v8type.of({}));
// 'object'

console.log(v8type.of(function(){}));
// 'function'

console.log(v8type.of(new Date()));
// 'date'
```

### is function
```javascript
var v8type = require('v8type');

v8type.is([1,2,3], v8type.ARRAY);
// true

v8type.is({}, v8type.NULL);
// false

// Is does not check inheritence
v8type.is([], v8type.OBJECT);
// false
```

### instance function
```javascript
var v8type = require('v8type');

v8type.instance([], v8type.ARRAY);
// true

v8type.instance([], v8type.OBJECT);
// true

v8type.instance(5, v8type.OBJECT);
// false

v8type.instance(5, v8type.PRIMITIVE);
// true

v8type.instance(new Number(5), v8type.NUMBER);
// true

v8type.instance(new Number(5), v8type.OBJECT);
// true
```

## License
The MIT License (MIT)
Copyright (c) 2012 Brett Langdon <brett@blangdon.com>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
