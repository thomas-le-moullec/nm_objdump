/*
** check_data.c for check in /home/le-mou_t/rendu/TEK2/Module_Memoire/PSU_2016_nmobjdump/objdump
** 
** Made by Thomas LE MOULLEC
** Login   <le-mou_t@epitech.net>
** 
** Started on  Sun Feb 19 13:53:33 2017 Thomas LE MOULLEC
** Last update Sun Feb 19 13:56:10 2017 Thomas LE MOULLEC
*/

#include "objdump.h"

BOOL             is_elf(char *magic)
{
  if (magic[0] == ELFMAG0 && magic[1] == ELFMAG1 && \
      magic[2] == ELFMAG2 && magic[3] == ELFMAG3)
    return (TRUE);
  return (FALSE);
}

BOOL             is_correct_class(unsigned char *identifier)
{
  if (identifier[EI_CLASS] == ELFCLASS64)
    return (TRUE);
  if (identifier[EI_CLASS] == ELFCLASS32)
    return (TRUE);
  return (FALSE);
}

BOOL             is_correct_type(int type)
{
  if (type == ET_NONE)
    return (FALSE);
  return (TRUE);
}

BOOL             is_correct_data(Elf64_Ehdr *elf)
{
  if (elf->e_ident[EI_CLASS] == ELFCLASSNONE ||	    \
      elf->e_ident[EI_DATA] == ELFDATANONE ||	    \
      elf->e_ident[EI_VERSION] == EV_NONE ||	    \
      elf->e_type == ET_NONE ||			    \
      elf->e_machine == EM_NONE ||		    \
      elf->e_version == EV_NONE)
    return (FALSE);
  return (TRUE);
}
