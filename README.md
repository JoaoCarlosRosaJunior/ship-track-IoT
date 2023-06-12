# IoT device (Ship Tracking)

This repository contains an arduino code to get the location of the device and send it to the computer by serial communication. It also contains a python code to serialize this arduino data and send it to our backend system


## Tech Stack

**Physical Materials:** 
- GPS module GY-GPS6MV1 
- Arduino Uno R3 
- PC to run the script

**Language:** 
- Ino code: Arduino code that is compiled to C++
- Python: To run the script

## Have the materials and want to test the code?

1. Download the [TinyGPS library](https://github.com/mikalhart/TinyGPS).
2. Assemble the connections as it is in the circuit.

<img src="./public/circuit.jpeg" width="400"/>

3. Upload the code to the arduino.

## Want to test the code but don't have the IoT device? We created a script for you to test it

1. First you need a orderId that can be created on our [front-end](https://ship-chain-dash.fly.dev)

2. Pick up 2 points you would like to be the addr of source and destination. We need the latitude and longitude points. How to get the latitude and longitude? You can access this [link](https://support.google.com/maps/answer/18539?hl=en&co=GENIE.Platform%3DDesktop)

3. Run the command:
```
cd test
```

Install the dependencies:
```
pip install -r requirements.txt
```

4. Run the script:
```
python3 script.py
```