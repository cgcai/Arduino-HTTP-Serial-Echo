#Arduino Http Serial Echo#
==========================
##Overview##
This sketch echos back characters received from the serial port to a socket client connecting on port 80.

It is an early part of a development effort to write a display controller for tricolor LEDs.

##Usage##
Sending characters to the Arduino over serial stores them in a buffer.

Socket clients connecting on port 80 are replied with a brief Http header, followed by the contents of the buffer. If the client is a web browser, and the buffer contains valid HTML, the browser renders and displays this HTML.

##Parameters##
Serial Baud Rate: 9600 bps

Maximum buffer size: 1024 bytes
