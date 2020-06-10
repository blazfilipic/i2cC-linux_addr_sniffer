#include <iostream>
#include <fstream>
#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>

using namespace std;

int start = 0;
int file_i2c;
int length;
unsigned char buffer[8] = { 0 };

int main(void)
{
	char* filename = (char*)"/dev/i2c-1";
	if ((file_i2c = open(filename, O_RDWR)) < 0) {
		cout << "Failed to open the i2c bus" << endl;
		return 0;
	}   
	for (int i = 0; i < 128; i += 16) {
		printf("%02x: ", i);

		for (int j = 0; j < 16; j++) {

			fflush(stdout);

			uint8_t addr = i + j;
			int lenghtRead = 0;
			uint8_t buffer2[1] = { 0 };

			if (ioctl(file_i2c, I2C_SLAVE, addr) < 0)
			{
				printf("Failed to acquire bus access and/or talk to slave.\n");
				//ERROR HANDLING; you can check errno to see what went wrong
				return 0;
			}
			length = 1;
			if (read(file_i2c, buffer, length) != length) {
				printf("-- ");

			}

			else {

				printf("%02x ", addr);
			}
		}

		printf("\n");
	}

	cout << "exiting" << endl;
	start = 1;
	return 0;
}
