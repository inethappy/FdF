#include "fdf.h"

// gcc -I /usr/local/include test.c -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit

int	p_error(char *s)
{
	ft_printf("%s\n", s);
		system("leaks fdf > leaks");

	exit(0);
}

int red_cross(void *param)
{
	(void)param;
	exit(0);
	return (0);
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
			mlx->read->zoom_in = 1;
		mlx->read->zoom_out = 1;
		mlx->read->fl = 0;
		put_img(mlx, mlx->read);
	}
	if (key == 19)
	{
		mlx->read->zoom_in = 1;
		mlx->read->zoom_out = 1;
		mlx->read->fl = 1;
		put_img(mlx, mlx->read);
	}
	if (key == 20)
	{
		mlx->read->zoom_in = 1;
		mlx->read->zoom_out = 1;
		mlx->read->fl = 2;
		put_img(mlx, mlx->read);
	}
	if (key == 69 || key == 24)
	{
		mlx->read->zoom_in *= 2;
		put_img(mlx, mlx->read);
	}
	if (key == 78 || key == 27)
	{
		mlx->read->zoom_out *= 2;
		put_img(mlx, mlx->read);
	}
	return (0);
}

int ft_atoi_base(char *str, int base)
{
	int res;
	int i;

	res = 0;
	i = 0;
	if (str == NULL || str[0] == '\0' || base < 2 || base > 16)
		return (-1);
	while (str[i])
	{
		if (!ft_strchr("0123456789abcdefABCDEF", str[i]))
			return (-1);
		if (str[i] >= '0' && str[i] <= '9')
			res = res * base + str[i] - '0';
		if (str[i] >= 'A' && str[i] <= 'F')
			res = res * base + str[i] - 'A' + 10;
		if (str[i] >= 'a' && str[i] <= 'f')
			res = res * base + str[i] - 'a' + 10;
		i++;
	}
	return (res);
}

void d_free(t_str **new)
{
	int i;

	i = -1;
	while (new[++i])
		free(new[i]);
	free(new);
}

void put_img(t_mllib *mlx, t_fdf *read)
{
	t_str **new;
	if (read->fl_put == 1)
	{
		mlx_destroy_image(mlx->mlx_ptr, mlx->img_ptr);
		mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, WIDTH, HEIGHT);
		mlx->addr = mlx_get_data_addr(mlx->img_ptr, &mlx->bbp, &mlx->sl, &mlx->end);
	}
	if (read->fl == 0)
		new = usual(read);
		// put_lines(mlx, read, usual(read));
	else if (read->fl == 1)
		new = iso(read);
		// put_lines(mlx, read, iso(read));
	else if (read->fl == 2)
		new = perspective(read);
		// put_lines(mlx, read, perspective(read));
	// else if (read->fl == 3)
	// 	new =
	put_lines(mlx, read, new);
	d_free(new);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
}

int main(int argc, char **argv)
{
	t_mllib *mlx;
	if (argc != 2)
		return (p_error("Nothing turns in!"));
	mlx = ft_memalloc(sizeof(t_mllib));
	mlx->read = ft_memalloc(sizeof(t_fdf));
	mlx->read->zoom_in = 1;
	mlx->read->zoom_out = 1;
	mlx->read->fd = open(argv[1], O_RDONLY);
	save_map(mlx->read);
	new_img(mlx, mlx->read);
	return (0);
}
