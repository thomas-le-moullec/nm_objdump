/*
** exec_nm.c for exec_nm in /home/le-mou_t/rendu/TEK2/Module_Memoire/PSU_2016_nmobjdump/nm
** 
** Made by Thomas LE MOULLEC
** Login   <le-mou_t@epitech.net>
** 
** Started on  Fri Feb 24 12:55:56 2017 Thomas LE MOULLEC
** Last update Sat Feb 25 17:33:11 2017 Thomas LE MOULLEC
*/

#include "nm.h"

int             dump_nm(void *data, BOOL is_archive, t_elf *elformat)
{
  Elf64_Ehdr    *elf;
  Elf64_Sym     **tab;
  char          *strtab;

  if (file_specifications((Elf64_Ehdr *)data, elformat->file) == FALSE)
    return (-1);
  if (elformat->ac > 2)
    printf("\n%s:\n", elformat->file);
  elf = (Elf64_Ehdr *)data;
  if (is_archive == FALSE && check_file_size(elf, elformat) == FALSE)
    return (-2);
  if ((tab = get_sym(elf, (Elf64_Shdr *)(data + elf->e_shoff), &strtab, elformat)) == NULL)
    return (-4);
  tab = order_tab(tab, strtab);
  if (is_archive == TRUE)
    get_symbol(data, elf);
  print_symb(tab, strtab, (Elf64_Shdr *)(data + elf->e_shoff));
  if (tab != NULL)
    {
      free(tab);
      tab = NULL;
    }
  return (0);
}
