/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walhamad <walhamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:14:35 by walhamad          #+#    #+#             */
/*   Updated: 2024/09/04 18:14:36 by walhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
   Here's the function that handles command blocks enclosed in brackets.

   - How It Works:
     - Calls `handle_cmdblocks` to process the list of command blocks 
       and get the status.
     - Frees the memory allocated for the list of command blocks using 
       `ft_lstclear` and the `free_cmdblock` function.
     - Returns the status from `handle_cmdblocks`.

   - Data Types:
     - Input: `t_mini *mini` (mini environment structure), `t_list 
       *cmdblocks_list` (list of command blocks).
     - Output: `int` (status of the command block handling).
*/
int	handle_bracket_cmdblock(t_mini *mini, t_list *cmdblocks_list)
{
	int	status;

	status = handle_cmdblocks(mini, cmdblocks_list);
	ft_lstclear(&cmdblocks_list, free_cmdblock);
	return (status);
}

/*
   Here's the function that handles the execution of a command block by 
   processing the command input, expanding variables, and managing 
   execution status.

   - How It Works:
     - Checks if the command block is within brackets; if so, it 
       handles bracketed command blocks by splitting and processing 
       them separately.
     - Tokenizes the command input into arguments.
     - Iterates through the arguments to expand variables if needed, 
       updating the arguments array with expanded values.
     - Executes the command using the `executor` function and stores the 
       exit status.
     - Finalizes redirection handling, updates the global error number, 
       and frees allocated memory for arguments.
     - Resets redirection flags and returns the exit status of the command 
       block.

   - Data Types:
     - Input: `t_mini *mini` (mini environment structure), `t_cmdblock 
       *cmdblock` (command block to be handled).
     - Output: `int` (exit status of the command block).
*/
int	handle_cmdblock(t_mini *mini, t_cmdblock *cmdblock)
{
	int	i;

	if (cmdblock->in_bracket)
		return (handle_bracket_cmdblock(mini,
				split_cmdblocks(cmdblock->input, 1)));
	cmdblock->cmd_argv = tokenize_cmd(mini, cmdblock->input);
	i = -1;
	while (cmdblock->cmd_argv[++i] != NULL)
	{
		if (expand_input(mini, &cmdblock->cmd_argv[i]) != 0)
			cmdblock->cmd_argv = insert_arr_to_2darr(
					tokenize_cmd(mini, cmdblock->cmd_argv[i]),
					cmdblock->cmd_argv, &i);
	}
	cmdblock->exit_status = executor(mini, cmdblock);
	done_redir(mini, 0);
	g_errno = cmdblock->exit_status;
	ft_free2darr((void **)cmdblock->cmd_argv);
	mini->pipes.is_redir_in = 0;
	return (cmdblock->exit_status);
}

/*
   Here's the function that processes a list of command blocks by 
   handling pipes, executing commands, and managing command 
   execution based on previous command statuses.

   - How It Works:
     - Initializes pointers for iterating through the command blocks 
       and tracking the previous command block.
     - Checks for syntax errors in the command blocks list; if errors 
       are found, returns `258`.
     - Iterates through the command blocks list and prepares for pipe 
       handling.
     - Determines if the current command block should be executed based 
       on the previous command block's exit status.
     - If needed, handles pipes and finishes pipe setup.
     - Updates the previous command block pointer and moves to the next 
       command block in the list.
     - Waits for all child processes to complete and returns the exit 
       status of the command blocks list.

   - Data Types:
     - Input: `t_mini *mini` (mini environment structure), `t_list 
       *cmdblocks_list` (list of command blocks).
     - Output: `int` (exit status of the command blocks list).
*/
int	handle_cmdblocks(t_mini *mini, t_list *cmdblocks_list)
{
	t_list		*temp;
	t_cmdblock	*prev_cmdblock;
	t_cmdblock	*cmdblock;

	temp = cmdblocks_list;
	prev_cmdblock = NULL;
	if (check_syntax(mini, cmdblocks_list) == 0)
		return (258);
	while (temp != NULL)
	{
		cmdblock = (t_cmdblock *)temp->content;
		prepare_handling(mini, temp, cmdblock);
		if (should_execute(prev_cmdblock, cmdblock))
			cmdblock->exit_status = handle_cmdblock(mini, cmdblock);
		else
			cmdblock->exit_status = 0;
		if (mini->pipes.do_pipe || mini->pipes.prep_pipe)
			finish_pipe(mini);
		prev_cmdblock = cmdblock;
		temp = temp->next;
	}
	wait_childs(cmdblocks_list);
	return (get_exit_status(cmdblocks_list));
}

/*
   Here's the function that prepares the environment for handling 
   pipes and manages pipe flags based on the command block splitter 
   types.

   - How It Works:
     - Checks if there is a next command block in the list (`curr_node`).
     - If a next command block exists and its splitter type is `PIPE`, 
       sets `mini->pipes.prep_pipe` to 1.
     - If the current command block's splitter type is `PIPE`, sets 
       `mini->pipes.do_pipe` to 1.
     - If `mini->pipes.prep_pipe` is set, calls `prepare_pipe` to 
       set up the pipe.

   - Data Types:
     - Input: `t_mini *mini` (mini environment structure), `t_list 
       *curr_node` (current node in the list), `t_cmdblock *cmdblock` 
       (current command block).
     - Output: None (void function).
*/
void	prepare_handling(t_mini *mini, t_list *curr_node, t_cmdblock *cmdblock)
{
	t_cmdblock	*next_cmdblock;

	next_cmdblock = NULL;
	if (curr_node->next != NULL)
		next_cmdblock = (t_cmdblock *)curr_node->next->content;
	if (cmdblock->spliter_type == PIPE)
		mini->pipes.do_pipe = 1;
	if (next_cmdblock != NULL && next_cmdblock->spliter_type == PIPE)
		mini->pipes.prep_pipe = 1;
	if (mini->pipes.prep_pipe)
		prepare_pipe(mini);
}

/*
   Here's the function that determines if the current command block 
   should be executed based on the exit status of the previous command 
   block and the logical operators.

   - How It Works:
     - Checks if there is a previous command block (`prev_cmdblock`).
     - If the current command block's splitter type is `AND` and the 
       previous command block's exit status is non-zero, returns 0 
       (indicating no execution).
     - If the splitter type is `OR` and the previous command block's 
       exit status is zero, also returns 0 (indicating no execution).
     - In other cases, returns 1 (indicating execution).

   - Data Types:
     - Input: `t_cmdblock *prev_cmdblock` (previous command block), 
       `t_cmdblock *cmdblock` (current command block).
     - Output: Returns an integer (0 for no execution, 1 for execution).
*/
int	should_execute(t_cmdblock *prev_cmdblock, t_cmdblock *cmdblock)
{
	if (prev_cmdblock != NULL)
	{
		if (cmdblock->spliter_type == AND && prev_cmdblock->exit_status != 0)
			return (0);
		else if (cmdblock->spliter_type == OR
			&& prev_cmdblock->exit_status == 0)
			return (0);
	}
	return (1);
}
