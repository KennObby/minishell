LIBFT_DIR = Libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS =  src/binary_tree/parsing/bt_parser.c				\
		src/binary_tree/parsing/bt_parser_cmd.c 		\
		src/binary_tree/parsing/bt_parser_redirs.c 		\
		src/binary_tree/parsing/bt_parser_utils.c 		\
		src/binary_tree/parsing/bt_parser_args.c 		\
		src/binary_tree/parsing/bt_parser_helpers.c		\
		src/binary_tree/tokens/token.c 				\
		src/binary_tree/tokens/token_utils.c		\
		src/binary_tree/tokens/wildcard_mgmt.c 		\
		src/binary_tree/tokens/wildcard_utils.c 	\
		src/binary_tree/init/init_tree.c 			\
		src/binary_tree/init/init_data.c 			\
		src/binary_tree/utils/free_tree.c 			\
		src/binary_tree/utils/to_str_helper.c 		\
		src/binary_tree/utils/signal_handler.c 		\
		src/binary_tree/exec/exec_ops.c 			\
		src/binary_tree/exec/exec_mgmt.c 			\
		src/builtins/builtin_mgmt.c 			\
		src/builtins/env/env_mgmt.c 			\
		src/builtins/env/env_init.c 			\
		src/builtins/env/free_env.c 			\
		src/builtins/pwd/pwd_mgmt.c 			\
		src/builtins/echo/echo_mgmt.c			\
		src/builtins/cd/cd_mgmt.c 				\
		src/builtins/export/export_mgmt.c 		\
		src/builtins/unset/unset_mgmt.c 		\
		src/builtins/exit/exit_mgmt.c 			\
		src/binary_tree/main.c

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror 

INC = -I inc/ -I $(LIBFT_DIR) 
LDFLAGS = -L $(LIBFT_DIR) -L /usr/local/lib -lreadline -lft

NAME = minishell
RM = rm -rf

VALGRIND = valgrind --leak-check=full --show-leak-kinds=definite --track-origins=yes
SUPPRESS_FILE = readline.supp 

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

val: re
	$(VALGRIND) --suppressions=$(SUPPRESS_FILE) ./minishell

.PHONY: all clean fclean re
	
