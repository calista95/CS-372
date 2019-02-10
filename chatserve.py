#Project 1
#Nsme: chatserve.py
#Language of implementation: Python
#Description: This is the server. It takes a port number specified from the command line, sets up a TCP welcoming socket, and begins listening for client requests. 
#Source code borrowed from Lecture 15, slide 9
#Name: Calista Wong
#Class: CS 372

from socket import * #import Python's socket library
import sys #so we can use command line arguments

#get command line argument of the port specified 
serverPort = int(sys.argv[1])
serverSocket = socket(AF_INET,SOCK_STREAM) #specify that we want a TCP connection
serverSocket.bind(('', serverPort))
serverSocket.listen(1) #server begins listening for incoming TCP request
while 1: #stay open to any incoming connections
	print ('The server is ready to receive')
	connectionSocket,addr = serverSocket.accept() #server waits on accept() for incoming requests, new socket created on return 
	
	while 1: #keep the current connection ongoing 
		sentence = connectionSocket.recv(8000) #read bytes from socket 
		if not sentence: #check if sentence is good 
			break
		print (sentence.decode("utf-8")) #print client's message

		#respond to client 
		message='' #clear the message buffer 
		message = raw_input("server> ")

		#make sure that message is 500 char or less, otherwise, truncate
		if len(message)>500:
			print("Note: Your message is longer than 500 characters. It will be truncated.")
			message = message[:500]

		if message == "\quit": #determine if user wants to quit
			#print ("The server has requested to quit. Goodbye!")
			quitMessage = "\quit"
			connectionSocket.send(quitMessage.encode())
			break
		else:
			#do stuff with the client message here#
			connectionSocket.send(message.encode())
	connectionSocket.close() #close connection to this client, but not to welcoming socket
