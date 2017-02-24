/*
** objdump.c for objdump in /home/le-mou_t/rendu/TEK2/Module_Memoire/PSU_2016_nmobjdump
** 
** Made by Thomas LE MOULLEC
** Login   <le-mou_t@epitech.net>
** 
** Started on  Wed Feb 15 09:06:22 2017 Thomas LE MOULLEC
** Last update Fri Feb 24 10:06:13 2017 Thomas LE MOULLEC
*/

#include "objdump.h"

BOOL global_option_f		= FALSE;
BOOL global_only_flags		= TRUE;
char *binary			= NULL;

static BOOL	my_dump(int fd, t_elf *elformat)
{
  SYS		result;

  if ((result = init_elf(fd, elformat)) == ERROR_SYS)
    {
      close(fd);
      return (FALSE);
    }
  if (result == UNDEFINED)
    archive(elformat);
  if (result == SYS_64)
    dump_obj_64(elformat->shdr_64, elformat->strtab,		\
		elformat->elf_64->e_shnum, elformat);
  if (result == SYS_32)
    dump_obj_32(elformat->shdr_32, elformat->strtab,		\
		elformat->elf_32->e_shnum, elformat);
  return (TRUE);
}

BOOL		my_objdump(char *filename)
{
  int		fd;
  t_elf		*elformat;

  if ((elformat = malloc(sizeof(*elformat))) == NULL)
    exit(-1);
  if ((fd = open(filename, O_RDONLY)) != -1)
    {
      elformat->file = filename;
      if (my_dump(fd, elformat) == TRUE)
	{
	  close(fd);
	  return (TRUE);
	}
      return (TRUE);
    }
  fprintf(stderr, "%s: '%s': No such file\n", binary, filename);
  return (FALSE);
}
