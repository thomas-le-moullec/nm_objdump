/*
** objdump.c for objdump in /home/le-mou_t/rendu/TEK2/Module_Memoire/PSU_2016_nmobjdump
** 
** Made by Thomas LE MOULLEC
** Login   <le-mou_t@epitech.net>
** 
** Started on  Wed Feb 15 09:06:22 2017 Thomas LE MOULLEC
** Last update Sun Feb 19 14:21:24 2017 Thomas LE MOULLEC
*/

#include "objdump.h"

BOOL global_option_f		= FALSE;
BOOL global_only_flags		= TRUE;
char *binary			= NULL;

BOOL		my_objdump(char *filename)
{
  int		fd;
  t_elf		*elformat;

  if ((elformat = malloc(sizeof(*elformat))) == NULL)
    exit(-1);
  if ((fd = open(filename, O_RDONLY)) != -1)
    {
      elformat->file = filename;
      if ((init_elf(fd, elformat)) == FALSE)
	return (FALSE);
      dump_obj(elformat->shdr, elformat->strtab, elformat->elf->e_shnum, elformat);
      close(fd);
      return (TRUE);
    }
  fprintf(stderr, "%s: '%s': No such file\n", binary, filename);
  return (FALSE);
}
