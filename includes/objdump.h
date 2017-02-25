/*
** objdump.h for objdump in /home/le-mou_t/rendu/TEK2/Module_Memoire/PSU_2016_nmobjdump
** 
** Made by Thomas LE MOULLEC
** Login   <le-mou_t@epitech.net>
** 
** Started on  Thu Feb 16 10:17:22 2017 Thomas LE MOULLEC
** Last update Fri Feb 24 14:36:56 2017 Thomas LE MOULLEC
*/

#ifndef OBJDUMP_H_
# define OBJDUMP_H_

#include <elf.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>

#define MACHINES_NBR 18

typedef enum {TRUE, FALSE} BOOL;
typedef enum {SYS_32, SYS_64, ERROR_SYS, UNDEFINED} SYS;
extern BOOL global_option_f;
extern BOOL global_only_flags;
extern char *binary;

typedef struct	s_elf
{
  void		*data;
  Elf64_Ehdr	*elf_64;
  Elf64_Shdr	*shdr_64;
  Elf32_Ehdr	*elf_32;
  Elf32_Shdr	*shdr_32;
  char		*strtab;
  char		*file;
  unsigned int	class;
  int		filesize;
  BOOL		is_archive;
  char		*obj_archive;
  int		size_archive;
}		t_elf;

typedef struct	s_machines
{
  int		id;
  char		*archi;
}		t_machines;

void             get_name_obj32(void *, Elf32_Ehdr *, t_elf *);
void             get_name_obj64(void *, Elf64_Ehdr *, t_elf *);
char             **parse_options(char **, int *);
BOOL		my_objdump(char *);
SYS            init_elf(int, t_elf *);
BOOL		dump_obj_64(Elf64_Shdr *, char *, int, t_elf *);
BOOL		dump_obj_32(Elf32_Shdr *, char *, int, t_elf *);
char             *get_architecture(int);
BOOL             is_correct_data(unsigned char *, int, int, int);
BOOL             is_correct_type(int);
BOOL             is_correct_class(unsigned char *);
BOOL             is_elf(char *);
char             *get_magic(unsigned char *);
BOOL             bad_format_file(char *);
BOOL		is_archive(t_elf *);
void		archive(t_elf *);
SYS		init_64_Elf(t_elf *, void *);
SYS		init_32_Elf(t_elf *, void *);
SYS            file_format(void *);
SYS            check_archive(t_elf *);
char		*my_revstr(char *);
BOOL             file_specifications_64(t_elf *);
BOOL             file_specifications_32(t_elf *);
int              filesize(int);

#endif
