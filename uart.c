//Based on http://bradsmc.blogspot.com/2013/11/c-code-to-read-gps-data-via-serial-on.html
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define BAUDRATE B9600 // Change as needed, keep B
#define MODEMDEVICE "/dev/ttyO1" //Beaglebone Black serial port
#define _POSIX_SOURCE 1 /* POSIX compliant source */
#define FALSE 0
#define TRUE 1
main()
{
	//Initialize Values
	int fd, c, res;
	struct termios oldtio, newtio;
	char buf[255];

	// Load the pin configuration
	int ret = system("echo uart1 > /sys/devices/bone_capemgr.9/slots");

	//Open the device
	fd = open(MODEMDEVICE, O_RDWR | O_NOCTTY );
	if (fd < 0) { perror(MODEMDEVICE); exit(-1); }

	//clear struct for new settings
	bzero(&newtio, sizeof(newtio));

	//BAUDRATE: Set bps rate. You could also use cfsetispeed and cfsetospeed.
	//CRTSCTS : output hardware flow control (only used if the cable has
	// all necessary lines. See sect. 7 of Serial-HOWTO)
	//CS8 : 8n1 (8bit,no parity,1 stopbit)
	//CLOCAL : local connection, no modem contol
	//CREAD : enable receiving characters
	newtio.c_cflag = BAUDRATE | CRTSCTS | CS8 | CLOCAL | CREAD;

	//IGNPAR : ignore bytes with parity errors
	//otherwise make device raw (no other input processing)
	newtio.c_iflag = IGNPAR;

	// Raw output
	newtio.c_oflag = 0;

	//ICANON : enable canonical input
	//Disable all echo functionality, and don't send signals to calling program
	newtio.c_lflag = ICANON;

	//Now clean the modem line and activate the settings for the port
	tcflush(fd, TCIFLUSH);
	tcsetattr(fd,TCSANOW,&newtio);

	//Write
	while (TRUE) {
		//Delay
		int i;
		for(i = 0; i < 900000; i++);

		//Write string to file
		write(fd, "Hello World", 13);
	}

	//restore old port settings
	tcsetattr(fd,TCSANOW, &oldtio);

	//Close the device
	close (fd);
}
