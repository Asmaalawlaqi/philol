/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walhamad <walhamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:14:38 by walhamad          #+#    #+#             */
/*   Updated: 2024/09/04 18:14:39 by walhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
   Here's the function that skips past a splitter in the input string.

   - How It Works:
     - Checks the `spliter_type` to determine how many characters to 
       skip.
     - For `PIPE`, it skips 1 character.
     - For `AND` and `OR`, it skips 2 characters.
     - Returns the pointer to the new position in the input string after 
       skipping.

   - Data Types:
     - Input: `char *input` (the input string), `int spliter_type` (type 
       of splitter).
     - Output: `char *` (pointer to the new position in the input string).
*/
char	*skip_spliter(char *input, int spliter_type)
{
	if (spliter_type == 0)
		return (input);
	else if (spliter_type == PIPE)
		return (input + 1);
	else if (spliter_type >= AND && spliter_type <= OR)
		return (input + 2);
	return (input);
}

/*
   Here's the function that calculates the length of a command block 
   in the input string.

   - How It Works:
     - Iterates through the `input` string while keeping track of 
       quotes and special characters.
     - If a split type or '&' character is encountered outside of quotes, 
       the loop breaks.
     - Updates the length based on the presence of quotes and special 
       characters.
     - Returns the length of the command block.

   - Data Types:
     - Input: `char *input` (the input string to analyze).
     - Output: `int` (the length of the command block).
*/
int	calculate_cmdblock_length(char *input)
{
	int	quote;
	int	len;

	quote = 0;
	len = 0;
	while (input[len] != 0)
	{
		if (quote == 0 && (get_spliter_type(input + len) != INVALID
				|| input[len] == '&'))
			break ;
		if (quote != 0 && input[len] == quote)
			quote = 0;
		else if (quote == 0 && (input[len] == '\"' || input[len] == '\''))
			quote = input[len];
		len++;
	}
	return (len);
}

/*
   Here's the function that processes segments of input for quotes 
   and bracket levels.

   - How It Works:
     - Checks for quotes to start or end quoting based on the current 
       character.
     - Updates the `quote` variable when encountering the start or end 
       of quotes.
     - Adjusts the `bracket_level` when encountering opening or closing 
       parentheses.
     - Increments the index `i` to move through the input string.

   - Data Types:
     - Input: `char **input` (pointer to the input string), `int *i` 
       (current index), `int *quote` (current quote character), `int 
       *bracket_level` (current bracket nesting level).
     - Output: None (modifies the `i`, `quote`, and `bracket_level` 
       variables in place).
*/
void	process_input_segment(char **input, int *i,
	int *quote, int *bracket_level)
{
	if (*quote == 0 && ((*input)[*i] == '\'' || (*input)[*i] == '"'))
		*quote = (*input)[*i];
	else if (*quote && (*input)[*i] == *quote)
	{
		*quote = 0;
		(*i)++;
		return ;
	}
	if ((*input)[*i] == '(' && *quote == 0)
		(*bracket_level)++;
	else if ((*input)[*i] == ')' && *quote == 0)
		(*bracket_level)--;
	(*i)++;
}
