# Lidar-Lite

## Libraries for interacting with Lidar-Lite over I2C

This library will only work in a linux environment
please install i2c-dev and i2c-tools

For recent Raspberry Pis or if you get an error such as 

`/src/lidar_lite.cpp:36:64: error: ‘i2c_smbus_write_byte_data’ was not declared in this scope`

use this command to install `i2c-dev`:

`apt-get install libi2c-dev`

I found a great tutorial (using my library!) on this website: https://mobiusstripblog.wordpress.com/2016/12/26/first-blog-post/
Please check it out!


