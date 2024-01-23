<h1 align="center">
	💬 minitalk
</h1>

## 💡 About the project

You must create a communication program in the form of a client and a server.

I've written an article that provides detailed guidance on developing this project. 
You can access it on [Medium](https://medium.com/@beatrizbazaglia/minitalk-6176322eb954)

## 🛠️ Requirements

**Mandatory part:**

• The server must be started first. 
After its launch, it has to print its PID.

• The client takes two parameters:
   ◦ The server PID.
   ◦ The string to send.
   
• The client must send the string passed as a parameter to the server.
Once the string has been received, the server must print it.

• Your server should be able to receive strings from several clients in a row without needing to restart.

• The communication between your client and your server has to be done only using UNIX signals.

• You can only use these two signals: SIGUSR1 and SIGUSR2.

**Bonus part:**

• The server acknowledges every message received by sending back a signal to the
client.
• Unicode characters support!

## 📋 Testing

To compile, go to the project path and run:

```shell
$ make
```

Start the "server," and note it's PID displayed on the terminal.

```shell
$ ./server
```

In a separate shell tab, launch the "client," providing the server's PID and your message string as arguments

```shell
$ ./client "PID" "Your message string"
```

Your message will be displayed in the server window.
