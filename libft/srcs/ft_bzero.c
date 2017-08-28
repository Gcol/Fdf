/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 12:07:19 by gcollett          #+#    #+#             */
/*   Updated: 2016/11/08 09:48:52 by gcollett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_bzero(void *s, size_t n)
{
	unsigned char	*a;
	unsigned long	*lp;

	if (n == 0)
		return (s);
	lp = (unsigned long *)s;
	while (n >= sizeof(long int))
	{
		*lp++ = 0;
		n -= sizeof(long int);
	}
	a = (unsigned char *)lp;
	while (n--)
		*a++ = 0;
	return (s);
}
