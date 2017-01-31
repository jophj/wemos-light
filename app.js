var express = require('express')
var app = express()

app.get('/light/jopcave', function (req, res) {
  if (req.params.status === 'on') {
    // accippa
  }
  else if (req.params.status === 'off') {
    // spegni
  }
  res.send(200)
})

app.get('/light/jopcave/status', function(req, res) {
  res.send({
    id: 'jopcave',
    status: true
  })
})

app.listen(8077, function () {
  console.log('Light is go on port 8077')
})