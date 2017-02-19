/*
** objdump.c for objdump in /home/le-mou_t/rendu/TEK2/Module_Memoire/PSU_2016_nmobjdump
** 
** Made by Thomas LE MOULLEC
** Login   <le-mou_t@epitech.net>
** 
** Started on  Wed Feb 15 09:06:22 2017 Thomas LE MOULLEC
** Last update Sun Feb 19 13:31:44 2017 Thomas LE MOULLEC
*/

#include "objdump.h"

BOOL global_option_f		= FALSE;
BOOL global_only_flags		= TRUE;
char *binary			= NULL;

static BOOL			bad_format_file(char *file)
{
  fprintf(stderr, "%s : %s: File format not recognized\n", binary, file);
  return (FALSE);
}

static char		*get_magic(unsigned char *identifier)
{
  char			*magic;

  if ((magic = malloc(sizeof(char) * 4 + 1)) == NULL)
    return (NULL);
  magic[0] = identifier[EI_MAG0];
  magic[1] = identifier[EI_MAG1];
  magic[2] = identifier[EI_MAG2];
  magic[3] = identifier[EI_MAG3];
  magic[4] = '\0';
  return (magic);
}

static BOOL		is_elf(char *magic)
{
  if (magic[0] == ELFMAG0 && magic[1] == ELFMAG1 && \
      magic[2] == ELFMAG2 && magic[3] == ELFMAG3)
    return (TRUE);
  return (FALSE);
}

static BOOL		is_correct_class(unsigned char *identifier)
{
  if (identifier[EI_CLASS] == ELFCLASS64)
    return (TRUE);
  if (identifier[EI_CLASS] == ELFCLASS32)
    return (TRUE);
  return (FALSE);
}

static int		filesize(int fd)
{
  return (lseek(fd, 0, SEEK_END));
}

static BOOL		is_correct_type(int type)
{
  if (type == ET_NONE)
    return (FALSE);
  return (TRUE);
}

static BOOL		is_correct_data(Elf64_Ehdr *elf)
{
  if (elf->e_ident[EI_CLASS] == ELFCLASSNONE || \
      elf->e_ident[EI_DATA] == ELFDATANONE || \
      elf->e_ident[EI_VERSION] == EV_NONE ||  \
      elf->e_type == ET_NONE || \
      elf->e_machine == EM_NONE || \
      elf->e_version == EV_NONE)
    return (FALSE);
  return (TRUE);
}

static BOOL		file_specifications(t_elf *elformat)
{
  if (is_elf(get_magic(elformat->elf->e_ident)) == FALSE ||	\
      is_correct_class(elformat->elf->e_ident) == FALSE ||	\
      is_correct_type(elformat->elf->e_type) == FALSE ||
      is_correct_data(elformat->elf) == FALSE)
    return (FALSE);
  return (TRUE);
}

