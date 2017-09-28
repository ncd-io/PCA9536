# Usage

This library provides a class for reading and controlling the PCA9536. The pca9536.ino file provides a simple use case for the Particle cloud. You can copy all files from the `src` directory into Particle build, or clone this library into Particle Dev.

>Create a new instance of the device
```cpp
PCA9536 IOBoard;
```

>Set direction of specific ports, all ports default to inputs. Port numbers are expected to be 0 indexed.

>***init() must be called after this is set***
```cpp
//Set port 2 as an output. (For the buzzer mini module, port 2 is the buzzer);
IOBoard.setPortDirection(2, false);
```

>Set the input direction of all ports. Only the 4 least significant bits are recognized, a set bit will be read as an input, a cleared bit will be an output.

>***init() must be called after this is set***
```cpp
//Set ports 1 and 2 as outputs, and 0 and 3 as inputs
IOBoard.inputs = 6;
```

>Set the polarity of the bits for read operations, by default 1 means the input is not active, use this to reverse that.

>***init() must be called after this is set***
```cpp
//Set the second input channel to read a 0 when activated
IOBoard.setPortPolarity(1, true);
```

>Set the polarity of all ports. Only the 4 least significant bits are recognized, a set bit indicates the polarity should be reversed, and active inputs will be read as 1.

>***init() must be called after this is set***
```cpp
//Invert the polarity of ports 0 and 1
IOBoard.polarity = 3;
```

>Initialize the device, the argument is optional, and will set all outputs to off.
```cpp
IOBoard.init(true);
```

>Read the status of a particular port, this method will return true if the port is active regardless of the polarity settings.
```cpp
//For the buzzer mini module, port 3 indicates the status of the buzzer
IOBoard.readPortStatus(3);
```

>Read the status of all ports
```cpp
IOBoard.readAllPorts();
```

>Set the status of an output, if the second arguments is true, the output is active
```cpp
IOBoard.setOutput(2, true);
```
>Activate an output for n milliseconds, n defaults to 100. If thie method is called a second time before the input has turned off, it will clear the timer, turn off the port, and start fresh.
```cpp
IOBoard.momentary(2, 500);
