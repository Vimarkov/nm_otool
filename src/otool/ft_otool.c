/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimarkov <vimarkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 19:01:23 by vimarkov          #+#    #+#             */
/*   Updated: 2020/01/30 18:52:18 by vimarkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_otool.h"

void		ft_otool(void *ptr, off_t size, char *arg, int ac)
{
	uint32_t	magic_nb;

	magic_nb = *(uint32_t*)ptr;
	set_ac(ac, arg);
	if (magic_nb == AR_MAGIC || magic_nb == AR_CIGAM)
		handle_archive(ptr, arg, size);
	if (magic_nb == MH_MAGIC_64 || magic_nb == MH_CIGAM_64)
		handle_macho_64(ptr, size, ac);
	else if (magic_nb == MH_MAGIC || magic_nb == MH_CIGAM)
		handle_macho_32(ptr, size, ac);
	else if (magic_nb == FAT_MAGIC_64 || magic_nb == FAT_CIGAM_64)
		handle_fat_64(ptr, size, arg, ac);
	else if (magic_nb == FAT_MAGIC || magic_nb == FAT_CIGAM)
		handle_fat_32(ptr, size, arg, ac);
}
