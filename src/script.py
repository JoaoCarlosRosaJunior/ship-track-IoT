import serial
import requests
import json

arduino_port = "COM8" #serial port of Arduino
baud = 9600 #arduino uno runs at 9600 baud

BASE_URL = "https://ship-track.fly.dev/locations"

headers = {
    'Content-Type': 'application/json'
}

ser = serial.Serial(arduino_port, baud)
print("Connected to Arduino port:" + arduino_port)

def httpRequest(deviceid, latitude, longitude):
    payload = json.dumps({"deviceId": deviceid, "latitude": latitude, "longitude": longitude})
    if(latitude != 0 and longitude != 0):
        try:
            response = requests.request("POST",BASE_URL, headers=headers, data=payload)
            print(response.json())
        except requests.exceptions.RequestException as error:
            print(error)

while True:
    # Read data from the port
    line = ser.readline().decode('utf-8').strip()
    # Split the line into separate values
    values = line.split(",")
    # Check if the line contains GPS information
    if len(values) == 3:
        # Parse the latitude and longitude values
        lat, lon, deviceId = values
        print("Latitude:", lat)
        print("Longitude:", lon)
        print("Device Id: ", deviceId)
        httpRequest(deviceid=int(deviceId), latitude=int(lat), longitude=int(lon))