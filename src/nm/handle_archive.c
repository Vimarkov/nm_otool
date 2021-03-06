/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_archive.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimarkov <vimarkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:52:57 by vimarkov          #+#    #+#             */
/*   Updated: 2020/01/28 17:41:27 by vimarkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

void		print_headfile(char *arg, char *str)
{
	write(1, "\n", 1);
	write(1, arg, strlen(arg));
	write(1, "(", 1);
	write(1, str, strlen(str));
	write(1, "):\n", 3);
}

int			handle_archive(void *ptr, char *arg, int size)
{
	int					len;
	struct ar_hdr		*ar;
	char				*str;

	ptr += SARMAG;
	ar = (struct ar_hdr*)ptr;
	ptr = ptr + ft_atoi(ar->ar_size) + sizeof(struct ar_hdr);
	while (ptr)
	{
		ar = (struct ar_hdr*)ptr;
		if (ft_atoi(ar->ar_size) <= 0)
			return (0);
		str = ptr + sizeof(struct ar_hdr);
		if (ptr + (ft_atoi(ar->ar_size) + sizeof(struct ar_hdr)) > ptr + size)
			return (0);
		print_headfile(arg, str);
		len = ft_strlen(str);
		while (!str[len++])
			;
		ft_nm(ptr + sizeof(struct ar_hdr) + len - 1, size, arg, -1);
		ptr = ptr + ft_atoi(ar->ar_size) + sizeof(struct ar_hdr);
	}
	return (1);
}
