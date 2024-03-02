/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 14:39:35 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/03/02 17:20:13 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*	Go through every byte in line
 *	Up to find up_to char
 *	return len
 *	*/
int	get_len_up_to(char *line, char up_to)
{
	int	len;

	if (!line)
		return (0);
	len = 0;
	while (line[len] != up_to && line[len])
		len++;
	return (len);
}

/*	Join two stings in a buffer join
 *	return join - Free line buffer
 *	if malloc fails
 *	 return NULL - Free line buffer
 *	*/
char	*get_joined(char *line, char *read, int to_append)
{
	char	*join;
	int		len;
	int		i;
	int		j;

	len = get_len_up_to(line, '\0');
	join = malloc(sizeof(char) * (len + to_append + 1));
	if (!join)
		return (free(line), NULL);
	i = 0;
	while (i < len)
	{
		join[i] = line[i];
		i++;
	}
	j = 0;
	while (i < len + to_append)
		join[i++] = read[j++];
	join[i] = '\0';
	free(line);
	return (join);
}

/*	Search in line buffer for '\n'
 *	return NL_FOUND if '\n' is in buffer
 *	return NOT_NL_FOUND if not found
 *	*/
int	get_nl_info(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (NOT_NL_FOUND);
	while (line[i])
	{
		if (line[i] == '\n')
			return (NL_FOUND);
		i++;
	}
	return (NOT_NL_FOUND);
}
