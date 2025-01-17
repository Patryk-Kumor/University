var fs = require('fs');
var https = require('https');
(async function () {
    var pfx = await fs.promises.readFile('test.pfx');
    var server = https.createServer({
    pfx: pfx,
    passphrase: 'test'
    },
    (req, res) => {
        res.setHeader('Content-type', 'text/html; charset=utf-8');
        res.end('Hello world,\n ${new Date()}');
    });
    server.listen(4000);
    console.log('started');
})();