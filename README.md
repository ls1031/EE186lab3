# EE186lab3


(1 Point) What is the I2C addresses of the accelerometer and magnetometer? Represent the r/w bit
using b

The I2C address of the accelerometer is (0011001b)
Of the magnetometer (0011110b)

 (1 Point) What is the sub-address (SUB), and how does it differ from the I2C address?
 
 The sub-address is the address that is specifeid in the internal memory of the peripheral, the i2c address allows us to specify that specific peripheral but to specifiy a certain register in it we use the sub address.

 (1 Point) To enable acceleration data measurement, we need to configure the CTRL1 register by
selecting the data rate and setting the enable bits. What is the CTRL1 register address and what
value should be written to this register to accomplish this?

The address of the CTRL1 register is 0x20, and the value that should be written to it is 0x37.

(1 Point) To read acceleration data for the X, Y, and Z axes, what are the 8-bit sub-addresses that
the transmitter would use to request the data?

The sub-address of the xyz axes acceleration data is 0x28, 0x2A and 0x2C also including +1 as the data for each axis as its is stored into 2 registers.
