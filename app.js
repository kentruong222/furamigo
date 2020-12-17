var http = require('http');
var fs = require('fs');
var index = fs.readFileSync( 'index.html');

var SerialPort = require("serialport");

const parsers = SerialPort.parsers;

//how to recieve data
const parser = new parsers.Readline ({
    delimeter: '\r\n'
});

//location, for me COM3
var port = new SerialPort('COM3', {
    baudRate: 9600,
    dataBits: 8,
    parity: 'none',
    stopBits: 1,
    flowControl: false


}
)

port.on('error', function(err) { console.log('Error: ', err.message); })

port.pipe(parser);


//creates server
var app = http.createServer(function(req, res) {

    res.writeHead(200, {'Content-Type': 'text/html'});
    res.end(index);
});

//initalize socket
var io = require('socket.io').listen(app);

//when the connection happens
io.on('connection', function(data){

        console.log('Node.js is listening!');
})

//I believe we can output the data to the screen instead
parser.on('data', function(data){
    console.log(data)
    
    io.emit('data', data);
})

app.listen(1000);