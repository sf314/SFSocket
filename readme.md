# SFSocket: Simple socket library
Easy way to create clients and servers. I don't really care for configuring
sockets the normal way, as it's kinda 麻烦. 

Provided classes:
- SFSocketClient
- SFSocketServer

### Preparation: creating and linking against the static library
Run `make` in the repo's root directory. This creates the `libsfsocket.a` 
static library. 

When compiling the program, be sure to include the `libsfsocket/include` 
directory, so you get access to the header files. This is because I prefer to 
keep the code in a nearby directory (like a git submodule), instead of 
installing the things directly onto the local machine. 

You'll also need to supply the path to `libsfsocket.a` after your own source
files. Be sure to put it after your files, but before things like `-lpthread`.

Simple example:
```
g++ -Ipath/to/libsfsocket/include my_code.cpp path/to/libsfsocket.a 
```

## Example Server and Client
The following example creates a simple case for a server/client architecture: 
both the server and client simple send and receive a string. Notably, you should
always `close` your server's connection before your program exits. Otherwise, 
that file pointer will persist, which will stop you from using that port for 
a while. It's annoying. The client doesn't need to be closed.

### Client:
```
// Connect to a socket
SFSocketClient client;
client.init();
client.connectTo("127.0.0.1", 1234);

// Send two strings
client.send("Hello!");

// Receive one string
cout << client.receive() << endl;
```

### Server:
```
// Create the server
SFSocketServer server;
server.init(1234);

// Accept the first connection (ideally spawn threads)
server.acceptConnection();

// Receive two strings
cout << server.receive() << endl;

// Send one string
server.send("Goodbye");

server.closeConnection();
```

Ideally, your server would spawn a new thread every time it receives a new 
connection. This way, the server can handle multiple simultaneous connections.
Do that however you want, but all you need to know is that your connection
filedescriptor (`connection_fd`) is all you need to care about when 
reading and writing from the server to multiple clients (as they would all
share the same `socket_fd`).
