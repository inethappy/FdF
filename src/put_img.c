/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_img.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkotytsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 12:04:31 by mkotytsk          #+#    #+#             */
/*   Updated: 2019/04/08 12:04:33 by mkotytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_pixel(t_mllib *mlx, int x, int y, t_fdf *read)
{
	char	*b;
	int		i;

	x += WIDTH / 2;
	y += HEIGHT / 2;
	b = (char*)mlx->addr;
	i = y * mlx->sl + x * mlx->bbp / 8;
	if (x >= 0 && x < WIDTH && y < HEIGHT && y >= 0)
	{
		b[i] = read->clr ? read->clr : 0xff;
		b[++i] = read->clr ? read->clr >> 8 : 0x7f;
		b[++i] = read->clr ? read->clr >> 16 : 0x50;
	}
}

void	coord_for_brez_j(t_fdf *read, t_str **map, int i, int j)
{
	read->x1 = map[i][j].x;
	read->x2 = map[i][j + 1].x;
	read->y1 = map[i][j].y;
	read->y2 = map[i][j + 1].y;
	read->clr = map[i][j].clr;
}

void	coord_for_brez_i(t_fdf *read, t_str **map, int i, int j)
{
	read->x1 = map[i][j].x;
	read->x2 = map[i + 1][j].x;
	read->y1 = map[i][j].y;
	read->y2 = map[i + 1][j].y;
	read->clr = map[i][j].clr;
}

void	put_lines(t_mllib *mlx, t_fdf *read, t_str **map)
{
	int i;
	int j;

	i = -1;
	read->fl_put = 1;
	while (++i < read->count_y)
	{
		j = -1;
		while (++j < read->count_x)
		{
			if (j + 1 < read->count_x)
			{
				coord_for_brez_j(read, map, i, j);
				put_pixel(mlx, read->x1, read->y1, read);
				brezenham(mlx, read);
			}
			if (i + 1 < read->count_y)
			{
				coord_for_brez_i(read, map, i, j);
				brezenham(mlx, read);
			}
			put_pixel(mlx, read->x1, read->y1, read);
		}
	}
}

void	new_img(t_mllib *mlx, t_fdf *read)
{
	mlx->sl = 5;
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIDTH, HEIGHT, "FdF");
	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, WIDTH, HEIGHT);
	mlx->addr = mlx_get_data_addr(mlx->img_ptr, &mlx->bbp, &mlx->sl, &mlx->end);
	mlx_hook(mlx->win_ptr, 2, 0, deal_key, mlx);
	mlx_hook(mlx->win_ptr, 17, 0, red_cross, read);
	put_img(mlx, mlx->read);
	mlx_loop(mlx->mlx_ptr);
}
