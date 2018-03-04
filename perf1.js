
require('http').createServer(handle).listen(3000)

var stringify = require('fast-json-stringify')({
	type:'object',
	properties: { hello: { type: 'string'}}
})

function handle(req,res) {
	res.setHeader('Content-type', 'application/json');
	res.end(stringify({ hello: 'world'}));
}





