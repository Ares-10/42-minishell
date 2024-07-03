NAME = minishell

SRCS =  main.c					\
		signal.c				\
		prompt.c				\
		error.c					\
		parse/parse.c			\
		parse/token.c			\
		parse/quote.c			\
		parse/syntaxanalysis.c	\
		parse/treebuilder.c		\

OBJS = $(SRCS:.c=.o)

#CFLAGS =	-Wall -Wextra -Werror

CPPFLAGS = -I/opt/homebrew/opt/readline/include
LDFLAGS = -L/opt/homebrew/opt/readline/lib

LIBS = -lreadline		\
		Libft/libft.a	\


all : $(NAME)

$(NAME) : $(OBJS)
	@$(MAKE) -C ./Libft bonus
	cc $(LDFLAGS) $^ $(LIBS) -o $(NAME)

%.o: %.c
	cc $(CFLAGS)  $(CPPFLAGS) -c $< -o $@ -I minishell.h -I parse/parse.h

clean :
	@$(MAKE) -C ./Libft fclean
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re