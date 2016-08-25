# Measuring temperature using an i2c temperature sensor using a Riffle

## i2c basics

A [thermistor](https://en.wikipedia.org/wiki/Thermistor) provides a simple, precise way of measuring temperature.  The resistance of a thermistor is dependent on temperature in a particular way -- if we know this relationship, then we can measure temperature by measuring the resistance of the thermistor (something we can do with a simple electronic circuit.)

Adafruit has a [great tutorial](https://learn.adafruit.com/thermistor/overview) on thermistors, and measuring them with an Arduino.  The Riffle works very similarly to an Arduino, so their tutorial is a good resource for the Riffle circuitry as well. 

## i2c temperature sensors

There are several types of thermistors, and the relationship between resistance and temperature differs depending on the type.  It's important to know what type of thermistor you're using in order that your circuit and code are appropriate. 

The particular type of thermistor we'll be covering below is an "NTC" or "Negative Temperature Coefficient" thermistor -- which means that the resistance decreases as the temeprature increases.  Typically, for NTC thermistors, the important parameters to know are **B** -- the "B coefficient" of the thermistor -- and **R_o**, the resistance of the thermistor at room temperature (defined as 25 C).  

Here, we're using the same thermistor that is used in the Adafruit tutorial linked to above, which has the following properties: 

- **R_o** -- the resistance of the thermistor at 25 C -- is 10K
- **B** -- the "B parameter" -- is 3950

These numbers will show up in our Riffle temperature analysis code.

## i2c Circuit

**NOTE:**  Usually, i2c devices require 'pullups' -- resistors that connect the signal lines (SCL and SDA) to the power line.  On the Riffle, these 'pullups' are already present on the main Riffle board (they are needed for other i2c chips on the Riffle).  So you do not need to provide i2c pullups in your own circuit.  If these pullup resistors are already present on the board you are using, they usually won't interfere with your measurement.  

<img src="pics/i2c_schem_graphic.png">

## i2c Sensor connected to a Riffle Protoboard

Below is a picture of a simple voltage divider setup on the Riffle Protoboard which matches the schematic shown above.  Note that there is no 'polarity' to the thermistor, so either wire works in either position.  Also note that the 'columns' of pins on the Riffle Protoboard, as shown, are connected electrically by small traces -- this is what allows us to connect e.g. the red power line to one end of the resistor R1 by simply having the wires located in the same column.  

<img src="pics/i2c_proto.png">

## Code for i2c Temperature Sensor Datalogging with a Riffle

The Arduino code [riffle_thermistor.ino] in this repository will measure temperature using analog pin A0 on the Riffle, and record it to a microSD card along with a timestamp. 

The data is output in "TSV" format, with tabs separating columns of data (timestamp in the first column, RTC temperature in the second column, thermistor temperature in the third column).


