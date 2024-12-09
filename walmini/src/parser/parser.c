/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: walhamad <walhamad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:13:56 by walhamad          #+#    #+#             */
/*   Updated: 2024/09/04 18:13:57 by walhamad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
   Heres the function that trims leading and trailing spaces 
   from the input string.

   - Trim the input:
     Uses `ft_strtrim` to remove any leading and trailing spaces 
     from the input string.

   - Free the original input:
     Frees the memory allocated to the original input string 
     since it is no longer needed.

   - Return the trimmed result:
     Returns the new string that has had its spaces trimmed off.
*/
char	*trim_input(char *input)
{
	char	*result;

	result = ft_strtrim(input, " ");
	free(input);
	return (result);
}
