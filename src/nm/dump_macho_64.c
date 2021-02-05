/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_macho_64.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimarkov <vimarkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:52:40 by vimarkov          #+#    #+#             */
/*   Updated: 2020/02/04 17:46:43 by vimarkov         ###   ########.fr       */
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

void				print_macho_64(t_sort *sort, uint32_t nsyms,
									uint32_t cputype, t_symbols *sym)
{
	int				ac;
	char			*test;
	uint32_t		i;

	i = 0;
	ac = ac_args();
	test = ac_args_ar();
	sort = sort_macho(sort, ppc_64(nsyms, cputype));
	print_arg(ac, test);
	while (i < ppc_64(nsyms, cputype))
	{
		if (sort[i].c && sort[i].name[0])
		{
			if (ft_strchr(sort[i].c, 'U') || ft_strchr(sort[i].c, 'u'))
				write(1, "                ", 16);
			else
				print_hex(sort[i].value, 16, 16);
			ft_putstr(sort[i].c);
			ft_putendl((char*)sort[i].name);
		}
		i++;
	}
	free(sym);
	free(sort);
}

void				section_macho_64(struct load_command *lc)
{
	struct segment_command_64	*seg;
	struct section_64			*sec;
	uint32_t					i;

	i = 0;
	seg = (struct segment_command_64*)lc;
	sec = (struct section_64*)((void*)seg + sizeof(*seg));
	while (i < seg->nsects)
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

void				symtab_macho_64(struct symtab_command *symtab, void *ptr,
									uint32_t cpu)
{
	char			*str;
	struct nlist_64	*array;
	t_symbols		*sym;
	uint32_t		i;
	t_sort			*sort;

	i = 0;
	array = ptr + ppc_64(symtab->symoff, cpu);
	str = ptr + ppc_64(symtab->stroff, cpu);
	sym = (t_symbols*)malloc(sizeof(t_symbols) * ppc_64(symtab->nsyms, cpu));
	sort = (t_sort*)malloc(sizeof(t_sort) * ppc_64(symtab->nsyms, cpu));
	while (i < ppc_64(symtab->nsyms, cpu))
	{
		sym[i].name = str + ppc_64(array[i].n_un.n_strx, cpu);
		sym[i].value = array[i].n_value;
		sym[i].type = array[i].n_type & N_TYPE;
		sym[i].ext = array[i].n_type & N_EXT;
		sym[i].sect = array[i].n_sect;
		sort[i].c = get_symbols(sym, i);
		sort[i].value = ppc_64(sym[i].value, cpu);
		sort[i].name = sym[i].name;
		i++;
	}
	sort = sort_macho(sort, ppc_64(symtab->nsyms, cpu));
	print_macho_64(sort, symtab->nsyms, cpu, sym);
}
