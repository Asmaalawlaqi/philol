/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walhamad <walhamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:14:58 by walhamad          #+#    #+#             */
/*   Updated: 2024/09/04 18:14:59 by walhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
   This function checks if a given name matches a wildcard pattern.

   - Parameters:
     - `wildcard`: The wildcard pattern to match against.
     - `name`: The name to be checked for matching.

   - How It Works:
     - Loops through the wildcard pattern.
     - Extracts the pattern length at each position.
     - Uses `name_pattern_match()` to check if the current segment of 
       the name matches the pattern.
     - Returns `1` if the name matches the wildcard pattern; otherwise, 
       returns `0`.

   - Data Types:
     - Output:
       - `int` (1 if the name matches the pattern, otherwise 0).
*/
int	pattern_match(char *wildcard, char *name)
{
	int	pattern_len;
	int	wc_len;
	int	i;
	int	match_index;

	i = -1;
	wc_len = ft_strlen(wildcard);
	while (++i < wc_len)
	{
		pattern_len = get_pattern_len(wildcard + i);
		if (pattern_len == 0)
			continue ;
		match_index = name_pattern_match(wildcard + i, name, pattern_len);
		if (match_index == -1 || (i == 0 && match_index != 0))
			return (0);
		i += pattern_len;
		name += match_index + pattern_len;
	}
	return (1);
}

/*
   Here's the function that retrieves and returns a list of filenames 
   in the current working directory.

   - How It Works:
     - Opens the current directory using `opendir()`.
     - Reads directory entries using `readdir()` in a loop.
     - Adds each non-hidden file (not starting with '.') to a linked list.
     - Closes the directory using `closedir()`.
     - Sorts the list of filenames using `sort_names_list()`.
     - Returns the sorted list of filenames.

   - Data Types:
     - Output:
       - `t_list *` (a linked list of filenames in the current directory, 
         or `NULL` if the directory cannot be opened).
*/
t_list	*get_cwd_names(void)
{
	DIR				*dir;
	t_list			*names;
	struct dirent	*dir_info;

	names = NULL;
	dir = opendir(".");
	if (dir == NULL)
		return (NULL);
	dir_info = readdir(dir);
	while (dir_info != NULL)
	{
		if (dir_info->d_name[0] != '.')
			ft_lstadd_back(&names, ft_lstnew(ft_strdup(dir_info->d_name)));
		dir_info = readdir(dir);
	}
	closedir(dir);
	sort_names_list(&names);
	return (names);
}

/*
   Here's the function that expands a wildcard pattern into matching names.

   - How It Works:
     - Initializes `expanded` to `NULL`.
     - Iterates over each name in the `names` list.
     - Checks if the current name matches the wildcard pattern using 
       `pattern_match()`.
     - Concatenates matching names to `expanded` with spaces using 
       `ft_strjoin_free()`.
     - Returns the concatenated string of matched names.

   - Data Types:
     - Input:
       - `t_mini *mini` (context, not used in the function).
       - `t_list *names` (list of names to match against the wildcard).
       - `char *wildcard` (wildcard pattern to match).
     - Output:
       - `char *` (concatenated string of matched names, 
        or `NULL` if no matches).
*/
char	*get_wildcard_expanded(t_mini *mini, t_list *names, char *wildcard)
{
	char	*expanded;

	(void)mini;
	expanded = NULL;
	while (names != NULL)
	{
		if (pattern_match(wildcard, (char *)names->content))
		{
			expanded = ft_strjoin_free(expanded, " ");
			expanded = ft_strjoin_free(expanded, (char *)names->content);
		}
		names = names->next;
	}
	return (expanded);
}

/*
   Here's the function that handles wildcard expansion in a string.

   - How It Works:
     - Retrieves a list of current working directory names using 
       `get_cwd_names()`.
     - Expands the wildcard token using `get_wildcard_expanded()`.
     - Clears the list of names using `ft_lstclear()`.
     - If wildcard expansion is successful, replaces the original token 
       in the input string with the expanded value.
     - Updates the token with the expanded string and frees the old token.

   - Data Types:
     - Input: 
       - `t_mini *mini` (context for wildcard expansion).
       - `char **pinput` (pointer to the input string).
       - `char **ptoken` (pointer to the token to be expanded).
       - `int i` (start index for the expansion).
     - Output: 
       - Returns `1` if expansion was successful, `0` otherwise.
*/
int	wildcard(t_mini *mini, char **pinput, char **ptoken, int i)
{
	char	*expanded;
	t_list	*names;

	names = get_cwd_names();
	expanded = get_wildcard_expanded(mini, names, *ptoken);
	ft_lstclear(&names, free);
	if (expanded == NULL)
		return (0);
	ft_strexpand(pinput, expanded, i, ft_strlen(*ptoken));
	free(*ptoken);
	*ptoken = expanded;
	return (1);
}
