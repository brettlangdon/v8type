var v8type = require('../');

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
