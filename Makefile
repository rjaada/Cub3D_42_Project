NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Updated MLX paths
MLX_DIR = mlx
MLX_FLAGS = -LMLX42/build -lmlx42 -lglfw -lGL -lm
MLX_INCLUDES = -I$(MLX_DIR)

SRCDIR = src
SRCS = $(SRCDIR)/main.c

OBJDIR = obj
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(MLX_FLAGS) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(MLX_INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re