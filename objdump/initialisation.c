/*
** initialisation.c for init in /home/le-mou_t/rendu/TEK2/Module_Memoire/PSU_2016_nmobjdump/objdump
** 
** Made by Thomas LE MOULLEC
** Login   <le-mou_t@epitech.net>
** 
** Started on  Sun Feb 19 13:48:28 2017 Thomas LE MOULLEC
** Last update Sun Feb 19 16:39:53 2017 Thomas LE MOULLEC
*/

#include "objdump.h"

int              filesize(int fd)
{
  return (lseek(fd, 0, SEEK_END));
}

static BOOL             file_specifications_64(t_elf *elformat)
{
  if (is_elf(get_magic(elformat->elf_64->e_ident)) == FALSE ||     \
      is_correct_class(elformat->elf_64->e_ident) == FALSE ||      \
      is_correct_type(elformat->elf_64->e_type) == FALSE ||		\
      is_correct_data(elformat->elf_64->e_ident,			\
		      elformat->elf_64->e_type, elformat->elf_64->e_machine, \
		      elformat->elf_64->e_version) == FALSE)
    return (FALSE);
  return (TRUE);
}

static BOOL             file_specifications_32(t_elf *elformat)
{
  if (is_elf(get_magic(elformat->elf_32->e_ident)) == FALSE ||     \
      is_correct_class(elformat->elf_32->e_ident) == FALSE ||      \
      is_correct_type(elformat->elf_32->e_type) == FALSE ||	   \
      is_correct_data(elformat->elf_32->e_ident, \
		      elformat->elf_32->e_type, elformat->elf_32->e_machine, \
		      elformat->elf_32->e_version) == FALSE)
    return (FALSE);
  return (TRUE);
}

static SYS            file_format(void *data)
{
  unsigned char   *str;

  str = (unsigned char *)data;
  if (str[4] == ELFCLASS32)
    return (SYS_32);
  if (str[4] == ELFCLASS64)
    return (SYS_64);
  return (ERROR_SYS);
}

static BOOL	init_32_Elf(t_elf *elformat)
{
  elformat->elf_32 = (Elf32_Ehdr *)elformat->data;
  if (file_specifications_32(elformat) == FALSE)
    {
      bad_format_file(elformat->file);
      return (ERROR_SYS);
    }
  elformat->shdr_32 = (Elf32_Shdr *)(elformat->data + elformat->elf_32->e_shoff);
  elformat->strtab = (char *)(elformat->data + elformat->shdr_32 \
			      [elformat->elf_32->e_shstrndx].sh_offset);
  return (SYS_32);
}

static BOOL	init_64_Elf(t_elf *elformat)
{
  elformat->elf_64 = (Elf64_Ehdr *)elformat->data;
  if (file_specifications_64(elformat) == FALSE)
    {
      bad_format_file(elformat->file);
      return (ERROR_SYS);
    }
  elformat->shdr_64 = (Elf64_Shdr *)(elformat->data + elformat->elf_64->e_shoff);
  elformat->strtab = (char *)(elformat->data + elformat->shdr_64 \
			      [elformat->elf_64->e_shstrndx].sh_offset);
  return (SYS_64);
}

SYS		init_elf(int fd, t_elf *elformat)
{
  SYS		result;

  if ((elformat->filesize = filesize(fd)) < EI_NIDENT)
    return (bad_format_file(elformat->file));
  elformat->data = mmap(NULL, elformat->filesize, PROT_READ, MAP_SHARED, fd, 0);
  if ((result = file_format(elformat->data)) == SYS_32)
    return (init_32_Elf(elformat));
  else if (result == SYS_64)
    return (init_64_Elf(elformat));
  return (ERROR_SYS);
}
