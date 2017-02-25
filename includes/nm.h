/*
** nm.h for nm.h in /home/le-mou_t/rendu/TEK2/Module_Memoire/PSU_2016_nmobjdump/nm
** 
** Made by Thomas LE MOULLEC
** Login   <le-mou_t@epitech.net>
** 
** Started on  Fri Feb 24 12:29:43 2017 Thomas LE MOULLEC
** Last update Sat Feb 25 17:48:34 2017 Thomas LE MOULLEC
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
  char		*file;
  int		ac;
  int		fileSize;
  int		err;
}		t_elf;

int		filesize(int);
BOOL            my_nm(char *, int);
int		archive(unsigned char *, t_elf *);
int		get_nbr_size(unsigned char *, int);
BOOL             file_specifications(Elf64_Ehdr *, char *);
Elf64_Sym       **get_sym(Elf64_Ehdr *, Elf64_Shdr *, char **, t_elf *);
Elf64_Sym       **get_tab(Elf64_Ehdr *, Elf64_Sym *, int, t_elf *);
Elf64_Sym       **order_tab(Elf64_Sym **, char *);
char            *in_case(char *);
void            get_symbol(void *, Elf64_Ehdr *);
void            transformation(char *);
void            print_symb(Elf64_Sym **, char *, Elf64_Shdr *);
char            catch_sym(int, int, int, Elf64_Shdr *, Elf64_Sym *);
int             dump_nm(void *, BOOL, t_elf *);
char             *get_magic(unsigned char *);
BOOL		is_separator(unsigned char *, int);
BOOL            check_file_size(Elf64_Ehdr *, t_elf *);

#endif
