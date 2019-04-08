/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkotytsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 12:04:07 by mkotytsk          #+#    #+#             */
/*   Updated: 2019/04/08 12:04:10 by mkotytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		ft_atoi_base(char *str, int base)
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

void	put_img(t_mllib *mlx, t_fdf *read)
{
	t_str **new;

	if (read->fl_put == 1)
	{
		mlx_destroy_image(mlx->mlx_ptr, mlx->img_ptr);
		mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, WIDTH, HEIGHT);
		mlx->addr =
			mlx_get_data_addr(mlx->img_ptr, &mlx->bbp, &mlx->sl, &mlx->end);
	}
	if (read->fl == 0)
		new = usual(read);
	else if (read->fl == 1)
		new = iso(read);
	else if (read->fl == 2)
		new = perspective(read);
	if (mlx->read->mv_x || mlx->read->mv_y)
		move(new, read);
	if (read->zoom_in > 1)
		zoom_in(new, read);
	if (read->zoom_out > 1)
		zoom_out(new, read);
	put_lines(mlx, read, new);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
}

void	preparing(t_fdf *read)
{
	int i;

	read->zoom_in = 1;
	read->zoom_out = 1;
	read->map = ft_memalloc(sizeof(t_str*) * read->count_y + 1);
	read->map_us = ft_memalloc(sizeof(t_str*) * read->count_y + 1);
	read->map_iso = ft_memalloc(sizeof(t_str*) * read->count_y + 1);
	read->map_per = ft_memalloc(sizeof(t_str*) * read->count_y + 1);
	i = -1;
	while (++i < read->count_y)
	{
		read->map_us[i] = ft_memalloc(sizeof(t_str) * read->count_x);
		read->map_iso[i] = ft_memalloc(sizeof(t_str) * read->count_x);
		read->map_per[i] = ft_memalloc(sizeof(t_str) * read->count_x);
	}
	read->map_us[i] = NULL;
	read->map_iso[i] = NULL;
	read->map_per[i] = NULL;
}

void	welcome(int argc, char **argv, t_mllib *mlx)
{
	if (argc == 1)
		p_error("Usage: ./fdf map");
	if (argc > 2)
		p_error("Only 1 map please!");
	if ((mlx->read->fd = open(argv[1], O_DIRECTORY)) > 0)
		p_error("You are trying to open folder, not map file!");
	if ((mlx->read->fd = open(argv[1], O_RDONLY)) < 0)
		p_error("Wrong name of file!");
}

int		main(int argc, char **argv)
{
	char	*l;
	t_mllib	*mlx;

	mlx = ft_memalloc(sizeof(t_mllib));
	mlx->read = ft_memalloc(sizeof(t_fdf));
	welcome(argc, argv, mlx);
	mlx->read->count_y = 0;
	if (!(get_next_line(mlx->read->fd, &l) && ++mlx->read->count_y))
		return (p_error("Empty map!"));
	mlx->read->first = ft_lstnew(l, ft_strlen(l));
	free(l);
	while (get_next_line(mlx->read->fd, &l) && ++mlx->read->count_y)
	{
		ft_lstadd_end(mlx->read->first, ft_lstnew(l, ft_strlen(l)));
		free(l);
	}
	save_map(mlx->read);
	new_img(mlx, mlx->read);
	return (0);
}
