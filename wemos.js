const fetch = require('node-fetch');
const Promise = require('bluebird');

const ip = '192.168.1.99';
const statusApi = '/status';
const lightApi = '/light'
const onAction = '=on'
const offAction = '=off'

function getStatus() {
  const promise = new Promise(function(resolve) {
    fetch(`http://${ip}${statusApi}`).then((res) => resolve(res.json()))
  })
  return promise;
}

function switchOn() {
  const promise = new Promise(function(resolve) {
    fetch(`http://${ip}${lightApi}${onAction}`).then((res) => resolve(res))
  })
  return promise;
}

function switchOff() {
  const promise = new Promise(function(resolve) {
    fetch(`http://${ip}${lightApi}${offAction}`).then((res) => resolve(res))
  })
  return promise;
}

module.exports = {
  getStatus: getStatus,
  switchOn: switchOn,
  switchOff: switchOff
}
