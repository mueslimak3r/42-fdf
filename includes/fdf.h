/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calamber <calamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 17:28:33 by calamber          #+#    #+#             */
/*   Updated: 2019/07/01 18:31:26 by calamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/libft.h"
# include "mlx.h"
# include "keycode_mac.h"
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include <limits.h>

# define W_XSIZE ((int)1920)
# define W_YSIZE ((int)1080)
# define WHITE ((int)16777215)
# define SCALE ((double)-0.02)

typedef struct	s_mlxp
{
	void		*mlx;
	void		*win;
	void		*map;
}				t_mlxp;

typedef struct	s_vox
{
	double		x;
	double		y;
	double		z;
	int			c;
}				t_vox;

typedef struct	s_map
{
	t_vox		*v;
	int			rows;
	int			col;
	double		scale;
	double		tile;
}				t_map;

typedef struct	s_mlx_stuff
{
	t_mlxp		s;
	t_map		map;
	bool		v_flip;
	bool		h_flip;
}				t_mlx_stuff;

t_vox			g_rot_offset;
t_mlx_stuff		g_stuff;

int				create_map(t_map *map, char *mname);
void			update_window(void);
void			makehooks(t_mlxp *s);
void			mlx_destroy(t_mlxp *p);
int				newwindow(t_mlxp *s);
int				errorfunc(char *note, int v);
void			map_destroy(t_map *map);
void			draw_line(t_mlxp *p, t_vox a, t_vox b);
void			update_window(void);
t_vox			mlx_project(t_vox p);
#endif
