/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkotytsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 12:05:01 by mkotytsk          #+#    #+#             */
/*   Updated: 2019/04/08 12:05:03 by mkotytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_lstadd_end(t_list *alst, t_list *new)
{
	t_list *list_ptr;

	list_ptr = alst;
	while (list_ptr->next != NULL)
		list_ptr = list_ptr->next;
	list_ptr->next = new;
}

int		check_str(char *str, t_fdf *read)
{
	int i;

	i = -1;
	while (str[++i] != '\0')
		if (str[i] != ' ' && !ft_isdigit(str[i]) && str[i] != '+'
			&& str[i] != '-' && !ft_strrchr("ABCDEFabcdefx,", str[i]))
			return (1);
	return (0);
}

int		check_xy(char *xy)
{
	int i;
	int j;
	int c;

	i = -1;
	c = 0;
	while (++i < 10)
		if (ft_strchr(xy, (i + '0')))
			c++;
	if (c == 0)
		return (0);
	return (1);
}

t_str	*new_coord(t_fdf *read, char **xy, int y)
{
	t_str	*string;
	int		i;

	i = -1;
	string = ft_memalloc(sizeof(t_str) * read->count_x);
	while (xy[++i] && i < read->count_x)
	{
		if (!check_xy(xy[i]))
		{
			free(string);
			return (NULL);
		}
		string[i].x = (i - (read->count_x / 2)) * read->mt;
		string[i].y = (y - (read->count_y / 2)) * read->mt;
		string[i].z = ft_atoi(xy[i]) * read->mt / 2;
		if (ft_strrchr(xy[i], ','))
			string[i].clr = ft_atoi_base(ft_strrchr(xy[i], 'x') + 1, 16);
		else
			string[i].clr = string[i].z ? 0xFFbc33 : 0;
	}
	if (i < read->count_x)
		free(string);
	return ((i < read->count_x) ? NULL : string);
}

void	save_map(t_fdf *read)
{
	int		i;
	char	**xy;

	i = -1;
	read->count_x = ft_words_counter(read->first->content, ' ');
	read->mt = (read->count_x > read->count_y)
		? ((WIDTH / read->count_x) / 2) : ((HEIGHT / read->count_y) / 2);
	preparing(read);
	while (++i < read->count_y)
	{
		xy = ft_strsplit(read->first->content, ' ');
		if (check_str(read->first->content, read))
			p_error("Bad map!");
		read->map[i] = new_coord(read, xy, i);
		double_del(xy);
		if (read->map[i] == NULL)
			p_error("Bad map!");
		if (read->first->next)
			read->first = read->first->next;
	}
	read->map[i] = NULL;
}
