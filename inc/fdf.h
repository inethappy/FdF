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
# include <fcntl.h>
# define ABS(Value) (((Value) < 0) ? -(Value) : (Value))

typedef struct s_str
{
	int x;
	int y;
	int z;
	// struct s_str *next;
}				t_str;

typedef	struct s_fdf
{
	int fd;
	int count_y;
	t_list *first;
	t_str **map;
}				t_fdf;


#endif
