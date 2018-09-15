/*
** 
** Made by Thomas LE MOULLEC
** 
** Started on  Fri Feb 24 13:09:52 2017 Thomas LE MOULLEC
** Last update Sun Feb 26 17:44:52 2017 Thomas LE MOULLEC
*/

#include "nm.h"

static char            *no_underscore(char *str)
{
  char          *new;
  int           i;
  int           j;

  i = 0;
  j = 0;
  new = NULL;
  if ((new = malloc((strlen(str) + 1) * sizeof(*new))) == NULL)
    exit(-1);
  while (str[i])
    {
      if (str[i] != '_')
	new[j++] = str[i];
      i++;
    }
  new[j] = '\0';
  return (new);
}

static BOOL		is_data_start(t_elf *elformat, int i)
{
  if (elformat->tab[(i)] && elformat->tab[(i) + 1] && \
      strcasecmp(&elformat->strtab[elformat->tab[i]->st_name], \
		 "data_start") == 0 && \
      strcasecmp(&elformat->strtab[elformat->tab[i + 1]->st_name], \
		 "__data_start") == 0)
    return (TRUE);
  return (FALSE);
}

static int               sort_nm(t_elf *elformat, int i)
{
  if (is_data_start(elformat, i) == TRUE)
    {
      elformat->sym = elformat->tab[i];
      elformat->tab[i] = elformat->tab[i + 1];
      elformat->tab[i + 1] = elformat->sym;
      i = 0;
    }
  return (i);
}

static int		sort_in_loop(t_elf *elformat, int i)
{
  i = sort_nm(elformat, i);
  if (elformat->tab[i] && elformat->tab[i + 1] &&			\
      strcasecmp(no_underscore(&elformat->strtab[elformat->tab[i]->st_name]), \
		 no_underscore(&elformat->strtab[elformat->tab		\
						 [i + 1]->st_name])) > 0)
    {
      elformat->sym = elformat->tab[i];
      elformat->tab[i] = elformat->tab[i + 1];
      elformat->tab[i + 1] = elformat->sym;
      i = -1;
    }
  return (i);
}

void			sort_symboles(t_elf *elformat)
{
  int           size;
  int           i;

  size = 0;
  while (elformat->tab[size] != NULL)
    size++;
  i = 0;
  while (i < size)
    {
      i = sort_in_loop(elformat, i);
      i++;
    }
}
