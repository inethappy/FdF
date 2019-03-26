# include <mlx.h>
#include "fdf.h"

// gcc -I /usr/local/include test.c -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit

int	p_error(char *s)
{
	ft_printf("%s\n", s);
	return (0);
}

int deal_key(int key, void *param)
{
	if (key == 53)
		exit(0);
	ft_putchar('X');
	return 0;
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

t_str *new_coord(t_fdf *read, char *content, int y)
{
	t_str *string;
	char **xy;
	string = (t_str*)malloc(sizeof(t_str) * read->count_x);
	int i = 0;

	xy = ft_strsplit(content, ' ');
	while (i < read->count_x)
	{
		// printf("%s ", xy[i]);
		string[i].x = i;
		string[i].y = y;
		string[i].z = ft_atoi(xy[i]);
		// printf("%d,%d,%d ", string[i].x, string[i].y, string[i].z);
		i++;
	}
	// printf("\n");
	ft_strdel(xy);
	return (string);
}

void read_map(t_fdf *read)
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
	i = 0;
	// ft_printf("%d\n", ft_words_counter(read->first->content, ' '));
	read->count_x = ft_words_counter(read->first->content, ' ');
	// ft_printf("read->count_y = %d\n", read->count_y);
	read->map = (t_str**)malloc(sizeof(t_str*) * read->count_y);
	while (read->first != NULL)//i < read->count_y)
	{
		read->map[i] = new_coord(read, read->first->content, i);
		read->first = read->first->next;
		i++;
	}
	// while (read->first != NULL)
	// {
	// 	ft_printf("%s\n", read->first->content);
	// 	read->first = read->first->next;
	// }
	// ft_printf("%d\n", read->count_y);

}

int main(int argc, char **argv)
{
	void *mlx_ptr;
	void *win_ptr;
	void *img_ptr;
	void *param;
	char *s;

	if (argc != 2)
		return (p_error("Nothing turns in!"));
	s = "Tru-la-la";
	t_fdf *read;
	read = malloc(sizeof(t_fdf));
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "mlx 42");
	mlx_pixel_put(mlx_ptr, win_ptr, 250, 250, 0xFFFFFF);
	mlx_key_hook(win_ptr, deal_key, (void *)0);
	// mlx_mouse_hook(win_ptr, deal_mouse, (void *)0)
	mlx_string_put(mlx_ptr, win_ptr, 10, 10, 0x00FFFF, s);
	img_ptr = mlx_new_image(mlx_ptr, 100, 100);
	mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 100, 100);
	read->fd = open(argv[1], O_RDONLY);
	read_map(read);
	mlx_loop(mlx_ptr);
}
