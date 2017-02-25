/*
** exec_nm.c for exec_nm in /home/le-mou_t/rendu/TEK2/Module_Memoire/PSU_2016_nmobjdump/nm
** 
** Made by Thomas LE MOULLEC
** Login   <le-mou_t@epitech.net>
** 
** Started on  Fri Feb 24 12:55:56 2017 Thomas LE MOULLEC
** Last update Sat Feb 25 21:32:13 2017 Thomas LE MOULLEC
*/

#include "nm.h"

int             dump_nm(void *data, BOOL is_archive, t_elf *elformat)
{
  if (file_specifications((Elf64_Ehdr *)data, elformat->file, is_archive) == FALSE)
    return (-1);
  if (elformat->ac > 2)
    printf("\n%s:\n", elformat->file);
  elformat->elf = (Elf64_Ehdr *)data;
  if (is_archive == FALSE && check_file_size(elformat->elf, elformat) == FALSE)
    return (-2);
  if (get_symboles(elformat->elf, (Elf64_Shdr *)(data + elformat->elf->e_shoff), &elformat->strtab, elformat) == FALSE)
    return (-4);
  sort_symboles(elformat);
  if (is_archive == TRUE)
    get_file_name(data, elformat);
  print_my_nm(elformat, (Elf64_Shdr *)(data + elformat->elf->e_shoff));
  return (0);
}
