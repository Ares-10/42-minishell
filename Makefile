NAME = minishell

SRCS =  main.c							\
		signal.c						\
		prompt.c						\
		error.c							\
		parse/parse.c					\
		parse/token.c					\
		parse/tokenchecker.c			\
		parse/quote.c					\
		parse/replvar.c					\
		parse/split.c					\
		parse/treebuilder1.c			\
		parse/treebuilder2.c			\
		parse/treedestroyer.c			\
		run/builtin/builtin_cd.c		\
		run/builtin/builtin_echo.c		\
		run/builtin/builtin_env.c		\
		run/builtin/builtin_exit.c		\
		run/builtin/builtin_export.c	\
		run/builtin/builtin_export2.c	\
		run/builtin/builtin_pwd.c		\
		run/builtin/builtin_unset.c		\
		run/builtin/utils.c				\
		run/handle.c					\
		run/exec_cmd.c					\
		run/free.c						\
		run/terminal.c					\
		run/run.c						\

OBJS = $(SRCS:.c=.o)

CFLAGS =	-Wall -Wextra -Werror \
#-fsanitize=address

# LDFLAGS=-L/usr/local/opt/readline/lib
# CPPFLAGS=-I/usr/local/opt/readline/include
LDFLAGS = -L/opt/homebrew/opt/readline/lib\
#-fsanitize=address
CPPFLAGS = -I/opt/homebrew/opt/readline/include

LIBS = -lreadline		\
		Libft/libft.a	\


all : $(NAME)

$(NAME) : $(OBJS)
	@$(MAKE) -C ./Libft bonus
	cc $(LDFLAGS) $^ $(LIBS) -o $(NAME)

%.o: %.c
	cc $(CFLAGS)  $(CPPFLAGS) -c $< -o $@ -I. -I./parse -I./run

clean :
	@$(MAKE) -C ./Libft fclean
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re
