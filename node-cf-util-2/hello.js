var addon = require('bindings')('hello');

console.log(addon.hello()); // 'world'


console.log('calling encrypt ...');
console.log(addon.encrypt());