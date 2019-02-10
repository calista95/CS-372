# Programming Assignment 1

To start the server:
Type the following line, followed by your four digit port number   
For example, to run the server on port 9999, type in  

```
python chatserve.py 9999

```
If this is done correctly, the server will give the following response:
```
The server is ready to receive
```

To start the client:
We first need to compile our client file, since it is written in C. To do this, type in the following line in your terminal: 
```
gcc -o client chatclient.c
```

Now that you have an executable file client, type the following line, followed by your hostname and four digit port number of the server that is currently running  
For example, to run the client on local host 127.0.0.1 and port 9999, type in    
```
client 127.0.0.1 9999
```

At this point, your server and client have a connection. On the client window, you will be asked to enter a handle made up of 10 or less characters. After this information is submitted, the client initiates the initial message. Then, it is the server's turn to respond. This pattern keeps alternating until one side decides to quit. 

To quit: 
1) The client types in '\quit' at its turn. 
2) The server types in '\quit' at its turn. 
Either way, this will cut off the connection with the client. The server will still be open to receiving any client connections and return to this state:
```
The server is ready to receive
```

Example of output on client side:
```
Enter your client handle:
Bob
Bob> Hello
Server> Hi
Bob> Goodbye
Server > See you
Bob \quit
```
Example of output on server side:
```
The server is ready to receive
Bob> Hello
Server> Hi
Bob> Goodbye
Server > See you
The server is ready to receive 
```
To end the server program that is running, hit Ctrl-C. 
