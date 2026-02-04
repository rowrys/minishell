CC=cc
NAME = minishell
SRCS_DIR = srcs/
SOURCES =	$(SRCS_DIR)minishell.c					\
			$(SRCS_DIR)ctx/ctx_destroy.c			\
			$(SRCS_DIR)ctx/ctx_init.c				\
			$(SRCS_DIR)parse/parse.c				\
			$(SRCS_DIR)parse/parse_line.c			\
			$(SRCS_DIR)parse/parse_token_list.c		\
 			$(SRCS_DIR)parse/expand.c				\
			$(SRCS_DIR)parse/valid_line.c			\
			$(SRCS_DIR)parse/syntax_error.c			\
			$(SRCS_DIR)parse/get_next_token.c		\
			$(SRCS_DIR)parse/parse_block.c			\
			$(SRCS_DIR)utils/utils.c				\
			$(SRCS_DIR)utils/env_utils.c			\
			$(SRCS_DIR)utils/parse_utils.c			\
			$(SRCS_DIR)utils/ft_split_expand.c		\
			$(SRCS_DIR)utils/ft_split_readline.c	\
			$(SRCS_DIR)utils/close.c				\
			$(SRCS_DIR)utils/error.c				\
			$(SRCS_DIR)utils/free.c					\
			$(SRCS_DIR)sig/sig_mini_shell.c			\
			$(SRCS_DIR)sig/sig_here_doc.c			\
			$(SRCS_DIR)here_doc/here_doc.c			\
			$(SRCS_DIR)here_doc/parse_limiter.c		\
			$(SRCS_DIR)execute/cmd_to_arg.c			\
			$(SRCS_DIR)execute/execute.c			\
			$(SRCS_DIR)execute/execute_chunk.c		\
			$(SRCS_DIR)execute/execute_cmd.c		\
			$(SRCS_DIR)execute/forgotten_child.c	\
			$(SRCS_DIR)execute/manage_redir.c		\

OBJ_DIR = .build/
OBJS = $(SOURCES:$(SRCS_DIR)%.c=$(OBJ_DIR)%.o)

DEPS = $(SOURCES:$(SRCS_DIR)%.c=$(OBJ_DIR)%.d)

CFLAGS = -MP -MMD -Wall -Werror -Wextra -g
INCLUDE = -I includes/ -I libft/includes/
LIB = libft/libft.a

all: $(NAME)

$(NAME): make_dir $(OBJS)
	$(MAKE) --no-print-directory -C libft/
	$(CC) $(OBJS) $(CFLAGS) -lreadline  $(INCLUDE) $(LIB) -o $(NAME)

make_dir:
	@mkdir -p .build/
	@mkdir -p .build/parse
	@mkdir -p .build/ctx
	@mkdir -p .build/utils
	@mkdir -p .build/sig
	@mkdir -p .build/here_doc
	@mkdir -p .build/execute

$(OBJ_DIR)%.o:  $(SRCS_DIR)%.c
	$(CC) $(CFLAGS) $(INCLUDE) $< -c -o $@

gdb: $(NAME)
	gdb -tui $(NAME)

clean:
	$(MAKE) clean --no-print-directory -C libft/
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) fclean -C libft/
	rm -rf $(NAME)

re: fclean all

.PHONY: all fclean clean re gdb

-include $(DEPS)