/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbazagli <bbazagli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:49:18 by bbazagli          #+#    #+#             */
/*   Updated: 2023/12/13 13:44:34 by bbazagli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int		g_bit_received;

void	send_bit(int pid, int bit)
{
	int	signal;

	if (bit == 1)
		signal = SIGUSR1;
	else
		signal = SIGUSR2;
	if (kill(pid, signal) == -1)
		exit(ft_printf("Error sending signal\n"));
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

void	handle_server_signal(int signum)
{
	if (signum == SIGUSR1)
		g_bit_received = 1;
}

int	main(int argc, char **argv)
{
	struct sigaction	sig;
	int					server_pid;

	if (argc != 3)
		exit(ft_printf("Correct usage: ./client [server's PID] [string]\n"));
	server_pid = ft_atoi(argv[1]);
	if (kill(server_pid, 0) == -1 || server_pid == 0)
		exit(ft_printf("Invalid PID: %s\n", argv[1]));
	ft_bzero(&sig, sizeof(struct sigaction));
	sig.sa_handler = &handle_server_signal;
	if (sigaction(SIGUSR1, &sig, NULL) == -1)
		exit(ft_printf("Error setting up signal handler\n"));
	send_string(server_pid, argv[2]);
	send_string(server_pid, "\n");
	return (0);
}
