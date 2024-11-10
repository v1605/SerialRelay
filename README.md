# SerialRelay
An simple, Json based web server to print usb serial commands over wifi. Useful for controlling serial devices over the network.

## Usage

The web server responds to a post request. The body of the request is a json object with the following parameters:
1. commands: A array of string values to print out to the serial interface.
2. delay: (Optional) The amount of time in milliseconds to wait in between serial commands. Default value is 0.
3. ending: (Optional) A string to append after every command (convience to not have to terminate every command). Default value is blank.

## Examples

This request will print out "HelloWorld" with no new lines.
```json
{
  "comands": ["Hello", "World"]
}
```

This request will print out "Hello\nWorld\n", waiting two seconds after each line.
```json
{
  "comands": ["Hello", "World"],
  "delay": 2000,
  "ending": "\n"
}
```

## Setup
1. Setup and install the Ardunio IDE.
2. Install the ArdunioJson libary.
3. Update the Wifi name and password in the "SerialRelay.hpp" file.
4. (Optional): Change any other settings, such as baud rate.
