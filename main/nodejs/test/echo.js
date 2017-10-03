'use strict';

const d = require('../app/interface/device.js');
const Device = d.Device;

const SerialPort = require('serialport/test'); // when installed as a package
const MockBinding = SerialPort.Binding;

const portPath = 'COM_ECHO';
MockBinding.createPort(portPath, { echo: true, record: false });


let device = new Device('test1', portPath, 115200);
device.connect()
  .then(d => {
    d.sendMessage('test1');
    d.sendMessage('teste2');
    d.sendMessage('teste4');
    d.sendMessage('teste5');
    d.sendMessage('teste6');
    d.sendMessage('teste7');
    d.sendMessage('teste8');
    d.setListener(data => {
      console.log('Received message:\t')
      console.log(data.toString('utf8'))
    });
  })
  .catch((err) => console.error(err));
MockBinding.reset();

MockBinding.reset();
