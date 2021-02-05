/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_fat_32.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimarkov <vimarkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 17:58:43 by vimarkov          #+#    #+#             */
/*   Updated: 2020/01/30 19:04:34 by vimarkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_otool.h"

static int		host_arch(cpu_type_t type)
{
	if ((type == CPU_TYPE_X86_64) && (sizeof(void *) == 8))
		return (1);
	if ((type == CPU_TYPE_I386) && (sizeof(void *) == 4))
		return (1);
	return (0);
}

int				header_arch(char *arg, int i)
{
	if (i == 0)
	{
		write(1, arg, ft_strlen(arg));
		write(1, " (architecture ppc):\n", 21);
	}
	else
	{
		write(1, arg, ft_strlen(arg));
		write(1, " (architecture i386):\n", 22);
	}
	return (-1);
}

int				handle_fat_32(void *ptr, int size, char *arg, int ac)
{
	struct fat_header	*header;
	struct fat_arch		*arch;
	int					narch;
	int					i;

	i = -1;
	header = (struct fat_header *)ptr;
	arch = (struct fat_arch *)(header + 1);
	narch = swap_endian(header->nfat_arch);
	while (++i < narch)
	{
		if (narch > 1 && !i && host_arch(swap_endian(arch[i + 1].cputype)))
			continue ;
		if (narch > 1 && !host_arch(swap_endian(arch[i].cputype)))
			ac = header_arch(arg, i);
		ft_otool(ptr + swap_endian(arch[i].offset), size, arg, ac);
		if (host_arch(swap_endian(arch[i].cputype)))
			return (1);
	}
	return (1);
}
