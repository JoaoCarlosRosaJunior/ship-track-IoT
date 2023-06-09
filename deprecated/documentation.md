This is the old code we has using to create the integration with arduino, ESP8266-01 for wifi communication and GPS module NEO-6M.

This code with this setup would not work, so our strategy is to change de board to NodeMCU ESP8266, that is a robust microcontroller with a builtin wifi module, but the board didn't arrived at time.

Because that we use the python code on the src folder to serialize the location data and send to the backend service. The gps-tracking ino code get the location data and sends via serial communication to de PC.