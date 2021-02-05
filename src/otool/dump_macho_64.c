/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_macho_64.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimarkov <vimarkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 18:54:52 by vimarkov          #+#    #+#             */
/*   Updated: 2020/02/04 17:50:55 by vimarkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_otool.h"

static void			print_hex(size_t addr, size_t base, size_t len)
{
	char	value;

	if (len <= 0)
		return ;
	print_hex(addr / base, base, len - 1);
	value = HEX_STRING[(addr % base)];
	write(1, &value, 1);
}

static void			print_text_content(void *ptr, uint64_t size, uint64_t addr,
											off_t len)
{
	uint32_t i;

	i = 0;
	if (ptr + len < ptr + size)
		return ;
	while (i < size + ((size % 16) ? (16 - size % 16) : 0))
	{
		if (i % 16 == 0)
		{
			print_hex(addr + i, 16, 16);
			write(1, "\t", 1);
		}
		if (i < size)
			print_hex(0xff & ((char*)ptr)[i], 16, 2);
		if (!*get_ac() && i < size)
			write(1, " ", 1);
		if (*get_ac() && (i % 4 == 3) && i < size)
			write(1, " ", 1);
		if (i % 16 == 15)
			write(1, "\n", 1);
		i++;
	}
	if ((i - 1) % 16 != 15)
		write(1, "\n", 1);
}

int					section_macho_64(struct load_command *lc, void *ptr,
										uint32_t cputype, off_t size)
{
	struct segment_command_64	*seg;
	struct section_64			*sec;
	uint32_t					i;

	i = 0;
	seg = (struct segment_command_64*)lc;
	sec = (struct section_64*)((void*)seg + sizeof(*seg));
	while (i < power_pc_64(seg->nsects, cputype))
	{
		if (!(ft_strcmp(sec[i].sectname, SECT_TEXT)) &&
				!(ft_strcmp(sec[i].segname, SEG_TEXT)))
		{
			write(1, "Contents of (__TEXT,__text) section\n", 36);
			print_text_content(ptr + power_pc_64(sec[i].offset, cputype), \
				power_pc_64(sec[i].size, cputype),
				power_pc_64(sec[i].addr, cputype), size);
		}
		i++;
	}
	return (1);
}

void				handle_macho_64(void *ptr, off_t size, int nb)
{
	int							ncmds;
	int							i;
	struct mach_header_64		*header;
	struct load_command			*lc;
	t_ac_args					ac;

	ac.arg = ac_args_ar();
	i = 0;
	header = (struct mach_header_64 *)ptr;
	ncmds = power_pc_64(header->ncmds, header->cputype);
	lc = ptr + sizeof(*header);
	set_ac(swap_uint64(header->cputype) == CPU_TYPE_POWERPC64, ac.arg);
	if (nb >= 0)
	{
		write(1, ac.arg, ft_strlen(ac.arg));
		write(1, ":\n", 2);
	}
	while (i < ncmds)
	{
		if (power_pc_64(lc->cmd, header->cputype) == LC_SEGMENT_64)
			section_macho_64(lc, ptr, header->cputype, size);
		lc = (void*)lc + power_pc_64(lc->cmdsize, header->cputype);
		i++;
	}
}
