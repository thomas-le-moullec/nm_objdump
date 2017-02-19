##
## Makefile for Makefile in /home/le-mou_t/rendu/TEK2/Module_Memoire/PSU_2016_nmobjdump
## 
## Made by Thomas LE MOULLEC
## Login   <le-mou_t@epitech.net>
## 
## Started on  Sun Feb 19 12:08:27 2017 Thomas LE MOULLEC
## Last update Sun Feb 19 12:40:08 2017 Thomas LE MOULLEC
##

CC      	=       gcc

SRCS_NM  	=       ./nm/my_nm.c

SRCS_OBJ  	=       ./objdump/my_objdump.c

NAME_NM 	=       my_nm

NAME_OBJ 	=       my_objdump

OBJS_NM 	=       $(SRCS_NM:.c=.o)

OBJS_OBJ 	=       $(SRCS_OBJ:.c=.o)

IFLAGS		=	-I./includes/

CFLAGS  	=       -Wall -Werror -Wextra $(IFLAGS)

all :           $(NAME_OBJ) $(NAME_NM)

$(NAME_OBJ) :   $(OBJS_OBJ)
		$(CC) $(CFLAGS) -o $(NAME_OBJ) $(OBJS_OBJ)

$(NAME_NM) :    $(OBJS_NM)
		$(CC) -o $(NAME_NM) $(OBJS_NM)

nm :            $(NAME_NM)

objdump :       $(NAME_OBJ)

clean :
		rm -f $(OBJS_OBJ) $(OBJS_NM)

fclean :        clean
		rm -f $(NAME_OBJ) $(NAME_NM)

re_nm :         fclean nm

re_objdump :    fclean objdump

re :            fclean all
