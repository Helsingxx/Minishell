NAME := minishell

CC := cc

RM := rm -rf

SRC := main.c signals.c tokenisation.c start_tokenizer.c process_token.c \
		process_env.c get_words.c error_handeling.c resolute.c env_in_list.c \
		utils.c utils_2.c utils_3.c utils_4.c ft_itoa.c ft_atoi.c ft_isint.c ft_split.c help.c

LDFLAGS += -lreadline -L$(shell brew --prefix)/opt/readline/lib/
CPPFLAGS += -I$(shell brew --prefix)/opt/readline/include/ -I.
CFLAGS += -Wall -Wextra -Werror

SRC_EXEC := apply_redir.c apply_redir1.c apply_redir2.c apply_redirf.c \
		exec.c exec1.c exec2.c exec3.c exec4.c exec5.c \
		fail.c ft_lstnew.c call.c \
		final_parse.c final_parse1.c final_parse2.c final_parse3.c final_parse4.c final_parse5.c \
		builtins.c builtins1.c builtins2.c builtinshlp.c

VPATH := errors parsing execution utils signals execution/built_ins/

OBJS := $(SRC:.c=.o) $(SRC_EXEC:.c=.o)
all: $(NAME) 

$(NAME) : $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)

%.o : %.c minishell.h Makefile
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
