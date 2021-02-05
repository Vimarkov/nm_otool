/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_fat_32.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimarkov <vimarkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:52:19 by vimarkov          #+#    #+#             */
/*   Updated: 2020/01/28 16:39:07 by vimarkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

static int		host_arch(cpu_type_t type)
{
	if ((type == CPU_TYPE_X86_64) && (sizeof(void *) == 8))
		return (1);
	if ((type == CPU_TYPE_I386) && (sizeof(void *) == 4))
		return (1);
	return (0);
}

void			header_arch(char *arg, int i)
{
	if (i == 0)
	{
		write(1, "\n", 1);
		write(1, arg, ft_strlen(arg));
		write(1, " (for architecture ppc):\n", 25);
	}
	else
	{
		write(1, "\n", 1);
		write(1, arg, ft_strlen(arg));
		write(1, " (for architecture i386):\n", 26);
	}
}

int				handle_fat_32(void *ptr, int size, char *arg)
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
			header_arch(arg, i);
		ft_nm(ptr + swap_endian(arch[i].offset), size, arg, 0);
		if (host_arch(swap_endian(arch[i].cputype)))
			return (1);
	}
	return (1);
}
