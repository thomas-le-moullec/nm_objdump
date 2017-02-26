/*
** dump_obj.c for dump in /home/le-mou_t/rendu/TEK2/Module_Memoire/PSU_2016_nmobjdump/objdump
** 
** Made by Thomas LE MOULLEC
** Login   <le-mou_t@epitech.net>
** 
** Started on  Sun Feb 19 14:01:30 2017 Thomas LE MOULLEC
** Last update Sun Feb 26 18:17:55 2017 Thomas LE MOULLEC
*/

#include "objdump.h"

static void     dump_hexa_32(unsigned char *data, int bytes, \
			     int i, Elf32_Shdr *shdr)
{
  unsigned int  idx;
  unsigned char *infos;

  idx = 0;
  infos = data + bytes + shdr[i].sh_offset;
  while (idx < 16)
    {
      if (idx % 4 == 0)
	printf(" ");
      if (idx < shdr[i].sh_size - bytes)
	printf("%02x", infos[idx]);
      else
	printf("  ");
      idx++;
    }
  printf("  ");
}

static void     dump_ascii_32(unsigned char *data, int bytes, \
			      int i, Elf32_Shdr *shdr)
{
  unsigned int  idx;
  unsigned char *infos;

  idx = 0;
  infos = data + bytes + shdr[i].sh_offset;
  while (idx < 16)
    {
      if (idx < shdr[i].sh_size - bytes)
	{
	  if (infos[idx] >= ' ' && infos[idx] <= '~')
	    printf("%c", infos[idx]);
	  else
	    printf(".");
	}
      else
	printf(" ");
      idx++;
    }
  printf("\n");
}

static void     dump_section_32(Elf32_Shdr *shdr, char *strtab, \
				t_elf *elformat, int i)
{
  int           bytes;

  bytes = 0;
  printf("Contents of section %s:\n", &strtab[shdr[i].sh_name]);
  while (bytes + shdr[i].sh_offset < shdr[i].sh_offset + shdr[i].sh_size)
    {
      printf(" %04x", (int)(shdr[i].sh_addr + bytes));
      dump_hexa_32((unsigned char *)(elformat->data), bytes, i, shdr);
      dump_ascii_32((unsigned char *)(elformat->data), bytes, i, shdr);
      bytes += 16;
    }
}

static BOOL	check_error(Elf32_Shdr *shdr, char *strtab, int i)
{
  if (&strtab[shdr[i].sh_name] && shdr[i].sh_type != SHT_NULL &&	\
      shdr[i].sh_type != SHT_SHLIB && shdr[i].sh_type != SHT_SYMTAB &&	\
      shdr[i].sh_size && strcmp(&strtab[shdr[i].sh_name], ".bss") != 0 && \
      strcmp(&strtab[shdr[i].sh_name], ".rela.text") != 0 &&		\
      strcmp(&strtab[shdr[i].sh_name], ".rela.debug_info") != 0 &&	\
      strcmp(&strtab[shdr[i].sh_name], ".rela.debug_aranges") != 0 &&	\
      strcmp(&strtab[shdr[i].sh_name], ".rela.debug_line") != 0 &&	\
      strcmp(&strtab[shdr[i].sh_name], ".rela.eh_frame") != 0 &&
      strcmp(&strtab[shdr[i].sh_name], ".rela.debug_pubnames") != 0 &&	\
      strcmp(&strtab[shdr[i].sh_name], ".rel.text") != 0 &&		\
      strcmp(&strtab[shdr[i].sh_name], ".rel.debug_info") != 0 &&	\
      strcmp(&strtab[shdr[i].sh_name], ".rel.debug_arranges") != 0 &&	\
      strcmp(&strtab[shdr[i].sh_name], ".rel.eh_frame") != 0 &&		\
      strcmp(&strtab[shdr[i].sh_name], ".rel.debug_line") != 0 &&	\
      strcmp(&strtab[shdr[i].sh_name], ".rel.debug_pubnames") != 0)
    return (TRUE);
  return (FALSE);
}

BOOL     dump_obj_32(Elf32_Shdr *shdr, char *strtab, \
		     int shnum, t_elf *elformat)
{
  int    i;

  i = 0;
  dump_header(elformat, elformat->elf_32->e_ident, elformat->elf_32->e_type, \
	      elformat->elf_32->e_machine);
  dump_addr(elformat->elf_32->e_entry, elformat);
  while (i < shnum && global_option_f == FALSE)
    {
      if ((void *)elformat->elf_32 + elformat->filesize < (void *)&shdr[i])
	return (bad_format_file(elformat->file));
      if (strcmp(&strtab[shdr[i].sh_name], ".shstrtab") == 0)
	break ;
      if (check_error(shdr, strtab, i) == TRUE)
	dump_section_32(shdr, strtab, elformat, i);
      i++;
    }
  return (TRUE);
}
