#include <X11/Xlib.h>
#include <X11/X.h>
#include <X11/Xutil.h>

#include <string.h>
#include <cstdio>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


using namespace std;

/*int main()
{
	Display *display = XOpenDisplay(NULL);
	Window root = DefaultRootWindow(display);

	XWindowAttributes gwa;

	XGetWindowAttributes(display, root, &gwa);
	int width = gwa.width;
	int height = gwa.height;


	XImage *image = XGetImage(display,root, 0,0 , width,height,AllPlanes, ZPixmap);

	const double csokkento = 1.1;

	width/=csokkento; height/=csokkento;

	unsigned char *array = new unsigned char[width * height * 3];

	unsigned long rr_mask = image->red_mask;
	unsigned long gg_mask = image->green_mask;
	unsigned long bb_mask = image->blue_mask;

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height ; y++)
		{
			unsigned long pixel = XGetPixel(image,x*csokkento,y*csokkento);

			unsigned char bb = (pixel & bb_mask);
			unsigned char gg = (pixel & gg_mask) >> 8;
			unsigned char rr = (pixel & rr_mask) >> 16;

			array[(x + width * y) * 3+0] = rr;
			array[(x + width * y) * 3+1] = gg;
			array[(x + width * y) * 3+2] = bb;
		}
	}

	return 0;
}*/


#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <netdb.h>
#include <stdarg.h>
#include <string.h>

#define SERVER_PORT 25565
#define BUFFER_SIZE 1024

int main()
{
	printf("...Server Start...\n");
	struct sockaddr_in server_addr;
	bzero(&server_addr,sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(SERVER_PORT);

	int server_socket = socket(AF_INET,SOCK_DGRAM,0);
	if(server_socket < 0)
	{
		printf("Create socket failed!\n");
		exit(1);
	}

	if(bind(server_socket,(struct sockaddr*)&server_addr,sizeof(server_addr)))
	{
		printf("Server bind port:%d failed!\n",SERVER_PORT);
		exit(1);
	}

	while(1)
	{
		struct sockaddr_in client_addr;
		socklen_t length = sizeof(client_addr);
		
		char buffer[BUFFER_SIZE];
		bzero(buffer,BUFFER_SIZE);

		if(recvfrom(server_socket,buffer,BUFFER_SIZE,0,(struct sockaddr*)&client_addr,&length) == -1)
		{
			printf("Receive data failed!\n");
			exit(1);
		}
		printf("buffer length:%d\n", strlen(buffer));
		printf("%s\n", buffer);
		char ki[] = "Pong";
		if(sendto(server_socket,ki,sizeof(ki),0,(struct sockaddr*)&client_addr,sizeof(client_addr)) < 0)
		{
			printf("Send failed!\n");
			exit(1);
		}
	}
	close(server_socket);
	printf("...Server End...\n");
	return 0;
}