/*
** get_data.c for get_data in /home/le-mou_t/rendu/TEK2/Module_Memoire/PSU_2016_nmobjdump/objdump
** 
** Made by Thomas LE MOULLEC
** Login   <le-mou_t@epitech.net>
** 
** Started on  Sun Feb 19 13:56:47 2017 Thomas LE MOULLEC
** Last update Sun Feb 19 16:17:35 2017 Thomas LE MOULLEC
*/

#include "objdump.h"

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

char			*get_architecture(int machine)
{
  t_machines		architectures[] = {{EM_NONE, "None"}, {EM_M32, "WE32100"},
				       {EM_SPARC, "Sparc"}, {EM_386, "Intel 80386"},
				       {EM_68K, "MC68000"}, {EM_88K, "MC88000"},
				       {EM_860, "Intel 80860"},{EM_SPARCV9, "Sparc v9"},
				       {EM_MIPS, "MIPS R3000"}, {EM_PARISC, "HPPA"},
				       {EM_SPARC32PLUS, "Sparc v8+"},
				       {EM_PPC, "PowerPC"}, {EM_PPC64, "PowerPC64"},
				       {EM_S390, "IBM S/390"}, {EM_ARM, "ARM"},
				       {EM_SH, "Renesas / SuperH SH"},
				       {EM_IA_64, "Intel IA-64"},
				       {EM_X86_64, "i386:x86-64"}};
  int           i;

  i = 0;
  while (i < MACHINES_NBR)
    {
      if (machine == architectures[i].id)
	return (architectures[i].archi);
      i++;
    }
  return (NULL);
}
