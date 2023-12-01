#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// This function is called whenever a signal is received by the server process
void	handle_signal(int signal, siginfo_t *info, void *ucontext)
{
	static int				bit_count;
	static unsigned char	character;

	(void)ucontext;
	(void)info;

	// Shift the bits of 'character' to the left by one position.
	character = character << 1;

	// If the received signal is SIGUSR1, set the least significant bit of 'character' to 1.
	if (signal == SIGUSR1)
		character = character | 1;

	// Increment the bit count.
	bit_count++;

	// If 8 bits have been received, write the character to the console, reset the bit count to 0, and reset the character to 0.
	if (bit_count == 8)
	{
		write(1, &character, 1);
		bit_count = 0;
		character = 0;
	}
	// If less than 8 bits have been received, print the bit count for debugging purposes.
	else
		printf("Received bit %d\n", bit_count);
}

int	main(void)
{
	// Define a 'sigaction' structure to specify the action to be taken when a signal is received.
	struct sigaction	sa;

	// Initialize the 'sa_mask' field of the 'sigaction' structure to an empty set of signals.
	sigemptyset(&sa.sa_mask);

	// Set the 'sa_flags' field of the 'sigaction' structure to SA_SIGINFO | SA_RESTART.
	// SA_SIGINFO means that the signal handler will be called with three arguments,
	// and SA_RESTART means that if a system call is interrupted by a signal, it will be restarted.
	sa.sa_flags = SA_SIGINFO | SA_RESTART;

	// Set the 'sa_sigaction' field of the 'sigaction' structure to the address of the signal handler function.
	sa.sa_sigaction = &handle_signal;

	// Install the signal handler for SIGUSR1 and SIGUSR2.
	if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL) == -1)
		exit(printf("Error setting up signal handler\n"));

	// Print the PID of the server process.
	printf("Server PID: %d\n", getpid());

	// Wait for signals to be received.
	while (1)
		pause();
	return (0);
}

// for bonus
// if (signal == SIGUSR1)
// 	kill(info->si_pid, SIGUSR1);
// else if (signal == SIGUSR2)
// 	kill(info->si_pid, SIGUSR2);

/*  Notes about the signal.h library:
sigemptyset(&sa.sa_mask) -> Change the default behavior of SIGUSR1 and SIGUSR2 signals.
	Instead of their default behavior, which might terminate the program or interrupt its execution, it specifies a custom action to be taken when these signals are received. 

The sigaction structure is defined as something like:

    struct sigaction {
        void     (*sa_handler)(int);
        void     (*sa_sigaction)(int, siginfo_t *, void *);
        sigset_t   sa_mask;
        int        sa_flags;
        void     (*sa_restorer)(void);
    };

	* sa_handler specifies the action to be associated with signum;
	* sa_restorer field is not intended for application use;
	* sa_mask specifies a mask of signals which should be blocked;
	* sa_flags specifies a set of flags which modify the behavior of the signal
	* sa_sigaction specifies the signal-handling function for signum

SA_SIGINFO is a flag that indicates that the signal handler function (sa_sigaction) should be used instead of the more basic signal handler (sa_handler).

When the SA_SIGINFO flag is specified in act.sa_flags, the signal handler address is passed via the act.sa_sigaction field.  
		
	void handler(int sig, siginfo_t *info, void *ucontext)
    sig -> the number of the signal that caused invocation of the handler
	info ->  a pointer to a siginfo_t, which is a structure containing further information about the signal
	ucontext -> the structure pointed to by this field contains signal context information that was saved on the user-space stack by the kernel. 
*/