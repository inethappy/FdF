# include <mlx.h>
#include "fdf.h"

// gcc -I /usr/local/include test.c -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit

int	p_error(char *s)
{
	ft_printf("%s\n", s);
	exit(0);
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

int ft_atoi_base(char *str, int base)
{
	int res;
	int i;

	res = 0;
	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			res = (res * base - '0');
		else if (str[i] >= 'A' && str[i] <= 'F')
			res = res * base - 'A' + 10 - '0'; //value_tmp % base + x - 10;
		else if (str[i] > 'a' && str[i] < 'f')
			res = res * base - str[i] + 10;
		i++;
	}
	return (res);
}

int check_str(char* str)
{
	int i;

	i = -1;
	while (str[++i] != '\0')
		if (str[i] != ' ' && !ft_isdigit(str[i]) && str[i] != '+' && str[i] != '-')
			return (1);
	return (0);
}

t_str *new_coord(t_fdf *read, char *content, int y)
{
	t_str *string;
	char **xy;
	string = ft_memalloc(sizeof(t_str) * read->count_x);
	int i = 0;
	if (check_str(content))
		return (NULL);
	xy = ft_strsplit(content, ' ');
	while (i < read->count_x)
	{
		string[i].x = i;
		string[i].y = y;
		string[i].z = ft_atoi(xy[i]);
		if (ft_strrchr(xy[i], 'x'))
			string[i].clr = ft_atoi_base(xy[i], 16);
		// ft_printf("%d,%d,%d,%#x ", string[i].x, string[i].y, string[i].z, string[i].clr);
		i++;
	}
	// printf("\n");
	if (++i < read->count_x || xy[++i] != NULL)
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
	// ft_printf("%d\n", ft_words_counter(read->first->content, ' '));
	read->count_x = ft_words_counter(read->first->content, ' ');
	// ft_printf("read->count_y = %d\n", read->count_y);
	read->map = ft_memalloc(sizeof(t_str*) * read->count_y);
	while (++i < read->count_y)
	{
		if (!(read->map[i] = new_coord(read, read->first->content, i)))
			p_error("Bad map!");
		read->first = read->first->next;
	}

	// while (read->first != NULL)
	// {
	// 	ft_printf("%s\n", read->first->content);
	// 	read->first = read->first->next;
	// }
	// ft_printf("%d\n", read->count_y);
}

void put_pixel(t_mllib *mlx, int x, int y)
{
	int *b;
	b = (int*)mlx->addr;
	int i = 0;

	while (i< 100)
	{
		b[i*y + x] = 0xFFFFFF;
		i += 1;
	}
}

void new_img(t_mllib *mlx, t_fdf *read)
{
	mlx->sl = 5;
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIDTH, HEIGHT, "FdF");
	mlx_key_hook(mlx->win_ptr, deal_key, (void *)0);
	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, WIDTH, HEIGHT);

	mlx->addr = mlx_get_data_addr(mlx->img_ptr, &mlx->bbp, &mlx->sl, &mlx->end);
	int i = -1;
	int j = -1;
	while (++i < read->count_y)
	{
		while (++j < read->count_x)
			put_pixel(mlx, read->map[i][j].x, read->map[i][j].y);
		j = -1;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
	mlx_loop(mlx->mlx_ptr);
}

int main(int argc, char **argv)
{
	t_fdf *read;
	t_mllib *mlx;
	if (argc != 2)
		return (p_error("Nothing turns in!"));
	read = ft_memalloc(sizeof(t_fdf));
	mlx = ft_memalloc(sizeof(t_mllib));
	read->fd = open(argv[1], O_RDONLY);
	save_map(read);
	new_img(mlx, read);
}

// void *mlx_ptr;
// 	void *win_ptr;
// 	void *img_ptr;
// 	void *param;
// 	char *s;

// 	if (argc != 2)
// 		return (p_error("Nothing turns in!"));
// 	s = "Tru-la-la";
// 	t_fdf *read;
// 	read = malloc(sizeof(t_fdf));
// 	mlx_ptr = mlx_init();
// 	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "FdF");
// 	// mlx_pixel_put(mlx_ptr, win_ptr, 250, 250, 0xFFFFFF);
// 	mlx_key_hook(win_ptr, deal_key, (void *)0);
// 	// mlx_mouse_hook(win_ptr, deal_mouse, (void *)0)
// 	// mlx_string_put(mlx_ptr, win_ptr, 10, 10, 0x00FFFF, s);
// 	img_ptr = mlx_new_image(mlx_ptr, 100, 100);
// 	mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 100, 100);
// 	read->fd = open(argv[1], O_RDONLY);
// 	read_map(read);
// 	mlx_loop(mlx_ptr);
// }
