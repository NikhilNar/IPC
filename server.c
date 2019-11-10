#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <signal.h>
#define PORT 8080
int noOfDigits = 0;
int noOfLines = 0;

void sigintHandler(int sig_num)
{
    printf("Total number of lines = %d", noOfLines);
    printf("\nTotal number of digits = %d", noOfDigits);
    printf("\n");
    exit(0);
}

int main(int argc, char const *argv[])
{
    int serverFd, newSocket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    // Creating socket file descriptor
    if ((serverFd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Forcefully attaching socket to the port 8080
    if (bind(serverFd, (struct sockaddr *)&address,
             sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(serverFd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((newSocket = accept(serverFd, (struct sockaddr *)&address,
                            (socklen_t *)&addrlen)) < 0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    // check if the user enters ctrl+c
    signal(SIGINT, sigintHandler);

    while (1)
    {
        valread = read(newSocket, buffer, 1024);
        if (strstr(buffer, "exit"))
        {
            printf("Total number of lines = %d", noOfLines);
            printf("\nTotal number of digits = %d", noOfDigits);
            printf("\n");
            break;
        }
        printf("%s\n", buffer);
        char *s;
        //parse the input and count the digits
        for (s = buffer; *s != NULL; s++)
        {
            if (isdigit(*s))
                noOfDigits++;
        }
        noOfLines++;
    }
    return 0;
}