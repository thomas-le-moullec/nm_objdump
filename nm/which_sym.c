/*
** which_sym.c for which_sym in /home/le-mou_t/rendu/TEK2/Module_Memoire/PSU_2016_nmobjdump/nm
** 
** Made by Thomas LE MOULLEC
** Login   <le-mou_t@epitech.net>
** 
** Started on  Sun Feb 26 16:16:59 2017 Thomas LE MOULLEC
** Last update Sun Feb 26 17:35:38 2017 Thomas LE MOULLEC
*/

#include "nm.h"

BOOL            textcode(Elf64_Shdr *parts, Elf64_Sym *symbol, \
			 int stb, int get)
{
  char                  c;

  (void)get;
  if (stb == STB_LOCAL)
    {
      if ((parts[symbol->st_shndx].sh_type == SHT_PROGBITS ||
	              parts[symbol->st_shndx].sh_type == SHT_FINI_ARRAY ||
	   parts[symbol->st_shndx].sh_type == SHT_INIT_ARRAY) &&
	  (parts[symbol->st_shndx].sh_flags == 6 ||
	   parts[symbol->st_shndx].sh_flags == 3))
	{
	  c = 't';
	  printf("%c ", my_weak(get, stb, c));
	  return (TRUE);
	}
    }
  return (FALSE);
}

BOOL            debug(Elf64_Shdr *parts, Elf64_Sym *symbol, \
		      int stb, int get)
{
  char                  c;

  if (stb == STB_LOCAL)
    {
      if ((get == STT_NOTYPE || get == STT_OBJECT) &&
	            parts[symbol->st_shndx].sh_type == SHT_PROGBITS &&
	  parts[symbol->st_shndx].sh_flags == 0)
	{
	  c = 'n';
	  printf("%c ", my_weak(get, stb, c));
	  return (TRUE);
	}
    }
  return (FALSE);
}

BOOL            indicates(Elf64_Shdr *parts, Elf64_Sym *symbol, \
			  int stb, int get)
{
  char                  c;

  if (stb == STB_LOCAL)
    {
      if (get == STT_LOOS &&
	            parts[symbol->st_shndx].sh_type == SHT_PROGBITS &&
	  parts[symbol->st_shndx].sh_flags == 6)
	{
	  c = 'i';
	  printf("%c ", my_weak(get, stb, c));
	  return (TRUE);
	}
    }
  return (FALSE);
}

BOOL            unData(Elf64_Shdr *parts, Elf64_Sym *symbol, \
		       int stb, int get)
{
  char                  c;

  if (stb == STB_LOCAL)
    {
      if ((get == STT_NOTYPE || get == STT_OBJECT || get == STT_TLS) &&
	            parts[symbol->st_shndx].sh_type == SHT_NOBITS &&
	  (parts[symbol->st_shndx].sh_flags == 3 ||
	   parts[symbol->st_shndx].sh_flags == 1027))
	{
	  c = 'b';
	  printf("%c ", my_weak(get, stb, c));
	  return (TRUE);
	}
    }
  return (FALSE);
}

BOOL            readOnly(Elf64_Shdr *parts, Elf64_Sym *symbol, \
			 int stb, int get)
{
  char                  c;

  if (stb == STB_LOCAL)
    {
      if ((get == STT_NOTYPE || get == STT_OBJECT) &&
	  (parts[symbol->st_shndx].sh_type == SHT_NOTE ||
	   parts[symbol->st_shndx].sh_type == SHT_PROGBITS) &&
	  (parts[symbol->st_shndx].sh_flags == 2 ||
	   parts[symbol->st_shndx].sh_flags == 50))
	{
	  c = 'r';
	  printf("%c ", my_weak(get, stb, c));
	  return (TRUE);
	}
    }
  return (FALSE);
}
