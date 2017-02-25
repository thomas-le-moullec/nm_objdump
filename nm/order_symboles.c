
/*
** order_symboles.c for order_symboles in /home/le-mou_t/rendu/TEK2/Module_Memoire/PSU_2016_nmobjdump/nm
** 
** Made by Thomas LE MOULLEC
** Login   <le-mou_t@epitech.net>
** 
** Started on  Fri Feb 24 13:09:52 2017 Thomas LE MOULLEC
** Last update Sat Feb 25 10:12:05 2017 Thomas LE MOULLEC
*/

#include "nm.h"

char            *in_case(char *str)
{
  char          *new;
  int           i;
  int           j;

  i = 0;
  j = 0;
  new = NULL;
  if ((new = malloc((strlen(str) + 1) * sizeof(*new))) == NULL)
    return (NULL);
  while (str[i] == '_' && str[i] != '\0')
    i++;
  while (str[i] != '\0')
    {
      while (str[i] == '_' && str[i] != '\0')
	i++;
      if (str[i] != '\0')
	{
	  new[j] = str[i];
	  j++;
	  i++;
	}
    }
  new[j] = '\0';
  return (new);
}

static Elf64_Sym               **swap_data(Elf64_Sym **tab, char *strtab, int *i)
{
  Elf64_Sym             *tmp;

  if (tab[(*i)] && tab[(*i) + 1] &&                                  \
      strcasecmp(&strtab[tab[(*i)]->st_name], "data_start") == 0 &&     \
      strcasecmp(&strtab[tab[(*i) + 1]->st_name], "__data_start") == 0)
    {
      tmp = tab[(*i)];
      tab[(*i)] = tab[(*i) + 1];
      tab[(*i) + 1] = tmp;
      (*i) = 0;
    }
  return (tab);
}

Elf64_Sym       **order_tab(Elf64_Sym **tab, char *strtab)
{
  Elf64_Sym     *tmp;
  int           size;
  int           i;

  size = 0;
  while (tab[size] != NULL)
    size++;
  i = 0;
  while (i < size)
    {
      tab = swap_data(tab, strtab, &i);
      if (tab[i] && tab[i + 1] &&                        \
	  strcasecmp(in_case(&strtab[tab[i]->st_name]),                 \
		     in_case(&strtab[tab[i + 1]->st_name])) > 0)
	{
	  tmp = tab[i];
	  tab[i] = tab[i + 1];
	  tab[i + 1] = tmp;
	  i = -1;
	}
      i++;
    }
  return (tab);
}
