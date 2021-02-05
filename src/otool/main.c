/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimarkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 19:06:49 by vimarkov          #+#    #+#             */
/*   Updated: 2020/01/28 20:33:44 by vimarkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_otool.h"

int		main(int ac, char **av)
{
	void			*ptr;
	int				i;
	int				fd;
	struct stat		buf;

	i = 0;
	if (ac >= 2)
		i++;
	if (ac <= 1)
		return (EXIT_FAILURE);
	while (i < ac)
	{
		if ((fd = open(av[i], O_RDONLY)) < 0)
			return (EXIT_FAILURE);
		if (fstat(fd, &buf) < 0)
			return (EXIT_FAILURE);
		if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE,
				fd, 0)) == MAP_FAILED)
			return (EXIT_FAILURE);
		ft_otool(ptr, buf.st_size, av[i], ac);
		if ((munmap(ptr, buf.st_size)) < 0)
			return (EXIT_FAILURE);
		close(fd);
		i++;
	}
}
