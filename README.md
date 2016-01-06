# Uno-WIFI-Contest
My project for the UNO Wifi Contest that circulates heat from a running clothes dryer into the house when the humidity of the hot air is 
below a set value.

This project uses an UNO, at TMP36 temperature sensor, an HIH-5030-001 Humidity sensor, a servo, a potentiometer and a 
Dryer Vent Heat Deflector similar to:
http://www.acehardware.com/product/index.jsp?productId=1273159&KPID=964390&pla=pla_964390

An Electric Imp was also used to log data to data.sparkfun.com through the home WIFI.  The temperature and humidity can then be viewed and graphed 
on a web page developed for the Electric Imp.

These dryer vent heat deflectors work by deflecting the heat from a dryer during winter months into the house.  The problem is it's not a 
good idea to deflect the heat into the house if the humidity of the air is high.  This project keeps the door of the vent closed until 
both the temperature is >100 and the humidity is < a set point.  The set point is a potentiometer but could be set from the Electric
Imp web page as well.

Here is a video of the servo moving the door open and closed:
https://youtu.be/COTz70SJQqE

