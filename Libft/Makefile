SRCS = ft_atoi.c 			\
	   			ft_atoi_base.c 			\
	   			ft_bzero.c  			\
				ft_calloc.c 			\
				ft_itoa.c 				\
				ft_isalpha.c 			\
				ft_isalnum.c 			\
				ft_isascii.c 			\
				ft_isdigit.c			\
				ft_isprint.c 			\
				ft_memchr.c 			\
				ft_memcmp.c 			\
				ft_memcpy.c				\
				ft_memmove.c 			\
				ft_memset.c 			\
				ft_peek.c 				\
				ft_putchar_fd.c 		\
				ft_putendl_fd.c 		\
				ft_putnbr_fd.c 			\
				ft_putstr_fd.c 			\
				ft_split.c 				\
				ft_strlcat.c 			\
				ft_strlcpy.c 			\
				ft_strlen.c 			\
				ft_strnstr.c 			\
				ft_strcmp.c 			\
				ft_strncmp.c 			\
				ft_strchr.c 			\
				ft_strrchr.c 			\
				ft_strdup.c 			\
				ft_strjoin.c 			\
				ft_strtok.c 			\
				ft_strtrim.c 			\
				ft_strmapi.c 			\
				ft_striteri.c 			\
				ft_substr.c 			\
				ft_toupper.c 			\
				ft_tolower.c 	

SRCSB = ft_lstnew_bonus.c 	\
				ft_lstadd_front_bonus.c	\
				ft_lstsize_bonus.c 		\
				ft_lstlast_bonus.c 		\
				ft_lstadd_back_bonus.c 	\
				ft_lstdelone_bonus.c 	\
				ft_lstclear_bonus.c 	\
				ft_lstiter_bonus.c 		\
				ft_lstmap_bonus.c 		

GNL = 	get_next_line_bonus.c

PRINTF = ft_printf.c 		\
		 		ft_putchar.c 			\
				ft_putnbr.c  			\
				ft_putunbr.c 			\
				ft_putstr.c 			\
				ft_putptr.c 			\
				ft_puthex_lower.c 		\
				ft_puthex_upper.c 		

ALL_SRCS = $(SRCS) $(SRCSB) $(GNL) $(PRINTF)

ALL_OBJS = $(ALL_SRCS:.c=.o)

NAME = libft.a 

AR = ar rcs

CC			= cc
RM			= rm -f
CFLAGS 		= -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(ALL_OBJS)
	@$(AR) $(NAME) $(ALL_OBJS)
	@echo "Compilation complete"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(ALL_OBJS)

fclean: clean
	@$(RM) $(NAME)
	@echo "Clean complete"

re: fclean all

.PHONY: all clean fclean re
