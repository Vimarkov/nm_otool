/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_macho_32.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimarkov <vimarkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 18:02:49 by vimarkov          #+#    #+#             */
/*   Updated: 2020/02/04 17:49:28 by vimarkov         ###   ########.fr       */
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

static void			print_text_content(void *ptr, uint32_t size, uint64_t addr,
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
			print_hex(addr + i, 16, 8);
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

int					section_macho_32(struct load_command *lc, void *ptr,
										uint32_t cputype, off_t size)
{
	struct segment_command		*seg;
	struct section				*sec;
	uint32_t					i;

	i = 0;
	seg = (struct segment_command*)lc;
	sec = (struct section*)((void*)seg + sizeof(*seg));
	while (i < power_pc(seg->nsects, cputype))
	{
		if (!(ft_strcmp(sec[i].sectname, SECT_TEXT)) &&
				!(ft_strcmp(sec[i].segname, SEG_TEXT)))
		{
			write(1, "Contents of (__TEXT,__text) section\n", 36);
			print_text_content(ptr + power_pc(sec[i].offset, cputype), \
			power_pc(sec[i].size, cputype), power_pc(sec[i].addr, cputype),
			size);
		}
		i++;
	}
	return (1);
}

void				handle_macho_32(void *ptr, off_t size, int nb)
{
	int							ncmds;
	int							i;
	struct mach_header			*header;
	struct load_command			*lc;
	t_ac_args					ac;

	i = 0;
	ac.arg = ac_args_ar();
	header = (struct mach_header *)ptr;
	ncmds = power_pc(header->ncmds, header->cputype);
	lc = ptr + sizeof(*header);
	set_ac(swap_endian(header->cputype) == CPU_TYPE_POWERPC, ac.arg);
	if (nb >= 0)
	{
		write(1, ac.arg, ft_strlen(ac.arg));
		write(1, ":\n", 2);
	}
	while (i < ncmds)
	{
		if (power_pc(lc->cmd, header->cputype) == LC_SEGMENT)
			section_macho_32(lc, ptr, header->cputype, size);
		lc = (void*)lc + power_pc(lc->cmdsize, header->cputype);
		i++;
	}
}
