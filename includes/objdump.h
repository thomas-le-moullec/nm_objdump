/*
** objdump.h for objdump in /home/le-mou_t/rendu/TEK2/Module_Memoire/PSU_2016_nmobjdump
** 
** Made by Thomas LE MOULLEC
** Login   <le-mou_t@epitech.net>
** 
** Started on  Thu Feb 16 10:17:22 2017 Thomas LE MOULLEC
** Last update Fri Feb 17 11:59:53 2017 Thomas LE MOULLEC
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
