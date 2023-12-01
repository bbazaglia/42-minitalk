#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void	handle_signal(int signum)
{
	static char	character = 0;
	static int	bit_count = 0;
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
}

int	main(void)
{
	struct sigaction	sa;

	sa.sa_handler = &handle_signal;
	sa.sa_flags = SA_RESTART; // restart functions if interrupted by handler
	if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGUSR2, &sa, NULL) == -1)
		exit(printf("Error setting up signal handler\n"));
	printf("Server PID: %d\n", getpid());
	while (1)
		pause();
	return (0);
}

/* Overview of signals:

Signals are a form of inter-process communication in Unix-like operating systems. 
They are used to notify a process that a particular event (e.g. user input) has occurred.

There are two primary ways to handle signals: 
(1) the signal() function is a simpler method for setting the disposition of a signal.
(2) the sigaction() functions provides more flexibility and is more portable.
	The sigaction() function allows you to specify a signal handler, which is a function that will be called when the signal is received. 
	It also allows you to specify additional arguments for the signal handler, which is not possible with signal(). 
	This function also allows you to specify a set of signals to be blocked while the handler runs, and various flags that can affect the behavior of the signal.

A process can change the disposition of a signal using sigaction or signal.  
	Using these system calls, a process can elect one of the following behaviors to occur on delivery of the signal: 
		(1) perform the default action; 
		(2) ignore the signal; 
		(3) catch the signal with a signal handler, a programmer-defined function that is automatically invoked when the signal is delivered.

The kill() function allow the caller to send a signal.

The pause() function suspends the calling process until a signal is received.

About the RESTART flag: By default, when a system call is interrupted by a signal handler, the system call will fail with the error EINTR. 
However, if the SA_RESTART flag is set when establishing the signal handler with sigaction(), the system call will be automatically restarted after the signal handler returns. 
This means that the system call will continue from where it was interrupted, without having to be manually restarted by the program.

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
*/