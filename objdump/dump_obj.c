/*
** dump_obj.c for dump in /home/le-mou_t/rendu/TEK2/Module_Memoire/PSU_2016_nmobjdump/objdump
** 
** Made by Thomas LE MOULLEC
** Login   <le-mou_t@epitech.net>
** 
** Started on  Sun Feb 19 14:01:30 2017 Thomas LE MOULLEC
** Last update Fri Feb 24 10:32:33 2017 Thomas LE MOULLEC
*/

#include "objdump.h"

static void     dump_header(t_elf *elformat, unsigned char *identifier, int type, long unsigned int entry, int machine)
{
  printf("\n");
  if (identifier[EI_CLASS] == ELFCLASS64)
    elformat->class = 64;
  else
    elformat->class = 32;
  if (elformat->is_archive == FALSE)
    printf("%s", elformat->file);
  else
    printf("%s", elformat->obj_archive);
  printf(":     file format elf%d", elformat->class);
  if (elformat->class == 64)
    printf("-x86-%d\n", elformat->class);
  else
    printf("-i386\n");
  if (strcmp(get_architecture(machine), "Intel 80386") == 0 && \
      elformat->class == 32)
    printf("architecture: i386, flags ");
  else
    printf("architecture: %s, flags ", get_architecture(machine));
  if (type == ET_REL)
    printf("0x00000011:\nHAS_RELOC, HAS_SYMS\n");
  else if (type == ET_EXEC)
    printf("0x00000112:\nEXEC_P, HAS_SYMS, D_PAGED\n");
  else if (type == ET_DYN)
    printf("0x00000150:\nHAS_SYMS, DYNAMIC, D_PAGED\n");
  else
    fprintf(stderr, "An unknown type\n");
  if (elformat->class == 64)
    printf("start address 0x%016lx\n\n", entry);
  else
    printf("start address 0x%08lx\n\n", entry);
}

static void     dump_hexa_64(unsigned char *data, int bytes, int i, Elf64_Shdr *shdr)
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

static void     dump_ascii_64(unsigned char *data, int bytes, int i, Elf64_Shdr *shdr)
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

static void     dump_hexa_32(unsigned char *data, int bytes, int i, Elf32_Shdr *shdr)
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

static void     dump_ascii_32(unsigned char *data, int bytes, int i, Elf32_Shdr *shdr)
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

static void     dump_section_64(Elf64_Shdr *shdr, char *strtab, t_elf *elformat, int i)
{
  int           bytes;

  bytes = 0;
  printf("Contents of section %s:\n", &strtab[shdr[i].sh_name]);
  while (bytes + shdr[i].sh_offset < shdr[i].sh_offset + shdr[i].sh_size)
    {
      printf(" %04x", (int)(shdr[i].sh_addr + bytes));
      dump_hexa_64((unsigned char *)(elformat->data), bytes, i, shdr);
      dump_ascii_64((unsigned char *)(elformat->data), bytes, i, shdr);
      bytes += 16;
    }
}

static void     dump_section_32(Elf32_Shdr *shdr, char *strtab, t_elf *elformat, int i)
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

BOOL     dump_obj_64(Elf64_Shdr *shdr, char *strtab, int shnum, t_elf *elformat)
{
  int    i;

  i = 0;
  dump_header(elformat, elformat->elf_64->e_ident, elformat->elf_64->e_type, \
	      elformat->elf_64->e_entry, elformat->elf_64->e_machine);
  while (i < shnum && global_option_f == FALSE)
    {
      if ((void *)elformat->elf_64 + elformat->filesize < (void *)&shdr[i])
	return (bad_format_file(elformat->file));
      if (strcmp(&strtab[shdr[i].sh_name], ".shstrtab") == 0)
	break ;
      if (&strtab[shdr[i].sh_name] && shdr[i].sh_type != SHT_NULL &&	\
	  shdr[i].sh_type != SHT_SHLIB && shdr[i].sh_type != SHT_SYMTAB && \
	  shdr[i].sh_size && strcmp(&strtab[shdr[i].sh_name], ".bss") != 0 && \
	  strcmp(&strtab[shdr[i].sh_name], ".rela.text") != 0 &&	\
	  strcmp(&strtab[shdr[i].sh_name], ".rela.debug_info") != 0 &&	\
	  strcmp(&strtab[shdr[i].sh_name], ".rela.debug_aranges") != 0 && \
	  strcmp(&strtab[shdr[i].sh_name], ".rela.debug_line") != 0 &&	\
	  strcmp(&strtab[shdr[i].sh_name], ".rela.eh_frame") != 0)
	dump_section_64(shdr, strtab, elformat, i);
      i++;
    }
  return (TRUE);
}

BOOL     dump_obj_32(Elf32_Shdr *shdr, char *strtab, int shnum, t_elf *elformat)
{
  int    i;

  i = 0;
  dump_header(elformat, elformat->elf_32->e_ident, elformat->elf_32->e_type, \
	      elformat->elf_32->e_entry, elformat->elf_32->e_machine);
  while (i < shnum && global_option_f == FALSE)
    {
      if ((void *)elformat->elf_32 + elformat->filesize < (void *)&shdr[i])
	return (bad_format_file(elformat->file));
      if (strcmp(&strtab[shdr[i].sh_name], ".shstrtab") == 0)
	break ;
      if (&strtab[shdr[i].sh_name] && shdr[i].sh_type != SHT_NULL &&	\
	  shdr[i].sh_type != SHT_SHLIB && shdr[i].sh_type != SHT_SYMTAB && \
	  shdr[i].sh_size && strcmp(&strtab[shdr[i].sh_name], ".bss") != 0 && \
	  strcmp(&strtab[shdr[i].sh_name], ".rela.text") != 0 &&	\
	  strcmp(&strtab[shdr[i].sh_name], ".rela.debug_info") != 0 &&	\
	  strcmp(&strtab[shdr[i].sh_name], ".rela.debug_aranges") != 0 && \
	  strcmp(&strtab[shdr[i].sh_name], ".rela.debug_line") != 0 &&	\
	  strcmp(&strtab[shdr[i].sh_name], ".rela.eh_frame") != 0)
	dump_section_32(shdr, strtab, elformat, i);
      i++;
    }
  return (TRUE);
}
