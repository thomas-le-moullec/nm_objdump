/*
** symboles.c for symboles in /home/le-mou_t/rendu/TEK2/Module_Memoire/PSU_2016_nmobjdump/nm
** 
** Made by Thomas LE MOULLEC
** Login   <le-mou_t@epitech.net>
** 
** Started on  Fri Feb 24 12:58:46 2017 Thomas LE MOULLEC
** Last update Sat Feb 25 20:46:50 2017 Thomas LE MOULLEC
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

static BOOL		loop_get_symboles(int *id, Elf64_Shdr *sections, \
					  Elf64_Ehdr *elf, t_elf *elformat)
{
  int           i;
  BOOL		is_sym;

  is_sym = FALSE;
  i = 0;
  while (i < elf->e_shnum)
    {
      if (sections[i].sh_type == SHT_SYMTAB)
	{
	  is_sym = TRUE;
	  *id = sections[i].sh_link;
	  if ((elformat->tab = get_sym_tab(elf, \
					   elformat, sections, i)) == NULL)
	    return (FALSE);
	}
      i++;
    }
  if (is_sym == FALSE)
    return (FALSE);
  return (TRUE);
}

BOOL		get_symboles(Elf64_Ehdr *elf, Elf64_Shdr *sections, \
			     char **strtab, t_elf *elformat)
{
  int           id;

  id = 0;
  if (loop_get_symboles(&id, sections, elf, elformat) == FALSE)
    return (FALSE);
  if (sections[id].sh_type == SHT_STRTAB)
    (*strtab) = (char *)elf + sections[id].sh_offset;
  return (TRUE);
}