static char		*get_architecture(t_elf *elformat)
{
  t_machines        architectures[] = {{EM_NONE, "None"}, {EM_M32, "WE32100"},
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
  int		i;

  i = 0;
  while (i < MACHINES_NBR)
    {
      if (elformat->elf->e_machine == architectures[i].id)
	return (architectures[i].archi);
      i++;
    }
  return (NULL);
}

static void	dump_header(t_elf *elformat)
{
  printf("\n");
  if (elformat->elf->e_ident[EI_CLASS] == ELFCLASS64)
    elformat->class = 64;
  else
    elformat->class = 32;
  printf("%s:     file format elf%d-x86-%d\n", elformat->file,	\
	 elformat->class, elformat->class);
  printf("architecture: %s, flags ", get_architecture(elformat));
  if (elformat->elf->e_type == ET_REL)
    printf("Pas cool\n");
  else if (elformat->elf->e_type == ET_EXEC)
    printf("0x00000112:\nEXEC_P, HAS_SYMS, D_PAGED\n");
  else if (elformat->elf->e_type == ET_DYN)
    printf("0x00000150:\nHAS_SYMS, DYNAMIC, D_PAGED\n");
  else
    fprintf(stderr, "An unknown type\n");
  printf("start address 0x%016lx\n\n", elformat->elf->e_entry);
}

static void	dump_hexa(unsigned char *data, int bytes, int i, Elf64_Shdr *shdr)
{
  unsigned int	idx;
  unsigned char	*infos;

  idx = 0;
  infos = data + bytes + shdr[i].sh_offset;
  while (idx < 16)
    {
      if (idx % 4 == 0)
	printf(" ");
      if (idx < shdr[i].sh_size - bytes)
	printf("%02x", infos[idx]);
      else
	printf("  ");
      idx++;
    }
  printf("  ");
}

static void	dump_ascii(unsigned char *data, int bytes, int i, Elf64_Shdr *shdr)
{
  unsigned int	idx;
  unsigned char	*infos;

  idx = 0;
  infos = data + bytes + shdr[i].sh_offset;
  while (idx < 16)
    {
      if (idx < shdr[i].sh_size - bytes)
	{
	  if (infos[idx] >= ' ' && infos[idx] <= '~')
	    printf("%c", infos[idx]);
	  else
	    printf(".");
	}
      else
	printf(" ");
      idx++;
    }
  printf("\n");
}

static void	dump_section(Elf64_Shdr *shdr, char *strtab, t_elf *elformat, int i)
{
  int		bytes;

  bytes = 0;
  printf("Contents of section %s:\n", &strtab[shdr[i].sh_name]);
  while (bytes + shdr[i].sh_offset < shdr[i].sh_offset + shdr[i].sh_size)
    {
      printf(" %04x", (int)(shdr[i].sh_addr + bytes));
      dump_hexa((unsigned char *)(elformat->data), bytes, i, shdr);
      dump_ascii((unsigned char *)(elformat->data), bytes, i, shdr);
      bytes += 16;
    }
}

static BOOL	dump_obj(Elf64_Shdr *shdr, char *strtab, int shnum, t_elf *elformat)
{
  int    i;

  i = 0;
  dump_header(elformat);
  while (i < shnum && global_option_f == FALSE)
    {
      if ((void *)elformat->elf + elformat->filesize < (void *)&shdr[i])
	return (bad_format_file(elformat->file));
      if (strcmp(&strtab[shdr[i].sh_name], ".shstrtab") == 0)
	break ;
      if (&strtab[shdr[i].sh_name] && shdr[i].sh_type != SHT_NULL && \
	  shdr[i].sh_type != SHT_SHLIB && shdr[i].sh_type != SHT_SYMTAB &&
	  shdr[i].sh_size && strcmp(&strtab[shdr[i].sh_name], ".bss") != 0)
	dump_section(shdr, strtab, elformat, i);
      i++;
    }
  return (TRUE);
}

static BOOL		init_elf(int fd, t_elf *elformat)
{
  if ((elformat->filesize = filesize(fd)) < EI_NIDENT)
    return (bad_format_file(elformat->file));
  elformat->data = mmap(NULL, elformat->filesize, PROT_READ, MAP_SHARED, fd, 0);
  elformat->elf = (Elf64_Ehdr *)elformat->data;
  if (file_specifications(elformat) == FALSE)
    return (bad_format_file(elformat->file));
  elformat->shdr = (Elf64_Shdr *)(elformat->data + elformat->elf->e_shoff);
  elformat->strtab = (char *)(elformat->data + elformat->shdr \
			      [elformat->elf->e_shstrndx].sh_offset);
  return (TRUE);
}

static BOOL		flag_f()
{
  global_option_f = TRUE;
  return (TRUE);
}

static BOOL		my_objdump(char *filename)
{
  int		fd;
  t_elf		*elformat;

  if ((elformat = malloc(sizeof(*elformat))) == NULL)
    exit(-1);
  if ((fd = open(filename, O_RDONLY)) != -1)
    {
      elformat->file = filename;
      if ((init_elf(fd, elformat)) == FALSE)
	return (FALSE);
      dump_obj(elformat->shdr, elformat->strtab, elformat->elf->e_shnum, elformat);
      close(fd);
      return (TRUE);
    }
  fprintf(stderr, "%s: '%s': No such file\n", binary, filename);
  return (FALSE);
}

static char		**parse_options(char **av, int *ac)
{
  int			idx;
  int			index;
  char			**args;

  index = 0;
  idx = 1;
  if ((args = malloc(sizeof(**args) * (*ac))) == NULL)
    exit(-1);
  while (idx < *ac)
    {
      if (strcmp(av[idx], "-f") == 0) //ptr on functions
	flag_f();
      else
	{
	  global_only_flags = FALSE;
	  args[index] = strdup(av[idx]);
	  index++;
	}
      idx++;
    }
  *ac = index;
  return (args);
}

int		main(int ac, char **av)
{
  int		index;
  char		**args;

  index = 0;
  binary = av[0];
  if (ac == 1)
    return (my_objdump("a.out"));
  args = parse_options(av, &ac);
  if (global_only_flags == TRUE)
    return (my_objdump("a.out"));
  while (index < ac)
    {
      my_objdump(args[index]);
      index++;
    }
  return (0);
}
