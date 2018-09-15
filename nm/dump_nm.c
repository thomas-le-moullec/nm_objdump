/*
** 
** Made by Thomas LE MOULLEC
** 
** Started on  Fri Feb 24 13:55:47 2017 Thomas LE MOULLEC
** Last update Sun Feb 26 17:46:36 2017 Thomas LE MOULLEC
*/

#include "nm.h"

int global_idx = 0;

static void	print_value(t_elf *elformat, int i)
{
  if (elformat->tab[i]->st_value || elformat->tab[i]->st_shndx)
    printf("%016x ", (unsigned int)elformat->tab[i]->st_value);
  else
    printf("                 ");
}

void            print_my_nm(t_elf *elformat, Elf64_Shdr *sections)
{
  int           idx;

  idx = 0;
  while (elformat->tab[idx] != NULL)
    {
      if (elformat->tab[idx]->st_info != STT_FILE && \
	  strlen(&elformat->strtab[elformat->tab[idx]->st_name]) != 0 \
	  && elformat->tab[idx]->st_shndx != SHN_ABS)
	{
	  print_value(elformat, idx);
	  global_idx = elformat->tab[idx]->st_shndx;
	  print_symboles(sections, elformat->tab[idx], \
			 ELF64_ST_BIND(elformat->tab[idx]->st_info), \
			 ELF64_ST_TYPE(elformat->tab[idx]->st_info));
	  printf("%s\n", &elformat->strtab[elformat->tab[idx]->st_name]);
	}
      idx++;
    }
}
