/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iofile_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walhamad <walhamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:14:06 by walhamad          #+#    #+#             */
/*   Updated: 2024/09/04 18:14:07 by walhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
   Heres the functions that handle setting input and output files for commands.

   get_infile:
   - Set the infile for the command:
     Assign the next argument (after the redirection symbol) as the input file 
     for the command.

   get_outfile:
   - Set the outfile for the command:
     Assign the next argument (after the redirection symbol) as the output file 
     for the command.
*/
static void	get_infile(t_mini *mini, t_cmdblock *cmdblock, int i)
{
	(void)mini;
	cmdblock->infile = cmdblock->cmd_argv[i + 1];
}

static void	get_outfile(t_mini *mini, t_cmdblock *cmdblock, int i)
{
	(void)mini;
	cmdblock->outfile = cmdblock->cmd_argv[i + 1];
}

/*
   Heres the function that handles getting the input/output files for a command.

   - Check if theres a file after the redirection symbol:
     If theres no file after the symbol (like >, >>, <, <<), return an error.

   - Handle input file or heredoc:
     If the current argument is an input redirection or heredoc, process the 
     input file using get_infile.

   - Handle output file or append mode:
     If the current argument is an output redirection or append mode, process 
     the output file using get_outfile.

   - Return success:
     After handling the input/output files, return a success code.
*/
int	get_iofile(t_mini *mini, t_cmdblock *cmdblock, int i)
{
	if (cmdblock->cmd_argv[i + 1] == NULL)
		return (ERROR);
	if ((ft_strcmp(cmdblock->cmd_argv[i], S_IN) == 0)
		|| (ft_strcmp(cmdblock->cmd_argv[i], S_HEREDOC) == 0))
	{
		get_infile(mini, cmdblock, i);
	}
	if ((ft_strcmp(cmdblock->cmd_argv[i], S_OUT) == 0)
		|| (ft_strcmp(cmdblock->cmd_argv[i], S_APPEND) == 0))
	{
		get_outfile(mini, cmdblock, i);
	}
	return (SUCCESS);
}
