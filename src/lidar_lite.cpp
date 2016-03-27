#include <include/lidar_lite.h>

using namespace std;

Lidar_Lite::Lidar_Lite (int bus){
  err = 0;
  adapter_num = bus;
  snprintf(filename, 19, "/dev/i2c-%d", adapter_num);
}

Lidar_Lite::~Lidar_Lite(void){
  printf("Ending Lidar-Lite Session");
  if (i2c_bus > 0){
   int e = close(i2c_bus);
  }
}

int Lidar_Lite::connect( void ) {
  printf("Connecting to %s", filename);
  i2c_bus = open(filename, O_RDWR);
  if (i2c_bus < 0){
    err = errno;
    printf("Connect Error: %d", err);
    return -1;
  }
  if (ioctl(i2c_bus, I2C_SLAVE, 0x62) < 0) {
    err = errno;
    printf("Bus Error: %d", err);
    return -1;
  }
  return 0;
}


int Lidar_Lite::writeAndWait(int writeRegister, int value){
  res = i2c_smbus_write_byte_data(i2c_bus, writeRegister, value);
  usleep(10000);
  if (res < 0){
    err = errno;
    printf("Write Error %d", err);
    return -1;
  } else {
    return 0;
  }
}

int Lidar_Lite::readAndWait(int readRegister){
  res = i2c_smbus_read_byte_data(i2c_bus, readRegister);
  usleep(10000);
  if (res < 0){
    err = errno;
    printf("Read Error: %d", err);
    return -1;
  } else {
    return 0;
  }
}

int Lidar_Lite::getDistance( void ){
  int buf[2];
  int e = 0;
  e = writeAndWait(0x00,0x04);
  if (e < 0){
    return e;
  }
  e = readAndWait(0x8f);
  if (e < 0){
    return e;
  } else {
    buf[0] = res;
  }
  e = readAndWait(0x10);
  if (e < 0){
    return e;
  } else {
    buf[1] = res;
  }
  return (buf[0] << 8) + buf[1];
}

int Lidar_Lite::getError(void){
  return err;
}
