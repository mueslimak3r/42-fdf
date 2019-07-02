#include "../includes/fdf.h"

int         errorfunc(char *note, int v)
{
    ft_printf("%s", note);
    return (v);
}

int abs (int n) 
{ 
    return ( (n>0) ? n : ( n * (-1))); 
} 

void DDA(t_mlxp *s, t_vox *start, t_vox *end, int color) 
{ 
    int dx;
    float Xinc;
    int dy;
    float Yinc; 
    int steps;
    int i;
    dx = (int)end->x - (int)start->x;
    dy = (int)end->y - (int)start->y;
    steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);  
    Xinc = dx / (float) steps;
    Yinc = dy / (float) steps;
    i = 0;
    while(i <= steps) 
    {
        if (i > 0 && i < steps)
            mlx_pixel_put(s, s->win, start->x, start->y, color);
        start->x += Xinc;
        start->y += Yinc;
        i++;
    }
}

t_vox mlx_rotate(t_vox *a)
{
    t_vox t_a;
    t_vox *r;
    r = &g_rot_offset;
    t_a.x = (cos(r->y) * a->x + sin(r->y) * a->z);
    t_a.z = (-sin(r->y) * a->x + cos(r->y) * a->z);
    t_a.y = (cos(r->x) * a->y - sin(r->x) * t_a.z);
    t_a.z = (sin(r->x) * a->y + cos(r->x) * t_a.z);
    t_a.c = a->c;
    return (t_a);
}

t_vox mlx_project(t_vox p)
{
    t_vox t_a;
    p.x -= (g_stuff.map.col / 2);
    p.y -= (g_stuff.map.rows / 2);
    p.z *= SCALE;
    t_a = mlx_rotate(&p);
    t_a.x = (double)((W_XSIZE / 2)) + (t_a.x * g_stuff.map.tile);
    t_a.y = (double)((W_YSIZE / 2)) + (t_a.y * g_stuff.map.tile);
    return (t_a);
}

void mlx_draw_line(t_vox *a, t_vox *b, t_mlx_stuff *stuff)
{
    t_vox t_a;
    t_vox t_b;

    t_a = mlx_project(*a);
    t_b = mlx_project(*b);
    DDA(&stuff->s, &t_a, &t_b, (((int)a->z != 0 && (int)b->z == 0) || ((int)b->z != 0 && (int)a->z == 0)) ? 14358738 : a->c);
}

void draw_point(t_vox *v, int x, int y, t_mlx_stuff *stuff)
{
    t_vox *b;
    if ((int)v->x + 1 < (stuff->map.col))
    {
        b = &(stuff->map.v)[stuff->map.col * y + x + 1];
        mlx_draw_line(v, b, stuff);
    }
    if ((int)v->x - 1 >= 0)
    {
        b = &(stuff->map.v)[stuff->map.col * y + x - 1];
        mlx_draw_line(v, b, stuff);
    }
    if ((int)v->y + 1 < stuff->map.rows)
    {
        b = &(stuff->map.v)[stuff->map.col * (y + 1) + x];
        mlx_draw_line(v, b, stuff);
    }
    if ((int)v->y - 1 >= 0)
    {
        b = &(stuff->map.v)[stuff->map.col * (y - 1) + x];
        mlx_draw_line(v, b, stuff);
    }
}

void update_window(void)
{
    int y = 0;
    int x;
    while (g_stuff.map.v && y < g_stuff.map.rows)
    {
        x = 0;
        while (g_stuff.map.v && x < g_stuff.map.col)
        {
            t_vox *v = &g_stuff.map.v[g_stuff.map.col * y + x];
            draw_point(v, x, y, &g_stuff);
            x++;
        }
        y++;
    }
}

int main(int ac, char **av)
{
    g_rot_offset.x = 0.002;
    g_rot_offset.y = 0.002;
    if (ac == 2)
    {
        if (!create_map(&g_stuff.map, av[1]))
            return (errorfunc("error: map gen", 0));
        if (!newwindow(&g_stuff.s))
        {
            mlx_destroy(g_stuff.s.mlx);
            return (errorfunc("error: mlx init\n", 0));
        }
        update_window();
        makehooks(&g_stuff.s);
    }
    else
        return (errorfunc("usage: ./fdf map", 0));
    return (1);
}