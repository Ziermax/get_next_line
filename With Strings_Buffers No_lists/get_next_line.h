/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 14:41:06 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/03/02 17:43:06 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# define NL_FOUND 10
# define NOT_NL_FOUND 5
# define FAIL 9
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10

# endif

int		get_len_up_to(char *line, char up_to);
char	*get_joined(char *line, char *to_append, int read);
int		get_nl_info(char *line);
char	*get_text(int fd, char *line);
char	*get_line(char *text);
char	*get_keep(char *text, int *info);
char	*get_next_line(int fd);

#endif
