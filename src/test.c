#include <mlx.h>
#include <unistd.h>
#include <stdlib.h>

// gcc -I /usr/local/include test.c -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit

void ft_putchar(char c)
{
	write(1, &c, 1);
}

int deal_key(int key, void *param)
{
	if (key == 53)
		exit(0);
	ft_putchar('X');
	return 0;

}

int key_press(int keycode, void *param)
{
	(void)param;
    exit(0);
    return (0);
}

int main()
{
	void *mlx_ptr;
	void *win_ptr;
	void *img_ptr;
	void *param;
	char *s;

	s = "Tru-la-la";

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 500, 500, "mlx 42");
	mlx_pixel_put(mlx_ptr, win_ptr, 250, 250, 0xFFFFFF);
	mlx_key_hook(win_ptr, deal_key, (void *)0);
	mlx_string_put(mlx_ptr, win_ptr, 10, 10, 0x00FFFF, s);
	img_ptr = mlx_new_image(mlx_ptr, 100, 100);
	mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 100, 100);
	// mlx_hook(win_ptr, 2, 0, key_press(53, param), param);
	mlx_loop(mlx_ptr);
}
