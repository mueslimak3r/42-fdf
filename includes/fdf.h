#ifndef FDF_H
# define FDF_H

# include "../libft/libft.h"
# include "mlx.h"
# include <unistd.h>
# include <math.h>

# define W_XSIZE ((int)800)
# define W_YSIZE ((int)600)
# define X_ORI ((int)(K_W / 2))
# define Y_ORI ((int)(K_H / 2))
# define K_WHITE ((int)16777215)
# define K_SCALE ((double)1.5)

typedef struct      s_mlxp
{
	void		    *mlx;
	void		    *win;
	void		    *map;
}                   t_mlxp;

#endif