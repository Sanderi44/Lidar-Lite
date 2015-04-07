#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

int main() {

	int file;
	int adapter_nr = 1;  // Get dynamically later
	char filename[20];

	snprintf(filename, 19, "/dev/i2c-%d", adapter_nr);
	printf("%s\n", filename);
	file = open(filename, O_RDWR);
	printf("file: %d\n", file);
	if (file < 0){
		printf("Problem Opening %s\n", filename);
		printf("Error Number: %d", errno);
		exit(1);  // you can check errno to see what went wrong
	}

	int addr = 0x62;  // Address of Lidar-Lite
	if (ioctl(file, I2C_SLAVE, 0x62) < 0) {
		printf("IOCTL Error: %d", errno);
		exit(1); //  Check errno to see what went wrong
	}

	__u8 distCom = 0x00;
	__u8 distVal = 0x04;
	__u8 distRead = 0x8f;
	__s32 res;
	__s32 res1;
	__s32 res2;
	while(1){
		res = i2c_smbus_write_byte_data(file, 0x00, 0x04);
		usleep(100000);
		if (res < 0){
			printf("Write Errno: %d\n", errno);
		}
		res1 = i2c_smbus_read_byte_data(file, 0x8f);
		usleep(100000);
		res2 = i2c_smbus_read_byte_data(file, 0x98);
		usleep(100000);
		__s32 val = (res1 << 8) + res2;
		if (res1 < 0) {
			printf("Read Errno: %d\n", errno);
		} else {
			printf("Got Value: %d\n", val);
		}
	}
}
