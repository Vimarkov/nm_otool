/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_macho_32.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimarkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:52:35 by vimarkov          #+#    #+#             */
/*   Updated: 2020/02/04 17:42:44 by vimarkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

static void			print_arg(int ac, char *test)
{
	if (ac > 2)
	{
		write(1, "\n", 1);
		write(1, test, ft_strlen(test));
		write(1, ":\n", 2);
	}
}

void				print_macho_32(t_sort *sort, uint32_t nsyms,
									uint32_t cputype, t_symbols *sym)
{
	int				ac;
	char			*test;
	uint32_t		i;

	i = 0;
	ac = ac_args();
	test = ac_args_ar();
	sort = sort_macho(sort, power_pc(nsyms, cputype));
	print_arg(ac, test);
	while (i < power_pc(nsyms, cputype))
	{
		if (sort[i].c && sort[i].name[0])
		{
			if (ft_strchr(sort[i].c, 'U') || ft_strchr(sort[i].c, 'u'))
				write(1, "        ", 8);
			else
				print_hex(sort[i].value, 16, 8);
			ft_putstr(sort[i].c);
			ft_putendl(sort[i].name);
		}
		i++;
	}
	free(sym);
	free(sort);
}

void				section_macho_32(struct load_command *lc, uint32_t cputype)
{
	struct segment_command	*seg;
	struct section			*sec;
	uint32_t				i;

	i = 0;
	seg = (struct segment_command*)lc;
	sec = (struct section*)((void*)seg + sizeof(*seg));
	while (i < power_pc(seg->nsects, cputype))
	{
		if (!(ft_strcmp(sec[i].sectname, SECT_TEXT)) &&
				!(ft_strcmp(sec[i].segname, SEG_TEXT)))
			ret_sec()->text = ret_sec()->ind + 1;
		else if (!(ft_strcmp(sec[i].sectname, SECT_DATA)) &&
				!(ft_strcmp(sec[i].segname, SEG_DATA)))
			ret_sec()->data = ret_sec()->ind + 1;
		else if (!(ft_strcmp(sec[i].sectname, SECT_BSS)) &&
				!(ft_strcmp(sec[i].segname, SEG_DATA)))
			ret_sec()->bss = ret_sec()->ind + 1;
		++(ret_sec()->ind);
		i++;
	}
}

void				symtab_macho_32(struct symtab_command *symtab,
										void *ptr, uint32_t cpu)
{
	char			*str;
	struct nlist	*array;
	t_symbols		*sym;
	uint32_t		i;
	t_sort			*sort;

	i = 0;
	array = ptr + power_pc(symtab->symoff, cpu);
	str = ptr + power_pc(symtab->stroff, cpu);
	sym = (t_symbols*)malloc(sizeof(t_symbols) * power_pc(symtab->nsyms, cpu));
	sort = (t_sort*)malloc(sizeof(t_sort) * power_pc(symtab->nsyms, cpu));
	while (i < power_pc(symtab->nsyms, cpu))
	{
		sym[i].name = str + power_pc(array[i].n_un.n_strx, cpu);
		sym[i].value = array[i].n_value;
		sym[i].type = array[i].n_type & N_TYPE;
		sym[i].ext = array[i].n_type & N_EXT;
		sym[i].sect = array[i].n_sect;
		sort[i].c = get_symbols(sym, i);
		sort[i].value = power_pc(sym[i].value, cpu);
		sort[i].name = ft_strdup(sym[i].name);
		i++;
	}
	sort = sort_macho(sort, power_pc(symtab->nsyms, cpu));
	print_macho_32(sort, symtab->nsyms, cpu, sym);
}
