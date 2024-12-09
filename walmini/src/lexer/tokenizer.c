/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walhamad <walhamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:13:50 by walhamad          #+#    #+#             */
/*   Updated: 2024/09/04 18:13:51 by walhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	 Heres the function that extracts a token enclosed in quotes 
	 from the input string.

	 - Initialize length counter:
		 Sets up `len` to measure the length of the quoted token.

	 - Find the closing quote:
		 Iterates through the input starting from index `i` to locate 
		 the closing quote that matches the opening quote.

	 - Return the quoted token:
		 Once the closing quote is found, the function duplicates the 
		 quoted string including the quotes and returns it.
*/
static char	*get_quote_token(char *input, int i, int quote)
{
	int	len;

	len = 0;
	while ((input + i)[++len] != quote && (input + i)[len] != 0)
		;
	return (ft_strndup(input + i, len + 1));
}

/*
	 Heres the function that calculates the total number of tokens 
	 in the input string.

	 - Initialize counters:
		 Sets up `i` to iterate through the string and `size` to keep 
		 track of the number of tokens detected.

	 - Loop through input:
		 Iterates over each character in the input string.

	 - Handle quotes:
		 If a quote is found, the function delegates the token length 
		 detection to `detect_quote_token`, skips over the quoted 
		 section, and increments the token count `size`.

	 - Handle normal tokens:
		 If the character is not a space and not a quote, it delegates 
		 the length detection to `detect_normal_token`, skips the 
		 token, and increments `size`.

	 - Return total size:
		 After processing the entire input string, the function returns 
		 the total count of tokens.
*/
int	get_tokens_size(char *input)
{
	int	i;
	int	size;

	i = -1;
	size = 0;
	while (input[++i] != 0)
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			i += detect_quote_token(input + i, input[i]);
			size++;
		}
		else if (input[i] != ' ')
		{
			i += detect_normal_token(input + i);
			size++;
		}
		if (input[i] == 0)
			break ;
	}
	return (size);
}

/*
	 Heres the function that extracts the next token from the input 
	 string starting at position `i`.

	 - Check for quotes:
		 If the current character is a single or double quote, it 
		 delegates the token extraction to `get_quote_token`.

	 - Initialize target delimiter:
		 Sets `target` as a space character to find the end of the 
		 token, unless quotes are found, which will change the target.

	 - Loop through input:
		 Iterates over the characters starting from `i`, adjusting the 
		 token length `len` based on delimiters or special characters 
		 like `\1` or `\3`.

	 - Handle special characters:
		 If a special character is found and it’s not the first 
		 character of the token, it returns the token up to this point. 
		 Otherwise, it continues to process the special characters.

	 - Adjust for quotes:
		 If quotes are encountered, it switches the `target` to that 
		 quote character to include the entire quoted section.

	 - Return extracted token:
		 Returns a newly allocated string containing the next token.
*/
char	*get_next_token(char *input, int i, int quote)
{
	int		len;
	int		target;

	len = 0;
	if (quote == '\'' || quote == '"')
		return (get_quote_token(input, i, quote));
	target = ' ';
	while ((input + i)[len] != 0 && (input + i)[len] != target)
	{
		if (target == ' ' && ft_strchr("\1\3", (input + i)[len]))
		{
			if (len != 0)
				return (ft_strndup((input + i), len));
			while (ft_strchr("\1\3", (input + i)[len]))
				len++;
			return (ft_strndup((input + i), len));
		}
		if ((input + i)[len] == '\'' || (input + i)[len] == '"')
			target = (input + i)[len];
		len++;
	}
	return (ft_strndup((input + i), len + (target != ' ')));
}

/*
	 Heres the function that breaks down the input command string 
	 into tokens and stores them in a dynamically allocated array.

	 - Initialize variables:
		 Sets up the loop indices `i` and `j` and allocates memory for 
		 the `result` array to hold the tokens.

	 - Loop through the input:
		 Iterates through the `input` string, skipping spaces and 
		 identifying tokens. For each token found, stores it in 
		 `result[j]`.

	 - Handle quotes:
		 If a quote is detected, it processes the entire quoted 
		 section as a single token.

	 - Adjust index:
		 After storing a token, adjusts `i` to skip over the processed 
		 part of the input string.

	 - Null-terminate result:
		 Ensures that the final `result` array is null-terminated.

	 - Return tokenized array:
		 Returns the array of tokenized strings.
*/
char	**tokenize_cmd(t_mini *mini, char *input)
{
	int		i;
	int		j;
	char	**result;
	int		quote;

	(void)mini;
	i = -1;
	j = -1;
	result = malloc((get_tokens_size(input) + 1) * sizeof(char *));
	while (input[++i] != 0)
	{
		if (input[i] == ' ')
			continue ;
		quote = input[i];
		result[++j] = get_next_token(input, i, quote);
		if (!result[j])
			return (NULL);
		i += ft_strlen(result[j]);
		if (input[i] != ' ')
			i--;
		if (input[i] == 0)
			break ;
	}
	result[j + 1] = NULL;
	return (result);
}
