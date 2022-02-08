NAME = philo
SRCDIR = source/
SRCS = main.c parse.c print.c utils.c philo.c watcher.c
SRCFILES = $(addprefix $(SRCDIR),$(SRCS))
HEADERS = philo.h
OBJDIR = obj/
OBJS = $(SRCS:.c=.o)
OBJFILES = $(addprefix $(OBJDIR),$(OBJS))
CC = gcc
CFLAGS = -I. -Wall -Wextra -Werror

all: $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.c $(HEADERS) $(OBJDIR) Makefile
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJFILES)
	$(CC) $(OBJFILES) -lpthread -o $(NAME)

$(OBJDIR):
	mkdir $(OBJDIR)

clean:
	$(RM) $(OBJFILES)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
