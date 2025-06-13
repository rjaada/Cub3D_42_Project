# Colors
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
MAGENTA = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m
RESET = \033[0m
BOLD = \033[1m

# Project
NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

# MLX42
MLX_DIR = MLX42
MLX_FLAGS = -LMLX42/build -lmlx42 -lglfw -lGL -lm
MLX_INCLUDES = -I$(MLX_DIR)/include

# Libft
LIBFT_DIR = libraries/libft
LIBFT = $(LIBFT_DIR)/libft.a

# Sources
SRCDIR = src
SRCS = $(SRCDIR)/main.c $(SRCDIR)/parsing.c $(SRCDIR)/2Dmap.c $(SRCDIR)/movements.c \
		$(SRCDIR)/colors.c $(SRCDIR)/init.c $(SRCDIR)/raycasting.c
OBJDIR = obj
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Progress bar
TOTAL_FILES = $(words $(SRCS))
CURRENT_FILE = 0

all: header $(NAME) footer

header:
	@echo "$(CYAN)$(BOLD)"
	@echo "╔═══════════════════════════════════════════════════════════════╗"
	@echo "║                        🎮 CUB3D 🎮                            ║"
	@echo "║                    Building 3D Engine...                      ║"
	@echo "╚═══════════════════════════════════════════════════════════════╝"
	@echo "$(RESET)"

$(NAME): $(OBJS) $(LIBFT)
	@echo "$(GREEN)$(BOLD)🔗 Linking $(NAME)...$(RESET)"
	@$(CC) $(OBJS) $(MLX_FLAGS) -L$(LIBFT_DIR) -lft -o $(NAME)
	@echo "$(GREEN)$(BOLD)✅ $(NAME) built successfully!$(RESET)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@$(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE)+1))))
	@echo "$(YELLOW)📁 Compiling [$(CURRENT_FILE)/$(TOTAL_FILES)] $<$(RESET)"
	@printf "$(BLUE)▓"
	@for i in $$(seq 1 $$(echo "scale=0; $(CURRENT_FILE) * 50 / $(TOTAL_FILES)" | bc 2>/dev/null || echo "25")); do printf "▓"; done
	@printf "$(RESET)\n"
	@$(CC) $(CFLAGS) $(MLX_INCLUDES) -Ilibraries/libft -Iincludes -c $< -o $@

$(LIBFT):
	@echo "$(MAGENTA)🔨 Building libft...$(RESET)"
	@make -C $(LIBFT_DIR) --quiet

clean:
	@echo "$(RED)🧹 Cleaning object files...$(RESET)"
	@rm -rf $(OBJDIR)
	@make clean -C $(LIBFT_DIR) --quiet
	@echo "$(RED)✅ Clean complete!$(RESET)"

fclean: clean
	@echo "$(RED)🔥 Full clean...$(RESET)"
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR) --quiet
	@echo "$(RED)✅ Full clean complete!$(RESET)"

re: fclean all

footer:
	@echo "$(CYAN)$(BOLD)"
	@echo "╔═══════════════════════════════════════════════════════════════╗"
	@echo "║                     🚀 BUILD COMPLETE! 🚀                     ║"
	@echo "║                  Ready to render some 3D! 🎮                  ║"
	@echo "║                                                               ║"
	@echo "║                Usage: ./$(NAME) maps/test.cub                   ║"
	@echo "╚═══════════════════════════════════════════════════════════════╝"
	@echo "$(RESET)"

bonus: $(NAME)

.PHONY: all clean fclean re bonus header footer

# Progress indicator
.SILENT: $(OBJS) header footer