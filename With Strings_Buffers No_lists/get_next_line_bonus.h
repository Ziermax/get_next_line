/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 17:34:20 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/03/02 17:43:03 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <limits.h>
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
