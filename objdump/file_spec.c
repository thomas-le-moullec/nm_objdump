/*
** 
** Made by Thomas LE MOULLEC
** 
** Started on  Fri Feb 24 10:11:47 2017 Thomas LE MOULLEC
** Last update Fri Feb 24 10:14:37 2017 Thomas LE MOULLEC
*/

#include "objdump.h"

SYS            file_format(void *data)
{
  unsigned char   *str;

  str = (unsigned char *)data;
  if (str[4] == ELFCLASS32)
    return (SYS_32);
  if (str[4] == ELFCLASS64)
    return (SYS_64);
  return (ERROR_SYS);
}

int              filesize(int fd)
{
  return (lseek(fd, 0, SEEK_END));
}

BOOL             file_specifications_64(t_elf *elformat)
{
  if (is_elf(get_magic(elformat->elf_64->e_ident)) == FALSE ||     \
      is_correct_class(elformat->elf_64->e_ident) == FALSE ||      \
      is_correct_type(elformat->elf_64->e_type) == FALSE ||             \
      is_correct_data(elformat->elf_64->e_ident,                        \
		      elformat->elf_64->e_type, elformat->elf_64->e_machine, \
		      elformat->elf_64->e_version) == FALSE)
    return (FALSE);
  return (TRUE);
}

BOOL             file_specifications_32(t_elf *elformat)
{
  if (is_elf(get_magic(elformat->elf_32->e_ident)) == FALSE ||     \
      is_correct_class(elformat->elf_32->e_ident) == FALSE ||      \
      is_correct_type(elformat->elf_32->e_type) == FALSE ||        \
      is_correct_data(elformat->elf_32->e_ident, \
		      elformat->elf_32->e_type, elformat->elf_32->e_machine, \
		      elformat->elf_32->e_version) == FALSE)
    return (FALSE);
  return (TRUE);
}
