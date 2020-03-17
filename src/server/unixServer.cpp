/*
Server for Unix Platform.

Basic Logic:
	Set up server socket.
	Bind it with some IP::Port.
	Wait for client connection.
	Accept connection
		while(true)
			Receive position message from clients
			Calculate the position of the ball
			send the position message to clients

	Close the socket.
*/


