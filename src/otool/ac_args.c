/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ac_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimarkov <vimarkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 19:12:14 by vimarkov          #+#    #+#             */
/*   Updated: 2020/01/30 16:23:39 by vimarkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_otool.h"

int				*get_ac(void)
{
	static int	ac;

	return (&ac);
}

char			**get_arg(void)
{
	static char	*arg;

	return (&arg);
}

void			set_ac(int ac, char *arg)
{
	*get_ac() = ac;
	*get_arg() = arg;
}

uint32_t		ac_args(void)
{
	uint8_t	ac;

	ac = *get_ac();
	return (ac);
}

char			*ac_args_ar(void)
{
	char *arg;

	arg = ft_strdup(*get_arg());
	return (arg);
}
