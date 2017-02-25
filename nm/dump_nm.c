/*
** dump_nm.c for dump_nm in /home/le-mou_t/rendu/TEK2/Module_Memoire/PSU_2016_nmobjdump/nm
** 
** Made by Thomas LE MOULLEC
** Login   <le-mou_t@epitech.net>
** 
** Started on  Fri Feb 24 13:55:47 2017 Thomas LE MOULLEC
** Last update Sat Feb 25 21:30:45 2017 Thomas LE MOULLEC
*/

#include "nm.h"

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
  char          c;

  idx = 0;
  while (elformat->tab[idx] != NULL)
    {
      if (elformat->tab[idx]->st_info != STT_FILE &&			\
	  strlen(&elformat->strtab[elformat->tab[idx]->st_name]) != 0	\
	  && elformat->tab[idx]->st_shndx != SHN_ABS)
	{
	  print_value(elformat, idx);
	  c = catch_sym(elformat->tab[idx]->st_shndx,	  \
			ELF64_ST_TYPE(elformat->tab[idx]->st_info), \
			ELF64_ST_BIND(elformat->tab[idx]->st_info), \
			sections, elformat->tab[idx]);
	  printf("%c ", c);
	  printf("%s\n", &elformat->strtab[elformat->tab[idx]->st_name]);
	}
      idx++;
    }
}
