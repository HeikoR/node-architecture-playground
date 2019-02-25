var cf = require('./');

console.log('starting ...');

cf.hwrTestParamInOut('hello', function(strRet) {
	console.log('hello + ', strRet);
})