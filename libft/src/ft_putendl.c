/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimarkov <vimarkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 15:55:53 by viclucas          #+#    #+#             */
/*   Updated: 2020/01/30 15:12:39 by vimarkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putendl(char const *s)
{
	int i;

	i = 0;
	while ((s[i] < 127 && s[i] > 10) && s[i])
	{
		if (s[i] < 127 && s[i] > 3)
			ft_putchar(s[i]);
		i++;
	}
	if (s[i] == 10)
		ft_putchar('\n');
	ft_putchar('\n');
}
