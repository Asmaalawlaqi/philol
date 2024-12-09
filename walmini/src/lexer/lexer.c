/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walhamad <walhamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:13:47 by walhamad          #+#    #+#             */
/*   Updated: 2024/09/04 18:13:48 by walhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
   Heres the function that creates a new command block structure,
   initializes its fields, and returns it.

   - Allocate memory:
     Allocates memory for a new `t_cmdblock` structure. 
     If allocation fails, returns NULL.

   - Initialize fields:
     Sets `spliter_type` to the provided value, `in_bracket` to 
     indicate if the command is within brackets, and `need_wait` 
     to 0 as default. `cmd_argv` is initialized to NULL.

   - Return command block:
     Returns the pointer to the newly created and initialized 
     `t_cmdblock` structure.
*/
static t_cmdblock	*create_new_cmdblock(int spliter_type, int in_bracket)
{
	t_cmdblock	*new_cmdblock;

	new_cmdblock = malloc(sizeof(t_cmdblock));
	if (new_cmdblock == NULL)
		return (NULL);
	new_cmdblock->spliter_type = spliter_type;
	new_cmdblock->in_bracket = in_bracket;
	new_cmdblock->need_wait = 0;
	new_cmdblock->cmd_argv = NULL;
	return (new_cmdblock);
}

/*
   Heres the function that handles command blocks enclosed in brackets 
   and returns them as list nodes.

   - Initialize:
     Starts by initializing the quote to 0 and len to 1 to skip 
     the opening '('.

   - Traverse input:
     Loops through the input string, managing quotes and looking 
     for the closing ')' while ignoring content inside quotes.

   - Update quote:
     If the loop encounters a quote character, it updates the 
     quote variable to track the current quoting state.

   - Create command block:
     Allocates and initializes a new `t_cmdblock` using 
     `create_new_cmdblock` with `in_bracket` set to 1. 
     If allocation fails, returns NULL.

   - Extract input:
     Copies the relevant portion of the input into the new 
     command block, excluding the brackets if they match.

   - Return as list node:
     Wraps the command block in a list node and returns it.
*/
t_list	*get_bracket_cmdblock(char *input, int spliter_type)
{
	int			quote;
	int			len;
	t_cmdblock	*new_cmdblock;

	quote = 0;
	len = 1;
	while (input[len] != 0
		&& (quote != 0 || ft_strncmp(input + len, ")", 1) != 0))
	{
		if (quote != 0 && input[len] == quote)
			quote = 0;
		else if (quote == 0 && (input[len] == '\"' || input[len] == '\''))
			quote = input[len];
		len++;
	}
	new_cmdblock = create_new_cmdblock(spliter_type, 1);
	if (new_cmdblock == NULL)
		return (NULL);
	if (input[len] != ')')
		new_cmdblock->input = ft_strndup(input, len);
	else
		new_cmdblock->input = ft_strndup(input + 1, len - 1);
	return (ft_lstnew((void *)new_cmdblock));
}

/*
   Heres the function that creates a new command block 
   from the input string and returns it as a list node.

   - Skip splitter:
     Moves the input pointer past any initial splitter 
     characters using `skip_spliter`.

   - Skip spaces:
     Skips any leading spaces in the input string.

   - Handle brackets:
     If the input starts with '(', it calls `get_bracket_cmdblock` 
     to handle the bracketed command.

   - Calculate length:
     Determines the length of the command block using 
     `calculate_cmdblock_length`.

   - Create command block:
     Allocates and initializes a new `t_cmdblock` using 
     `create_new_cmdblock`. If allocation fails, it returns NULL.

   - Duplicate input:
     Copies the relevant portion of the input into the new command 
     block.

   - Return as list node:
     Wraps the command block in a list node and returns it.
*/
t_list	*get_new_cmdblock(char *input, int spliter_type)
{
	int			len;
	t_cmdblock	*new_cmdblock;

	input = skip_spliter(input, spliter_type);
	while (*input == ' ')
		input++;
	if (ft_strncmp(input, "(", 1) == 0)
		return (get_bracket_cmdblock(input, spliter_type));
	len = calculate_cmdblock_length(input);
	new_cmdblock = create_new_cmdblock(spliter_type, 0);
	if (new_cmdblock == NULL)
		return (NULL);
	new_cmdblock->input = ft_strndup(input, len);
	return (ft_lstnew((void *)new_cmdblock));
}

/*
   Heres the function that adds a new command block to the list 
   and updates the input pointer for the next segment.

   - Create new command block:
     Calls `get_new_cmdblock` to generate a new command block 
     from the current input segment.

   - Add to list:
     Uses `ft_lstadd_back` to append the new command block to the 
     end of `cmdblock_list`.

   - Update input pointer:
     Moves the input pointer forward by the length of the current 
     segment (`*i`).

   - Handle splitters:
     Adjusts the input pointer depending on whether the splitter 
     is a pipe `|`, a logical operator `&&`, `||`, or a semicolon 
     `;`.

   - Reset index:
     Resets the index (`*i`) to 0, ready for the next segment.
*/
void	add_cmdblock_to_list(t_list **cmdblock_list, char **input, int *i)
{
	t_list	*new_cmdblock;

	new_cmdblock = get_new_cmdblock(*input, BEGINNING);
	ft_lstadd_back(cmdblock_list, new_cmdblock);
	*input += *i;
	*i = 0;
	if (get_spliter_type(*input) == PIPE)
		*input += 1;
	else if (get_spliter_type(*input) != INVALID || **input == ';')
		*input += 2;
}

/*
   Heres the function that splits the input string into command 
   blocks based on delimiters like pipes `|`, logical operators 
   `&&`, `||`, or semicolons `;`.

   - Initialize variables:
     We start by setting up the necessary variables to track 
     quotes, bracket levels, and the command block list.

   - Process the input string:
     The function loops through the input string, segmenting it 
     based on quotes, brackets, and special splitters.

   - Handling splitters:
     When it encounters a valid splitter or semicolon, it calls 
     `add_cmdblock_to_list` to add the command block to the list.

   - Final command block:
     If theres remaining input after the loop, it adds the final 
     command block to the list.

   - Return:
     The function returns a linked list of command blocks 
     (`cmdblock_list`).
*/
t_list	*split_cmdblocks(char *input, int bracket)
{
	int		i;
	t_list	*cmdblock_list;
	int		quote;
	int		bracket_level;

	(void)bracket;
	quote = 0;
	bracket_level = 0;
	cmdblock_list = NULL;
	i = 0;
	while (input[i] != 0)
	{
		process_input_segment(&input, &i, &quote, &bracket_level);
		if (bracket_level == 0 && (get_spliter_type(input + i) != INVALID
				|| input[i] == ';'))
			add_cmdblock_to_list(&cmdblock_list, &input, &i);
	}
	if (*input != 0)
		add_cmdblock_to_list(&cmdblock_list, &input, &i);
	return (cmdblock_list);
}
