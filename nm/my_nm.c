/*
** my_nm.c for my_nm in /home/le-mou_t/rendu/TEK2/Module_Memoire/PSU_2016_nmobjdump/nm
** 
** Made by Thomas LE MOULLEC
** Login   <le-mou_t@epitech.net>
** 
** Started on  Fri Feb 24 12:34:06 2017 Thomas LE MOULLEC
** Last update Sat Feb 25 17:00:45 2017 Thomas LE MOULLEC
*/

#include "nm.h"

int              filesize(int fd)
{
  return (lseek(fd, 0, SEEK_END));
}

static BOOL	error_file(char *file)
{
  fprintf(stderr, "nm: '%s': No such file\n", file);
  return (FALSE);
}

static void	print_error(t_elf *elformat)
{
  if (elformat->err == -2)
    fprintf(stderr, "nm: %s: File truncated\n", elformat->file);
  if (elformat->err == -3)
    fprintf(stderr, "nm: %s: Malformed archive\n", elformat->file);
  if (elformat->err == -4)
    fprintf(stderr, "nm: %s: no symbols\n", elformat->file);
}

static void            is_archive(void *data, t_elf *elformat)
{
  unsigned char *str;

  str = (unsigned char *)data;
  if (elformat->fileSize > EI_NIDENT)
    {
      if (str && strlen((char *)str) > 8 && str[0] == '!' && str[1] == '<' && \
	  str[2] == 'a' && str[3] == 'r' && str[4] == 'c' && str[5] == 'h' && \
	  str[6] == '>' && str[7] == '\n')
	elformat->err = archive(data, elformat);
      else
	elformat->err = dump_nm(data, 1, elformat);
    }
}

BOOL             my_nm(char *file, int ac)
{
  int           fd;
  t_elf		*elformat;
  void		*data;

  if ((elformat = malloc(sizeof(*elformat))) == NULL)
    exit(-1);
  if ((fd = open(file, O_RDONLY)) == -1)
    return (error_file(file));
  elformat->fileSize = filesize(fd);
  elformat->ac = ac;
  elformat->file = file;
  elformat->err = 0;
  if ((data = mmap(NULL, elformat->fileSize, PROT_READ, MAP_SHARED, fd, 0)) == (void*)-1)
    return (FALSE);
  is_archive(data, elformat);
  print_error(elformat);
  close(fd);
  return (TRUE);
}
