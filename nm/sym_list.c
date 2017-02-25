/*
** sym_list.c for sym_list in /home/le-mou_t/rendu/TEK2/Module_Memoire/PSU_2016_nmobjdump/nm
** 
** Made by Thomas LE MOULLEC
** Login   <le-mou_t@epitech.net>
** 
** Started on  Fri Feb 24 13:02:45 2017 Thomas LE MOULLEC
** Last update Sat Feb 25 15:41:44 2017 Thomas LE MOULLEC
*/

#include "nm.h"

Elf64_Sym           **get_tab(Elf64_Ehdr *elf, Elf64_Sym *symtab, int size, t_elf *elformat)
{
  Elf64_Sym         **tab;
  int               i;
  int                   j;

  tab = NULL;
  if ((void *)elf > (void *)symtab)
    return (NULL);
  if (((void *)elf + elformat->fileSize) < (void *)symtab)
    return (NULL);
  if ((tab = malloc(sizeof(*tab) * (size + 1))) == NULL)
    return (NULL);
  j = 0;
  i = 0;
  while (i < size)
    {
      tab[j] = &symtab[i];
      i++;
      j++;
    }
  tab[j] = NULL;
  return (tab);
}
