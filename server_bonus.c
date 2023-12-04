#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>

void	handle_signal(int signum, siginfo_t *siginfo, void *context)
{
	static char	character;
	static int	bit_count;

	(void)context;
	character = character << 1;
	if (signum == SIGUSR1)
		character = character | 1;
	bit_count++;
	if (bit_count == 8)
	{
		write(1, &character, 1);
		bit_count = 0;
		character = 0;
	}
	// send signal to client to indicate that the signal has been received
	kill(siginfo->si_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;
	bzero(&sa, sizeof(struct sigaction));
	sa.sa_sigaction = &handle_signal;
	sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL) == -1)
		exit(printf("Error setting up signal handler\n"));
	printf("Server PID: %d\n", getpid());
	while (1)
		pause();
	return (0);
}
