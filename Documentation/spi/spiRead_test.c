
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>


static uint8_t lsb;
static uint8_t bits = 8;
static uint32_t speed = 30000;

int main()
{
	int ret = 0;
	int fd;
	int len = 6;
	int receivedValue = 0;
	struct spi_ioc_transfer spi;
	int spiWRMode = SPI_MODE_0;
	int spiRDMode = SPI_MODE_0;
	unsigned char buff[6];

	printf("1\n");
	fd = open("/dev/spidev1.0", O_RDWR);
	printf("2\n");
	if (   (ioctl(fd, SPI_IOC_WR_MODE, &spiWRMode) < 0)
		|| (ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits) < 0)
		|| (ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed)  < 0)
		|| (ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits) < 0)
		|| (ioctl(fd, SPI_IOC_RD_MODE, &spiRDMode) < 0)
		|| (ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed)  < 0)
		|| (ioctl(fd, SPI_IOC_RD_LSB_FIRST, &lsb) < 0)){
		printf("error");
		return -1;
	}
	printf("3\n");
	//buff[0] = 0x00;
	//spi.tx_buf        = (unsigned long)(buff) ;  // transmit from "data"
	spi.rx_buf        = (unsigned long)(buff) ;  // receive into "data"
	spi.len           = len;
	spi.speed_hz      = speed;
	spi.bits_per_word = bits;
	spi.cs_change     = 0;                       // this keep CS active between the different transfers
	spi.delay_usecs   = 0;
	printf("4\n");
	if(ioctl(fd, SPI_IOC_MESSAGE(1), &spi) < 0){
		return -1;
	}
	printf("5\n");
	receivedValue += buff[3];
	receivedValue += (buff[4] & 0x3)<<8;
	printf(" # Read value %02x %02x, %02x, %02x %02x, %02x, %d\n", buff[0], buff[1], buff[2], buff[3], buff[4], buff[5], receivedValue);
	

	close(fd);
	return 0;
}



