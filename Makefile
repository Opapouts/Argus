NAME    = aerosphere
CC      = gcc
CFLAGS  = -g -Wall -Wextra -Werror

CURL_INC = $(shell pkg-config --cflags libcurl)
CURL_LIB = $(shell pkg-config --libs libcurl)

# Raylib and standard Linux math/threading/graphics dependencies
RAY_LIB = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

SRCS    = main.c
OBJS    = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@echo "Linking $(NAME)..."
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(CURL_LIB) $(RAY_LIB)

%.o: %.c
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) $(CURL_INC) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
