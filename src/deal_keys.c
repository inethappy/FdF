#include "fdf.h"

int	p_error(char *s)
{
	ft_printf("%s\n", s);
	exit(0);
}

int red_cross(void *param)
{
	(void)param;
	exit(0);
	return (0);
}

void freshing_flags(t_fdf *read)
{
		read->mv_x = 0;
		read->mv_y = 0;
		read->zoom_in = 1;
		read->zoom_out = 1;
		read->turn_x = 0.0;
		read->turn_y = 0.0;
		read->turn_z = 0.0;
}

void other_keys(int key, t_mllib *mlx)
{
	if (key == 123 || key == 124)
	{
		mlx->read->mv_x += (key == 123) ? -10 : 10;
		put_img(mlx, mlx->read);
	}
	if (key == 126 || key == 125)
	{
		mlx->read->mv_y += (key == 126) ? -10 : 10;
		put_img(mlx, mlx->read);
	}
	if (key == 91 || key == 84)
	{
		mlx->read->turn_x += (key == 91) ? -0.05 : 0.05;
		put_img(mlx, mlx->read);
	}
	if (key == 86 || key == 88)
	{
		mlx->read->turn_y += (key == 86) ? -0.05 : 0.05;
		put_img(mlx, mlx->read);
	}
	if (key == 89 || key == 85)
	{
		mlx->read->turn_z += (key == 89) ? -0.05 : 0.05;
		put_img(mlx, mlx->read);
	}
}

int deal_key(int key, t_mllib *mlx)
{
	if (key == 53)
	{
		system("leaks fdf > leaks");
		exit(0);
	}
	if (key == 18)
	{
		freshing_flags(mlx->read);
		mlx->read->fl = 0;
		put_img(mlx, mlx->read);
	}
	if (key == 19 || key == 20)
	{
		freshing_flags(mlx->read);
		mlx->read->fl = (key == 19) ? 1 : 2;
		put_img(mlx, mlx->read);
	}
	if (key == 69 || key == 24 || key == 78 || key == 27)
	{
		mlx->read->zoom_in *= (key == 69 || key == 24) ? 2 : 1;
		mlx->read->zoom_out *= (key == 78 || key == 27) ? 2 : 1;
		put_img(mlx, mlx->read);
	}
	other_keys(key, mlx);
	return (0);
}
