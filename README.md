# Server-Client_Programm-using-TCP-and-UDP
This is a Server-Client program implemented in C language using TCP and UDP protocols. 
The program allows the client to send messages to the server, change the server's IP address, display network traffic, and quit the program. 
The program uses the sys/socket.h library for socket operations and the pcap.h library for capturing network information.

# Features

**TCP Communication:** Clients can send messages to the server using the TCP protocol. The server listens for incoming TCP connections and handles each client request individually.

**UDP Communication:** Clients can also send messages to the server using the UDP protocol. The server receives UDP packets and processes the messages from the clients.

**IP Address Management:** The program allows the server to change its IP address dynamically. This feature enables the server to adapt to different network configurations.

**Network Traffic Display:** The server includes a feature to capture and display network traffic using the pcap library. 
                        It allows monitoring and analysis of the data packets flowing through the network interface.

**Communication Logging:** All communication between the client and server is logged in a file. The program records the messages sent and received, along with timestamps, for future reference and analysis.

# Getting Started

**Prerequisites**
To compile and run this program, you need the following:

1. C compiler (e.g., GCC)
2. pcap library (for capturing network traffic)

Make sure you have these dependencies installed on your system before proceeding.

**Compilation**
1. Clone the repository or download the source code files to your local machine.

2. Open a terminal or command prompt and navigate to the project directory.

3. Compile the server program using the following command:

   gcc server.c -o server -lpcap
  
5.  Compile the client program using the following command:

    *gcc client.c -o client*

**Usage**
1. Run the server program by executing the following command:

          <b>./server</b>

The server will start listening for client connections on port 12345.

2. Run the client program by executing the following command:

          <b>./client</b>

The client program will display a menu with various options.

3. Choose an option from the menu by entering the corresponding number and pressing Enter.

4. Follow the prompts to perform the selected operation (e.g., enter a message to send).

5. The server will display the received messages and log all communication in the "communication.log" file.

6. Repeat steps 3-5 to perform additional operations or choose the "Quit" option to exit the client program.

 **Contributing**

Contributions are welcome! If you find any issues or have suggestions for improvements, please open an issue or submit a pull request.

**Acknowledgments**

This program was created as a demonstration and learning exercise for socket programming in C.

**Contact**
For any questions or inquiries, please contact:

<b>Project Maintainer: Muhammad Luqman Shoaib</b>   

You can customize this README file further by adding sections such as "Dependencies," 
"Troubleshooting," or "FAQ" based on your program's specific requirements.
Include any necessary setup instructions, troubleshooting steps, 
or frequently asked questions to help users understand and use your program effectively.
