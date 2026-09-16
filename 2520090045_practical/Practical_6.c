#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define FIFO1 "client_to_server"
#define FIFO2 "server_to_client"

int main()
{
    char message[100];
    char response[100];

    mkfifo(FIFO1, 0666);
    mkfifo(FIFO2, 0666);

    printf("Server waiting for client...\n");

    int fd1 = open(FIFO1, O_RDONLY);
    int fd2 = open(FIFO2, O_WRONLY);

    read(fd1, message, sizeof(message));
    printf("Client message: %s\n", message);

    sprintf(response, "Server processed: %s", message);

    write(fd2, response, strlen(response) + 1);

    close(fd1);
    close(fd2);

    unlink(FIFO1);
    unlink(FIFO2);

    return 0;
}
 #client#

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define FIFO1 "client_to_server"
#define FIFO2 "server_to_client"

int main()
{
    char message[100];
    char response[100];

    printf("Enter message: ");
    fgets(message, sizeof(message), stdin);

    int fd1 = open(FIFO1, O_WRONLY);
    int fd2 = open(FIFO2, O_RDONLY);

    write(fd1, message, strlen(message) + 1);

    read(fd2, response, sizeof(response));

    printf("Server response: %s\n", response);

    close(fd1);
    close(fd2);

    return 0;
}

#signal

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void signal_handler(int signal)
{
    if (signal == SIGINT)
        printf("\nSIGINT received: Interrupt signal handled.\n");

    else if (signal == SIGTERM)
        printf("\nSIGTERM received: Termination signal handled.\n");

    else if (signal == SIGUSR1)
        printf("\nSIGUSR1 received: User-defined signal handled.\n");
}

int main()
{
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);
    signal(SIGUSR1, signal_handler);

    printf("Process ID: %d\n", getpid());
    printf("Waiting for signals...\n");

    while (1)
    {
        printf("Program is running...\n");
        sleep(3);
    }

    return 0;
}