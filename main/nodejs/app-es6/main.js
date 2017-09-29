import { SerialHelper } from './interface/serial-helper.js';
import yargs from  'yargs';

//const serialport = require('serialport');
//const SerialPort = serialport.SerialPort;
//const yargs = require('yargs');

yargs.command('discover', 'list all ports',
    argv => {
        SerialHelper.list();
    })
    .argv;
