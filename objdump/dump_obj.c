/*
** dump_obj.c for dump in /home/le-mou_t/rendu/TEK2/Module_Memoire/PSU_2016_nmobjdump/objdump
** 
** Made by Thomas LE MOULLEC
** Login   <le-mou_t@epitech.net>
** 
** Started on  Sun Feb 19 14:01:30 2017 Thomas LE MOULLEC
** Last update Sun Feb 19 14:03:00 2017 Thomas LE MOULLEC
*/

#include "objdump.h"

static void     dump_header(t_elf *elformat)
{
  printf("\n");
  if (elformat->elf->e_ident[EI_CLASS] == ELFCLASS64)
    elformat->class = 64;
  else
    elformat->class = 32;
  printf("%s:     file format elf%d-x86-%d\n", elformat->file,  \
	 elformat->class, elformat->class);
  printf("architecture: %s, flags ", get_architecture(elformat));
  if (elformat->elf->e_type == ET_REL)
    printf("Pas cool\n");
  else if (elformat->elf->e_type == ET_EXEC)
    printf("0x00000112:\nEXEC_P, HAS_SYMS, D_PAGED\n");
  else if (elformat->elf->e_type == ET_DYN)
    printf("0x00000150:\nHAS_SYMS, DYNAMIC, D_PAGED\n");
  else
    fprintf(stderr, "An unknown type\n");
  printf("start address 0x%016lx\n\n", elformat->elf->e_entry);
}

static void     dump_hexa(unsigned char *data, int bytes, int i, Elf64_Shdr *shdr)
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

static void     dump_ascii(unsigned char *data, int bytes, int i, Elf64_Shdr *shdr)
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

static void     dump_section(Elf64_Shdr *shdr, char *strtab, t_elf *elformat, int i)
{
  int           bytes;

  bytes = 0;
  printf("Contents of section %s:\n", &strtab[shdr[i].sh_name]);
  while (bytes + shdr[i].sh_offset < shdr[i].sh_offset + shdr[i].sh_size)
    {
      printf(" %04x", (int)(shdr[i].sh_addr + bytes));
      dump_hexa((unsigned char *)(elformat->data), bytes, i, shdr);
      dump_ascii((unsigned char *)(elformat->data), bytes, i, shdr);
      bytes += 16;
    }
}

BOOL     dump_obj(Elf64_Shdr *shdr, char *strtab, int shnum, t_elf *elformat)
{
  int    i;

  i = 0;
  dump_header(elformat);
  while (i < shnum && global_option_f == FALSE)
    {
      if ((void *)elformat->elf + elformat->filesize < (void *)&shdr[i])
	return (bad_format_file(elformat->file));
      if (strcmp(&strtab[shdr[i].sh_name], ".shstrtab") == 0)
	break ;
      if (&strtab[shdr[i].sh_name] && shdr[i].sh_type != SHT_NULL && \
	            shdr[i].sh_type != SHT_SHLIB && shdr[i].sh_type != SHT_SYMTAB &&
	  shdr[i].sh_size && strcmp(&strtab[shdr[i].sh_name], ".bss") != 0)
	dump_section(shdr, strtab, elformat, i);
      i++;
    }
  return (TRUE);
}
