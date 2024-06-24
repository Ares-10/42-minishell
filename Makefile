NAME = minishell

SRCS =  main.c		\

OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror	\

LIBS = -lreadline		\
		Libft/libft.a	\


all : $(NAME)

$(NAME) : $(OBJS)
	@$(MAKE) -C ./Libft all
	cc $(CFLAGS) $^ $(LIBS) -o $(NAME)

%.o: %.c
	cc $(CFLAGS) -c $< -o $@ -I minishell.h

clean :
	@$(MAKE) -C ./Libft fclean
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re