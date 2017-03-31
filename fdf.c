/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/31 13:20:10 by gcollett          #+#    #+#             */
/*   Updated: 2017/03/31 17:42:17 by gcollett         ###   ########.fr       */
/*                    i                                                        */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include <stdio.h>



int *parsing_fdf(char *ligne, char *argv)
{
	char *save;
	int *matrice;

	int fd;
	int cmp;


	cmp = 1;
	fd = open(argv, O_RDONLY);
	save = ft_memalloc(BUFF_SIZE + 1);
	while(read(fd,save,BUFF_SIZE))
		if ((ligne = ft_strjoin_free(ligne,save)))
			save = ft_memalloc(BUFF_SIZE + 1);
	matrice = malloc(ft_strlen(save));
	while((*save++))
		if (*save != '\t' || *save != ' ')
		{
			if (ft_atoi(save))
			{
				*matrice++ = ft_atoi(save);
				*(save) = *(save + ft_intlen(*(matrice - 1)));
			}
		}
	return (matrice);
}

int escape(int keycode, char *param)
{
	param = 0;
	if (keycode == 53)
		exit(0);
	return (0);
}

int main(int argc, char **argv)
{
	int *matrice;
	int x;
	int y;
	int z;
	int cmp;

	x = 10;
	y = 10;
		cmp = 0;
	z = 0;
	if (argc == 2)
	{
		matrice = parsing_fdf("", argv[1]);
		while(matrice[cmp++])
			printf("%d\n",matrice[cmp]);
	}
	else 
		write(2,"Usage : ./fdf <filename> [ case_size z_size ]\n",46);
	return (0);
}
