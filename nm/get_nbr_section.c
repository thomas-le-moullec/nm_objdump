/*
** get_nbr_section.c for get_nbr_section in /home/le-mou_t/rendu/TEK2/Module_Memoire/PSU_2016_nmobjdump/nm
** 
** Made by Thomas LE MOULLEC
** Login   <le-mou_t@epitech.net>
** 
** Started on  Fri Feb 24 12:54:12 2017 Thomas LE MOULLEC
** Last update Fri Feb 24 12:55:05 2017 Thomas LE MOULLEC
*/

#include "nm.h"

static int     my_getnbr_space(unsigned char *str)
{
  int   res;
  int   i;

  res = 0;
  i = 0;
  while (str[i] >= '0' && str[i] <= '9')
    {
      res *= 10;
      res += str[i] - '0';
      i++;
    }
  return (res);
}

int     get_nbr_size(unsigned char *str, int i)
{
  i--;
  while (i > 0 && (str[i] == ' ' || str[i] == '/' || str[i] == '\\' ||
		   str[i] == '`' || str[i] == '\n'))
    i--;
  while (i > 0 && str[i] >= '0' && str[i] <= '9')
    i--;
  i++;
  return (my_getnbr_space(&str[i]));
}
