#include "../includes/fdf.h"

void    update_window(t_mlxp *s, int c)
{
    int y = 0;
    int x;
    while (y <= W_YSIZE)
    {
        x = 0;
        while (x <= W_XSIZE)
        {
            mlx_pixel_put(s->mlx, s->win, x, y, c);
            x++;
        }
        y++;
    }
}

void	mlx_destroy(t_mlxp *p)
{
	if (p->win)
		mlx_destroy_window(p->mlx, p->win);
	exit(0);
}

static int	fdf_key_hook(int key, t_mlxp *p)
{
	if (key == 53)
		mlx_destroy(p);
    else if (key == 123)
        update_window(p, (0 << 16) | (0 << 8) | (0));
    else if (key == 124)
        update_window(p, (255 << 16) | (255 << 8) | (255));
	return (0);
}

int         errorfunc(char *note, int v)
{
    ft_printf("%s", note);
    return (v);
}

int     newwindow(t_mlxp *s)
{
    ft_memset(s, 0, sizeof(t_mlxp));
    if (!(s->mlx = mlx_init()) ||
		!(s->win = mlx_new_window(s->mlx, W_XSIZE, W_YSIZE, "fdf")))
	{
        if (s->win)
		    mlx_destroy_window(s->mlx, s->win);
		return (errorfunc("fdf: mlx window make fail", -1));
	}
    return (0);
}

void    makehooks(t_mlxp *s)
{
    mlx_hook(s->win, 2, 5, fdf_key_hook, s);
	mlx_string_put(s->mlx, s->win, 10, W_YSIZE - 30, K_WHITE, "ESC: exit");
    mlx_loop(s->mlx);
}



int main(void)
{
    t_mlxp  s;
    if (newwindow(&s) == -1)
    {
        mlx_destroy(s.mlx);
			return (errorfunc("main.c:main\tcould not create mlx", -1));
    }
    update_window(&s, (255 << 16) | (255 << 8) | (255));
    makehooks(&s);
    return (0);
}