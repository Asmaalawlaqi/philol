/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walhamad <walhamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:14:17 by walhamad          #+#    #+#             */
/*   Updated: 2024/09/04 18:14:18 by walhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
   Heres the functions that handle signals during shell execution.

   signal_handler_exec:
   - This function manages the SIGINT and SIGQUIT signals.
   - If SIGINT is received, it prints a newline to standard error.
   - If SIGQUIT is received, it prints "Quit: " followed by the 
     signal number and a newline to standard error.

   signal_handler:
   - This function specifically handles the SIGINT signal.
   - It prints a newline, clears the current input line using 
     rl_replace_line, and refreshes the prompt with rl_redisplay.
   - Finally, it sets the global error number g_errno to 1, 
     signaling an interruption.
*/
void	signal_handler_exec(int signo)
{
	if (signo == SIGINT)
		ft_putstr_fd("\n", STDERR_FILENO);
	else if (signo == SIGQUIT)
	{
		ft_putstr_fd("Quit: ", STDERR_FILENO);
		ft_putnbr_fd(signo, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
	}
}

void	signal_handler(int signo)
{
	if (signo != SIGINT)
		return ;
	printf ("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_errno = 1;
}

/*
   Heres the function that initializes signal handling and terminal 
   settings for the shell.

   - First, it fetches the current terminal attributes using tcgetattr.
   - Then, it modifies the terminal settings to disable ECHOCTL, 
     which prevents the shell from displaying control characters 
     like ^C when SIGINT is triggered.
   - If the settings can't be fetched or applied, it exits with an 
     error message.
   - Finally, it sets up signal handlers: SIGINT is handled by 
     signal_handler, and SIGQUIT is ignored.
*/
void	init_signal(void)
{
	struct termios	termios_current;

	if (tcgetattr(STDIN_FILENO, &termios_current) == -1)
	{
		perror("Tcgetattr failed\n");
		exit(0);
	}
	termios_current.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &termios_current) == -1)
	{
		perror("Tcsetattr failed\n");
		exit(0);
	}
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}
