#include "fdf.h"

void put_pixel(t_mllib *mlx, int x, int y, t_fdf *read)
{
	// int *b;
	// x += WIDTH / 2;
	// y += HEIGHT / 2;
	// b = (int*)mlx->addr;
	// int i = y * WIDTH + x;

	// if (x >= 0 && x < WIDTH && y < HEIGHT && y >= 0)
	// {
	// 	b[i] = read->clr ? read->clr : 0xEA03F7;
	// }
	char *b;
	x += WIDTH / 2;
	y += HEIGHT / 2;
	b = (char*)mlx->addr;
	int i = y * mlx->sl + x * mlx->bbp / 8;

	if (x >= 0 && x < WIDTH && y < HEIGHT && y >= 0)
	{
		b[i] = read->clr ? read->clr : 0xff;
		b[++i] = read->clr ? read->clr >> 8 : 0x7f;
		b[++i] = read->clr ? read->clr >> 16 : 0x50;
	}
}

void brezenham(t_mllib *mlx, t_fdf *read)
{
	int deltax;
	int deltay;
	int signx;
	int signy;
	int err;
	int deltaerr;

	deltax = ABS(read->x2 - read->x1);
	deltay = ABS(read->y2 - read->y1);
	signx = read->x1 < read->x2 ? 1 : -1;
	signy = read->y1 < read->y2 ? 1 : -1;
	err = deltax - deltay;
	while (read->x1 != read->x2 || read->y1 != read->y2)
	{
		put_pixel(mlx, read->x1, read->y1, read);
		deltaerr = err * 2;
		if (deltaerr > -deltay)
		{
			err -= deltay;
			read->x1 += signx;
		}
		if (deltaerr < deltax)
		{
			err += deltax;
			read->y1 += signy;
		}
	}
}

void put_lines(t_mllib *mlx, t_fdf *read, t_str **map)
{
	int i = -1;
	int j = -1;

	read->fl_put = 1;
	while (++i < read->count_y)
	{
		while (++j < read->count_x)
		{
			if (j + 1 < read->count_x)
			{
				read->x1 = map[i][j].x;
				read->x2 = map[i][j + 1].x;
				read->y1 = map[i][j].y;
				read->y2 = map[i][j + 1].y;
				read->clr = map[i][j].clr;
				brezenham(mlx, read);
			}
			if (i + 1 < read->count_y)
			{
				read->x1 = map[i][j].x;
				read->x2 = map[i + 1][j].x;
				read->y1 = map[i][j].y;
				read->y2 = map[i + 1][j].y;
				read->clr = map[i][j].clr;
				brezenham(mlx, read);
			}
		}
		j = -1;
	}
}

void new_img(t_mllib *mlx, t_fdf *read)
{
	mlx->sl = 5;
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIDTH, HEIGHT, "FdF");
	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, WIDTH, HEIGHT);
	mlx->addr = mlx_get_data_addr(mlx->img_ptr, &mlx->bbp, &mlx->sl, &mlx->end);
}
