#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>

int		g_bit_received;

void	send_bit(int pid, int bit)
{
	int	signal;

	if (bit == 1)
		signal = SIGUSR1;
	else
		signal = SIGUSR2;
	if (kill(pid, signal) == -1)
		exit(printf("Error sending signal\n"));
}

void	send_char(int pid, unsigned char c)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		g_bit_received = 0;
		send_bit(pid, (c >> i) & 1);
		i--;
		// wait for the signal handler to receive the signal
		while (!g_bit_received)
			;
	}
}

void	send_string(int pid, const char *str)
{
	while (*str)
		send_char(pid, *str++);
	send_char(pid, '\0');
}

void	receive_signal(int signum)
{
	if (signum == SIGUSR1)
		g_bit_received = 1;
}

int	main(int argc, char **argv)
{
	struct sigaction	sig;
	int					pid;

	if (argc != 3)
		exit(printf("Usage: ./client [PID] [string]\n"));
	pid = atoi(argv[1]);
	if (pid <= 0)
		exit(printf("Invalid PID: %s\n", argv[1]));
	bzero(&sig, sizeof(struct sigaction));
	sig.sa_handler = &receive_signal;
	if (sigaction(SIGUSR1, &sig, NULL) == -1)
		exit(printf("Error setting up signal handler\n"));
	send_string(pid, argv[2]);
	send_string(pid, "\n");
	return (0);
}
