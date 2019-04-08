/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brezenhame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkotytsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 12:25:24 by mkotytsk          #+#    #+#             */
/*   Updated: 2019/04/08 12:25:25 by mkotytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	double_del(char **xy)
{
	int i;

	i = -1;
	while (xy[++i])
	{
		if (xy[i])
			free(xy[i]);
	}
	if (xy)
		free(xy);
}

void	brezenham(t_mllib *mlx, t_fdf *read)
{
	int deltax;
	int deltay;
	int signx;
	int signy;

	deltax = ABS(read->x2 - read->x1);
	deltay = ABS(read->y2 - read->y1);
	signx = read->x1 < read->x2 ? 1 : -1;
	signy = read->y1 < read->y2 ? 1 : -1;
	mlx->err = deltax - deltay;
	while (read->x1 != read->x2 || read->y1 != read->y2)
	{
		put_pixel(mlx, read->x1, read->y1, read);
		mlx->deltaerr = mlx->err * 2;
		if (mlx->deltaerr > -deltay)
		{
			mlx->err -= deltay;
			read->x1 += signx;
		}
		if (mlx->deltaerr < deltax)
		{
			mlx->err += deltax;
			read->y1 += signy;
		}
	}
}
