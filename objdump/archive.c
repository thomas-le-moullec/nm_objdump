/*
** archive.c for archive in /home/le-mou_t/rendu/TEK2/Module_Memoire/PSU_2016_nmobjdump/objdump
** 
** Made by Thomas LE MOULLEC
** Login   <le-mou_t@epitech.net>
** 
** Started on  Tue Feb 21 15:10:18 2017 Thomas LE MOULLEC
** Last update Fri Feb 24 10:25:29 2017 Thomas LE MOULLEC
*/

#include "objdump.h"

static int		start_archive(t_elf *elformat)
{
  int			i;
  int			cmpt;
  unsigned char		*str;

  i = 0;
  cmpt = 0;
  str = (unsigned char *)elformat->data;
  while (i < elformat->filesize)
    {
      if (str[i] == '`' && str[i + 1] == '\n')
	cmpt++;
      if (cmpt >= 3)
	break;
      i++;
    }
  if (cmpt < 3)
    return (-1);
  elformat->data = &str[i];
  return (i);
}

static int		find_size_part(unsigned char *str, int i, t_elf *elformat)
{
  char			*size_part;
  int			idx;

  idx = 0;
  if ((size_part = malloc(sizeof(*size_part) * 25)) == NULL)
    exit(-1);
  while (i > 0 && str[i] == ' ')
    i--;
  if (i == 0)
    return (-1);
  while (i > 0 && str[i] >= '0' && str[i] <= '9')
    {
      size_part[idx] = str[i];
      idx++;
      i--;
    }
  size_part[idx] = '\0';
  elformat->size_archive += atoi(my_revstr(size_part));
  elformat->size_archive += 60;
  return (atoi(my_revstr(size_part)));
}

SYS			check_archive(t_elf *elformat)
{
  unsigned int		section_size;
  int			i;
  unsigned char		*str;

  i = 0;
  section_size = 6;
  str = (unsigned char *)elformat->data;
  elformat->size_archive = 8;
  printf("In archive %s:\n", elformat->file);
  while (i < elformat->filesize)
    {
      if (str[i] == '`' && str[i + 1] == '\n')
	{
	  if (section_size + 60 != 0)
	    return (ERROR_SYS);
	  if ((section_size = find_size_part(str, i - 1, elformat)) == FALSE)
	    return (ERROR_SYS);
	}
      section_size--;
      i++;
    }
  if (elformat->size_archive != elformat->filesize)
    return (ERROR_SYS);
  return (UNDEFINED);
}

static void		obj_section(void *data, t_elf *elformat)
{
  SYS			result;

  if ((result = file_format(data)) == SYS_32)
    {
      init_32_Elf(elformat, data);
      get_name_obj32(data, elformat->elf_32, elformat);
      dump_obj_32(elformat->shdr_32, elformat->strtab,		\
		  elformat->elf_32->e_shnum, elformat);
    }
  else if (result == SYS_64)
    {
      init_64_Elf(elformat, data);
      get_name_obj64(data, elformat->elf_64, elformat);
      dump_obj_64(elformat->shdr_64, elformat->strtab,		\
		  elformat->elf_64->e_shnum, elformat);
    }
}

void			archive(t_elf *elformat)
{
  unsigned char		*str;
  int			i;
  int			j;


  if ((j = start_archive(elformat)) == -1)
    return ;
  i = 0;
  str = (unsigned char *)elformat->data;
  while (i + j < elformat->filesize)
    {
      if (str[i] == '`' && str[i + 1] == '\n')
	{
	  i += 2;
	  elformat->data = &str[i];
	  j++;
	  obj_section(elformat->data, elformat);
	}
      i++;
    }
}
