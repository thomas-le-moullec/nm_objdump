/*
** valid_elf.c for valid_elf in /home/le-mou_t/rendu/TEK2/Module_Memoire/PSU_2016_nmobjdump/nm
** 
** Made by Thomas LE MOULLEC
** Login   <le-mou_t@epitech.net>
** 
** Started on  Fri Feb 24 13:15:34 2017 Thomas LE MOULLEC
** Last update Sat Feb 25 21:10:21 2017 Thomas LE MOULLEC
*/

#include "nm.h"

static BOOL             is_correct_class(unsigned char *identifier)
{
  if (identifier[EI_CLASS] == ELFCLASS64)
    return (TRUE);
  if (identifier[EI_CLASS] == ELFCLASS32)
    return (TRUE);
  return (FALSE);
}

static BOOL             is_correct_type(int type)
{
  if (type == ET_NONE)
    return (FALSE);
  return (TRUE);
}

static BOOL             is_correct_data(unsigned char *identifier, int type, \
					int machine, int version)
{
  if (identifier[EI_CLASS] == ELFCLASSNONE ||			  \
      identifier[EI_DATA] == ELFDATANONE ||			  \
      identifier[EI_VERSION] == EV_NONE ||			  \
      type == ET_NONE ||					  \
      machine == EM_NONE ||					  \
      version == EV_NONE)
    return (FALSE);
  return (TRUE);
}

BOOL             file_specifications(Elf64_Ehdr *elf, char *file, BOOL is_archive)
{
  if (!elf || elf->e_ident[EI_MAG0] != ELFMAG0 ||		 \
      elf->e_ident[EI_MAG1] != ELFMAG1 ||			 \
      elf->e_ident[EI_MAG2] != ELFMAG2 ||			 \
      elf->e_ident[EI_MAG3] != ELFMAG3 ||			 \
      is_correct_class(elf->e_ident) == FALSE ||		 \
      is_correct_type(elf->e_type) == FALSE ||			 \
      is_correct_data(elf->e_ident, elf->e_type, elf->e_machine, \
		      elf->e_version) == FALSE)
    {
      if (is_archive == FALSE)
	fprintf(stderr, "nm: %s: File format not recognized\n", file);
      return (FALSE);
    }
  return (TRUE);
}
