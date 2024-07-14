NAME = minishell

SRCS =  main.c					\
		signal.c				\
		prompt.c				\
		error.c					\
		parse/parse.c			\
		parse/token.c			\
		parse/quote.c			\
		parse/replvar.c			\
		parse/split.c			\
		parse/treebuilder1.c	\
		parse/treebuilder2.c	\
		run/builtin/env.c		\
		run/builtin/exit.c		\
		run/builtin/export.c	\
		run/builtin/simple.c	\
		run/builtin/unset.c		\
		run/builtin/utils.c		\
		run/exec_cmd.c			\
		run/run.c				\
		run/error.c				\

OBJS = $(SRCS:.c=.o)

#CFLAGS =	-Wall -Wextra -Werror

LDFLAGS=-L/usr/local/opt/readline/lib
CPPFLAGS=-I/usr/local/opt/readline/include
#LDFLAGS = -L/opt/homebrew/opt/readline/lib
#CPPFLAGS = -I/opt/homebrew/opt/readline/include

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