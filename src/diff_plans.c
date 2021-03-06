/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diff_plans.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkotytsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 12:49:26 by mkotytsk          #+#    #+#             */
/*   Updated: 2019/04/08 12:49:27 by mkotytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_str	**usual(t_fdf *read)
{
	int i;
	int j;

	i = -1;
	j = -1;
	while (++i < read->count_y)
	{
		while (++j < read->count_x)
		{
			read->map_us[i][j].x = read->map[i][j].x;
			read->map_us[i][j].y = read->map[i][j].y;
			read->map_us[i][j].clr = read->map[i][j].clr;
		}
		j = -1;
	}
	rotate(read->map_us, read);
	return (read->map_us);
}

t_str	**iso(t_fdf *read)
{
	int i;
	int j;
	int mt;

	mt = 1;
	i = -1;
	j = -1;
	while (++i < read->count_y)
	{
		while (++j < read->count_x)
		{
			read->map_iso[i][j].x = (((read->map[i][j].x - read->map[i][j].y)
				* cos(0.223599)) / mt);
			read->map_iso[i][j].y = ((-read->map[i][j].z
				+ (read->map[i][j].x + read->map[i][j].y)
				* sin(0.223599)) / mt);
			read->map_iso[i][j].clr = read->map[i][j].clr;
		}
		j = -1;
	}
	return (read->map_iso);
}

t_str	**perspective(t_fdf *read)
{
	int		i;
	int		j;
	double	dst;

	dst = WIDTH / 1.5 * -1;
	i = -1;
	while (++i < read->count_y)
	{
		j = -1;
		while (++j < read->count_x)
		{
			if (read->map[i][j].z != dst)
			{
				read->map_per[i][j].x = read->map[i][j].x
					/ (1 + read->map[i][j].z / dst);
				read->map_per[i][j].y = read->map[i][j].y
					/ (1 + read->map[i][j].z / dst);
				read->map_per[i][j].clr = read->map[i][j].clr;
			}
		}
	}
	return (read->map_per);
}
