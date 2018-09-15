/*
** 
** Made by Thomas LE MOULLEC
** 
** Started on  Fri Feb 24 12:31:52 2017 Thomas LE MOULLEC
** Last update Sat Feb 25 13:57:08 2017 Thomas LE MOULLEC
*/

#include "nm.h"

int             main(int ac, char **av)
{
  int           index;

  index = 1;
  if (ac == 1)
    return (my_nm("a.out", 1));
  while (index < ac)
    my_nm(av[index++], ac);
  return (0);
}
