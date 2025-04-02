LIBFT_DIR = Libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS =  src/binary_tree/bt_parser.c				\
		src/binary_tree/bt_parser_utils.c 		\
		src/binary_tree/token.c 				\
		src/binary_tree/init_tree.c 			\
		src/binary_tree/free_tree.c 			\
		src/binary_tree/to_str_helper.c 		\
		src/binary_tree/exec_ops.c 				\
		src/binary_tree/exec_mgmt.c 			\
		src/builtins/builtin_mgmt.c 			\
		src/builtins/env/env_mgmt.c 			\
		src/builtins/env/env_init.c 			\
		src/builtins/env/free_env.c 			\
		src/binary_tree/main.c

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror 

INC = -I inc/ -I $(LIBFT_DIR) 
LDFLAGS = -L $(LIBFT_DIR) -L /usr/local/lib -lreadline -lft

NAME = minishell
RM = rm -rf

all: $(LIBFT) $(NAME)

$(LIBFT):
		@make -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
		@echo "Compiling $@..."
		@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

%.o: %.c
		@echo "Compiling $@..."
		@$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
		@make -C $(LIBFT_DIR) clean
		@$(RM) $(OBJS)

fclean: clean
		@make -C $(LIBFT_DIR) fclean
		@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
	
