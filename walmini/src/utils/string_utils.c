/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walhamad <walhamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:14:50 by walhamad          #+#    #+#             */
/*   Updated: 2024/09/04 18:14:51 by walhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
   Here's the function that performs string expansion by inserting a 
   substring into a specified position within another string.

   - How It Works:
     - Checks if the insertion parameters are valid.
     - Allocates memory for the resulting string based on the new length.
     - Copies the portion of the original string before the insertion 
       point.
     - Inserts the new substring into the specified position.
     - Copies the remaining portion of the original string after the 
       insertion point.
     - Frees the original string and updates the pointer to point to the 
       newly created string.

   - Data Types:
     - Input: 
       - `char **s` (pointer to the original string that will be modified)
       - `char *insert` (substring to insert)
       - `int start` (position in the original string where insertion starts)
       - `int n` (number of characters to replace in the original string)
     - Output: None (the original string is modified in place).
*/
void	ft_strexpand(char **s, char *insert, int start, int n)
{
	char	*result;
	int		len;
	int		insert_len;
	int		i;

	if (start > (int)ft_strlen(*s) || start < 0 || n < 0)
		return ;
	if (n > (int)ft_strlen(*s + start))
		n = ft_strlen(*s + start);
	insert_len = ft_strlen(insert);
	len = ft_strlen(*s) + insert_len - n;
	result = malloc((len + 1) * sizeof(char));
	result[len] = 0;
	i = -1;
	while (++i < start)
		result[i] = (*s)[i];
	while (++i - start - 1 < insert_len)
		result[i - 1] = insert[i - 1 - start];
	i += n;
	while (++i - 2 - n < len)
		result[i - 2 - n] = (*s)[i - 2 - insert_len];
	free(*s);
	*s = result;
}

/*
   Here's the function that sorts a linked list of names in ascending 
   order.

   - How It Works:
     - Iterates through the linked list `names`.
     - Compares adjacent nodes' contents (strings) using `ft_strcmp`.
     - Swaps the contents of nodes if they are out of order.
     - Resets to the start of the list whenever a swap occurs, ensuring 
       that all nodes are properly sorted.

   - Data Types:
     - Input: `t_list **names` (pointer to the start of the linked list 
       of names).
     - Output: None (the list is sorted in place).
*/
void	sort_names_list(t_list **names)
{
	t_list	*curr;
	void	*temp;

	curr = *names;
	while (curr->next != NULL)
	{
		if (ft_strcmp((char *)curr->content, (char *)curr->next->content) > 0)
		{
			temp = curr->content;
			curr->content = curr->next->content;
			curr->next->content = temp;
			curr = *names;
		}
		else
			curr = curr->next;
	}
}

/*
   Here's the function that calculates the length of a pattern in a 
   string up to a wildcard or the end of the string.

   - How It Works:
     - Iterates through the `str` until it encounters a '*' or end of 
       the string.
     - Returns the length of the substring up to (but not including) 
       the '*' or the entire length if no '*' is found.

   - Data Types:
     - Input: `char *str` (string containing the pattern).
     - Output: `int` (length of the pattern).
*/
int	get_pattern_len(char *str)
{
	int	len;

	len = 0;
	while (str[len] != 0 && str[len] != '*')
		len++;
	if (str[len] == 0)
		len++;
	return (len);
}

/*
   Here's the function that checks if a pattern (wildcard) matches 
   a segment of the name string and returns the start index of the 
   match.

   - How It Works:
     - Iterates through the `name` string.
     - For each position in `name`, compares the substring with the 
       `wildcard` pattern using `ft_strncmp`.
     - Returns the starting index if a match is found.
     - Returns -1 if no match is found.

   - Data Types:
     - Input: `char *wildcard` (pattern to match), `char *name` (string 
       to search in), `int pattern_len` (length of the pattern).
     - Output: `int` (starting index of the match, or -1 if no match).
*/
int	name_pattern_match(char *wildcard, char *name, int pattern_len)
{
	int	i;

	i = -1;
	while (name[++i] != 0)
	{
		if (ft_strncmp(wildcard, name + i, pattern_len) == 0)
			return (i);
	}
	return (-1);
}
