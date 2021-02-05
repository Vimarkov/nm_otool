/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimarkov <vimarkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:52:44 by vimarkov          #+#    #+#             */
/*   Updated: 2020/01/30 16:05:55 by vimarkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

void			handle_macho_64(void *ptr)
{
	int							ncmds;
	int							i;
	struct mach_header_64		*header;
	struct load_command			*lc;
	struct symtab_command		*sym;

	i = 0;
	header = (struct mach_header_64 *)ptr;
	ncmds = ppc_64(header->ncmds, header->cputype);
	lc = ptr + sizeof(*header);
	while (i++ < ncmds)
	{
		if (ppc_64(lc->cmd, header->cputype) == LC_SEGMENT_64)
			section_macho_64(lc);
		if (ppc_64(lc->cmd, header->cputype) == LC_SYMTAB)
		{
			sym = (struct symtab_command*)lc;
			symtab_macho_64(sym, ptr, header->cputype);
		}
		lc = (void*)lc + ppc_64(lc->cmdsize, header->cputype);
	}
}

void			handle_macho_32(void *ptr)
{
	int							ncmds;
	int							i;
	struct mach_header			*header;
	struct load_command			*lc;
	struct symtab_command		*sym;

	i = 0;
	header = (struct mach_header *)ptr;
	ncmds = power_pc(header->ncmds, header->cputype);
	lc = ptr + sizeof(*header);
	while (i++ < ncmds)
	{
		if (power_pc(lc->cmd, header->cputype) == LC_SEGMENT)
			section_macho_32(lc, header->cputype);
		if (power_pc(lc->cmd, header->cputype) == LC_SYMTAB)
		{
			sym = (struct symtab_command*)lc;
			symtab_macho_32(sym, ptr, header->cputype);
		}
		lc = (void*)lc + power_pc(lc->cmdsize, header->cputype);
	}
}

void			ft_nm(void *ptr, int size, char *arg, int ac)
{
	uint32_t		magic_nb;

	magic_nb = *(uint32_t*)ptr;
	reset_sec();
	set_ac(ac, arg);
	if (magic_nb == AR_MAGIC || magic_nb == AR_CIGAM)
		handle_archive(ptr, arg, size);
	else if (magic_nb == MH_MAGIC_64 || magic_nb == MH_CIGAM_64)
		handle_macho_64(ptr);
	else if (magic_nb == MH_MAGIC || magic_nb == MH_CIGAM)
		handle_macho_32(ptr);
	else if (magic_nb == FAT_MAGIC_64 || magic_nb == FAT_CIGAM_64)
		handle_fat_64(ptr, size, arg);
	else if (magic_nb == FAT_MAGIC || magic_nb == FAT_CIGAM)
		handle_fat_32(ptr, size, arg);
}
