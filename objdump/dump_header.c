/*
** 
** Made by Thomas LE MOULLEC
** 
** Started on  Sun Feb 26 17:15:16 2017 Thomas LE MOULLEC
** Last update Sun Feb 26 17:16:41 2017 Thomas LE MOULLEC
*/

#include "objdump.h"

void    dump_addr(long unsigned int entry, t_elf *elformat)
{
  if (elformat->class == 64)
    printf("start address 0x%016lx\n\n", entry);
  else
    printf("start address 0x%08lx\n\n", entry);
}

static void disp_flags(int type)
{
  if (type == ET_REL)
    printf("0x00000011:\nHAS_RELOC, HAS_SYMS\n");
  else if (type == ET_EXEC)
    printf("0x00000112:\nEXEC_P, HAS_SYMS, D_PAGED\n");
  else if (type == ET_DYN)
    printf("0x00000150:\nHAS_SYMS, DYNAMIC, D_PAGED\n");
  else
    fprintf(stderr, "An unknown type\n");
}

void     dump_header(t_elf *elformat, unsigned char *identifier, \
		     int type, int machine)
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
  disp_flags(type);
}
