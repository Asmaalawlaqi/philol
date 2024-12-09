/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walhamad <walhamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:14:53 by walhamad          #+#    #+#             */
/*   Updated: 2024/09/04 18:14:54 by walhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
   Here's the function that waits for all child processes associated
   with command blocks and updates their exit statuses.

   - How It Works:
     - Iterates through the list of command blocks (`cmdblocks`).
     - For each command block, if `need_wait` is true, it waits for 
       the child process using `waitpid`.
     - Updates the `exit_status` of each command block based on the
       status returned by `waitpid`.
     - If the process terminated normally, sets `exit_status` to the
       exit status code.
     - If the process was terminated by a signal, sets `exit_status` 
       to the signal number plus 128.

   - Data Types:
     - Input: 
       - `t_list *cmdblocks` (list of command blocks, each containing 
         a child process to wait for).
     - Output: 
       - None (modifies the `exit_status` field of the command blocks).
*/
void	wait_childs(t_list *cmdblocks)
{
	t_cmdblock	*curr;

	while (cmdblocks != NULL)
	{
		curr = (t_cmdblock *)cmdblocks->content;
		if (curr->need_wait)
		{
			waitpid(curr->pid, &curr->estatus, WUNTRACED);
			if (WIFEXITED((curr->estatus)))
				curr->exit_status = WEXITSTATUS((curr->estatus));
			if (WIFSIGNALED(curr->estatus))
				curr->exit_status = WTERMSIG(curr->estatus) + 128;
		}
		cmdblocks = cmdblocks->next;
	}
}

/*
   Here's the function that opens a file with the specified flags and mode,
   and handles errors by reporting them and setting a global error number.

   - How It Works:
     - Calls `open` to open the file specified by `filename` with the given
       `flags` and `mode`.
     - If `open` fails (returns -1), reports an error using `cmd_error`, 
       sets a global error number `g_errno` to 1, and returns -1.
     - If successful, returns the file descriptor obtained from `open`.

   - Data Types:
     - Input:
       - `t_mini *mini` (pointer to the mini shell structure).
       - `char *filename` (name of the file to open).
       - `int flags` (flags for file access mode).
       - `int mode` (permissions mode for the file).
     - Output: 
       - `int` (file descriptor on success or -1 on failure).
*/
int	ms_open(t_mini *mini, char *filename, int flags, int mode)
{
	int	fd;

	fd = open(filename, flags, mode);
	if (fd == -1)
	{
		cmd_error(mini, &filename, NSFD);
		g_errno = 1;
		return (-1);
	}
	return (fd);
}

/*
   Here's the function that duplicates a file descriptor to a specified 
   standard file descriptor and closes the original file descriptor.

   - How It Works:
     - Uses `dup2` to duplicate the file descriptor `fd` to `std_file_no`.
       This makes `std_file_no` refer to the same file or device as `fd`.
     - Closes the original file descriptor `fd`.

   - Data Types:
     - Input: 
       - `int fd` (file descriptor to be duplicated).
       - `int std_file_no` (standard file descriptor to replace with `fd`).
*/
void	handle_io(int fd, int std_file_no)
{
	dup2(fd, std_file_no);
	close(fd);
}

/*
   Here's the function that inserts one 2D array into another at a 
   specified index and returns the updated 2D array.

   - How It Works:
     - Checks if the `insert` array contains only one element.
       If so, it frees the `insert` array and returns the original `arr`.
     - Allocates memory for a new 2D array that is the sum of the lengths 
       of `arr` and `insert`.
     - Copies elements from `arr` to the new array up to the given index.
     - Inserts elements from `insert` into the new array starting at the 
       specified index.
     - Frees the old arrays (`arr` and `insert`) and updates the index.
     - Returns the new 2D array.

   - Data Types:
     - Input: 
       - `char **insert` (array to be inserted).
       - `char **arr` (original array to be updated).
       - `int *index` (position in `arr` where `insert` will be placed).
     - Output: `char **` (new 2D array with `insert` inserted at `index`).
*/
char	**insert_arr_to_2darr(char **insert, char **arr, int *index)
{
	char	**new;
	int		i;

	if (ft_2darrlen((void *)insert) == 1)
	{
		ft_free2darr((void **)insert);
		return (arr);
	}
	new = malloc(sizeof(char *)
			* (ft_2darrlen((void **)arr) + ft_2darrlen((void **)insert)));
	i = -1;
	while (++i < *index)
		new[i] = arr[i];
	i--;
	while (++i < *index + ft_2darrlen((void **)insert))
		new[i] = insert[i - *index];
	new[i] = NULL;
	free(arr[*index]);
	*index += ft_2darrlen((void **)insert) - 1;
	free(insert);
	free(arr);
	return (new);
}

/*
   Here's the function that determines the exit status based on a list 
   of command blocks and their exit statuses.

   - How It Works:
     - Iterates through the list of command blocks.
     - Checks the type of each command block (AND, OR).
     - For `OR` type, if any command block has a status of 0, the 
       function returns 0 immediately.
     - For `AND` type, updates the exit status based on the command 
       block statuses.
     - Returns the exit status of the last processed command block.

   - Data Types:
     - Input: `t_list *cmdblock_list` (list of command blocks).
     - Output: `int` (exit status of the last command block based on 
       logical conditions).
*/
int	get_exit_status(t_list *cmdblock_list)
{
	t_cmdblock	*cmdblock;
	int			exit_status;

	exit_status = 0;
	while (cmdblock_list != NULL)
	{
		cmdblock = (t_cmdblock *)cmdblock_list->content;
		if (cmdblock->spliter_type == OR && cmdblock->exit_status == 0)
			return (0);
		else if (cmdblock->spliter_type == AND)
		{
			if ((cmdblock->exit_status == 0 && exit_status == 0)
				|| (cmdblock->exit_status != 0))
				exit_status = cmdblock->exit_status;
		}
		else
			exit_status = cmdblock->exit_status;
		cmdblock_list = cmdblock_list->next;
	}
	return (exit_status);
}
