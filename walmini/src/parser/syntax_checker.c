/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walhamad <walhamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:13:59 by walhamad          #+#    #+#             */
/*   Updated: 2024/09/04 18:14:00 by walhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
   Heres the function that finds the unexpected token in the input
   string during parsing.

   - Check for immediate closing parenthesis:
     If the input starts with `)`, return it as the unexpected token.

   - Skip the first character:
     Move the input pointer to the next character.

   - Skip any leading spaces:
     Continue moving the input pointer until non-space character is found.

   - Find the unexpected token:
     Loop through the characters to find the next space, `(`, or `)` 
     which will indicate the end of the token.

   - Handle special case:
     If no valid token is found, return "newline" to indicate 
     a missing command or argument.

   - Return the token:
     Return the found token or "newline" as a newly allocated string.
*/
static char	*find_unexpected_token(char *input)
{
	int	i;

	if (input[0] == ')')
		return (ft_strdup(")"));
	input++;
	while (*input == ' ')
		input++;
	i = -1;
	while (input[++i] != 0)
	{
		if (input[i] == ' ' || input[i] == '(' || input[i] == ')')
			break ;
	}
	if (i == 0)
		return (ft_strdup("newline"));
	return (ft_strndup(input, i));
}

/*
   Heres the function that finds out how long a quoted token is 
   inside the input string.

   - Initialize index `i`:
     Start with `i` at 0, which will track how far we go in the string.

   - Loop through the input:
     Start looping from the next character to find the closing quote.

   - Check for the closing quote:
     If the current character matches the opening `quote`, stop 
     the loop. 

   - Return the distance:
     Return the number of characters traversed, which is the 
     length of the quoted token.
*/
int	detect_quote_token(char *input, int quote)
{
	int	i;

	i = 0;
	while (input[++i] != 0)
	{
		if (input[i] == quote)
			break ;
	}
	return (i);
}

/*
   Heres the function that figures out how long a "normal" token 
   is in the input string. It handles quotes and special characters 
   while determining the length.

   - Initialize variables:
     `i` is the loop index, starting at -1. `special_token` checks 
     if the first character is a special one.

   - Loop through the input:
     Go through each character in `input` to determine the token's 
     length.

   - Handle quotes:
     If a quote is found, call `detect_quote_token` to skip over 
     the quoted part.

   - Check for special characters:
     If the first character isn't special but a special one is 
     found later, backtrack by 1 and break the loop.

   - End of token:
     If the current character is a space, null terminator, or a 
     transition from special to non-special character, stop the loop.

   - Return the token length:
     Return `i - 1` if at the end or if dealing with a special token, 
     otherwise just return `i`.
*/
int	detect_normal_token(char *input)
{
	int		i;
	char	*special_token;

	special_token = ft_strchr("\1\3", input[0]);
	i = -1;
	while (input[++i] != 0)
	{
		if (input[i] == '\'' || input[i] == '"')
			i += detect_quote_token(input + i, input[i]);
		if (!special_token && ft_strchr("\1\3", input[i]))
		{
			i--;
			break ;
		}
		if ((special_token && !ft_strchr("\1\3", input[i]))
			|| input[i] == ' ' || input[i] == 0)
			break ;
	}
	if (input[i] == 0 || special_token)
		return (i - 1);
	return (i);
}

/*
   Heres the function that checks the syntax of a command block by
   analyzing the input string for issues like unexpected tokens
   and unclosed quotes.

   - Initialize variables:
     `i` is used to loop through the input string, `quote` tracks 
     if the current position is inside a quote.

   - Loop through the input string:
     Iterate over each character in `cmdblock->input` to check for 
     syntax errors.

   - Check for unexpected parentheses:
     If an unexpected '(' or ')' is found outside of quotes, 
     call `syntax_error` and return 0.

   - Track quotes:
     If a quote is found, set `quote` to that character. If the same 
     quote is found again, reset `quote` to 0.

   - Check for unclosed quotes:
     After the loop, if `quote` is still non-zero, it means a quote 
     was not closed, so return a syntax error.

   - Return 1 if syntax is correct:
     If no errors are found, return 1 to indicate the command block 
     has valid syntax.
*/
int	check_cmdblock_syntax(t_mini *mini, t_cmdblock *cmdblock)
{
	int	i;
	int	quote;

	i = -1;
	quote = 0;
	while (cmdblock->input[++i] != 0)
	{
		if (quote == 0
			&& (cmdblock->input[i] == '(' || cmdblock->input[i] == ')'))
		{
			return (syntax_error(mini, UNEXPECTED_TOKEN,
					find_unexpected_token(cmdblock->input + i)));
		}
		else if (quote == 0
			&& (cmdblock->input[i] == '\'' || cmdblock->input[i] == '"'))
			quote = cmdblock->input[i];
		else if (quote != 0 && cmdblock->input[i] == quote)
			quote = 0;
	}
	if (quote != 0)
		return (syntax_error(mini, UNCLOSED_QUOTE, NULL));
	return (1);
}

/*
   Heres the function that checks the syntax of each command block
   in the list.

   - Traverse the command blocks list:
     Loops through each command block in `cmdblocks_list`.

   - Check syntax for each command block:
     Calls `check_cmdblock_syntax` to verify the syntax of the 
     current command block.

   - Return 0 if syntax error is found:
     If any command block fails the syntax check, return 0 to indicate
     an error.

   - Return 1 if all command blocks pass:
     If all command blocks pass the syntax check, return 1 to indicate
     that the syntax is correct.
*/
int	check_syntax(t_mini *mini, t_list *cmdblocks_list)
{
	t_cmdblock	*cmdblock;

	while (cmdblocks_list != NULL)
	{
		cmdblock = (t_cmdblock *)cmdblocks_list->content;
		if (check_cmdblock_syntax(mini, cmdblock) == 0)
			return (0);
		cmdblocks_list = cmdblocks_list->next;
	}
	return (1);
}
