# networks_lab_2
This program allows you to receive and send files no larger than one terabyte using the TCP protocol.
You can run the program either as a server or as a client.
To start the server, pass 'listen' and the port as command line arguments, for example,
>listen 8080.
>
To start the client, pass as command-line arguments 'send', the file name, the IP address of the server and the port, for example
>send file.txt 127.0.0.1 8080
