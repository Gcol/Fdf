/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/05 02:09:27 by gcollett          #+#    #+#             */
/*   Updated: 2017/08/05 02:13:04 by gcollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>


#include <stdio.h>

int	ft_i_lower(int src, int src1, int max)
{
	if ((src > 0 && src < max) || (src1 > 0 && src1 < max))
		return (1);
	return (0);
}

void	line_init(t_line *pt, t_modif *md, t_map *map, int state)
{
	if (state == 1)
	{
		pt->color = map->matrice[pt->i][pt->j + 1] + map->matrice[pt->i][pt->j];
		pt->x1 = pt->x0 + md->distance - map->matrice[pt->i][pt->j + 1] * md->zoom ;
		pt->y1 = pt->y0 - map->matrice[pt->i][pt->j + 1] * md->zoom ;
	}
	else if (state == 2)
	{
		pt->color = map->matrice[pt->i][pt->j] + map->matrice[pt->i + 1][pt->j];
		pt->x1 = pt->x0 - map->matrice[pt->i + 1][pt->j] * md->zoom ;
		pt->y1 = pt->y0 + md->distance - map->matrice[pt->i + 1][pt->j] * md->zoom;
	}
	pt->x0 = pt->x0 - ((map->matrice[pt->i][pt->j]) * md->zoom);
	pt->y0 = pt->y0 - ((map->matrice[pt->i][pt->j]) * md->zoom);
	pt->dx = labs(pt->x1 - pt->x0);
	pt->sx = pt->x0 < pt->x1 ? 1 : -1;
	pt->dy = labs(pt->y1 - pt->y0);
	pt->sy = pt->y0 < pt->y1 ? 1 : -1;
	pt->err = (pt->dx > pt->dy ? pt->dx : -pt->dy) / 2;
	state = 0;
}


void	ft_line(t_map *map, t_modif *modif, t_line line, int state)
{
	line_init(&line, modif, map, state);
	state = 0;
	if ((ft_i_lower((line.x0 - line.y0),(line.x1 - line.y1), WIDTH)) &&
	(ft_i_lower((line.x0 + line.y0) / 2,(line.x1 - line.y1) / 2, HEIGHT)))
	while (1)
	{
		if ((((line.x0 - line.y0) > 0 && (line.x0 - line.y0) < WIDTH) &&
		(line.y0 + line.x0) > 0 && (line.y0 + line.x0) / 2 < HEIGHT) && (state = 1))
			map->img.dta[(line.x0 - line.y0) +
				(line.y0 + line.x0) / 2 * WIDTH] = line.color * map->modif->clr + map->modif->clr;
		else if(state == 1)
			state = 2;
		if ((line.x0 == line.x1 && line.y0 == line.y1 ) || state == 2)
			break ;
		line.e2 = line.err;
		if (line.e2 > -line.dx)
		{
			line.err -= line.dy;
			line.x0 += line.sx;
		}
		if (line.e2 < line.dy)
		{
			line.err += line.dx;
			line.y0 += line.sy;
		}
	}
}

void	calcul_matrice(t_map *map, t_modif *modif)
{
	t_line	line;

	line.i = -1;
	while (++line.i < map->len)
	{
		line.j = -1;
		while (++line.j < map->len_line[line.i])
		{
			line.y0 = line.i * modif->distance + modif->y_base;
			line.x0 = line.j * modif->distance + modif->x_base;
			if (line.j + 1 < map->len_line[line.i])
				ft_line(map, modif, line, 1);
			if (line.i + 1 < map->len && line.j < map->len_line[line.i + 1])
				ft_line(map, modif, line, 2);
		}
	}
}
