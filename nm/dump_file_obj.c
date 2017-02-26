/*
** dump_file_obj.c for dump_file_obj in /home/le-mou_t/rendu/TEK2/Module_Memoire/PSU_2016_nmobjdump/nm
** 
** Made by Thomas LE MOULLEC
** Login   <le-mou_t@epitech.net>
** 
** Started on  Sun Feb 26 16:44:17 2017 Thomas LE MOULLEC
** Last update Sun Feb 26 16:44:41 2017 Thomas LE MOULLEC
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

void     dump_file_obj(char *src)
{
  printf("\n%s:\n", to_obj(src));
}
