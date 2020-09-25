var http = require('http');
var server =
    http.createServer(
    (req, res) => {
        res.setHeader('Content-type', 'text/html; charset=utf-8');
        res.write('HELLO <br>');
        res.end(`Hello world,\n ${new Date()}`);
});
server.listen(3000);
console.log('started');