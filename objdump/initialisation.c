/*
** initialisation.c for init in /home/le-mou_t/rendu/TEK2/Module_Memoire/PSU_2016_nmobjdump/objdump
** 
** Made by Thomas LE MOULLEC
** Login   <le-mou_t@epitech.net>
** 
** Started on  Sun Feb 19 13:48:28 2017 Thomas LE MOULLEC
** Last update Sun Feb 19 14:27:44 2017 Thomas LE MOULLEC
*/

#include "objdump.h"

int              filesize(int fd)
{
  return (lseek(fd, 0, SEEK_END));
}

static BOOL             file_specifications(t_elf *elformat)
{
  if (is_elf(get_magic(elformat->elf->e_ident)) == FALSE ||     \
      is_correct_class(elformat->elf->e_ident) == FALSE ||      \
      is_correct_type(elformat->elf->e_type) == FALSE ||
      is_correct_data(elformat->elf) == FALSE)
    return (FALSE);
  return (TRUE);
}

BOOL             init_elf(int fd, t_elf *elformat)
{
  if ((elformat->filesize = filesize(fd)) < EI_NIDENT)
    return (bad_format_file(elformat->file));
  elformat->data = mmap(NULL, elformat->filesize, PROT_READ, MAP_SHARED, fd, 0);
  elformat->elf = (Elf64_Ehdr *)elformat->data;
  if (file_specifications(elformat) == FALSE)
    return (bad_format_file(elformat->file));
  elformat->shdr = (Elf64_Shdr *)(elformat->data + elformat->elf->e_shoff);
  elformat->strtab = (char *)(elformat->data + elformat->shdr \
			      [elformat->elf->e_shstrndx].sh_offset);
  return (TRUE);
}
