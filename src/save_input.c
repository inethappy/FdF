#include "fdf.h"

t_list	*ft_lstnew_new(char *content, size_t content_size)
{
	t_list *new;

	if (!(new = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	if (content == NULL)
	{
		new->content = NULL;
		new->content_size = 0;
	}
	else
	{
		new->content_size = content_size;
		if (!(new->content = ft_strdup(content)))
		{
			free(new);
			return (NULL);
		}
	}
	new->next = NULL;
	return (new);
}

void	ft_lstadd_end(t_list **alst, t_list *new)
{
	t_list *list_ptr;

	list_ptr = *alst;
	while (list_ptr->next != NULL)
		list_ptr = list_ptr->next;
	list_ptr->next = new;
	new->next = NULL;
}

int check_str(char* str)
{
	int i;

	i = -1;
	while (str[++i] != '\0')
		if (str[i] != ' ' && !ft_isdigit(str[i]) && str[i] != '+' && str[i] != '-' && !ft_strrchr("ABCDEFabcdefx,", str[i]))
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
	string = ft_memalloc(sizeof(t_str) * read->count_x);
	if (check_str(content))
		return (NULL);
	xy = ft_strsplit(content, ' ');
	while (xy[i] && i < read->count_x)
	{
		string[i].x = (i - (read->count_x / 2)) * mt;
		string[i].y = (y - (read->count_y / 2)) * mt;;
		string[i].z = ft_atoi(xy[i]) * (mt / 3);
		if (ft_strrchr(xy[i], ','))
			string[i].clr = ft_atoi_base(ft_strrchr(xy[i], 'x') + 1, 16);
		else
			string[i].clr = string[i].z ? 0xFFbc33 : 0;
		// ft_printf("%d,%d,%d,%#X ", string[i].x, string[i].y, string[i].z, string[i].clr);
		i++;
	}
	// ft_printf("\n");
	if (/*xy[i] != NULL || */i < read->count_x)
		return (NULL);
	ft_strdel(xy);
	return (string);
}

void save_map(t_fdf *read)
{
	char *l;
	int i;
	t_list *list_ptr;

	read->count_y = 0;
	get_next_line(read->fd, &l);
	read->first = ft_lstnew_new(l, ft_strlen(l));
	list_ptr = read->first;
	while (++read->count_y && get_next_line(read->fd, &l))
		ft_lstadd_end(&list_ptr, ft_lstnew_new(l, ft_strlen(l)));
	i = -1;
	read->count_x = ft_words_counter(read->first->content, ' ');
	read->map = ft_memalloc(sizeof(t_str*) * read->count_y + 1);
	while (++i < read->count_y)
	{
		if (!(read->map[i] = new_coord(read, read->first->content, i)))
			p_error("Bad map!");
		read->first = read->first->next;
	}
	read->map[i] = NULL;
	iso(read);
	perspective(read);
}