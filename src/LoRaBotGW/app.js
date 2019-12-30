/*
 * LoRaBot Serial HTTP Gateway
 * 2019/12/30 JL1NIE
 */

var express = require('express');
var app = express();
var http = require('http').Server(app)
var path = require('path')
const io = require('socket.io')(http)
const PORT = process.env.PORT || 3000
const SerialPort = require('serialport')
const Readline = SerialPort.parsers.Readline
const LoRaPort = '/dev/ttyACM0'
var botSerial;

var connectLoRaBot = function() {
    botSerial = new SerialPort(LoRaPort,{
	baudRate: 9600,
	dataBits: 8,
	parity: 'none',
	stopBits: 1,
	flowControl: false
    });
    var parser = botSerial.pipe(new Readline({ delimiter: '\n' }));
    parser.on('data', function(data) {
	console.log(data);
	io.emit('message', data);
    });

    botSerial.on('open', function () {
	console.log('LoRaBot connected.');
    });

    botSerial.on('close', function () {
	console.log('LoRaBot disconnected.');
	botSerial.resume();
	reconnectLoRaBot();
    });
}

connectLoRaBot();

var reconnectLoRaBot = function() {
    setTimeout(function() {
	console.log('Reconnect LoRaBot');
	connectLoRaBot();
    }, 2000);
};

function port_write(data) {
    console.log('Write: ' + data);
    botSerial.write(data, function(err, results) {
      if(err) {
        console.log('Err: ' + err);
        console.log('Results: ' + results);
      }
  });
}

io.on('connection',function(socket){
    socket.on('message',function(msg){
        console.log('Command: ' + msg);
	port_write(msg + '\r\n');
    });
});

app.use(express.static(path.join(__dirname, 'public')));
app.use(express.static(path.join(__dirname, '/node_modules')));
http.listen(PORT);



