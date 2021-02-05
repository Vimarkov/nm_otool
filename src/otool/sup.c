/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimarkov <vimarkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 19:09:06 by vimarkov          #+#    #+#             */
/*   Updated: 2020/01/28 19:26:06 by vimarkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_otool.h"

t_sections		*ret_sec(void)
{
	static	t_sections sections;

	sections.bss = 0;
	sections.cputype = 0;
	sections.data = 0;
	sections.ind = 0;
	sections.nb = 0;
	sections.text = 0;
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
