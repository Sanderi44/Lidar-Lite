from lidar_lite import Lidar_Lite

lidar = Lidar_Lite()
connected = lidar.connect(1)

if connected < -1:
  print "Not Connected"

print lidar.getDistance()
print lidar.getVelocity()
