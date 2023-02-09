# heatgun
A small hot air station for soldering, using type-858 heat gun as handle, STC8G1k17 as MCU, copper wire resistor for cold junction compensation.

##Features:

* Small, cheap, esay to make
* With cold junction compensation
* Software correction 
* Compatible with most type-858 handle
* Settings can be remembered
* PID temperature control

## Burning/Downloading

This program is only for MCU STC8G1K17-16pin, compiled and linked by SDCC 4.2.0

It must be burned at following scheme:

* Internal IRC Freq. : 22.1184MHz (as same as specified in def.h)
* User EEPROM size : 2k (as same as specified in def.h)
* Low-voltage reset : Enable
* Reset pin used as I/O port : Yes
* Hardware enable WDT : Disable (I will use software enable it)
* Add a reset code in front of ID : Yes (it will adds Band-Gap voltage reference)
* Erase all EEPROM data : Yes
* Fill data to space area : 0XFF

## About cold junction compensation for the thermocouple in the handle

I add a coper wire wound resistor (nearly 13.5 OHM) in the handle, in series with the thermocouple, for cold junction compensation at a suitable bias current.
And my software will do some corrections/calculations for getting accurate temperature from the thermocouple.

But if the connector between your handle and main controller board is not in good contact, this will introduce jitter in the temperature values.

In this case, the coper wire resistor can be totally removed, and several components (R5,R13) on the PCB can also be removed,
and several parameters inside the program can also be adjusted (set g_ana_pk=0 at main.c). 

In fact, the temperature rising of the thermocouple's cold junction within the handle, is not obvious. 
It is not really necessary to do cold junction compensation, and there are already an offset compensation. 
As long as you press and hold the button at startup, you can enter room temperature parameter.
In most cases, this is enough.

## About offset adjustment for AMP (LM321)

LM321 used in my circuit is not a precision OP-AMP and there may be large input offset voltage (normally within a few millivolts).
Because of the cold junction compensation circuit, its negative offset can be ignored, 
but if the positive offset is too large, it may be necessary to add resistor (R14) to the circuit for keeping the output in the linear range.

If you remove the cold junction compensation resistor in the handle, and the negative offset cannot be ignored, 
I suggest that you still need to add one resistor in series, however, this resistor can take a larger value, 
and at the same time increase the values of R5 and R13 in the circuit, 
so that there will be no obvious jitter caused by the connector contact resistor.

Also do not adjust the offset to 0, keep an output of OP-AMP hundreds of millivolts at least.

## About the gain of AMP (LM321)

LM321 is also not a rail-to-rail OP-AMP, especially since its high output is close to 1V away from the power voltage.

If the gain designed is too large, the temperature measurement range will be limited. 
With my current design, there is no problem with the range within 500 centidegrees, 
but if a larger range is needed, the gain needs to be reduced (change R8/R9) and the parameters (g_ana_gain at main.c) in program needs to be adjusted too.

## About power supply

The circuit requires 2 ways of power supply, a 5V for controller, another 24V for the fan (normally 24V 0.1xxA) in the handle.
I didn't include this in my design, you can use the finished product from other way, or modify an unused phone charger like me (10W required).



