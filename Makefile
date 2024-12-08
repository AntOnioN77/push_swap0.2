NAME = push_swap
CC = cc
CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = -I. -I/libft/headers
DBGFLAGS = -g3
LDFLAGS = -L ./libft -lft
SOURCES = chunker.c find_right_course.c main.c\
src/instructions/sa_sb_ss.c src/instructions/pa_pb.c src/instructions/ra_rb_rr.c\
src/instructions/rra_rrb_rrr.c src/parsing.c
OBJECTS = $(SOURCES:.c=.o)
HEADERS = libft/headers/libft.h libft/headers/ring.h circular_array.h

all: $(NAME)
debug: CFLAGS += $(DBGFLAGS)
debug: fclean all
$(NAME): libft/libft.a $(OBJECTS) $(HEADERS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(OBJECTS) $(LDFLAGS) -o $(NAME)
libft/libft.a:
	make extra -C libft
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@ 
.PHONY: clean fclean all re
clean:
	rm -f $(OBJECTS)
	make clean -C libft
fclean: clean
	rm -f $(NAME)
	rm -f libft/libft.a
re: fclean all