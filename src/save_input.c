#include "fdf.h"

void	ft_lstadd_end(t_list *alst, t_list *new)
{
	t_list *list_ptr;

	list_ptr = alst;
	while (list_ptr->next != NULL)
		list_ptr = list_ptr->next;
	list_ptr->next = new;
}

int check_str(char* str, t_fdf *read)
{
	int i;

	i = -1;
	while (str[++i] != '\0')
		if (str[i] != ' ' && !ft_isdigit(str[i]) && str[i] != '+'
			&& str[i] != '-' && !ft_strrchr("ABCDEFabcdefx,", str[i]))
			return (1);
	return (0);
}

t_str *new_coord(t_fdf *read, char *content, int y)
{
	t_str *string;
	int mt;
	char **xy;
	int i = 0;

	mt = (read->count_x > read->count_y) ? ((WIDTH / read->count_x) / 2) : ((HEIGHT / read->count_y) / 2);
	if (check_str(content, read))
		return (NULL);
	string = ft_memalloc(sizeof(t_str) * read->count_x);
	xy = ft_strsplit(content, ' ');
	while (xy[i] && i < read->count_x)
	{
		string[i].x = (i - (read->count_x / 2)) * mt;
		string[i].y = (y - (read->count_y / 2)) * mt;;
		string[i].z = ft_atoi(xy[i]) * mt / 2;
		if (ft_strrchr(xy[i], ','))
			string[i].clr = ft_atoi_base(ft_strrchr(xy[i], 'x') + 1, 16);
		else
			string[i].clr = string[i].z ? 0xFFbc33 : 0;
		// ft_printf("%d,%d,%d,%#X ", string[i].x, string[i].y, string[i].z, string[i].clr);
		i++;
	}
	int j = -1;
	while (xy[++j])
		free(xy[j]);
	free(xy);
	// ft_printf("\n");
	if (/*xy[i] != NULL || */i < read->count_x)
		return (NULL);
	return (string);
}

void save_map(t_fdf *read)
{
	int i;

	i = -1;
	read->count_x = ft_words_counter(read->first->content, ' ');
	preparing(read);
	while (++i < read->count_y)
	{
		if (!(read->map[i] = new_coord(read, read->first->content, i)))
			p_error("Bad map!");
		read->first = read->first->next;
	}
	read->map[i] = NULL;
}
