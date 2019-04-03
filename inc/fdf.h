/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkotytsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/23 12:52:05 by mkotytsk          #+#    #+#             */
/*   Updated: 2019/03/23 12:52:07 by mkotytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "ft_printf.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <mlx.h>
# include <math.h>
# include <fcntl.h>
# define ABS(Value) (((Value) < 0) ? -(Value) : (Value))
# define WIDTH 1200
# define HEIGHT 1200
# define SGN ((a) < 0) ? -1 : 1);

typedef struct s_str
{
	int x;
	int y;
	int z;
	int clr;
}				t_str;

typedef	struct s_fdf
{
	int fd;
	int count_y;
	int count_x;
	int fl;
	int fl_put;
	int x1;
	int y1;
	int x2;
	int y2;
	int clr;
	t_list *first;
	t_str **map;
	t_str **map_iso;
	t_str **map_per;
}				t_fdf;

typedef	struct s_mllib
{
	void *mlx_ptr;
	void *win_ptr;
	void *img_ptr;
	void *param;
	char *addr;
	int bbp;
	int sl;
	int end;
	t_fdf *read;

}				t_mllib;



t_list	*ft_lstnew_new(char *content, size_t content_size);
void	ft_lstadd_end(t_list **alst, t_list *new);
int check_str(char* str);
t_str *new_coord(t_fdf *read, char *content, int y);
void save_map(t_fdf *read);
int ft_atoi_base(char *str, int base);
int	p_error(char *s);
void put_pixel(t_mllib *mlx, int x, int y, t_fdf *read);
void iso(t_fdf *read);
void brezenham(t_mllib *mlx, t_fdf *read);
void new_img(t_mllib *mlx, t_fdf *read);
int deal_key(int key, t_mllib *mlx);
void put_img(t_mllib *mlx, t_fdf *read);
int red_cross(void *param);
void put_lines(t_mllib *mlx, t_fdf *read, t_str **map);
void key_init(t_mllib *mlx);
void perspective(t_fdf *read);



#endif
