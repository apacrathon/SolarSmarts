/* eslint-disable no-console */
const logger = require('winston');
const app = require('./app');
const port = app.get('port');
const fs = require('fs');
const https  = require('https');
//const server = app.listen(port);
const server = https.createServer({
  key: fs.readFileSync('privateKey.key'),
  cert: fs.readFileSync('certificate.crt')
}, app).listen(443);

app.setup(server);

process.on('unhandledRejection', (reason, p) =>
  logger.error('Unhandled Rejection at: Promise ', p, reason)
);

server.on('listening', () =>
  logger.info('BarBeerDrinker Plus started on https://%s', app.get('host'))
);
