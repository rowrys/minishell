CC=cc
NAME = minishell
SRCS_DIR = srcs/
SOURCES =	$(SRCS_DIR)minishell.c				\

OBJ_DIR = .build/
OBJS = $(SOURCES:$(SRCS_DIR)%.c=$(OBJ_DIR)%.o)

DEPS = $(SOURCES:$(SRCS_DIR)%.c=$(OBJ_DIR)%.d)

CFLAGS = -MP -MMD -Wall -Werror -Wextra #-lreadline 
INCLUDE = -I includes/ -I libft/includes/
LIB = libft/libft.a

all: $(NAME)

$(NAME): make_dir $(OBJS)
	$(MAKE) --no-print-directory -C libft/
	$(CC) $(OBJS) $(CFLAGS) $(INCLUDE) $(LIB) -o $(NAME)

make_dir:
	@mkdir -p .build/
	@mkdir -p .build/parse

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