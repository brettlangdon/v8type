var v8type = require('../');

console.dir(v8type.is([1,2,3], v8type.ARRAY));
// true

console.dir(v8type.is({}, v8type.NULL));
// false

// is does not check inheritence
console.dir(v8type.is([], v8type.OBJECT));
// false
