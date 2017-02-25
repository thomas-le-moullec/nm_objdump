/*
** dump_nm.c for dump_nm in /home/le-mou_t/rendu/TEK2/Module_Memoire/PSU_2016_nmobjdump/nm
** 
** Made by Thomas LE MOULLEC
** Login   <le-mou_t@epitech.net>
** 
** Started on  Fri Feb 24 13:55:47 2017 Thomas LE MOULLEC
** Last update Sat Feb 25 10:08:45 2017 Thomas LE MOULLEC
*/

#include "nm.h"

void            print_symb(Elf64_Sym **tab, char *strtab, Elf64_Shdr *sections)
{
  int           i;
  char          c;

  i = 0;
  while (tab[i] != NULL)
    {
      if (tab[i]->st_info != STT_FILE && strlen(&strtab[tab[i]->st_name]) != 0 \
	  && tab[i]->st_shndx != SHN_ABS)
	{
	  if (tab[i]->st_value || tab[i]->st_shndx)
	    printf("%016x ", (unsigned int)tab[i]->st_value);
	  else
	    printf("                 ");
	  c = catch_sym(tab[i]->st_shndx,
			ELF64_ST_TYPE(tab[i]->st_info),
			ELF64_ST_BIND(tab[i]->st_info),
			sections, tab[i]);
	  printf("%c ", c);
	  printf("%s\n", &strtab[tab[i]->st_name]);
	}
      i++;
    }
}
