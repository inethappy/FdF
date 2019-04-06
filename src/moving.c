#include "fdf.h"

void rotate(t_str **new, t_fdf *read)
{
	int i;
	int j;
	int buf;

	i = -1;
	while (++i < read->count_y)
	{
		j = -1;
		while (++j < read->count_x)
		{
			new[i][j].y = read->map[i][j].y * cos(read->turn_x) + read->map[i][j].z * sin(read->turn_x);
			new[i][j].z = -read->map[i][j].y * sin(read->turn_x) + read->map[i][j].z * cos(read->turn_x);
		}
	}
	i = -1;
	while (++i < read->count_y)
	{
		j = -1;
		while (++j < read->count_x)
		{
			new[i][j].x = new[i][j].x * cos(read->turn_y) + new[i][j].z * sin(read->turn_y);
			new[i][j].z = -new[i][j].x * sin(read->turn_y) + new[i][j].z * cos(read->turn_y);
		}
	}
	i = -1;
	// if (read->turn_z)
	// {
	// 	while (++i < read->count_y)
	// {
	// 	j = -1;
	// 	while (++j < read->count_x)
	// 	{
	// 		new[i][j].x = new[i][j].x * cos(read->turn_z) - new[i][j].y * sin(read->turn_z);
	// 		new[i][j].y = new[i][j].x * sin(read->turn_z) + new[i][j].z * cos(read->turn_z);
	// 	}
	// }
	// }
}

void zoom(t_str **new, t_fdf *read)
{
	int i;
	int j;

	i = -1;
	j = -1;
	while (++i < read->count_y)
	{
		while (++j < read->count_x)
		{
			new[i][j].x = new[i][j].x * read->zoom_in / read->zoom_out;
			new[i][j].y = new[i][j].y * read->zoom_in / read->zoom_out;
		}
		j = -1;
	}
}

void move(t_str **new, t_fdf *read)
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
