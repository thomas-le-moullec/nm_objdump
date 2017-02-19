/*
** objdump.h for objdump in /home/le-mou_t/rendu/TEK2/Module_Memoire/PSU_2016_nmobjdump
** 
** Made by Thomas LE MOULLEC
** Login   <le-mou_t@epitech.net>
** 
** Started on  Thu Feb 16 10:17:22 2017 Thomas LE MOULLEC
** Last update Sun Feb 19 14:28:17 2017 Thomas LE MOULLEC
*/

#include <elf.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>

#define MACHINES_NBR 18

typedef struct	s_elf
{
  void		*data;
  Elf64_Ehdr	*elf;
  Elf64_Shdr	*shdr;
  char		*strtab;
  char		*file;
  unsigned int	class;
  int		filesize;
}		t_elf;

typedef struct	s_machines
{
  int		id;
  char		*archi;
}		t_machines;

typedef enum {TRUE, FALSE} BOOL;

extern BOOL global_option_f;
extern BOOL global_only_flags;
extern char *binary;

char             **parse_options(char **, int *);
BOOL		my_objdump(char *);
BOOL            init_elf(int, t_elf *);
BOOL		dump_obj(Elf64_Shdr *, char *, int, t_elf *);
char             *get_architecture(t_elf *);
BOOL             is_correct_data(Elf64_Ehdr *);
BOOL             is_correct_type(int);
BOOL             is_correct_class(unsigned char *);
BOOL             is_elf(char *);
char             *get_magic(unsigned char *);
BOOL             bad_format_file(char *);
