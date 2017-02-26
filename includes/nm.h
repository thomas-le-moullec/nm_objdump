/*
** nm.h for nm.h in /home/le-mou_t/rendu/TEK2/Module_Memoire/PSU_2016_nmobjdump/nm
** 
** Made by Thomas LE MOULLEC
** Login   <le-mou_t@epitech.net>
** 
** Started on  Fri Feb 24 12:29:43 2017 Thomas LE MOULLEC
** Last update Sun Feb 26 17:41:05 2017 Thomas LE MOULLEC
*/

#ifndef NM_H_
# define NM_H_

#include <elf.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>

typedef enum {TRUE, FALSE} BOOL;

typedef struct	s_elf
{
  Elf64_Ehdr	*elf;
  Elf64_Sym	**tab;
  Elf64_Sym	*sym;
  char		*strtab;
  char		*file;
  int		ac;
  int		fileSize;
  int		err;
}		t_elf;

typedef struct	s_symTab
{
  BOOL          (*which)(Elf64_Shdr *, Elf64_Sym *, int, int);
}		t_symTab;

extern int global_idx;

int		filesize(int);
BOOL            my_nm(char *, int);
int		archive(unsigned char *, t_elf *);
int		get_size_section(unsigned char *, int);
BOOL             file_specifications(Elf64_Ehdr *, char *, BOOL);
BOOL            get_symboles(Elf64_Ehdr *, Elf64_Shdr *, char **, t_elf *);
Elf64_Sym       **get_sym_tab(Elf64_Ehdr *, t_elf *, Elf64_Shdr *, int);
void		sort_symboles(t_elf *);
char            *in_case(char *);
void            get_file_name(void *, t_elf *);
void            transformation(char *);
void            print_my_nm(t_elf *, Elf64_Shdr *);
void            print_symboles(Elf64_Shdr *, Elf64_Sym *, int, int);
int             dump_nm(void *, BOOL, t_elf *);
char             *get_magic(unsigned char *);
BOOL		is_separator(unsigned char *, int);
BOOL            check_file_size(Elf64_Ehdr *, t_elf *);
BOOL		space(Elf64_Shdr *, Elf64_Sym *, int, int);
BOOL		std_undefined(Elf64_Shdr *, Elf64_Sym *, int, int);
BOOL		absolute(Elf64_Shdr *, Elf64_Sym *, int, int);
BOOL		common(Elf64_Shdr *, Elf64_Sym *, int, int);
BOOL		data(Elf64_Shdr *, Elf64_Sym *, int, int);
BOOL		my_read(Elf64_Shdr *, Elf64_Sym *, int, int);
BOOL		un_data(Elf64_Shdr *, Elf64_Sym *, int, int);
BOOL		undefined(Elf64_Shdr *, Elf64_Sym *, int, int);
BOOL		text(Elf64_Shdr *, Elf64_Sym *, int, int);
BOOL		indirect(Elf64_Shdr *, Elf64_Sym *, int, int);
BOOL		my_abs(Elf64_Shdr *, Elf64_Sym *, int, int);
BOOL		ini_data(Elf64_Shdr *, Elf64_Sym *, int, int);
BOOL		unData(Elf64_Shdr *, Elf64_Sym *, int, int);
BOOL		readOnly(Elf64_Shdr *, Elf64_Sym *, int, int);
BOOL		textcode(Elf64_Shdr *, Elf64_Sym *, int, int);
BOOL		debug(Elf64_Shdr *, Elf64_Sym *, int, int);
BOOL		indicates(Elf64_Shdr *, Elf64_Sym *, int, int);
BOOL            my_weak(int, int, char);
void		dump_file_obj(char *);

#endif
