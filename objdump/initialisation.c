/*
** initialisation.c for init in /home/le-mou_t/rendu/TEK2/Module_Memoire/PSU_2016_nmobjdump/objdump
** 
** Made by Thomas LE MOULLEC
** Login   <le-mou_t@epitech.net>
** 
** Started on  Sun Feb 19 13:48:28 2017 Thomas LE MOULLEC
** Last update Sun Feb 26 17:01:55 2017 Thomas LE MOULLEC
*/

#include "objdump.h"

SYS	init_32_Elf(t_elf *elformat, void *data)
{
  elformat->elf_32 = (Elf32_Ehdr *)data;
  if (file_specifications_32(elformat) == FALSE)
    {
      bad_format_file(elformat->file);
      return (ERROR_SYS);
    }
  if (elformat->is_archive == FALSE && \
      (int)(elformat->elf_32->e_shoff + \
	    (elformat->elf_32->e_shentsize * \
	     elformat->elf_32->e_shnum)) != elformat->filesize)
    {
      fprintf(stderr, "%s: %s: File truncated\n", binary, elformat->file);
      return (ERROR_SYS);
    }
  elformat->shdr_32 = (Elf32_Shdr *)(data + elformat->elf_32->e_shoff);
  elformat->strtab = (char *)(elformat->data + elformat->shdr_32	\
			      [elformat->elf_32->e_shstrndx].sh_offset);
  return (SYS_32);
}

SYS	init_64_Elf(t_elf *elformat, void *data)
{
  elformat->elf_64 = (Elf64_Ehdr *)data;
  if (file_specifications_64(elformat) == FALSE)
    {
      bad_format_file(elformat->file);
      return (ERROR_SYS);
    }
  if (elformat->is_archive == FALSE && \
      (int)(elformat->elf_64->e_shoff + \
	    (elformat->elf_64->e_shentsize * \
	     elformat->elf_64->e_shnum)) != elformat->filesize)
    {
      fprintf(stderr, "%s: %s: File truncated\n", binary, elformat->file);
      return (ERROR_SYS);
    }
  elformat->shdr_64 = (Elf64_Shdr *)(data + elformat->elf_64->e_shoff);
  elformat->strtab = (char *)(data + elformat->shdr_64 \
			      [elformat->elf_64->e_shstrndx].sh_offset);
  return (SYS_64);
}

SYS		init_elf(int fd, t_elf *elformat)
{
  SYS		result;

  if ((elformat->filesize = filesize(fd)) < EI_NIDENT)
    return (bad_format_file(elformat->file));
  if ((elformat->data = mmap(NULL, elformat->filesize, \
			     PROT_READ, MAP_SHARED, fd, 0)) == (void*)-1)
    return (ERROR_SYS);
  if ((is_archive(elformat)) == TRUE)
    return (check_archive(elformat));
  if ((result = file_format(elformat->data)) == SYS_32)
    return (init_32_Elf(elformat, elformat->data));
  else if (result == SYS_64)
    return (init_64_Elf(elformat, elformat->data));
  return (ERROR_SYS);
}
