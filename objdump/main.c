/*
** main.c for main in /home/le-mou_t/rendu/TEK2/Module_Memoire/PSU_2016_nmobjdump/objdump
** 
** Made by Thomas LE MOULLEC
** Login   <le-mou_t@epitech.net>
** 
** Started on  Sun Feb 19 13:43:10 2017 Thomas LE MOULLEC
** Last update Sun Feb 19 13:45:11 2017 Thomas LE MOULLEC
*/

#include "objdump.h"

int             main(int ac, char **av)
{
  int           index;
  char          **args;

  index = 0;
  binary = av[0];
  if (ac == 1)
    return (my_objdump("a.out"));
  args = parse_options(av, &ac);
  if (global_only_flags == TRUE)
    return (my_objdump("a.out"));
  while (index < ac)
    {
      my_objdump(args[index]);
      index++;
    }
  return (0);
}
