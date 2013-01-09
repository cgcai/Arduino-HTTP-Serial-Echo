import sys
import serial
import os.path
    
def validate_modem(modem):
    if os.path.exists(modem):
        return modem
    else:
        print "Supplied modem does not exist!"
        exit()

def validate_baud(baud):
    accepted_rates = ["9600"]
    if baud in accepted_rates:
        return baud
    else:
        print "Unsupported baud rate!"
        exit()

def validate_text(text):
    if len(text) > 1024:
        print "Warning: Length exceeds Arduino buffer. Will not be completely transferred."
    return text

if len(sys.argv) != 4:
    print "Usage: ./settext.py <modem> <baud> <string>"
    exit()
    
modem = validate_modem(sys.argv[1])
baud = validate_baud(sys.argv[2])
text = validate_text(sys.argv[3])

console = serial.Serial(modem, baud, timeout = 0)
written = console.write("\n") # Clear buffer.
written += console.write(text) # Set new text
print "Written:", written
console.close()
