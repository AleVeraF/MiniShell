NAME        = minishell
CC          = cc
CFLAGS      = -Wall -Werror -Wextra -g3 -O0 
INCLUDES    = -I includes

# Rutas correctas de readline en macOS (Homebrew)
READLINE_INC = -I/opt/homebrew/opt/readline/include
READLINE_LIB = -L/opt/homebrew/opt/readline/lib -lreadline

SRCS        = srcs/main.c srcs/signals.c srcs/shell.c srcs/main_aux.c srcs/main_aux_input.c srcs/tokenizer.c srcs/tokenizer_aux.c srcs/tokenizer_join.c srcs/tokenizer_join_ppal.c srcs/debuger_temp.c srcs/handle_quotes.c srcs/parser.c srcs/parser_check.c srcs/parser_aux.c srcs/parser_extension.c srcs/executor_aux.c srcs/executor.c srcs/general_aux.c built/echo.c built/builtin_cd.c built/builtin_env.c built/builtin_exit.c built/builtin_export.c built/builtin_pwd.c built/builtin_unset.c 
OBJS        = $(SRCS:.c=.o)

HEADERS     = includes/minishell.h includes/shell.h includes/tokenizer.h includes/parser.h includes/status.h includes/signals.h includes/main_aux.h

LIBFT_DIR   = libft
LIBFT       = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(READLINE_LIB) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) $(READLINE_INC) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR) CFLAGS="-Wall -Wextra -Werror"

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
