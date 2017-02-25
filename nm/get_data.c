/*
** get_data.c for get_data in /home/le-mou_t/rendu/TEK2/Module_Memoire/PSU_2016_nmobjdump/nm
** 
** Made by Thomas LE MOULLEC
** Login   <le-mou_t@epitech.net>
** 
** Started on  Sat Feb 25 17:10:44 2017 Thomas LE MOULLEC
** Last update Sat Feb 25 17:11:49 2017 Thomas LE MOULLEC
*/

#include "nm.h"

char             *get_magic(unsigned char *identifier)
{
  char                  *magic;

  if ((magic = malloc(sizeof(char) * 4 + 1)) == NULL)
    return (NULL);
  magic[0] = identifier[EI_MAG0];
  magic[1] = identifier[EI_MAG1];
  magic[2] = identifier[EI_MAG2];
  magic[3] = identifier[EI_MAG3];
  magic[4] = '\0';
  return (magic);
}
