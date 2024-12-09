/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walhamad <walhamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:13:20 by walhamad          #+#    #+#             */
/*   Updated: 2024/09/04 18:13:21 by walhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
   Heres the function that is gonna handle getting input
   from the user and process it. Lets break it down:

   - We check if a command has been executed before using 
     `commanded`. If yes or no, we set up the prompt with 
     the same value.
   - We then use `readline` to get the user's input and 
     store it in `mini->input`. If the input is NULL, we 
     call `ms_exit` to exit the shell.
   - Next, we trim any extra whitespace from the input 
     using `trim_input`.
   - If the input is empty after trimming, we free up 
     resources using `ms_free` and set `commanded` to 0, 
     signaling no command was entered.
   - If the input is not empty, we set `commanded` to 1, 
     indicating that a command was entered.
   - Finally, we return 1 to show that a valid command was 
     received and processed.

   Functions used:
   - `readline`: Grabs the user input from the command line.
   - `ms_exit`: Exits the shell if something went wrong.
   - `trim_input`: Trims any leading/trailing spaces from 
     the input.
   - `ms_free`: Frees up memory allocated to `mini` to 
     avoid leaks.
*/
int	get_input(t_mini *mini, int *commanded)
{
	const char	*prompt;

	if (*commanded || !*commanded)
		prompt = PROMPT;
	mini->input = readline(prompt);
	if (mini->input == NULL)
		ms_exit(mini, NULL);
	mini->input = trim_input(mini->input);
	if (mini->input[0] == '\0')
	{
		ms_free(mini);
		*commanded = 0;
		return (0);
	}
	*commanded = 1;
	return (1);
}

static void	print_banner(void)
{
	printf(BGREEN);
	printf("=============================================================\n");
	printf("|   __   __ _ __    _ _   _____ __  __ .____  .     .        \n");
	printf("|   |    |  | |\\   |  |  (      |   |  /      /     /       \n");
	printf("|   |\\  /|  | | \\  |  |   `--.  |___|  |__.   |     |      \n");
	printf("|   | \\/ |  | |  \\ |  |      |  |   |  |      |     |      \n");
	printf("|   /    /  / |   \\|  / \\___.'  /   /  /----/ /---/ /---/  \n");
	printf("|                           _  _ ___  _ _                    \n");
	printf("|                          | || |__  \\| (_)                 \n");
	printf("|   ___ _ __ _ __ ___  _ __| || |__ ) | |_ _ __   ___        \n");
	printf("|  / _ \\ '__| '__/ _ \\| '__|__    _/ /| | | '_ \\ / _ \\   \n");
	printf("|  |  __/ |  | | | (_) | |     | |/ /_| | | | | |  __/       \n");
	printf("|   \\___|_|  |_|__\\___/|_|_    |_|____|_|_|_| |_|\\___|    \n");
	printf("|      |__   __|  ____|   /\\   |  \\/  |                    \n");
	printf("|         | |  | |__     /  \\  | \\  / |                    \n");
	printf("|         | |  |  __|   / /\\ \\ | |\\/| |                   \n");
	printf("|         | |  | |____ / ____ \\| |  | |                     \n");
	printf("|         |_|  |______/_/    \\_\\_|  |_|                    \n");
	printf("=============================================================\n");
	printf(RESET);
}

/*\ 
 * Lets get things going by working with the linked list and 
 * making sure the input values are good. We need a function to 
 * get the shell ready to roll. The main idea here is to set up 
 * the shell's environment and then jump into an endless loop.
 * 
 * Every time through the loop, we grab some input from the user, 
 * break it down into command blocks, and run those commands. After 
 * each run, we will save the input in the history and clean up 
 * the memory to keep the shell running smooth for the next round.
 * 
 * Functions We are Using:
 *   - print_banner(): Just shows the startup banner when the shell 
 *     kicks off.
 *   - ms_init(&mini, envp): Sets up the shell's internal structure 
 *     using the environment stuff.
 *   - ms_loop_init(&mini): Preps signals, the prompt, and pipes each 
 *     time we go through the loop.
 *   - get_input(&mini, &commanded): Grabs what the user types and 
 *     gets it ready to process.
 *   - split_cmdblocks(mini.input, 0): Breaks the input into chunks 
 *     (command blocks) we can work with.
 *   - handle_cmdblocks(&mini, mini.cmdblock_list): Runs the commands 
 *     we just split up.
 *   - add_history(mini.input): Sticks the user's input into the 
 *     shell’s history.
 *   - ms_free(&mini): Cleans up any memory we used in this loop to 
 *     keep things tidy.
 * 
 * Inputs:
 *   ac - Number of arguments (we do not really use this here)
 *   av - Argument values (again, not used here)
 *   envp - The environment variables we need to kick things off
 * 
 * Outputs:
 *   Returns 0 when we are all done and the shell exits nicely
 */
int	main(int ac, char **av, char **envp)
{
	t_mini	mini;
	int		commanded;

	(void)ac;
	(void)av;
	commanded = 1;
	print_banner();
	ms_init(&mini, envp);
	while (1)
	{
		ms_loop_init(&mini);
		if (get_input(&mini, &commanded) == 0)
			continue ;
		mini.cmdblock_list = split_cmdblocks(mini.input, 0);
		g_errno = handle_cmdblocks(&mini, mini.cmdblock_list);
		add_history(mini.input);
		ms_free(&mini);
		commanded = 1;
	}
	return (0);
}
