/*
** options.c for options in /home/le-mou_t/rendu/TEK2/Module_Memoire/PSU_2016_nmobjdump/objdump
** 
** Made by Thomas LE MOULLEC
** Login   <le-mou_t@epitech.net>
** 
** Started on  Sun Feb 19 13:43:51 2017 Thomas LE MOULLEC
** Last update Sun Feb 19 13:45:20 2017 Thomas LE MOULLEC
*/

#include "objdump.h"

static BOOL             flag_f()
{
  global_option_f = TRUE;
  return (TRUE);
}

char			**parse_options(char **av, int *ac)
{
  int                   idx;
  int                   index;
  char                  **args;

  index = 0;
  idx = 1;
  if ((args = malloc(sizeof(**args) * (*ac))) == NULL)
    exit(-1);
  while (idx < *ac)
    {
      if (strcmp(av[idx], "-f") == 0) //ptr on functions
	flag_f();
      else
	{
	  global_only_flags = FALSE;
	  args[index] = strdup(av[idx]);
	  index++;
	}
      idx++;
    }
  *ac = index;
  return (args);
}
