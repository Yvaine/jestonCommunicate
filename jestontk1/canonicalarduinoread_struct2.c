/* www.chrisheydrick.com
     
   June 23 2012

   CanonicalArduinoRead write a byte to an Arduino, and then
   receives a serially transmitted string in response.

   The call/response Arduino sketch is here:
   https://gist.github.com/2980344

   Arduino sketch details at www.chrisheydrick.com
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <sys/ioctl.h>

#define DEBUG 1

typedef struct control_{
  int LeftWheelSpeed;
  int RightWheelSpeed;
}Control;
int main(int argc, char *argv[])
{
  int fd, n, i;
  char buf[64] = "temp text";
  struct termios toptions;

  /* open serial port */
  fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY);
  printf("fd opened as %i\n", fd);
  
  /* wait for the Arduino to reboot */
  usleep(3500000);
  
  /* get current serial port settings */
  tcgetattr(fd, &toptions);
  /* set 9600 baud both ways */
  cfsetispeed(&toptions, B19200);
  cfsetospeed(&toptions, B19200);
  /* 8 bits, no parity, no stop bits */
  toptions.c_cflag &= ~PARENB;
  toptions.c_cflag &= ~CSTOPB;
  toptions.c_cflag &= ~CSIZE;
  toptions.c_cflag |= CS8;
  /* Canonical mode */
  toptions.c_lflag |= ICANON;
  /* commit the serial port settings */
  tcsetattr(fd, TCSANOW, &toptions);
  Control tk1_control;
while(1){
  /* Send byte to trigger Arduino to send string back */
  tk1_control.LeftWheelSpeed = 255;
  tk1_control.RightWheelSpeed = 255;
  
  write(fd, &tk1_control, 8);
  /* Receive string from Arduino */
  sleep(2);
  
  tk1_control.LeftWheelSpeed = -254;
  tk1_control.RightWheelSpeed = -254;
 
  write(fd, &tk1_control, 8);
  /* Receive string from Arduino */
  sleep(4);

  tk1_control.LeftWheelSpeed = 0;
  tk1_control.RightWheelSpeed = 0;
 
  write(fd, &tk1_control, 8);
  sleep(4);
  
  }
  return 0;
}
