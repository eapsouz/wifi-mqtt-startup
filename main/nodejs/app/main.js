'use strict';

var _serialHelper = require('./interface/serial-helper.js');

var _yargs = require('yargs');

var _yargs2 = _interopRequireDefault(_yargs);

function _interopRequireDefault(obj) { return obj && obj.__esModule ? obj : { default: obj }; }

//const serialport = require('serialport');
//const SerialPort = serialport.SerialPort;
//const yargs = require('yargs');

_yargs2.default.command('discover', 'list all ports', function (argv) {
    _serialHelper.SerialHelper.list();
}).argv;
//# sourceMappingURL=main.js.map