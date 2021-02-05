/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimarkov <vimarkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 15:10:43 by vimarkov          #+#    #+#             */
/*   Updated: 2020/01/30 18:52:34 by vimarkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OTOOL_H
# define FT_OTOOL_H
# include <stdint.h>
# include <mach/machine.h>
# include <architecture/byte_order.h>
# include <mach-o/fat.h>
# include <mach-o/loader.h>
# include <unistd.h>
# include <mach-o/nlist.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <stdio.h>
# include <stdlib.h>
# include <ar.h>
# include "../libft/includes/libft.h"

# define AR_MAGIC 0x72613c21
# define AR_CIGAM 0x213c6172
# define HEX_STRING "0123456789abcdef"

typedef struct	s_symbols
{
	char		*name;
	uint8_t		ext;
	uint8_t		type;
	uint8_t		sect;
	uint16_t	desc;
	uint64_t	value;
	char		sym;
}				t_symbols;

typedef struct	s_sections
{
	int			data;
	int			nb;
	int			bss;
	int			text;
	int			ind;
	int			cputype;
}				t_sections;

typedef struct	s_ac_args
{
	int		ac;
	char	*arg;
}				t_ac_args;

void			ft_otool(void *ptr, off_t size, char *arg, int ac);
void			handle_macho_64(void *ptr, off_t size, int ac);
void			handle_macho_32(void *ptr, off_t size, int nb);
char			*hex_convert (int nb);
t_sections		*ret_sec(void);
void			reset_sec(void);
int				*get_ac(void);
void			set_ac(int ac, char *arg);
uint64_t		swap_uint64(uint64_t val);
uint64_t		power_pc_64(uint64_t nb, uint32_t cputype);
uint32_t		power_pc(uint32_t nb, uint32_t cputype);
uint32_t		swap_endian(uint32_t val);
char			**get_arg(void);
int				handle_archive(void *ptr, char *arg, int size);
int				handle_fat_64(void *ptr, int size, char *arg, int ac);
int				handle_fat_32(void *ptr, int size, char *arg, int nb);
uint32_t		ac_args(void);
char			*ac_args_ar(void);

#endif
