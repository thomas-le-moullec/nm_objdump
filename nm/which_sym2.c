/*
** 
** Made by Thomas LE MOULLEC
** 
** Started on  Sun Feb 26 16:22:40 2017 Thomas LE MOULLEC
** Last update Sun Feb 26 17:38:57 2017 Thomas LE MOULLEC
*/

#include "nm.h"

BOOL            common(Elf64_Shdr *parts, Elf64_Sym *symbol, \
		       int stb, int get)
{
  char                  c;

  (void)parts;
  (void)symbol;
  (void)get;
  if (stb == STB_GLOBAL)
    {
      if (global_idx == SHN_COMMON)
	{
	  c = 'C';
	  printf("%c ", my_weak(get, stb, c));
	  return (TRUE);
	}
    }
  return (FALSE);
}

BOOL            data(Elf64_Shdr *parts, Elf64_Sym *symbol, \
		     int stb, int get)
{
  char                  c;

  if (stb == STB_GLOBAL)
    {
      if ((get == STT_NOTYPE || get == STT_OBJECT) &&
	            parts[symbol->st_shndx].sh_type == SHT_PROGBITS &&
	  parts[symbol->st_shndx].sh_flags == 3)
	{
	  c = 'D';
	  printf("%c ", my_weak(get, stb, c));
	  return (TRUE);
	}
    }
  return (FALSE);
}

BOOL            my_read(Elf64_Shdr *parts, Elf64_Sym *symbol, \
			int stb, int get)
{
  char                  c;

  if (stb == STB_GLOBAL)
    {
      if (get == STT_OBJECT &&
	  parts[symbol->st_shndx].sh_type == SHT_PROGBITS)
	{
	  c = 'R';
	  printf("%c ", my_weak(get, stb, c));
	  return (TRUE);
	}
    }
  return (FALSE);
}

BOOL            un_data(Elf64_Shdr *parts, Elf64_Sym *symbol, \
			int stb, int get)
{
  char                  c;

  (void)get;
  if (stb == STB_GLOBAL)
    {
      if (parts[symbol->st_shndx].sh_type == SHT_NOBITS &&
	  parts[symbol->st_shndx].sh_flags == 3)
	{
	  c = 'B';
	  printf("%c ", my_weak(get, stb, c));
	  return (TRUE);
	}
    }
  return (FALSE);
}

BOOL            absolute(Elf64_Shdr *parts, Elf64_Sym *symbol, \
			 int stb, int get)
{
  char                  c;

  (void)parts;
  (void)symbol;
  (void)get;
  if (stb == STB_GLOBAL)
    {
      if (global_idx == SHN_ABS)
	{
	  c = 'A';
	  printf("%c ", my_weak(get, stb, c));
	  return (TRUE);
	}
    }
  return (FALSE);
}
