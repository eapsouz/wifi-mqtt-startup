import serialport from 'serialport';
export class SerialHelper {
    constructor(){
        throw new Error('Cannot be Directly instantiated');
    }

    static list(){
        serialport.list(function(err,ports){
            ports.forEach(function(port){
                console.log(port.comName);
            })
        })
    }

}





