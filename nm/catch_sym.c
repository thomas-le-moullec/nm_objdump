/*
** main_c.c for main in /home/le-mou_t/rendu/TEK2/Module_Memoire/PSU_2016_nmobjdump/nm
** 
** Made by Thomas LE MOULLEC
** Login   <le-mou_t@epitech.net>
** 
** Started on  Fri Feb 24 12:29:16 2017 Thomas LE MOULLEC
** Last update Sat Feb 25 10:16:44 2017 Thomas LE MOULLEC
*/

#include "nm.h"

static char		check_weak(int index, int type, int bind, char c)
{
  if (bind == STB_WEAK && type == STT_OBJECT)
    c = 'v';
  if (bind == STB_WEAK && type == STT_OBJECT && index != SHN_UNDEF)
    c = 'V';
  if (bind == STB_WEAK)
    c = 'w';
  if (bind == STB_WEAK && index != SHN_UNDEF)
    c = 'W';
  return (c);
}

char	        catch_sym(int index, int type, int bind, Elf64_Shdr *sections, Elf64_Sym *sym)
{
  char		c;

  c = ' ';
  if (bind == STB_GNU_UNIQUE)
    c = 'u';
  if (bind == STB_GLOBAL)
    {
      if (index == SHN_ABS)
	c = 'A';
      else if (index == SHN_COMMON)
	c = 'C';
      else if ((type == STT_NOTYPE || type == STT_OBJECT) &&
	       sections[sym->st_shndx].sh_type == SHT_PROGBITS &&
	       sections[sym->st_shndx].sh_flags == 3)
	c = 'D';
      else if (type == STT_OBJECT &&
	       sections[sym->st_shndx].sh_type == SHT_PROGBITS)
	c = 'R';
      else if (sections[sym->st_shndx].sh_type == SHT_NOBITS &&
	       sections[sym->st_shndx].sh_flags == 3)
      	c = 'B';
      else if (sections[sym->st_shndx].sh_flags == 0 &&
	       sections[sym->st_shndx].sh_type == SHT_NULL &&
	       index == SHN_UNDEF)
	c = 'U';
      else if (type == STT_FUNC &&
	       sections[sym->st_shndx].sh_type == SHT_PROGBITS &&
	       sections[sym->st_shndx].sh_flags == 6)
	c = 'T';
      else if (type == STT_LOOS &&
	       sections[sym->st_shndx].sh_type == SHT_PROGBITS
	       && sections[sym->st_shndx].sh_flags == 6)
	c = 'i';
      return (check_weak(index, type, bind, c));
    }

  if (bind == STB_LOCAL)
    {
      if (index == SHN_ABS)
	c = 'a';
      else if ((type == STT_NOTYPE || type == STT_OBJECT || type == STT_TLS) &&
      	       (sections[sym->st_shndx].sh_type == SHT_PROGBITS ||
		sections[sym->st_shndx].sh_type ==  SHT_DYNAMIC) &&
      	       (sections[sym->st_shndx].sh_flags == 3 ||
	       sections[sym->st_shndx].sh_flags == 1027))
        c = 'd';
      else if ((type == STT_NOTYPE || type == STT_OBJECT || type == STT_TLS) &&
      	       sections[sym->st_shndx].sh_type == SHT_NOBITS &&
	       (sections[sym->st_shndx].sh_flags == 3 ||
		sections[sym->st_shndx].sh_flags == 1027))
        c = 'b';
      else if ((type == STT_NOTYPE || type == STT_OBJECT) &&
	       (sections[sym->st_shndx].sh_type == SHT_NOTE ||
		sections[sym->st_shndx].sh_type == SHT_PROGBITS) &&
	       (sections[sym->st_shndx].sh_flags == 2 ||
		sections[sym->st_shndx].sh_flags == 50))
        c = 'r';
      else if ((sections[sym->st_shndx].sh_type == SHT_PROGBITS ||
		sections[sym->st_shndx].sh_type == SHT_FINI_ARRAY ||
	       	sections[sym->st_shndx].sh_type == SHT_INIT_ARRAY) &&
	       (sections[sym->st_shndx].sh_flags == 6 ||
		sections[sym->st_shndx].sh_flags == 3))
	c = 't';
      else if ((type == STT_NOTYPE || type == STT_OBJECT) &&
	       sections[sym->st_shndx].sh_type == SHT_PROGBITS &&
	       sections[sym->st_shndx].sh_flags == 0)
	c = 'n';
      else if (type == STT_LOOS &&
	       sections[sym->st_shndx].sh_type == SHT_PROGBITS &&
	       sections[sym->st_shndx].sh_flags == 6)
	c = 'i';
      return (check_weak(index, type, bind, c));
    }

  return (check_weak(index, type, bind, '?'));
}
