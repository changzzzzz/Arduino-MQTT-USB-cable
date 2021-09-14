const mqtt = require('mqtt');
const SerialPort = require('serialport');
const Readline = require('@serialport/parser-readline');

const port = new SerialPort('/dev/ttyUSB0', { baudRate: 9600 });
const parser = port.pipe(new Readline({ delimiter: '\n' }));
const client = mqtt.connect("mqtt://broker.hivemq.com:1883");

client.on('connect', () => {
  client.subscribe('sit217test');
  console.log('mqtt connected');
});

const topic = 'sit217test';



// Read the port data
port.on("open", () => {
  console.log('serial port open');
});

// Got a message from the Arduino
parser.on('data', datasend =>{
  console.log('got word from arduino:', datasend);
  client.publish(topic, datasend, () => {
    console.log('published the message to MQTT...');
  });
    
});



client.on('message', (topic, message) => {
  console.log(`Received message on ${topic}: ${message}`);
});

client.on('message', (topic, message) => {
  if (topic == 'sit217test') {
    msg = `${message}\n`;
    console.log(msg);

    //now send it to the Arduino
    port.write(msg, (err) => {
      if (err) {
        return console.log('Error on write: ', err.message);
      }
      console.log('message written');
    });

  }
});