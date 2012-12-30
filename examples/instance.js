var v8type = require('../');

console.dir(v8type.instance([], v8type.ARRAY));
// true

console.dir(v8type.instance([], v8type.OBJECT));
// true

console.dir(v8type.instance(5, v8type.OBJECT));
// false

console.dir(v8type.instance(5, v8type.PRIMITIVE));
// true

console.dir(v8type.instance(new Number(5), v8type.NUMBER));
// true

console.dir(v8type.instance(new Number(5), v8type.OBJECT));
// true
