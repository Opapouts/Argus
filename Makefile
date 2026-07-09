NAME    = Argus
CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -g
ASAN_FLAGS = -fsanitize=address

# ---- Directories ----
SRCS_DIR		= src/
DATA_DIR		= $(SRCS_DIR)data_ingestion/
GRAPH_DIR		= $(SRCS_DIR)graphics_engine/
UTILS_DIR		= $(SRCS_DIR)utils/
CURL_DIR		= vendor/local_curl/
RAYLIB_DIR		= vendor/raylib/src/
CJSON_DIR		= vendor/cJSON/
OBJ_DIR			= objects/

# ---- vpath will tell make where to find all the .c files ----
vpath %.c $(SRCS_DIR) $(DATA_DIR) $(GRAPH_DIR) $(UTILS_DIR) $(CJSON_DIR)

# ---- Depedencies ----
INCLUDES		= -I includes \
			  -I $(RAYLIB_DIR) \
			  -I $(CURL_DIR)include \
			  -I $(CJSON_DIR)

RAYLIB			= $(RAYLIB_DIR)libraylib.a
RAYLIB_FLAGS		= -L $(RAYLIB_DIR) -lraylib -lGL -lm -ldl -lpthread -lX11
CURL_FLAGS		= -L $(CURL_DIR)lib -lcurl

# ---- Source Files ----
MAIN_FILE		= main.c

DATA_FILES		= linked_list_functions.c \
			parser.c \
			webscrape.c

GRAPH_FILES		= convertions.c \
			set_up.c \
			update_camera.c

UTILS_FILES		= utils.c

CJSON_FILES		= cJSON.c

ALL_SRCS		= $(MAIN_FILE) \
			$(DATA_FILES) \
			$(GRAPH_FILES) \
			$(UTILS_FILES) \
			$(CJSON_FILES)

OBJS			= $(addprefix  $(OBJ_DIR), $(ALL_SRCS:.c=.o))

# ---- Rules ----
all: $(RAYLIB) $(NAME)


$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(RAYLIB_FLAGS) $(CURL_FLAGS) -o $(NAME)

# ---- Compilation Rule (vpath hanles the compilation path) ----
$(OBJ_DIR)%.o: %.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# ---- Raylib Build ----
$(RAYLIB):
	@$(MAKE) -C $(RAYLIB_DIR) PLATFORM=PLATFORM_DESKTOP --no-print-directory

# ---- Execution Rules ----
run: all 
	@./$(NAME)

# asan: fclean (OBJS)

clean:
	@rm -rf  $(OBJ_DIR)

fclean: clean
	@rm -rf  $(NAME) 

re: fclean all

.PHONY: all run clean fclean re
