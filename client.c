#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// This function sends a single bit to the server process.
// The bit is represented by a signal (SIGUSR1 for 1, SIGUSR2 for 0).
void	send_bit(int pid, int bit)
{
	int	signal;

	// If the bit is 1, send SIGUSR1. Otherwise, send SIGUSR2.
	if (bit == 1)
		signal = SIGUSR1;
	else
		signal = SIGUSR2;
		
	// Send the signal to the server process.
	if (kill(pid, signal) == -1)
	{
		perror("Error\n");
		exit(1);
	}
}

// This function sends a single character (8 bits) to the server process.
void	send_char(int pid, char c)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		// The bit is obtained by shifting the character to the right by 'i' positions and bitwise ANDing with 1.
		send_bit(pid, (c >> i) & 1);
		i++;
	}
}

// This function sends a string to the server process.
void	send_string(int pid, const char *str)
{
	// Send each character in the string one by one.
	while (*str)
		send_char(pid, *str++);
	// Send a null character to indicate the end of the string.
	send_char(pid, '\0');
}

int	main(int argc, char **argv)
{
	int	pid;

	// Check if the correct number of arguments have been provided.
	if (argc != 3)
		exit(printf("Usage: ./client [PID] [string]\n"));
		
	// Convert the second argument to an integer and store it in 'pid'.
	pid = atoi(argv[1]);

	// Check if 'pid' is a valid PID.
	if (pid <= 0)
		exit(printf("Invalid PID: %s\n", argv[1]));

	// Check if the third argument is a non-empty string.
	if (!argv[2])
		exit(printf("Empty string\n"));

	// Print the PID of the client process.
	printf("CLIENT PID: %d\n", getpid());
	 
	// Send the string to the server process.
	send_string(pid, argv[2]);
	return (0);
}
