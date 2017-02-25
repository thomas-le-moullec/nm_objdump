/*
** symboles.c for symboles in /home/le-mou_t/rendu/TEK2/Module_Memoire/PSU_2016_nmobjdump/nm
** 
** Made by Thomas LE MOULLEC
** Login   <le-mou_t@epitech.net>
** 
** Started on  Fri Feb 24 12:58:46 2017 Thomas LE MOULLEC
** Last update Sat Feb 25 16:38:01 2017 Thomas LE MOULLEC
*/

#include "nm.h"

void            transformation(char *str)
{
  char          *new;
  int           i;

  i = 0;
  new = strdup(str);
  while (new[i] != '.' && new[i] != '\0')
    i++;
  if (new[i] == '.' && new[i + 1] == 'c')
    new[i + 1] = 'o';
  printf("\n%s:\n", new);
}

void            get_symbol(void *data, Elf64_Ehdr *elf)
{
  Elf64_Shdr    *sct;
  Elf64_Sym     *symtab;
  char          *strtab;
  int           i;
  int           depus;

  sct = (Elf64_Shdr *)(data + elf->e_shoff);
  i = 0;
  depus = 0;
  while (i < elf->e_shnum)
    {
      if (sct[i].sh_type == SHT_SYMTAB)
	{
	  depus = 1;
	  strtab = (char *)elf + sct[sct[i].sh_link].sh_offset;
	  symtab = (void *)elf + sct[i].sh_offset;
	}
      i++;
    }
  if (depus == 1)
    transformation(&strtab[symtab[1].st_name]);
  else
    exit(-1);
}

Elf64_Sym       **get_sym(Elf64_Ehdr *elf, Elf64_Shdr *sections, char **strtab, t_elf *elformat)
{
  Elf64_Sym     *sym;
  Elf64_Sym     **tab;
  int           size;
  int           id_sym;
  int           i;
  int           depus;

  i = 0;
  id_sym = -1;
  depus = 0;
  while (i < elf->e_shnum)
    {
      if (sections[i].sh_type == SHT_SYMTAB)
	{
	  depus = 1;
	  id_sym = sections[i].sh_link;
	  sym = (void *)elf + sections[i].sh_offset;
	  size = (sections[i].sh_size / sizeof(*sym));
	  if ((tab = get_tab(elf, (void *)elf + sections[i].sh_offset, \
			     size, elformat)) == NULL)
	    return (NULL);
	}
      i++;
    }
  if (depus == 1 && sections[id_sym].sh_type == SHT_STRTAB)
    (*strtab) = (char *)elf + sections[id_sym].sh_offset;
  if (depus == 0)
    return (NULL);
  return (tab);
}
