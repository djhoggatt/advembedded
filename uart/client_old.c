//Based on http://bradsmc.blogspot.com/2013/11/c-code-to-read-gps-data-via-serial-on.html
//and https://groups.google.com/forum/#!topic/beagleboard/I26rrzcpr-g

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define BAUDRATE B9600   // Change as needed, keep B
#define MODEMDEVICE "/dev/ttyO1" //Beaglebone Black serial port
#define _POSIX_SOURCE 1 /* POSIX compliant source */
#define FALSE 0
#define TRUE 1

int rot13(char c)
{
  if('a' <= c && c <= 'z')
  {
    return (((c - 'a') + 13) % 26) + 'a';
  } 
  else if ('A' <= c && c <= 'Z') 
  {
    return (((c - 'A') + 13) % 26) + 'A';
  } 
  else 
  {
    return c;
  }
}

main()
{
    //Initialize Values
    int fd, c, res, i;
    struct termios oldtio, newtio;
    char *in;
    char out;

    // Load the pin configuration
    int ret = system("echo uart1 > /sys/devices/bone_capemgr.9/slots");

    //Open the device
    fd = open(MODEMDEVICE, O_RDWR | O_NOCTTY );
    if (fd < 0) { perror(MODEMDEVICE); exit(-1); }

    //clear struct for new settings
    bzero(&newtio, sizeof(newtio)); 

    //BAUDRATE: Set bps rate. You could also use cfsetispeed and cfsetospeed.
    //CRTSCTS : output hardware flow control (only used if the cable has
    //          all necessary lines. See sect. 7 of Serial-HOWTO)
    //CS8     : 8n1 (8bit,no parity,1 stopbit)
    //CLOCAL  : local connection, no modem contol
    //CREAD   : enable receiving characters
    newtio.c_cflag = BAUDRATE | CRTSCTS | CS8 | CLOCAL | CREAD;

    //IGNPAR  : ignore bytes with parity errors
    //otherwise make device raw (no other input processing)
    newtio.c_iflag = IGNPAR;

    //  Raw output
    newtio.c_oflag = 0;

    //ICANON  : enable canonical input
    //Disable all echo functionality, and don't send signals to calling program
    newtio.c_lflag = ICANON;

    //Now clean the modem line and activate the settings for the port
    tcflush(fd, TCIFLUSH);
    tcsetattr(fd,TCSANOW,&newtio);

    //Enter main while loop
    while (TRUE) {
        //Read input from user
	printf ("Input: ");

	//Gets is dangerous. For this assignment, we'll use it, but on future
	//assignments, we are going to replace it with something safer.
        gets(in);
        strcat(in,"\n");

        //Encrypt
        for(i = 0; in[i]!= '\0'; i++)
        { 
	    in[i] = rot13(in[i]);
        }

	//Print out the encryption
	printf("Encrypted Input: %s", in);
         
	//Write input to UART
	write(fd, in, strlen(in));

	//Delay for a bit
	for(i = 0; i < 3000000; i++);

	printf("Recieved From Server: ");

	while(out != '\n')
	{
                read(fd,&out, 1);

		//Print out the output
		printf("%c", out);
        }

	//Print out the newline
	printf("\n");
	out = '\0';
    }

    //restore old port settings
    tcsetattr(fd,TCSANOW, &oldtio);

    //Close the device
    close (fd);
}
