LIBFT_DIR = Libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS = src/test.c \
OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror 

INC = -I inc/ -I $(LIBFT_DIR) 
LDFLAGS = -L $(LIBFT_DIR) -lreadline -lft

NAME = minishell
RM = rm -rf

all: $(LIBFT) $(NAME)

$(LIBFT):
		@make -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
		@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
		@$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
		@make -C $(LIBFT_DIR) clean
		@$(RM) $(OBJS)

fclean: clean
		@make -C $(LIBFT_DIR) fclean
		@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
	
