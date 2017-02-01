const fetch = require('node-fetch');
const Promise = require('bluebird');

const ip = '192.168.1.99';
const statusApi = '/status';

function getStatus() {
  const promise = new Promise(function(resolve) {
    fetch(`http://${ip}${statusApi}`).then((res) => resolve(res.json()))
  })
  return promise;
}

module.exports = {
  getStatus: getStatus
};