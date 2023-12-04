#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void	send_bit(int pid, int bit)
{
	int	signal;
	if (bit == 1)
		signal = SIGUSR1;
	else
		signal = SIGUSR2;
	if (kill(pid, signal) == -1)
	{
		perror("Error\n");
		exit(1);
	}
}

void	send_char(int pid, unsigned char c)
{
	int	i = 7;
	while (i >= 0)
	{
		send_bit(pid, (c >> i) & 1);
		usleep(500);
		i--;
	}
}

void	send_string(int pid, const char *str)
{
	while (*str)
		send_char(pid, *str++);
	send_char(pid, '\0');
}

int	main(int argc, char **argv)
{
	if (argc != 3)
		exit(printf("Usage: ./client [PID] [string]\n"));
	int pid = atoi(argv[1]);
	if (pid <= 0)
		exit(printf("Invalid PID: %s\n", argv[1]));
	send_string(pid, argv[2]);
	return (0);
}