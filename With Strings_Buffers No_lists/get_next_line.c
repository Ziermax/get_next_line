/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 14:39:10 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/03/02 17:42:57 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*	Read BUFFER_SIZE bytes in file descriptor
 *	Append read bytes to line
 *	if read or malloc fails
 *	 return NULL - Free lecture - Free line
 *	if not new line in lecture
 *	 read again
 *	return line
 *	*/
char	*get_text(int fd, char *line)
{
	char	*lecture;
	int		rd;

	if (get_nl_info(line) == NL_FOUND)
		return (line);
	lecture = malloc(sizeof(char *) * (BUFFER_SIZE + 1));
	if (!lecture)
		return (free(line), NULL);
	rd = read(fd, lecture, BUFFER_SIZE);
	if (rd < 0)
		return (free(line), free(lecture), NULL);
	lecture[rd] = '\0';
	if (rd == 0)
		return (free(lecture), line);
	line = get_joined(line, lecture, rd);
	if (!line)
		return (free(lecture), NULL);
	if (get_nl_info(lecture) == NOT_NL_FOUND)
		line = get_text(fd, line);
	free(lecture);
	return (line);
}

/*	Copy in line buffer every character in text up to '\n'
 *	return line
 *	if malloc fails
 *	 return NULL - Free text
 *	*/
char	*get_line(char *text)
{
	char	*line;
	int		len;
	int		i;

	len = 0;
	while (text[len] != '\n' && text[len])
		len++;
	if (text[len] == '\n')
		len += 1;
	line = malloc(sizeof(char) * (len + 1));
	if (!line)
		return (free(text), NULL);
	i = 0;
	while (i < len)
	{
		line[i] = text[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

/*	Copy in keep buffer every character in text after '\n'
 *	return line
 *	if no bytes after '\n'
 *	 return NULL - free text
 *	if malloc fails
 *	 return NULL - Free text - Set info to FAIL
 *	*/
char	*get_keep(char *text, int *info)
{
	char	*keep;
	int		len;
	int		start;
	int		i;

	start = get_len_up_to(text, '\n');
	if (text[start] == '\n')
		start += 1;
	len = 0;
	while (text[start + len])
		len++;
	if (len == 0)
		return (free(text), NULL);
	keep = malloc(sizeof(char) * (len + 1));
	if (!keep)
		return (*info = FAIL, free(text), NULL);
	i = -1;
	while (++i < len)
		keep[i] = text[start + i];
	keep[i] = '\0';
	free(text);
	return (keep);
}

/*	Get next line
 *	*/
char	*get_next_line(int fd)
{
	char		*text;
	char static	*keep;
	char		*line;
	int			fail_info;

	if (fd < 0)
		return (NULL);
	fail_info = 0;
	text = get_text(fd, keep);
	if (!text)
		return (keep = NULL, NULL);
	line = get_line(text);
	if (!line)
		return (keep = NULL, NULL);
	keep = get_keep(text, &fail_info);
	if (fail_info == FAIL)
		return (free(line), NULL);
	return (line);
}
/*
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fd;
	char	*str;
	int		i;

	fd = open("test", O_RDONLY);
	i = 0;
	while(1)
	{
		str = get_next_line(fd);
		printf("line %d: \"%s\"\n", i++, str);
		free(str);
		if (str == NULL)
			break ;
	}
	close(fd);
}*/
