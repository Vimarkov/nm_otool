/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimarkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:53:01 by vimarkov          #+#    #+#             */
/*   Updated: 2020/01/28 16:33:05 by vimarkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

int		main(int ac, char **av)
{
	void			*ptr;
	int				i;
	int				fd;
	struct stat		buf;

	i = 0;
	if (ac >= 2)
		i++;
	while (i < ac)
	{
		if ((fd = open(av[i], O_RDONLY)) < 0)
			return (EXIT_FAILURE);
		if (fstat(fd, &buf) < 0)
			return (EXIT_FAILURE);
		if ((ptr = mmap(0, buf.st_size, PROT_READ,
							MAP_PRIVATE, fd, 0)) == MAP_FAILED)
			return (EXIT_FAILURE);
		ft_nm(ptr, buf.st_size, av[i], ac);
		if ((munmap(ptr, buf.st_size)) < 0)
			return (EXIT_FAILURE);
		close(fd);
		i++;
	}
}
