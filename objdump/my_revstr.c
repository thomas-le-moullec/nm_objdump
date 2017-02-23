/*
** my_revstr.c for my_revstr in /home/le-mou_t/rendu/TEK2/Module_Memoire/PSU_2016_nmobjdump
** 
** Made by Thomas LE MOULLEC
** Login   <le-mou_t@epitech.net>
** 
** Started on  Wed Feb 22 17:40:13 2017 Thomas LE MOULLEC
** Last update Wed Feb 22 17:53:18 2017 Thomas LE MOULLEC
*/

#include "objdump.h"

char		*my_revstr(char *src)
{
  char		*result;
  int		i;
  int		idx;

  i = strlen(src) - 1;
  idx = 0;
  if ((result = malloc(sizeof(*src) * (strlen(src) + 1))) == NULL)
    return (NULL);
  while (i >= 0)
    {
      result[idx] = src[i];
      idx++;
      i--;
    }
  result[idx] = '\0';
  return (result);
}
