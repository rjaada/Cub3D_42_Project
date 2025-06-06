NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Updated MLX paths
MLX_DIR = MLX42
MLX_FLAGS = -LMLX42/build -lmlx42 -lglfw -lGL -lm
MLX_INCLUDES = -I$(MLX_DIR)/include

# Libft - Updated path
LIBFT_DIR = libraries/libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCDIR = src
SRCS = $(SRCDIR)/main.c $(SRCDIR)/parsing.c $(SRCDIR)/colors.c $(SRCDIR)/init.c # Add other source files as needed

OBJDIR = obj
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(MLX_FLAGS) -L$(LIBFT_DIR) -lft -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(MLX_INCLUDES) -I$(LIBFT_DIR) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJDIR)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

bonus: $(NAME)

.PHONY: all clean fclean re bonus