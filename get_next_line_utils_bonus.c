/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvelazqu <mvelazqu@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 20:57:45 by mvelazqu          #+#    #+#             */
/*   Updated: 2024/02/04 22:04:08 by mvelazqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/*	ENLARGE LIST BY ONE NODE
 *	RETURN NODE APPENDED TO LIST
 *	RETURN NULL DIRECTION IF FAILS NODE MALLOCATION
 *	*/
t_line	*get_bigger_lst(t_line **lst)
{
	t_line	*new;
	t_line	*aux;
	int		i;

	new = malloc(sizeof(t_line));
	if (!new)
		return (NULL);
	i = 0;
	while (i < BUFFER_SIZE)
		new->chunk[i++] = 0;
	new->next = NULL;
	aux = *lst;
	if (!aux)
	{
		*lst = new;
		return (new);
	}
	while (aux->next)
		aux = aux->next;
	aux->next = new;
	return (new);
}

/*	SET TO 0 EVERY BYTE OF NODE'S CHUNK
 *	UP2 FIND '\n' IN CHUNK
 *	IF CHUNK IS FULL OF 0 FREE_ALL
 *	*/
void	get_last_chars(t_line *node, t_line **lst)
{
	int	i;

	i = 0;
	while (node->chunk[i] != '\n' && i < BUFFER_SIZE - 1)
		node->chunk[i++] = 0;
	node->chunk[i] = 0;
	while (node->chunk[i] == 0 && i < BUFFER_SIZE)
		i++;
	if (i == BUFFER_SIZE)
		get_free_lst(lst, FREE_ALL);
}

/*	SEARCH IN NODE'S CHUNK FOR '\n'
 *	UP2 RUNOUT OF CHUNK'S BUFFER
 *	RETURN 1 IF FOUND AND MODIFY BUFFSIZE
 *	RETURN 0 IF NOT AND MODIFY BUFFSIZE
 *	*/
int	get_nl_info(t_line *node, int *buffsize)
{
	int	i;
	int	start;

	if (!node)
		return (0);
	i = 0;
	while (node->chunk[i] == 0 && i < BUFFER_SIZE)
		i++;
	start = i;
	while (node->chunk[i] != 0 && i < BUFFER_SIZE)
	{
		if (node->chunk[i++] == '\n')
		{
			*buffsize = *buffsize + i - start;
			return (1);
		}
	}
	*buffsize = *buffsize + i - start;
	return (0);
}

/*	DELETE LAST NODE OF LIST
 *	SET BEFORE_LAST_NODE'S NEXT TO NULL DIRECTION
 *	IF LIST HAS 1 NODE, FREE IT AND SET LIST'S DIRECTION TO NULL
 *	*/
void	get_last_deleted(t_line **lst)
{
	t_line	*aux;
	t_line	*before_last;

	if (!*lst)
		return ;
	aux = *lst;
	if (aux->next == NULL)
	{
		free(aux);
		*lst = NULL;
		return ;
	}
	while (aux->next)
	{
		before_last = aux;
		aux = aux->next;
	}
	free(aux);
	before_last->next = NULL;
}

/*	KEEP_LAST:
 *	FREE EVERY NODE IN LIST EXCEPT LAST ONE
 *	SET LIST'S MEMORY DIRECTION TO LAST NODE
 *	SAVE LAST CHARS AFTER '\n'
 *	FREE_ALL:
 *	FREE EVERY NODE IN LIST
 *	SET LIST'S MEMORY DIRECTION TO NULL
 *	*/
void	get_free_lst(t_line **lst, int flag)
{
	t_line	*aux;
	t_line	*tmp;
	int		i;

	if (!*lst)
		return ;
	i = 0;
	aux = *lst;
	while (aux->next)
	{
		tmp = aux->next;
		free(aux);
		aux = tmp;
	}
	if (flag == KEEP_LAST)
	{
		*lst = aux;
		get_last_chars(aux, lst);
		return ;
	}
	free(aux);
	*lst = NULL;
}
