/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 20:58:03 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/02/04 21:49:45 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/*	CPY BUFFER_SIZE BYTES FROM FD TO NEW_NODE'S CHUNK
 *	UP2 FIND THE '\n' IN THE LIST
 *	OR READ LESS THAN BUFFER_SIZE BYTES
 *	IF READ OR NODE'S MALLOCATION FAILS, FREE LIST AND RETURN
 *	*/
void	get_linefd_to_lst(int fd, t_line **lst, int *buffsize)
{
	t_line	*node;
	int		rd_ret;
	int		nl_found;

	rd_ret = BUFFER_SIZE;
	nl_found = get_nl_info(*lst, buffsize);
	while (rd_ret == BUFFER_SIZE && !nl_found)
	{
		node = get_bigger_lst(lst);
		if (!node)
			return (get_free_lst(lst, FREE_ALL));
		rd_ret = read(fd, node->chunk, BUFFER_SIZE);
		nl_found = get_nl_info(node, buffsize);
	}
	if (rd_ret == 0)
		get_last_deleted(lst);
	if (rd_ret == -1)
		get_free_lst(lst, FREE_ALL);
}

/*	CPY LIST'S CHARACTER TO LINE'S BUFFER
 *	UP2 RUNOUT OF BUFFER
 *	*/
void	get_lst_to_line(t_line *lst, char *line, int buffsize)
{
	int	i;
	int	i_line;

	i_line = 0;
	while (lst)
	{
		i = 0;
		while (i < BUFFER_SIZE && lst->chunk[i] == 0)
			i++;
		while (i < BUFFER_SIZE && i_line < buffsize)
			line[i_line++] = lst->chunk[i++];
		lst = lst->next;
	}
	line[i_line] = '\0';
}

/*	GET NEXT LINE
 *	*/
char	*get_next_line(int fd)
{
	char			*line;
	static t_line	*lst_line[1024];
	int				buffsize;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= 1024)
		return (NULL);
	buffsize = 0;
	get_linefd_to_lst(fd, &lst_line[fd], &buffsize);
	if (!lst_line[fd])
		return (NULL);
	line = malloc(sizeof(char) * (buffsize + 1));
	if (!line)
	{
		get_free_lst(&lst_line[fd], FREE_ALL);
		return (NULL);
	}
	get_lst_to_line(lst_line[fd], line, buffsize);
	get_free_lst(&lst_line[fd], KEEP_LAST);
	return (line);
}
