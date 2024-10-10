/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbenmakh <rbenmakh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 23:30:24 by rbenmakh          #+#    #+#             */
/*   Updated: 2024/10/10 16:23:11 by rbenmakh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	enqueue(t_node **queue, int x, int y)
{
	t_node	*new_t_node;

	new_t_node = malloc(sizeof(t_node));
	if (!new_t_node)
		return (1);
	new_t_node->x = x;
	new_t_node->y = y;
	if ((*queue) == NULL)
	{
		(*queue) = new_t_node;
		(*queue)->parent = 0;
		(*queue)->next = 0;
	}
	else
	{
		new_t_node->next = (*queue)->next;
		new_t_node->parent = (*queue);
		(*queue)->next = new_t_node;
	}
	return (EXIT_SUCCESS);
}

void	dequeue(t_node **list, t_node *current)
{
	t_node	*tmp;
	t_node	*previous;

	if (!list || !*list || !current)
		return ;
	if (*list == current)
	{
		tmp = *list;
		*list = (*list)->next;
		free(tmp);
		return ;
	}
	else
	{
		previous = *list;
		while (previous->next != current && previous->next != NULL)
			previous = previous->next;
		if (previous->next == current)
			previous->next = current->next;
		else
			return ;
	}
	free(current);
	return ;
}

int	neighbors(t_node **queue, t_node *cur, t_mlx *d, int **vis)
{
	int	x;
	int	y;

	x = cur->x;
	y = cur->y;
	if (x + 1 < d->w_h / 50 - 1 && (d->map[x + 1][y] != '1' && d->map[x
			+ 1][y] != 'E') && vis[x + 1][y] == 0)
		enqueue(queue, x + 1, y);
	if (x - 1 > 0 && (d->map[x - 1][y] != '1' && d->map[x - 1][y] != 'E')
		&& vis[x - 1][y] == 0)
		enqueue(queue, x - 1, y);
	if (y + 1 < d->w_w / 50 - 1 && (d->map[x][y + 1] != '1' && d->map[x][y
		+ 1] != 'E') && vis[x][y + 1] == 0)
		enqueue(queue, x, y + 1);
	if (y - 1 > 0 && (d->map[x][y - 1] != '1' && d->map[x][y - 1] != 'E')
		&& vis[x][y - 1] == 0)
		enqueue(queue, x, y - 1);
	return (EXIT_SUCCESS);
}

int	init_row(int **arr, int i, t_mlx *d)
{
	int	j;

	j = 0;
	arr[i] = (int *)malloc(sizeof(int) * d->w_w / 50);
	if (!arr[i])
	{
		free_arr(d, (void **)arr, i, 0);
		return (1);
	}
	while (j < d->w_w / 50)
	{
		arr[i][j] = 0;
		j++;
	}
	return (EXIT_SUCCESS);
}

int	bfs(int st_x, int st_y, t_mlx *d)
{
	t_node	*queue;
	int		**arr;
	int		i;

	i = 0;
	arr = malloc(sizeof(int *) * d->w_h / 50);
	if (!arr)
		return (1);
	while (i < d->w_h / 50)
	{
		if (init_row(arr, i, d))
			return (1);
		i++;
	}
	queue = NULL;
	enqueue(&queue, st_x / 50, st_y / 50);
	while (queue)
	{
		arr[queue->x][queue->y] = 6;
		neighbors(&queue, queue, d, arr);
		dequeue(&queue, queue);
	}
	d->bmap = arr;
	return (EXIT_SUCCESS);
}
