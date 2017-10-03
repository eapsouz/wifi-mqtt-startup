import { SerialHelper } from './interface/serial-helper.js';
import { Device } from './interface/device.js'

import yargs from 'yargs';


yargs.command('discover', 'list all ports', argv => {
    SerialHelper.list();
})
    .command('connect', 'connect to a specific port',
    args => {
        args
            .option('port', {
                describe: 'supply port to connect'
            })
            .option('id', {
                describe: 'supply id',
                default: 'default'
            })
            .option('msg', {
                describe: 'supply message',
                default: 'hello world'
            })
            .option('baudrate', {
                describe: 'supply baudrate',
                default: 115200
            })
    }, argv => {
        if (argv.port) {
            let device = new Device(argv.id, argv.port, argv.baudrate);
            device.connect()
                .then(d => {
                    d.setListener((data) => {
                        console.log('Received: \t', data.toString('utf8'));
                    });
                    d.sendMessage(argv.msg);
                })
                .catch((err) => console.error(err));
        } else {
            console.log('port required');
        }
    })
    .argv;
