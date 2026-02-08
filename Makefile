CC=cc
NAME = minishell
SRCS_DIR = srcs/
SOURCES =	minishell.c						\
			ctx/ctx_destroy.c				\
			ctx/ctx_init.c					\
			ctx/env_init_default.c			\
			ctx/declare_x.c					\
			parse/parse.c					\
			parse/parse_line.c				\
			parse/parse_token_list.c		\
 			parse/expand.c					\
			parse/valid_line.c				\
			parse/syntax_error.c			\
			parse/get_next_token.c			\
			parse/parse_block.c				\
			utils/utils.c					\
			utils/env_utils.c				\
			utils/parse_utils.c				\
			utils/ft_split_expand.c			\
			utils/ft_split_readline.c		\
			utils/close.c					\
			utils/error.c					\
			utils/free.c					\
			utils/exec_utils.c				\
			sig/signal.c					\
			here_doc/here_doc.c				\
			here_doc/parse_limiter.c		\
			execute/cmd_to_arg.c			\
			execute/execute.c				\
			execute/execute_chunk.c			\
			execute/execute_cmd.c			\
			execute/forgotten_child.c		\
			execute/manage_redir.c			\
			execute/execute_built_in.c		\
			built_in/env.c					\
			built_in/exit/exit.c			\
			built_in/exit/exit_utils.c		\
			built_in/echo.c					\
			built_in/pwd.c					\
			built_in/cd/cd.c				\
			built_in/cd/cd_utils.c			\
			built_in/cd/cd_utils2.c			\
			built_in/export/export.c		\
			built_in/export/export_parse.c	\


SOURCES	:=	$(addprefix $(SRCS_DIR), $(SOURCES))

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
	@mkdir -p .build/built_in
	@mkdir -p .build/built_in/exit
	@mkdir -p .build/built_in/cd
	@mkdir -p .build/built_in/export

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