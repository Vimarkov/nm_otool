/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vimarkov <vimarkov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 15:03:48 by vimarkov          #+#    #+#             */
/*   Updated: 2020/02/04 17:50:06 by vimarkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H
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

# define SYMBOL_SIZE 512
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

typedef struct	s_sort
{
	char			*name;
	char			*c;
	uint64_t		value;
	int				size;
}				t_sort;

void			print_hex(size_t addr, size_t base, size_t len);
void			ft_nm(void *str, int size, char *arg, int ac);
t_sections		*ret_sec(void);
void			reset_sec(void);
t_sort			*sort_macho(t_sort *sort, int size);
char			*get_symbols(t_symbols *sym, int i);
void			section_macho_64(struct load_command *lc);
void			symtab_macho_64(struct symtab_command *symtab, void *ptr,
		uint32_t cpu);
t_sections		*ret_sec(void);
void			section_macho_32(struct load_command *lc, uint32_t cputype);
void			symtab_macho_32(struct symtab_command *symtab, void *ptr,
		uint32_t cpu);
int				handle_fat_32(void *ptr, int size, char *arg);
int				handle_archive(void *ptr, char *arg, int size);
uint32_t		swap_endian(uint32_t val);
uint64_t		swap_uint64(uint64_t val);
uint32_t		power_pc(uint32_t ncmds, uint32_t cputype);
char			*hex_convert (uint64_t nb, char *sym, uint32_t cputype);
void			set_ac(int ac, char *arg);
int				ac_args(void);
char			*ac_args_ar(void);
uint64_t		power_pc_64(uint64_t nb, uint32_t cputype);
int				handle_fat_64(void *ptr, int size, char *arg);
uint32_t		swap_endian(uint32_t val);
uint64_t		swap_uint64(uint64_t val);
uint32_t		power_pc(uint32_t nb, uint32_t cputype);
uint64_t		ppc_64(uint64_t nb, uint32_t cputype);

#endif
