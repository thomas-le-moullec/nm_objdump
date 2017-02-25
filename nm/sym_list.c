/*
** sym_list.c for sym_list in /home/le-mou_t/rendu/TEK2/Module_Memoire/PSU_2016_nmobjdump/nm
** 
** Made by Thomas LE MOULLEC
** Login   <le-mou_t@epitech.net>
** 
** Started on  Fri Feb 24 13:02:45 2017 Thomas LE MOULLEC
** Last update Sat Feb 25 20:16:26 2017 Thomas LE MOULLEC
*/

#include "nm.h"

static BOOL		check_sym(Elf64_Ehdr *elf, t_elf *elformat)
{
  if ((void *)elf > (void *)elformat->sym)
    return (FALSE);
  if (((void *)elf + elformat->fileSize) < (void *)elformat->sym)
    return (FALSE);
  return (TRUE);
}

Elf64_Sym           **get_sym_tab(Elf64_Ehdr *elf, t_elf *elformat, \
				  Elf64_Shdr *sections, int idx)
{
  Elf64_Sym         **tab_sym;
  int               i;
  int               j;
  int		    size_section;

  tab_sym = NULL;
  elformat->sym = (void *)elf + sections[idx].sh_offset;
  size_section = (sections[idx].sh_size / sizeof(*elformat->sym));
  if ((check_sym(elf, elformat) == FALSE) || \
      (tab_sym = malloc(sizeof(*tab_sym) * (size_section + 1))) == NULL)
    return (NULL);
  j = 0;
  i = 0;
  while (i < size_section)
    tab_sym[j++] = &elformat->sym[i++];
  tab_sym[j] = NULL;
  return (tab_sym);
}
