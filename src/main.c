/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calamber <calamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 17:42:11 by calamber          #+#    #+#             */
/*   Updated: 2019/07/03 22:14:48 by calamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int		errorfunc(char *note, int v)
{
	ft_printf("%s", note);
	return (v);
}

int		init()
{
	if (!newwindow(&g_stuff.s) || 
			(g_stuff.image = new_image(g_stuff.s.mlx)) == NULL) 
	{	// Pass MLX into it's delete function which deletes everything created
		// in memory
        mlxdel();
		return (0);
    }
	return (1);
}

int		main(int ac, char **av)
{
	g_rot_offset.x = 0.002;
	g_rot_offset.y = 0.002;
	if (ac == 2)
	{
		if (!create_map(&g_stuff.map, av[1]))
			return (errorfunc("error: map gen", 0));
		if (!init())
		{
			return (errorfunc("error: mlx init\n", 0));
		}
		update_window();
		makehooks(&g_stuff.s);
	}
	else
		return (errorfunc("usage: ./fdf map", 0));
	return (1);
}
