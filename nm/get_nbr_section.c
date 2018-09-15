/*
** 
** Made by Thomas LE MOULLEC
** 
** Started on  Fri Feb 24 12:54:12 2017 Thomas LE MOULLEC
** Last update Sun Feb 26 16:33:27 2017 Thomas LE MOULLEC
*/

#include "nm.h"

int     get_size_section(unsigned char *str, int i)
{
  int	result;

  result = 0;
  while (i > 0 && (str[i] == ' ' || str[i] == '/' || str[i] == '\\' ||
		   str[i] == '`' || str[i] == '\n'))
    i--;
  while (i > 0 && str[i] >= '0' && str[i] <= '9')
    i--;
  i++;
  while (str[i] >= '0' && str[i] <= '9')
    {
      result *= 10;
      result += str[i++] - '0';
    }
  return (result);
}
