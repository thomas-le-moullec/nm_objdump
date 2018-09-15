/*
** 
** Made by Thomas LE MOULLEC
** 
** Started on  Fri Feb 24 12:58:46 2017 Thomas LE MOULLEC
** Last update Sun Feb 26 16:44:57 2017 Thomas LE MOULLEC
*/

#include "nm.h"

static BOOL	is_in_symboles(t_elf *elformat, Elf64_Shdr *sh, \
			       BOOL is_sht, int i)
{
  if (sh[i].sh_type == SHT_SYMTAB)
    {
      elformat->strtab = (char *)elformat->elf + sh[sh[i].sh_link].sh_offset;
      elformat->sym = (void *)elformat->elf + sh[i].sh_offset;
      is_sht = TRUE;
    }
  return (is_sht);
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
