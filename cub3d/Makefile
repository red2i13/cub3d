#_______flags______#
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror -g3
CC = cc
AR = ar -crs
LIBFT_DIR = /libft/include
LIB = libft
SRC_DIR = src
#______files______#
FILES = main.c
FILES_BONUS =

#______patterns and substitutions based on BONUS variable______#
ifeq ($(BONUS),1)
SOURCES := $(addprefix $(SRC_DIR)/, $(FILES_BONUS))
else
SOURCES := $(addprefix $(SRC_DIR)/, $(FILES))
endif

SOURCES_B = $(addprefix $(SRC_DIR)/, $(FILES_BONUS))
OBJECTS := $(SOURCES:.c=.o)
OBJECTS_B := $(SOURCES_B:.c=.o)
#______Compilation process______#
NAME = cub3d

# Default rule
all: $(NAME)

bonus:
	$(MAKE) BONUS=1 all

$(LIB)/libft.a:
	$(MAKE) -C $(LIB) all

#$(NAME): $(OBJECTS) libmlx_Linux.a libft/libft.a
$(NAME): $(OBJECTS) libft/libft.a
	$(CC) $(CFLAGS) $^ -o $@ -lXext -lX11 -lm -lz

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) -c $< -o $@

#______cleaning______#
clean:
	$(RM) $(OBJECTS) $(OBJECTS_B)
	$(MAKE) -C $(LIB) clean
fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIB) fclean
re: fclean all

.PHONY: all clean fclean re bonus
