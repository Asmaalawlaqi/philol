/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walhamad <walhamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:13:43 by walhamad          #+#    #+#             */
/*   Updated: 2024/09/04 18:13:44 by walhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
   Heres the function that expands the special variable `$?` 
   in the input string. `$?` represents the exit status of the 
   last executed command, stored in `g_errno`.

   - Convert exit status to string:
     The function uses `ft_itoa()` to convert the integer exit 
     status `g_errno` into a string.

   - Replace `$?` in input:
     The input string is then updated, replacing the `$?` 
     with the exit status string using `ft_strexpand()`.

   - Adjust index:
     The index `i` is updated to point to the end of the 
     expanded status in the input string.

   - Cleanup:
     The function frees the memory allocated for the exit 
     status string after its expansion.

   - Return:
     The function returns `1` to indicate that the expansion 
     was performed.
*/
static int	expand_exit_status(t_mini *mini, char **pinput, int *i)
{
	char	*str_exit_status;

	(void)mini;
	str_exit_status = ft_itoa(g_errno);
	ft_strexpand(pinput, str_exit_status, *i, 2);
	*i += ft_strlen(str_exit_status) - 1;
	free(str_exit_status);
	return (1);
}

/*
   Heres the function that handles the expansion of environment 
   variables in the input string. It processes variables 
   prefixed by `$` and substitutes them with their corresponding 
   values.

   - Special case for `$?`:
     If the `$?` is encountered, it expands to the exit status 
     of the last executed command.

   - Parse variable name:
     The function identifies the variable name by checking for 
     alphanumeric characters and underscores. It stops parsing 
     if a quote or non-variable character is found.

   - Lookup environment variable:
     Once the variable name is identified, it fetches the 
     corresponding value from the environment using `get_env()`.

   - Replace in input:
     The variable in the input string is replaced with its value 
     using `ft_strexpand()`.

   - Adjust index:
     The function updates the index `i` to point to the 
     end of the expanded variable in the input string.

   - Return:
     The function returns `1` if a variable was expanded, or `0` 
     if no expansion occurred.
*/
static int	expand_var(t_mini *mini, char **pinput, int quote, int *i)
{
	int		n;
	char	*temp_key;
	char	*env_var;

	n = 1;
	env_var = NULL;
	if ((*pinput + *i)[1] == '?')
		return (expand_exit_status(mini, pinput, i));
	while ((ft_isalnum((*pinput + *i)[n])
		|| (*pinput + *i)[n] == '_')
		&& (*pinput + *i)[n] != quote)
		n++;
	if (n == 1)
		return (0);
	temp_key = ft_strndup((*pinput + *i + 1), n - 1);
	env_var = get_env(mini, temp_key);
	free(temp_key);
	ft_strexpand(pinput, env_var, *i, n);
	*i += ft_strlen(env_var) - 1;
	return (1);
}

/*
   Heres the function that handles the expansion of wildcards 
   in the input string. It iterates through the input, searching 
   for wildcard characters `*` and processes them accordingly.

   - Track tokens:
     It identifies tokens in the input, considering quotes 
     to avoid expanding wildcards inside quotes.

   - Check for `export` command:
     It checks if the current command is `export` to prevent 
     wildcard expansion for variable assignments.

   - Expand wildcards:
     If a wildcard `*` is found outside quotes, and it's not part 
     of an `export` assignment, it expands the wildcard by 
     calling `wildcard()`.

   - Manage indexes:
     The function adjusts the index after each token to 
     continue processing the input correctly.

   - Return:
     The function returns the total number of wildcard 
     expansions made in the input string.
*/
static int	expand_wildcard(t_mini *mini, char **pinput)
{
	int		i;
	int		quote;
	char	*token;
	int		is_export;
	int		expanded;

	i = -1;
	is_export = 0;
	expanded = 0;
	while ((*pinput)[++i] != 0)
	{
		quote = (*pinput)[i];
		token = get_next_token(*pinput, i, quote);
		if (i == 0 && ft_strcmp(token, "export") == 0)
			is_export = 1;
		if (quote != '\'' && quote != '"' && ft_strchr(token, '*') != NULL)
			if (!(is_export && ft_strchr(token, '=')))
				expanded += wildcard(mini, pinput, &token, i);
		i += ft_strlen(token);
		free(token);
		if (i >= 0 && (*pinput)[i] == 0)
			return (expanded);
	}
	return (expanded);
}

/*
   Heres the function that handles the expansion of variables 
   within the input string. It goes through the input, checking 
   for environment variables, redirection operators, and 
   managing quotes.

   - Expand variables:
     It looks for `$` signs to identify variables and 
     calls `expand_var()` to replace them with their values.

   - Handle redirection symbols:
     It checks for redirection operators `<` and `>`, converting 
     them into placeholders (1 and 3) to avoid conflicts 
     during parsing.

   - Manage quotes:
     It tracks whether the current context is within quotes 
     (single or double) to ensure correct parsing.

   - Return:
     The function returns the total number of expansions 
     made to the input string.
*/
static int	expand_variables(t_mini *mini, char **pinput)
{
	int		quote;
	int		i;
	int		expanded;

	quote = 0;
	i = -1;
	expanded = 0;
	while ((*pinput)[++i] != 0)
	{
		if (quote != '\'' && (*pinput)[i] == '$')
			expanded += expand_var(mini, pinput, quote, &i);
		else if (quote == 0 && ((*pinput)[i] == '<' || (*pinput)[i] == '>'))
		{
			(*pinput)[i] = 1 + ((*pinput)[i] == '>') * 2;
			expanded++;
		}
		else if (quote == 0 && ((*pinput)[i] == '\'' || (*pinput)[i] == '"'))
			quote = (*pinput)[i];
		else if (quote == (*pinput)[i])
			quote = 0;
		if (i >= 0 && (*pinput)[i] == 0)
			return (expanded);
	}
	return (expanded);
}

/*
   Heres the function that handles the expansion of input string 
   by expanding variables and wildcards, and also removing 
   surrounding quotes if any.

   - Expand variables:
     First, it calls `expand_variables()` to replace any environment 
     variables in the input with their values.

   - Expand wildcards:
     Then, it runs `expand_wildcard()` to handle wildcard 
     expansions like `*` and `?`.

   - Remove surrounding quotes:
     If the expanded input starts and ends with quotes 
     (either single or double), theyre removed to clean up 
     the input string.

   - Return:
     The function returns the sum of expansions made to the input.
*/
int	expand_input(t_mini *mini, char **pinput)
{
	int		expanded;
	char	*temp;

	expanded = 0;
	expanded += expand_variables(mini, pinput);
	expanded += expand_wildcard(mini, pinput);
	if (((*pinput)[0] == '\'' && (*pinput)[ft_strlen(*pinput) - 1] == '\'')
		|| ((*pinput)[0] == '"' && (*pinput)[ft_strlen(*pinput) - 1] == '"'))
	{
		temp = *pinput;
		*pinput = ft_strndup(temp + 1, ft_strlen(temp) - 2);
		free(temp);
	}
	return (expanded);
}
