/*
** 
** Made by Thomas LE MOULLEC
** 
** Started on  Fri Feb 24 10:22:52 2017 Thomas LE MOULLEC
** Last update Sun Feb 26 17:00:14 2017 Thomas LE MOULLEC
*/

#include "objdump.h"

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

BOOL            is_archive(t_elf *elformat)
{
  unsigned char *str;

  str = (unsigned char *)elformat->data;
  if (str && strlen((char *)str) > 8 && str[0] == '!' && str[1] == '<' && \
            str[2] == 'a' && str[3] == 'r' && \
      str[4] == 'c' && str[5] == 'h' && \
      str[6] == '>' && str[7] == '\n')
    {
      elformat->is_archive = TRUE;
      return (TRUE);
    }
  elformat->is_archive = FALSE;
  return (FALSE);
}

void             get_name_obj32(void *data, Elf32_Ehdr *elf, t_elf *elformat)
{
  Elf32_Shdr    *sct;
  Elf32_Sym     *symtab;
  char          *strtab;
  int           i;
  int		depu;

  sct = (Elf32_Shdr *)(data + elf->e_shoff);
  i = 0;
  depu = 0;
  while (i < elf->e_shnum)
    {
      if (sct[i].sh_type == SHT_SYMTAB)
	{
	  depu = 1;
	  strtab = (char *)elf + sct[sct[i].sh_link].sh_offset;
	  symtab = (void *)elf + sct[i].sh_offset;
	}
      i++;
    }
  if (depu == 0)
    exit(-1);
  elformat->obj_archive = to_obj(&strtab[symtab[1].st_name]);
}

void             get_name_obj64(void *data, Elf64_Ehdr *elf, t_elf *elformat)
{
  Elf64_Shdr    *sct;
  Elf64_Sym     *symtab;
  char          *strtab;
  int           i;
  int		depu;

  depu = 0;
  sct = (Elf64_Shdr *)(data + elf->e_shoff);
  i = 0;
  while (i < elf->e_shnum)
    {
      if (sct[i].sh_type == SHT_SYMTAB)
	{
	  depu = 1;
	  strtab = (char *)elf + sct[sct[i].sh_link].sh_offset;
	  symtab = (void *)elf + sct[i].sh_offset;
	}
      i++;
    }
  if (depu == 0)
    exit(-1);
  elformat->obj_archive = to_obj(&strtab[symtab[1].st_name]);
}
