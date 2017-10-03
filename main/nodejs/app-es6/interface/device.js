import SerialPort from 'serialport'

let ReadLine = SerialPort.parsers.Readline;

export class Device {
    constructor(id, port, baudrate) {
        this._id = id;
        this._port = port;
        this._baudrate = baudrate;
        this._isConnected = false;
    }

    getSerial() {
        if (this._isConnected) {
            return this;
        } else {
            this._serialPort = new SerialPort(
                this._port,
                { baudrate: this._baudrate });
        }
        return new Promise((resolve, reject) => {
            this._serialPort.parser = this._serialPort.pipe(new ReadLine({ delimiter: '\r\n' }))

            let isConnected = false
            this._serialPort.on('open', () => {
                isConnected = true;
            })
            
            setTimeout(() => {
                if (isConnected) resolve(this);
                else reject('not able to connect');
            }, 1000);
        })
    }

    setListener(handler) {
        this._serialPort.parser.on('data', handler);
    }

    sendMessage(msg) {
        msg += '\n'
        this._serialPort.write(msg, () => {
            console.log('Write:\t\t Complete!');
        });
    }
}