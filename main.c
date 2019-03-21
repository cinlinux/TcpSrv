#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
    int sock, listener;
    struct sockaddr_in addr;
    char buf[1024],
         sendBuf[1024];

    int bytes_read;

    short hport = 3425;

    listener = socket(AF_INET, SOCK_STREAM, 0);
    if( listener < 0 )
    {
        perror("socket");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(hport);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(listener, (struct sockaddr*)&addr, sizeof(addr))<0)
    {
        perror("bind");
        exit(2);
    }

    listen(listener, 1);
    printf("listen %d\n", hport);
    while(1)
    {
        sock = accept(listener, NULL, NULL);
        if(sock < 0)
        {
            perror("accept");
            exit(3);
        }
        printf("sodket \n");
        while(1)
        {

            memset(sendBuf, '\0', 1024);
            memset(buf, '\0', 1024);
            bytes_read = recv(sock, buf, 1024, 0);

            if(bytes_read <= 0)
                break;

            strncpy(sendBuf, buf, bytes_read - 1);
            strcat(sendBuf, "123\n\0");
            send(sock, sendBuf, sizeof(sendBuf), 0);
        }
        close(sock);
    }

    return 0;
}
