/*
** archive.c for archive in /home/le-mou_t/rendu/TEK2/Module_Memoire/PSU_2016_nmobjdump/nm
** 
** Made by Thomas LE MOULLEC
** Login   <le-mou_t@epitech.net>
** 
** Started on  Fri Feb 24 12:51:20 2017 Thomas LE MOULLEC
** Last update Sun Feb 26 16:33:42 2017 Thomas LE MOULLEC
*/

#include "nm.h"

static BOOL	trunc_archive(unsigned char *data, t_elf *elformat)
{
  int		size;
  int		idx;

  idx = 0;
  size = 0;
  while (idx < elformat->fileSize)
    {
      if (is_separator(data, idx) == TRUE)
	size += get_size_section(data, idx - 1) + 60;
      idx++;
    }
  size += 8;
  if (size != elformat->fileSize)
    return (FALSE);
  return (TRUE);
}

static int	error_archive(int error)
{
  if (error == -2)
    return (-2);
  if (error == -4)
    fprintf(stderr, "nm: no symbol\n");
  return (0);
}

int    archive(unsigned char *file, t_elf *elformat)
{
  int   error;
  int   idx;
  BOOL	header;

  idx = 0;
  header = TRUE;
  if (trunc_archive(file, elformat) == FALSE)
    return (-3);
  while (idx < elformat->fileSize - 1)
    {
      if (is_separator(file, idx) == TRUE && header == TRUE)
	{
	  error = dump_nm(&file[idx + 2], 0, elformat);
	  if (error_archive(error) == -2)
	    return (-2);
	}
      if (is_separator(file, idx) == TRUE)
	header = TRUE;
      idx++;
    }
  return (0);
}
