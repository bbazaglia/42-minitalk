/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:13:52 by bbazagli          #+#    #+#             */
/*   Updated: 2023/12/12 15:21:35 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handle_client_signal(int signum, siginfo_t *siginfo, void *context)
{
	static char	character;
	static int	bit_count;

	(void)context;
	if (signum == SIGUSR1)
		character = character | 1;
	bit_count++;
	if (bit_count == 8)
	{
		write(1, &character, 1);
		bit_count = 0;
		character = 0;
	}
	character = character << 1;
	if (kill(siginfo->si_pid, SIGUSR1) == -1)
		exit(ft_printf("Error sending signal\n"));
}

int	main(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(struct sigaction));
	sa.sa_sigaction = &handle_client_signal;
	sa.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sa, NULL) == -1 \
	|| sigaction(SIGUSR2, &sa, NULL) == -1)
		exit(ft_printf("Error setting up signal handler\n"));
	ft_printf("Server PID: %d\n", getpid());
	while (1)
		pause();
	return (0);
}
