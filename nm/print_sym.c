/*
** 
** Made by Thomas LE MOULLEC
** 
** Started on  Fri Feb 24 12:29:16 2017 Thomas LE MOULLEC
** Last update Sun Feb 26 18:25:32 2017 Thomas LE MOULLEC
*/

#include "nm.h"

void			print_symboles(Elf64_Shdr *parts, Elf64_Sym *symbol, \
				       int stb, int get)
{
  t_symTab		sym[] = {{&std_undefined}, {&absolute}, \
				 {&common}, {&data}, \
				 {&my_read}, {&un_data}, \
				 {&undefined}, {&text}, \
				 {&indirect}, {&my_abs}, \
				 {&ini_data}, {&unData}, \
				 {&readOnly}, {&textcode}, \
				 {debug}, {&indicates}, \
				 {space}};
  int			i;

  i = 0;
  while (i < 17)
    {
      if ((sym[i].which(parts, symbol, stb, get)) == TRUE)
	return ;
      i++;
    }
  printf("%c ", my_weak(get, stb, '?'));
}

BOOL		space(Elf64_Shdr *parts, Elf64_Sym *symbol, \
		      int stb, int get)
{
  char			c;

  (void)parts;
  (void)symbol;
  (void)get;
  if (stb == STB_LOCAL || stb == STB_GLOBAL)
    {
      c = ' ';
      printf("%c ", my_weak(get, stb, c));
      return (TRUE);
    }
  return (FALSE);
}

BOOL		std_undefined(Elf64_Shdr *parts, Elf64_Sym *symbol, \
			      int stb, int get)
{
  char			c;

  (void)parts;
  (void)symbol;
  (void)get;
  if (stb == STB_GNU_UNIQUE)
    {
      c = 'u';
      printf("%c ", my_weak(get, stb, c));
      return (TRUE);
    }
  return (FALSE);
}

BOOL		my_weak(int get, int stb, char c)
{
  if (stb == STB_WEAK)
    c = 'w';
  if (stb == STB_WEAK && get == STT_OBJECT && global_idx != SHN_UNDEF)
    c = 'V';
  if (stb == STB_WEAK && get == STT_OBJECT)
    c = 'v';
  if (stb == STB_WEAK && global_idx != SHN_UNDEF)
    c = 'W';
  return (c);
}
