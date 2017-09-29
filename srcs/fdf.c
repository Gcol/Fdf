/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 13:20:10 by gcollett          #+#    #+#             */
/*   Updated: 2017/09/29 19:25:12 by gcollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	parsing_fdf(char *ligne, char *argv, t_map *map, int len)
{
	char	**save;
	int		fd;
	int		i;
	int		cnt;

	cnt = -1;
	map->matrice = ft_memalloc_exit(sizeof(int *) * len + 1);
	map->len_line = ft_memalloc_exit(sizeof(int) * len);
	map->len = len;
	fd = open(argv, O_RDONLY);
	len = 0;
	while (get_next_line(fd, &ligne))
	{
		len = 0;
		save = ft_strsplit(ligne, ' ');
		while (save[len])
			len++;
		map->matrice[++cnt] = ft_memalloc_exit((sizeof(int)) * len);
		i = -1;
		while (save[++i])
			map->matrice[cnt][i] = ft_atoi(save[i]);
		map->len_line[cnt] = i;
		free(save);
	}
	close(fd);
}

void	re_trace(t_map *map, int reset)
{
	if (reset)
	{
		map->modif->x_base = 400;
		map->modif->y_base = 0;
		map->modif->distance = 10;
		map->modif->zoom = 0.1;
	}
	ft_bzero(map->img.dta, WIDTH * HEIGHT * 4);
	calcul_matrice(map, map->modif);
	mlx_put_image_to_window(map->mlx, map->win, map->img.img_addr, 0, 0);
	mlx_string_put(map->mlx, map->win, 15, 15, 0xffffff, map->path);
}

int		pressed_key(int keycode, t_map *map)
{
	if (keycode == 53)
		exit(0);
	if ((keycode >= 123 && keycode <= 126) || keycode == 69 ||
	keycode == 78 || keycode == 13 || keycode == 1 || keycode == 15)
	{
		if (keycode == 1 || keycode == 13)
			map->modif->zoom += (0.1 * ((keycode == 1) ? -1 : 1 ));
		else if (keycode == 69 || keycode == 78)
			map->modif->distance += (1 * ((keycode == 78) ? -1 : 1 ));
		else if (keycode == 126 || keycode == 125)
			map->modif->y_base += (20 * ((keycode == 125) ? -1 : 1 ));
		else if (keycode == 124 || keycode == 123)
			map->modif->x_base += (20 * ((keycode == 123) ? -1 : 1 ));
		if (keycode != 15)
			re_trace(map, 0);
		else
			re_trace(map, 1);
	}
	return (0);
}

void	create_win(char *argv, int cnt)
{
	t_map	*map;

	map = ft_memalloc_exit(sizeof(t_map));
	map->modif = ft_memalloc_exit(sizeof(t_modif));
	map->path = argv;
	map->modif->distance = 10;
	map->modif->x_base = 400;
	map->modif->zoom = 0.1;
	map->mlx = mlx_init();
	map->win = mlx_new_window(map->mlx, WIDTH, HEIGHT, argv);
	map->img.img_addr = mlx_new_image(map->mlx, WIDTH, HEIGHT);
	map->img.dta = (int *)mlx_get_data_addr(map->img.img_addr,
			&map->img.bpp, &map->img.sl, &map->img.end);
	parsing_fdf("", argv, map, cnt);
	calcul_matrice(map, map->modif);
	if (HEIGHT > 0 && WIDTH > 0)
	{
		mlx_put_image_to_window(map->mlx, map->win, map->img.img_addr, 0, 0);
		mlx_string_put(map->mlx, map->win, 15, 15, 0xffffff, argv);
		mlx_hook(map->win, 2, (1L << 0), &pressed_key, map);
		mlx_loop(map->mlx);
	}
}

int		main(int argc, char **argv)
{
	int		fd;
	int		cnt;
	char	*ligne;

	if (argc == 2)
	{
		cnt = 0;
		fd = open(argv[1], O_RDONLY);
		while (get_next_line(fd, &ligne))
			cnt++;
		close(fd);
		create_win(argv[1], cnt);
	}
	else
		write(2, "Usage : ./fdf <filename>\n", 25);
	return (0);
}
