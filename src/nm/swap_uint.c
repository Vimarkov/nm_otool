/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_uint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimarkov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:53:11 by vimarkov          #+#    #+#             */
/*   Updated: 2020/01/28 16:36:09 by vimarkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

uint32_t	swap_endian(uint32_t val)
{
	val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF);
	return (val << 16) | (val >> 16);
}

uint64_t	swap_uint64(uint64_t val)
{
	val = ((val << 8) & 0xFF00FF00FF00FF00ULL) |
		((val >> 8) & 0x00FF00FF00FF00FFULL);
	val = ((val << 16) & 0xFFFF0000FFFF0000ULL) |
		((val >> 16) & 0x0000FFFF0000FFFFULL);
	return (val << 32) | (val >> 32);
}

uint32_t	power_pc(uint32_t nb, uint32_t cputype)
{
	if (swap_endian(cputype) == CPU_TYPE_POWERPC)
		return (swap_endian(nb));
	return (nb);
}

uint64_t	ppc_64(uint64_t nb, uint32_t cputype)
{
	if (swap_uint64(cputype) == CPU_TYPE_POWERPC64)
		return (swap_uint64(cputype));
	return (nb);
}
