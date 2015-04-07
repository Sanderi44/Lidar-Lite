import smbus
import time
bus = smbus.SMBus(1)
address = 0x62

registerMeasure = 0x00
measureValue = 0x04
registerVelocity = 0x04
velocityValue = 0x08
registerHighLowB = 0x8f

bus = smbus.SMBus(1)

def writeAndWait(myAddress, myValue):
	bus.write_byte_data(address, myAddress, myValue)
	time.sleep(0.02)

def readAndWait(myAddress):
	res = bus.read_byte_data(address, myAddress)
	time.sleep(0.02)
	return res
	
def getDistance():
	writeAndWait(registerMeasure, measureValue)
	dist1 = readAndWait(registerHighLowB)
	dist2 = readAndWait(registerHighLowB + 0x09)
	
#	print dist1 << 7
#	print dist2
	return (dist1 << 8) + dist2


def getVelocity():
	writeAndWait(registerMeasure, measureValue)
	writeAndWait(registerVelocity, velocityValue)
	vel = readAndWait(0x09)
	
	
	return signedInt(vel)

def signedInt(value):
	if value > 127:
		return (256-value) * (-1)
	else:
		return value


while(True):
	print getVelocity()
	time.sleep(0.1)
