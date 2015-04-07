#ifndef LIDAR_LITE_H
#define LIDAR_LITE_H


#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <cstdlib>
#include <cstdio>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define LIDAR_LITE_ADDRESS = 0x62
#define LIDAR_LITE_DIST_WRITE_REG = 0x00
#define LIDAR_LITE_DIST_WRITE_VAL = 0x04
#define LIDAR_LITE_DIST_READ_REG = 0x8f
#define LIDAR_LITE_DIST_READ_REG_2 = 0x98

class Lidar_Lite{
    int i2c_bus;
    int adapter_num;
    char filename[20];
    int res;
  public:
    int err;
    Lidar_Lite(int);
    ~Lidar_Lite(void);
    int connect(void);
    int writeAndWait(int, int);
    int readAndWait(int);
    int getDistance(void);
    int getError(void);
};




#endif
