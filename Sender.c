#include "header.h"

int main()
{
    //### Reading the file and put it in an array ###//

    int characters = -1; // stands for the size of characters in the file
    char ch;
    FILE * file;
    file = fopen("text1.txt", "r");

    while ((ch = fgetc(file)) != EOF)
    {
        characters++;    // counting the number of characters in the file
    }

    printf("The number of characters in the file is: %d", characters);

    FILE * file1;
    file1 = fopen("text1.txt", "r");
    
    char arr1[characters/2];
    char arr2[characters/2];
    for (size_t i = 0; i < characters; i++)
    {
        if (i< characters/2)
        {
            arr1[i] = fgetc(file1);
        }
        else
        {
            arr2[i-characters/2] = fgetc(file1);
        }
    }

    int a = sizeof(arr1);
    int b = sizeof(arr2);

    //### Now I have two arrays the contains together all the file ###//
    
    int sockfd = socket(AF_INET, SOCK_STREAM, 0); // Creates the socket
    if (sockfd == -1)
    {
        printf("Could not create socket\n");       // Vailidation of the Socket creations..
    }
    else if (sockfd == 0)
    {
        printf("Created socket succesfully\n");
    }

    struct sockaddr_in serverAddress; // new struct decleration of sockaddr_in type
    struct sockaddr_in * pserver_addr = &serverAddress; // Pointer Decleration
    memset(&serverAddress,0, sizeof(serverAddress)); // zerod the last 8 bits so it will match the suckaddr struct

    serverAddress.sin_family = AF_INET; // value = AF_INET. match to the sa_family of suckaddr struct
    serverAddress.sin_port = htons(20000); // switch from host byte order to network(Big endian) byte order.
    int convert = inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr); // converting the IPv4 from text to binary
	if (convert <= 0)                                                       // Checking if the conversion worked
	{
		printf("inet_pton() failed\n"); 
		return -1;
	}
    
    int sockcon = connect(sockfd, (struct sockaddr *) &serverAddress, sizeof(serverAddress)); // Connecting to the Server

      if (sockcon == -1)                                                                      // Vailidation of the connections between
    {                                                                                         //  theserver      
        printf("connect() failed with error code\n\n");
    }
    else if (sockcon == 0)
    {
        printf("Connected to server succesfully!\n\n");
    }

    
    char temp[1000];
    int bool = 1;
    int userChoise = 1;
    char *exitMessage = "1111";
    int exitMessageLen = strlen(exitMessage) + 1;
    char *stayMessage = "0000";
    int stayMessageLen = strlen(exitMessage) + 1;
    int i = 0;
    int bytesSent;
    int xz= 0;
    printf ("\n\nsize of arr1: %ld\n\n", sizeof(arr1));
    printf ("\n\nsize of arr2: %ld\n\n", sizeof(arr2));
    while (userChoise == 1)
    {  
        printf("Sending the first half of the file...\n\n");
        // while(i < 500000 )
        // {
            bytesSent = send(sockfd, arr1, sizeof(arr1), 0);
        // i = i+5000;
        // xz += bytesSent;
        // }
        i = 0;
        printf("\n\nxz:%d\n\n", xz);
        if ( bytesSent == 0 || bytesSent == -1)
    {
        printf("didnt send\n\n");
    }

        if ( bytesSent > 0)
    {
        printf("Send succesfully!\n\n");
    }
        int xy = 0;
        
        char bufferReply[12] = {'\0'};
        char sample[] = "10010101110";  
        printf("\n\nhekk\n\n");
        int bytesReceived = recv(sockfd, bufferReply, 12, 0);
        printf("hezzzz");
        int zz = bytesReceived;
        printf("\n\nzz is:%d\n\n", zz);
        puts(bufferReply);
        puts(sample);
        if (1)
        {
            printf("The server send an Authentication!\n\n");

            setsockopt(sockfd, IPPROTO_TCP, TCP_CONGESTION, "reno", 4);
            printf ("Chanaging the CC Algorithm to reno...\n\n");
            // while(i < 500000)
            // {
            int bytesSent = send(sockfd, arr2, sizeof(arr2), 0); // Send the second part of the file
            // xy += bytesSent;
            // i = i + 5000;
            // }
            i = 0;
            printf ("Sending the second part of the file...\n\n");
        }
        else("NO ACK");
        
        printf("\n\nxy:%d\n\n", xy);
        printf("Do you want to send the file again? \npress 1 if yes, any other key for no\n\n");
        userChoise = 0;
        scanf("%d", &userChoise);
        
        if(userChoise == 1)
        {
            printf("chose 1");
            setsockopt(sockfd,SOL_SOCKET, TCP_CONGESTION, "cubic", 5);  // Change the CC Algorithm
            printf ("Chanaging the CC Algorithm to cubic...\n\n");
            int x = send(sockfd, stayMessage, 5, 0);
            printf("Sending the server that I wanna stay and keep sending messages... \n\n");
            int ww = x;
            printf("\n\nwwwwww is:%d\n\n", ww);
        }

        if (userChoise != 1)
        {
            int x = send(sockfd, exitMessage, exitMessageLen, 0);
            printf("Sending the server an Exit message and closing the socket! \n\n");
            break;
        }
        
    }
    
    printf("Disconnected from the server.\n");
    close(sockfd);

    return 1;
}