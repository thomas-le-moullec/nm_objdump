/*
** symboles.c for symboles in /home/le-mou_t/rendu/TEK2/Module_Memoire/PSU_2016_nmobjdump/nm
** 
** Made by Thomas LE MOULLEC
** Login   <le-mou_t@epitech.net>
** 
** Started on  Fri Feb 24 12:58:46 2017 Thomas LE MOULLEC
** Last update Sat Feb 25 21:05:19 2017 Thomas LE MOULLEC
*/

#include "nm.h"

static char             *to_obj(char *name)
{
  int                   i;
  char                  *str;

  i = 0;
  if (name == NULL || (str = malloc(sizeof(*str) * strlen(name) + 1)) == NULL)
    return (NULL);
  while (name[i] && name[i] != '.')
    {
      str[i] = name[i];
      i++;
    }
  if (name[i] == '.' && name[i + 1] == 'c')
    {
      str[i++] = '.';
      str[i++] = 'o';
    }
  str[i] = '\0';
  return (str);
}

static BOOL	is_in_symboles(t_elf *elformat, Elf64_Shdr *sh, BOOL is_sht, int i)
{
  if (sh[i].sh_type == SHT_SYMTAB)
    {
      elformat->strtab = (char *)elformat->elf + sh[sh[i].sh_link].sh_offset;
      elformat->sym = (void *)elformat->elf + sh[i].sh_offset;
      is_sht = TRUE;
    }
  return (is_sht);
}

static void	dump_file_obj(char *src)
{
  printf("\n%s:\n", to_obj(src));
}

void            get_file_name(void *data, t_elf *elformat)
{
  Elf64_Shdr    *sh;
  int           i;
  BOOL		is_sht;

  sh = (Elf64_Shdr *)(data + elformat->elf->e_shoff);
  i = 0;
  is_sht = FALSE;
  while (i < elformat->elf->e_shnum)
    {
      is_sht = is_in_symboles(elformat, sh, is_sht, i);
      i++;
    }
  if (is_sht == FALSE)
    exit(-1);
  dump_file_obj(&elformat->strtab[elformat->sym[1].st_name]);
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
