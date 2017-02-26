/*
** check_data.c for check in /home/le-mou_t/rendu/TEK2/Module_Memoire/PSU_2016_nmobjdump/objdump
** 
** Made by Thomas LE MOULLEC
** Login   <le-mou_t@epitech.net>
** 
** Started on  Sun Feb 19 13:53:33 2017 Thomas LE MOULLEC
** Last update Sun Feb 26 16:52:12 2017 Thomas LE MOULLEC
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

BOOL             is_correct_data(unsigned char *identifier, int type, \
				 int machine, int version)
{
  if (identifier[EI_CLASS] == ELFCLASSNONE ||		    \
      identifier[EI_DATA] == ELFDATANONE ||		    \
      identifier[EI_VERSION] == EV_NONE ||		    \
      type == ET_NONE ||				    \
      machine == EM_NONE ||				    \
      version == EV_NONE)
    return (FALSE);
  return (TRUE);
}
