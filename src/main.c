#include "../includes/fdf.h"

int         errorfunc(char *note, int v)
{
    ft_printf("%s", note);
    return (v);
}

int		ft_lerpi(int first, int second, double p)
{
	if (first == second)
		return (first);
	return ((int)((double)first + (second - first) * p));
}

int		clerp(int c1, int c2, double p)
{
	int		r;
	int		g;
	int		b;

	// If the two colors passed are the same, then return the first color 
	// passed
	if (c1 == c2)
		return (c1);
	// c1(RED) = 1111 1111 0000 0000 0000 0000 / 0xFF0000
	// c2(WHITE) = 1111 1111 1111 1111 1111 1111 / 0xFFFFFF
	// manipulates red value of final color; this will return 255
	r = ft_lerpi((c1 >> 16) & 0xFF, (c2 >> 16) & 0xFF, p);
	// manipulates green
	g = ft_lerpi((c1 >> 8) & 0xFF, (c2 >> 8) & 0xFF, p);
	// manipulates blue
	b = ft_lerpi(c1 & 0xFF, c2 & 0xFF, p);
	// Further manipulates the RGB Values
	return (r << 16 | g << 8 | b);
}

int abs (int n) 
{ 
    return ( (n>0) ? n : ( n * (-1))); 
} 

//DDA Function for line generation 
void DDA(t_mlxp *s, t_vox *start, t_vox *end, int color) 
{ 
    // calculate dx & dy 
    int dx;
    float Xinc;
    int dy;
    float Yinc;
    // calculate steps required for generating pixels 
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
            mlx_pixel_put(s, s->win, start->x, start->y, color);//clerp(start->c, end->c, col_g)); //clerp(start->c, end->c, col_g));  // put pixel at (X,Y)
        start->x += Xinc;           // increment in x at each step
        start->y += Yinc;           // increment in y at each step
        i++;                     // generation step by step
    }
}

void mlx_draw_line(t_vox *a, t_vox *b, t_mlx_stuff *stuff)
{
    //b->z += (g_rot_offset.y + g_rot_offset.x) * 10;
    //a->z += (g_rot_offset.y + g_rot_offset.x) * 10;

    int startx = ((W_XSIZE / 2) - ((stuff->map.col / 2) * stuff->map.tile)) + ((int)a->x * stuff->map.tile);// + (a->z * g_rot_offset.x);
    int starty = ((W_YSIZE / 2) - ((stuff->map.rows / 2) * stuff->map.tile)) + ((int)a->y * stuff->map.tile);// + (a->z * g_rot_offset.y); 
    int endx = ((W_XSIZE / 2) - ((stuff->map.col / 2) * stuff->map.tile)) + ((int)b->x * stuff->map.tile);// + (b->z * g_rot_offset.x);
    int endy = ((W_YSIZE / 2) - ((stuff->map.rows / 2) * stuff->map.tile)) + ((int)b->y * stuff->map.tile);// + (b->z * g_rot_offset.y);
    t_vox start;
    t_vox end;
    start.x = (startx + (a->z < 0 || a->z > 0 ? a->z : -1) * g_rot_offset.x);// * ((a->x > (stuff->map.col / 2)) ? g_rot_offset.x : g_rot_offset.x / 2);//cos(g_rot_offset.y + start.y) * start.y + sin(g_rot_offset.x + start.x) * start.x;
    end.x = (endx + (b->z < 0 || b->z > 0 ? b->z : -1) * g_rot_offset.x);// * ((b->x > (stuff->map.col / 2)) ? g_rot_offset.x : g_rot_offset.x / 2);//cos(g_rot_offset.y + end.y) * end.y + sin(g_rot_offset.x + end.x) * end.x;
    start.y = (starty + (a->z < 0 || a->z > 0 ? a->z : -1) * g_rot_offset.y);// * ((a->y > (stuff->map.rows / 2)) ? g_rot_offset.y : g_rot_offset.y / 2);
    end.y = (endy + (b->z < 0 || b->z > 0 ? b->z : -1) * g_rot_offset.y);// * ((b->y > (stuff->map.rows / 2)) ? g_rot_offset.y : g_rot_offset.y / 2);
    start.c = a->c;
    end.c = b->c;
    start.c = (((int)a->z != 0 && (int)b->z == 0) || ((int)b->z != 0 && (int)a->z == 0)) ? 14358738 : a->c;
    DDA(&stuff->s, &start, &end, start.c);
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
    g_rot_offset.x = 0.2;
    g_rot_offset.y = 0.1;
    if (ac == 2)
    {
        if (!create_map(&g_stuff.map, av[1]))
            return (errorfunc("", 0));
        if (!newwindow(&g_stuff.s))
        {
            mlx_destroy(g_stuff.s.mlx);
            return (errorfunc("error: could not create mlx\n", 0));
        }
        update_window();
        makehooks(&g_stuff.s);
    }
    else
        return (errorfunc("usage: ./fdf map", 0));
    return (1);
}