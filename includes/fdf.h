/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 12:10:27 by gcollett          #+#    #+#             */
/*   Updated: 2017/08/05 02:36:42 by gcollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include "libft.h"

typedef struct	s_img
{
	int			sl;
	int			bpp;
	int			end;
	void		*img_addr;
	int			*dta;
}				t_img;

typedef struct	s_modif
{
	int			x_base;
	int			y_base;
	int			z_base;
	double		zoom;
	int			distance;
	int			width;
	int			height;
}				t_modif;

typedef struct	s_map
{
	void		*mlx;
	void		*win;
	int			**matrice;
	int			*len_line;
	int			len;
	char		*path;
	char		clr;
	t_img		img;
	t_modif		*modif;
}				t_map;

typedef struct	s_line
{
	long		x0;
	long		y0;
	long		x1;
	long		y1;
	int			j;
	int			i;
	int			dx;
	int			sx;
	int			dy;
	int			sy;
	int			err;
	int			e2;
	int			color;
}				t_line;

void			calcul_matrice(t_map *map, t_modif *modif);

#endif
