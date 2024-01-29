// for compile and build: sudo g++ -o test test.cpp
// Program Information:
/*
    This example show how create raspberry pi as a server and other software as a client.
    other software can run on same machin or external pc machin.
*/
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>          // this is main library for use network programming.
#include <sys/socket.h>         // this is main library for use network programming.
#include <netinet/in.h>         // this is main library for use network programming.
#include <fcntl.h>              // this library use for non blocking mode of socket programming for accpet method function.


/*
To set a socket to non-blocking mode in C++, you can use the fcntl function. 
Non-blocking mode allows your program to continue executing code even if certain socket 
operations would normally block
*/

#define PORT 12345
/*
There are three ranges: Well-known ports: 0 to 1023. 
Registered ports: 1024 to 49151. 
Dynamic and/or private ports: 49152 to 65535.
*/
#define BUFFER_SIZE 1024
bool network_connected_flag = false;    // this flag indicates network connected or not connected.

int main() {
    int serverSocket, clientSocket;
    /*
    struct sockaddr_in is a structure used for representing an IPv4 socket address. Here's a breakdown of the structure:    
    struct sockaddr_in {
    short            sin_family;   // Address family (AF_INET for IPv4)
    unsigned short   sin_port;     // Port number
    struct in_addr   sin_addr;     // IP address
    char             sin_zero[8];  // Padding to make the structure the same size as struct sockaddr
};
    */
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addrLen = sizeof(clientAddr);
    char buffer[BUFFER_SIZE] = {0};

    // Create socket:
    if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        std::cerr << "Socket creation failed" << std::endl;
        return -1;
    }
    /*
    1- socket: The socket function is used to create a socket. It takes three arguments:

        - AF_INET: Specifies the address family, in this case, IPv4.
        - SOCK_STREAM: Specifies the socket type, in this case, a stream socket (TCP).
        - 0: The protocol parameter. When set to 0, the system chooses the appropriate 
            protocol based on the specified address family and socket type.
    
    2- (serverSocket = socket(...)) == 0: The result of the socket function is assigned to the serverSocket variable. 
    If the result is equal to 0, it indicates an error in socket creation.

    3- If the socket creation fails, an error message is printed to std::cerr, 
    and the program returns with a value of -1 to indicate an error condition.

    This block of code ensures that the server socket is successfully created, 
    and if not, it prints an error message and terminates the program. 
    It's a common practice in socket programming to check for errors after 
    attempting to create a socket, as failure in socket creation could indicate 
    issues like a lack of resources or permission problems.
    */

    // Set the server socket to non-blocking mode
    int flags = fcntl(serverSocket, F_GETFL, 0);
    if (flags == -1) {
        // Error handling for fcntl
        std::cerr << "Failed to get socket flags" << std::endl;
        close(serverSocket);
        return -1;
    }

    if (fcntl(serverSocket, F_SETFL, flags | O_NONBLOCK) == -1) {
        // Error handling for fcntl
        std::cerr << "Failed to set socket to non-blocking mode" << std::endl;
        close(serverSocket);
        return -1;
    }

    /*
    The fcntl function is used to get the current flags of the socket.

    The O_NONBLOCK flag is added to the current flags, indicating that the socket should be 
    set to non-blocking mode.

    The modified flags are then set back to the socket using another fcntl call.

    After setting the socket to non-blocking mode, the accept call will not block if there are no 
    incoming connections. Instead, it will return immediately with an error (EAGAIN or EWOULDBLOCK), 
    allowing your program to continue execution. You can handle this error appropriately in your code.
    */

    // Set up server address structure
    serverAddr.sin_family = AF_INET;    
    /*
    This line sets the address family of the serverAddr 
    structure to AF_INET, indicating that the address is an IPv4 address.
    */

    serverAddr.sin_addr.s_addr = INADDR_ANY;
    //serverAddr.sin_addr.s_addr = inet_addr("169.254.77.81"); // for fixed ip addresses.
    /*
    This line sets the IP address of the server. INADDR_ANY is a constant 
    that represents any available network interface on the machine. 
    This means that the server will be able to accept connections on any of its 
    network interfaces. In other words, it will listen on all available IP addresses.
    */
    /*
    If you want to bind the server socket to a specific IP address instead of using INADDR_ANY, 
    you can set the sin_addr.s_addr field of the serverAddr structure to the desired IPv4 address. 
    Here's an example of how you can modify the code to bind the server socket to a specific IP address:

    Assuming you want to bind to a specific IP address, let's say 192.168.1.100:
    serverAddr.sin_addr.s_addr = inet_addr("192.168.1.100"); // Use the desired IP address

    The inet_addr function is used to convert the string representation of the IP address to 
    the appropriate format. You provide the desired IP address as a string, and it returns the 
    equivalent in_addr_t value suitable for use in sin_addr.s_addr.
    */

    serverAddr.sin_port = htons(PORT);
    /*
    This line sets the port number of the server. htons is a function that converts 
    the port number from host byte order to network byte order. This is important because 
    different architectures may have different byte orders, and network protocols typically 
    use a standardized, big-endian (network byte order) format.
    */

    /*
    After these lines execute, serverAddr contains the necessary information for binding 
    the server socket to a specific IP address and port. The server socket can then listen 
    for incoming connections on the specified IP address and port.
    */

    // Bind the socket to the specified address and port
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Bind failed" << std::endl;
        perror("Bind failed");
        return -1;
    }

    // Listen for incoming connections
    if (listen(serverSocket, 3) < 0) {
        std::cerr << "Listen failed" << std::endl;
        return -1;
    }
    /*
    The listen function takes two parameters: the file descriptor of the server socket 
    (serverSocket) and the maximum number of pending connections that can be in the queue 
    for this socket (in this case, 3).
    */

    std::cout << "Server listening on port " << PORT << std::endl;

    while (true) 
    {
        // Accept a client connection
        if(network_connected_flag == false)
        {
            if ((clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &addrLen)) >= 0) 
            {
                std::cout<< serverSocket<< std::endl;
                network_connected_flag = true;
                std::cout << "Connection accepted from " << inet_ntoa(clientAddr.sin_addr) << ":" << ntohs(clientAddr.sin_port) << std::endl;
            }
        }

        /*
        This section of code deals with error checking after the accept function call. 
        The accept function is used to accept incoming client connections. 
        accept Function:

        The accept function takes three parameters: the file descriptor of the server socket 
        (serverSocket), a pointer to a structure (struct sockaddr_in) where the client's address 
        information will be stored ((struct sockaddr*)&clientAddr), and a pointer to a socklen_t 
        variable that will be updated with the size of the client's address structure (&addrLen).
        */
        /*
        Blocking Nature of accept:

        The accept function is inherently blocking. It waits for a client to connect before it returns. 
        If no client is connecting, the program will block at this point.
        */

        if(network_connected_flag == true)
        {
            // Receive data from the client
            int bytesRead = read(clientSocket, buffer, BUFFER_SIZE);
            /*
            read Function: The read function is a system call that attempts to read up to 
            BUFFER_SIZE bytes from the clientSocket and stores them in the buffer. 
            The return value (bytesRead) indicates the actual number of bytes read.

            - If bytesRead is positive, it represents the number of bytes successfully read.
            - If bytesRead is 0, it means the end of the file has been reached (the client has closed the connection).
            - If bytesRead is -1, an error occurred during the read operation.
            */

            if (bytesRead <= 0) 
            {
                std::cerr << "Error reading from client" << std::endl;
                network_connected_flag = false;
                // Close the client socket
                close(clientSocket);
                //return -1;
            }
            else
            {
                std::cout << "Received from client: " << buffer << std::endl;
                if(std::strcmp(buffer, "sudo reboot") == 0)
                {   
                    std::cout<< "System is rebooting ...!"<< std::endl;
                    system("sudo reboot");
                }
                // Send a response to the client
                const char* response = "Hello from Raspberry Pi!";
                send(clientSocket, response, strlen(response), 0);
            }
        }

    }

// Close the server socket (this code will not be reached in an infinite loop)
close(serverSocket);

return 0;
}
