NAME    = aerosphere
CC      = gcc
CFLAGS  = -g -Wall -Wextra -Werror

PROJECT_DIR = $(shell pwd)

CURL_DIR = $(PROJECT_DIR)/vendor/local_curl
CURL_INC = -I$(CURL_DIR)/include
CURL_LIB = -L$(CURL_DIR)/lib -lcurl

RAY_DIR = $(PROJECT_DIR)/vendor/local_raylib
RAY_INC = -I$(RAY_DIR)/include

# Raylib and standard Linux math/threading/graphics dependencies
RAY_LIB = -L$(RAY_DIR)/lib -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

SRCS    = main.c
OBJS    = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@echo "Linking $(NAME)..."
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(CURL_LIB) $(RAY_LIB)

%.o: %.c
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) $(CURL_INC) $(RAY_INC) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
