/*
** which_sym1.c for which_sym1 in /home/le-mou_t/rendu/TEK2/Module_Memoire/PSU_2016_nmobjdump/nm
** 
** Made by Thomas LE MOULLEC
** Login   <le-mou_t@epitech.net>
** 
** Started on  Sun Feb 26 16:19:52 2017 Thomas LE MOULLEC
** Last update Sun Feb 26 17:42:25 2017 Thomas LE MOULLEC
*/

#include "nm.h"

BOOL            my_abs(Elf64_Shdr *parts, Elf64_Sym *symbol, \
		       int stb, int get)
{
  char                  c;

  (void)get;
  (void)parts;
  (void)symbol;
  if (stb == STB_LOCAL)
    {
      if (global_idx == SHN_ABS)
	{
	  c = 'a';
	  printf("%c ", my_weak(get, stb, c));
	  return (TRUE);
	}
    }
  return (FALSE);
}

BOOL            ini_data(Elf64_Shdr *parts, Elf64_Sym *symbol, \
			 int stb, int get)
{
  char                  c;

  if (stb == STB_LOCAL)
    {
      if ((get == STT_NOTYPE || get == STT_OBJECT || get == STT_TLS) &&
	  (parts[symbol->st_shndx].sh_type == SHT_PROGBITS ||
	   parts[symbol->st_shndx].sh_type ==  SHT_DYNAMIC) &&
	  (parts[symbol->st_shndx].sh_flags == 3 ||
	   parts[symbol->st_shndx].sh_flags == 1027))
	{
	  c = 'd';
	  printf("%c ", my_weak(get, stb, c));
	  return (TRUE);
	}
    }
  return (FALSE);
}

BOOL            text(Elf64_Shdr *parts, Elf64_Sym *symbol, \
		     int stb, int get)
{
  char                  c;

  if (stb == STB_GLOBAL)
    {
      if (get == STT_FUNC &&
	            parts[symbol->st_shndx].sh_type == SHT_PROGBITS &&
	  parts[symbol->st_shndx].sh_flags == 6)
	{
	  c = 'T';
	  printf("%c ", my_weak(get, stb, c));
	  return (TRUE);
	}
    }
  return (FALSE);
}

BOOL            indirect(Elf64_Shdr *parts, Elf64_Sym *symbol, \
			 int stb, int get)
{
  char                  c;

  if (stb == STB_GLOBAL)
    {
      if (get == STT_LOOS &&
	            parts[symbol->st_shndx].sh_type == SHT_PROGBITS
	  && parts[symbol->st_shndx].sh_flags == 6)
	{
	  c = 'i';
	  printf("%c ", my_weak(get, stb, c));
	  return (TRUE);
	}
    }
  return (FALSE);
}

BOOL            undefined(Elf64_Shdr *parts, Elf64_Sym *symbol, \
			  int stb, int get)
{
  char                  c;

  (void)get;
  if (stb == STB_GLOBAL)
    {
      if (parts[symbol->st_shndx].sh_flags == 0 &&
	            parts[symbol->st_shndx].sh_type == SHT_NULL &&
	  global_idx == SHN_UNDEF)
	{
	  c = 'U';
	  printf("%c ", my_weak(get, stb, c));
	  return (TRUE);
	}
    }
  return (FALSE);
}
