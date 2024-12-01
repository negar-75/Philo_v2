NAME = philo
CC = cc
CFLAGS =  -Wall -Werror -Wextra -pthread -fsanitize=thread
RM = rm -f

LIBFT = $(addprefix ./libft/, \
	ft_atoi.c \
	ft_putchar_fd.c \
	ft_putendl_fd.c \
	ft_putstr_fd.c \
	ft_strlen.c)

UTILS = $(addprefix ./utils/, \
	helper.c \
	init.c \
	monitor.c \
	args_validation.c \
	routine.c \
	thread.c)

MAIN = ./main.c
SRCS = $(UTILS) $(MAIN) $(LIBFT)
OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all
