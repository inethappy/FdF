/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkotytsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 12:04:55 by mkotytsk          #+#    #+#             */
/*   Updated: 2019/04/08 12:04:56 by mkotytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate(t_str **new, t_fdf *read)
{
	int i;
	int j;

	i = -1;
	while (++i < read->count_y)
	{
		j = -1;
		while (++j < read->count_x)
		{
			new[i][j].y = read->map[i][j].y
				* cos(read->turn_x) + read->map[i][j].z * sin(read->turn_x);
			new[i][j].z = -read->map[i][j].y
				* sin(read->turn_x) + read->map[i][j].z * cos(read->turn_x);
			if (read->turn_y)
			{
				new[i][j].x = new[i][j].x
					* cos(read->turn_y) + new[i][j].z * sin(read->turn_y);
				new[i][j].z = -new[i][j].x
					* sin(read->turn_y) + new[i][j].z * cos(read->turn_y);
			}
		}
	}
}

void	zoom_out(t_str **new, t_fdf *read)
{
	int i;
	int j;

	i = -1;
	j = -1;
	if (ABS(new[0][1].x - new[0][0].x) < 1 || read->zoom_out > 10000)
	{
		read->zoom_out /= 2;
		read->zoom_in /= 2;
	}
	while (++i < read->count_y)
	{
		while (++j < read->count_x)
		{
			new[i][j].x = new[i][j].x / read->zoom_out;
			new[i][j].y = new[i][j].y / read->zoom_out;
		}
		j = -1;
	}
}

void	zoom_in(t_str **new, t_fdf *read)
{
	int i;
	int j;

	i = -1;
	j = -1;
	if (ABS(new[0][1].x - new[0][0].x) > 300 || read->zoom_in > 10000)
	{
		read->zoom_out /= 2;
		read->zoom_in /= 2;
	}
	while (++i < read->count_y)
	{
		while (++j < read->count_x)
		{
			new[i][j].x = new[i][j].x * read->zoom_in;
			new[i][j].y = new[i][j].y * read->zoom_in;
		}
		j = -1;
	}
}

void	move(t_str **new, t_fdf *read)
{
	int i;
	int j;

	i = -1;
	j = -1;
	while (++i < read->count_y)
	{
		while (++j < read->count_x)
		{
			new[i][j].x += read->mv_x;
			new[i][j].y += read->mv_y;
		}
		j = -1;
	}
}
