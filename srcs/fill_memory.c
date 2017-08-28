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

void	line_init(t_line *pt, t_modif *md, t_map *map, int state)
{
	if (state == 1)
	{
		state = md->zoom * md->distance;
		pt->color = (map->matrice[pt->i][pt->j + 1] ||
			map->matrice[pt->i][pt->j]) ? 0x00FF00 : 0xFF0000;
		pt->x1 = pt->x0 + md->distance - map->matrice[pt->i][pt->j + 1] * state;
		pt->y1 = pt->y0 - map->matrice[pt->i][pt->j + 1] * state;
		pt->x0 = pt->x0 - ((map->matrice[pt->i][pt->j]) * state);
		pt->y0 = pt->y0 - ((map->matrice[pt->i][pt->j]) * state);
	}
	else if (state == 2)
	{
		state = md->zoom * md->distance;
		pt->color = (map->matrice[pt->i][pt->j] ||
			map->matrice[pt->i + 1][pt->j]) ? 0x00FF00 : 0xFF0000;
		pt->x1 = pt->x0 - map->matrice[pt->i + 1][pt->j] * state;
		pt->y1 = pt->y0 + md->distance - map->matrice[pt->i + 1][pt->j] * state;
		pt->x0 = pt->x0 - ((map->matrice[pt->i][pt->j]) * state);
		pt->y0 = pt->y0 - ((map->matrice[pt->i][pt->j]) * state);
	}
	pt->dx = labs(pt->x1 - pt->x0);
	pt->sx = pt->x0 < pt->x1 ? 1 : -1;
	pt->dy = labs(pt->y1 - pt->y0);
	pt->sy = pt->y0 < pt->y1 ? 1 : -1;
	pt->err = (pt->dx > pt->dy ? pt->dx : -pt->dy) / 2;
}

void	ft_line(t_map *map, t_modif *modif, t_line line, int state)
{
	line_init(&line, modif, map, state);
	while (1)
	{
		if ((((line.x0 - line.y0) > 0 && (line.x0 - line.y0) < modif->width) &&
		(line.y0 + line.x0) > 0 && (line.y0 + line.x0) / 2 < modif->height))
			map->img.dta[(line.x0 - line.y0) +
				(line.y0 + line.x0) / 2 * modif->width] = line.color;
		if (line.x0 == line.x1 && line.y0 == line.y1)
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
	int		i;
	int		j;

	i = -1;
	while (++i < map->len)
	{
		j = -1;
		while (++j < map->len_line[i])
		{
			line.i = i;
			line.j = j;
			line.y0 = i * modif->distance + modif->y_base;
			line.x0 = j * modif->distance + modif->x_base;
			if (j + 1 < map->len_line[i])
				ft_line(map, modif, line, 1);
			if (i + 1 < map->len && j < map->len_line[i + 1])
				ft_line(map, modif, line, 2);
		}
	}
}
