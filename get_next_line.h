/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 18:07:06 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/02/04 20:53:42 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# define FREE_ALL 69
# define KEEP_LAST 10
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10

# endif

typedef struct s_line
{
	char			chunk[BUFFER_SIZE];
	struct s_line	*next;
}	t_line;

t_line	*get_bigger_lst(t_line **lst);
void	get_last_chars(t_line *node, t_line **lst);
int		get_nl_info(t_line *node, int *buffsize);
void	get_last_deleted(t_line **lst);
void	get_free_lst(t_line **lst, int flag);
void	get_linefd_to_lst(int fd, t_line **lst, int *buffsize);
void	get_lst_to_line(t_line *lst, char *line, int buffsie);
char	*get_next_line(int fd);

#endif
