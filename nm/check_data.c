/*
** check_data.c for check_data in /home/le-mou_t/rendu/TEK2/Module_Memoire/PSU_2016_nmobjdump/nm
** 
** Made by Thomas LE MOULLEC
** Login   <le-mou_t@epitech.net>
** 
** Started on  Sat Feb 25 17:26:19 2017 Thomas LE MOULLEC
** Last update Sun Feb 26 16:37:04 2017 Thomas LE MOULLEC
*/

#include "nm.h"

BOOL		check_file_size(Elf64_Ehdr *elf, t_elf *elformat)
{
  if ((int)(elf->e_shoff + (elf->e_shentsize * \
			    elf->e_shnum)) != elformat->fileSize)
    return (FALSE);
  return (TRUE);
}

BOOL		is_separator(unsigned char *data, int i)
{
  if (data[i] == '`' && data[i + 1] == '\n')
    return (TRUE);
  return (FALSE);
}
