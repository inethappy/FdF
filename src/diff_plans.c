#include "fdf.h"

t_str **usual(t_fdf *read)
{
	int i;
	int j;
	t_str **new;

	i = -1;
	j = -1;
	new = ft_memalloc(sizeof(t_str*) * read->count_y + 1);
	while (++i < read->count_y)
	{
		new[i] = ft_memalloc(sizeof(t_str) * read->count_x);
		while (++j < read->count_x)
		{
			new[i][j].x = read->map[i][j].x * read->zoom_in / read->zoom_out;
			new[i][j].y = read->map[i][j].y * read->zoom_in / read->zoom_out;
			new[i][j].clr = read->map[i][j].clr;
		}
		j = -1;
	}
	new[i] = NULL;
	return (new);
}

t_str **iso(t_fdf *read)
{
	int i;
	int j;
	int mt;

	mt = 1;
	i = -1;
	j = -1;
	// printf("%d\n", read->fl_put);
	read->map_iso = ft_memalloc(sizeof(t_str*) * read->count_y + 1);
	while (++i < read->count_y)
	{
		read->map_iso[i] = ft_memalloc(sizeof(t_str) * read->count_x);
		while (++j < read->count_x)
		{
			read->map_iso[i][j].x = (((read->map[i][j].x - read->map[i][j].y) * cos(0.223599)) / mt) * read->zoom_in / read->zoom_out;
			read->map_iso[i][j].y = ((-read->map[i][j].z + (read->map[i][j].x + read->map[i][j].y) * sin(0.223599)) / mt) * read->zoom_in / read->zoom_out;
			read->map_iso[i][j].clr = read->map[i][j].clr;
			if ((ABS(read->map_iso[i][j].x) > (WIDTH / 2) || ABS(read->map_iso[i][j].y) > (HEIGHT / 2)) && read->zoom_in == 1)
			{
				mt *= 2;
				i = 0;
				j = -1;
			}
		}
		j = -1;
	}
	read->map_iso[i] = NULL;
	return (read->map_iso);
}

t_str **perspective(t_fdf *read)
{
	int i;
	int j;
	double dst;

	dst = WIDTH / 1.5 * -1;
	read->map_per = ft_memalloc(sizeof(t_str*) * read->count_y + 1);
	i = -1;
	while (++i < read->count_y)
	{
		j = -1;
		read->map_per[i] = ft_memalloc(sizeof(t_str) * read->count_x);
		while (++j < read->count_x)
		{
			if (read->map[i][j].z != dst)
			{
				read->map_per[i][j].x = read->map[i][j].x / (1 + read->map[i][j].z / dst) * read->zoom_in / read->zoom_out;;
				read->map_per[i][j].y = read->map[i][j].y / (1 + read->map[i][j].z / dst) * read->zoom_in / read->zoom_out;;
				read->map_per[i][j].clr = read->map[i][j].clr;
				if ((ABS(read->map_per[i][j].x) > (WIDTH / 2) || ABS(read->map_per[i][j].y) > (HEIGHT / 2)) && read->zoom_in == 1)
				{
					dst /= 1.8;
					i = 0;
					j = -1;
				}
			}
		}
	}
	read->map_per[i] = NULL;
	return (read->map_per);
}
