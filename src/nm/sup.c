/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimarkov <vimarkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:53:06 by vimarkov          #+#    #+#             */
/*   Updated: 2020/01/28 16:49:07 by vimarkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

void			print_hex(size_t addr, size_t base, size_t len)
{
	char	value;

	if (len <= 0)
		return ;
	print_hex(addr / base, base, len - 1);
	value = HEX_STRING[(addr % base)];
	write(1, &value, 1);
}

t_sections		*ret_sec(void)
{
	static t_sections	sections = {0, 0, 0, 0, 0, 0};

	return (&sections);
}

void			reset_sec(void)
{
	ret_sec()->data = 0;
	ret_sec()->nb = 0;
	ret_sec()->bss = 0;
	ret_sec()->text = 0;
	ret_sec()->ind = 0;
}

char			*get_symbols(t_symbols *sym, int i)
{
	int x;
	int y;

	x = 0;
	y = 0;
	if (sym[i].type == N_UNDF && sym[i].ext == N_EXT)
		return (" U ");
	else if (sym[i].type == N_ABS)
		return (sym[i].ext ? " A " : " a ");
	else if (sym[i].type == N_INDR)
		return (sym[i].ext ? " I " : " i ");
	else if (sym[i].type == N_SECT)
	{
		if (sym[i].sect == ret_sec()->text)
			return (sym[i].ext ? " T " : " t ");
		else if (sym[i].sect == ret_sec()->data)
			return (sym[i].ext ? " D " : " d ");
		else if (sym[i].sect == ret_sec()->bss)
			return (sym[i].ext ? " B " : " b ");
		else
			return (sym[i].ext ? " S " : " s ");
	}
	else
		return (NULL);
	return (NULL);
}

t_sort			*sort_macho(t_sort *sort, int size)
{
	int			ret;
	int			i;
	int			j;
	t_sort		tmp;

	i = 0;
	while (i < size - 1)
	{
		j = i + 1;
		while (j < size)
		{
			ret = ft_strcmp(sort[i].name, sort[j].name);
			if (ret > 0 || (ret == 0 && sort[i].value > sort[j].value))
			{
				tmp = sort[i];
				sort[i] = sort[j];
				sort[j] = tmp;
			}
			++j;
		}
		++i;
	}
	return (sort);
}
