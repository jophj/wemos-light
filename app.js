const express = require('express')
const app = express()
const wemos = require('./wemos');

app.use('/light/jopcave', function(req, res, next) {
  console.log('Requested light ' + req.query.status + ' from ' + req.ip );
  next();
})

app.get('/light/jopcave', function (req, res) {
  if (req.query.status === 'on') {
    // TODO accippa
  }
  else if (req.query.status === 'off') {
    // TODO spegni
  }
  res.sendStatus(200)
})

app.get('/light/jopcave/status', function(req, res) {
  wemos.getStatus().then((status) => {
    res.send(status)
  })
})

app.use('/', express.static('static'))

app.listen(8077, function () {
  console.log('Light is go on port 8077')
})