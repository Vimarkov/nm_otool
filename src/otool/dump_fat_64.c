/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_fat_64.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimarkov <vimarkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 18:01:51 by vimarkov          #+#    #+#             */
/*   Updated: 2020/01/30 19:04:58 by vimarkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_otool.h"

static int		host_arch_64(cpu_type_t type)
{
	if ((type == CPU_TYPE_X86_64) && (sizeof(void *) == 8))
		return (1);
	if ((type == CPU_TYPE_I386) && (sizeof(void *) == 4))
		return (1);
	return (0);
}

int				header_arch_64(char *arg, int i)
{
	if (i == 0)
	{
		write(1, arg, ft_strlen(arg));
		write(1, " (for architecture ppc64):\n", 30);
	}
	else
	{
		write(1, arg, ft_strlen(arg));
		write(1, " (for architecture x86_64):\n", 30);
	}
	return (-1);
}

int				handle_fat_64(void *ptr, int size, char *arg, int nb)
{
	struct fat_header	*header;
	struct fat_arch		*arch;
	int					narch;
	int					i;

	i = -1;
	header = (struct fat_header *)ptr;
	arch = (struct fat_arch *)(header + 1);
	narch = swap_uint64(header->nfat_arch);
	while (++i < narch)
	{
		if (narch > 1 && !i && host_arch_64(swap_uint64(arch[i + 1].cputype)))
			continue ;
		if (narch > 1 && !host_arch_64(swap_uint64(arch[i].cputype)))
			nb = header_arch_64(arg, i);
		ft_otool(ptr + swap_uint64(arch[i].offset), size, arg, nb);
		if (host_arch_64(swap_uint64(arch[i].cputype)))
			return (1);
	}
	return (1);
}
