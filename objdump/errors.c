/*
** errors.c for errors in /home/le-mou_t/rendu/TEK2/Module_Memoire/PSU_2016_nmobjdump/objdump
** 
** Made by Thomas LE MOULLEC
** Login   <le-mou_t@epitech.net>
** 
** Started on  Sun Feb 19 13:52:32 2017 Thomas LE MOULLEC
** Last update Sun Feb 19 13:52:59 2017 Thomas LE MOULLEC
*/

#include "objdump.h"

BOOL                     bad_format_file(char *file)
{
  fprintf(stderr, "%s : %s: File format not recognized\n", binary, file);
  return (FALSE);
}
