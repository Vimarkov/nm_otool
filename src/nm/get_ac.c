/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ac.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimarkov <vimarkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:43:32 by vimarkov          #+#    #+#             */
/*   Updated: 2020/01/30 16:04:30 by vimarkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_nm.h"

static int		*get_ac(void)
{
	static int	ac;

	return (&ac);
}

static char		**get_arg(void)
{
	static char	*arg;

	return (&arg);
}

void			set_ac(int ac, char *arg)
{
	*get_ac() = ac;
	*get_arg() = arg;
}

int				ac_args(void)
{
	int	ac;

	ac = *get_ac();
	return (ac);
}

char			*ac_args_ar(void)
{
	char *arg;

	arg = *get_arg();
	return (arg);
}
