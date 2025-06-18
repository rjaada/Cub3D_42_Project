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
CFLAGS = -Wall -Wextra -Werror

# Libraries
MLX = MLX42/build/libmlx42.a
LIBFT = libft/libft.a

# Sources
SRCDIR = src
SRCS = $(SRCDIR)/main.c $(SRCDIR)/file_parsing.c $(SRCDIR)/texture_parsing.c \
		$(SRCDIR)/color_parsing.c $(SRCDIR)/config_validation.c $(SRCDIR)/error_handler.c \
		$(SRCDIR)/map_parsing.c $(SRCDIR)/player_parsing.c $(SRCDIR)/map_validation.c \
		$(SRCDIR)/wall_validation.c $(SRCDIR)/2Dmap.c $(SRCDIR)/movements.c \
		$(SRCDIR)/colors.c $(SRCDIR)/init.c $(SRCDIR)/raycasting.c $(SRCDIR)/map_validation_utils.c \
		$(SRCDIR)/texture_rendering.c $(SRCDIR)/ray_utils.c $(SRCDIR)/cleanup.c $(SRCDIR)/wall_validation_utils.c $(SRCDIR)/file_parsing_utils.c
OBJDIR = obj
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Progress bar
TOTAL_FILES = $(words $(SRCS))
CURRENT_FILE = 0

all: $(NAME)

$(NAME): $(MLX) $(LIBFT) $(OBJS)
	@echo "$(CYAN)$(BOLD)"
	@echo "╔═══════════════════════════════════════════════════════════════╗"
	@echo "║                        🎮 CUB3D 🎮                            ║"
	@echo "║                    Building 3D Engine...                      ║"
	@echo "╚═══════════════════════════════════════════════════════════════╝"
	@echo "$(RESET)"
	@echo "$(GREEN)$(BOLD)🔗 Linking $(NAME)...$(RESET)"
	@$(CC) $(OBJS) $(MLX) -lglfw -lm -o $(NAME) $(LIBFT)
	@echo "$(GREEN)$(BOLD)✅ $(NAME) built successfully!$(RESET)"
	@echo "$(CYAN)$(BOLD)"
	@echo "╔═══════════════════════════════════════════════════════════════╗"
	@echo "║                     🚀 BUILD COMPLETE! 🚀                     ║"
	@echo "║                  Ready to render some 3D! 🎮                  ║"
	@echo "║                                                               ║"
	@echo "║                Usage: ./$(NAME) maps/test.cub                   ║"
	@echo "╚═══════════════════════════════════════════════════════════════╝"
	@echo "$(RESET)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@$(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE)+1))))
	@echo "$(YELLOW)📁 Compiling [$(CURRENT_FILE)/$(TOTAL_FILES)] $<$(RESET)"
	@printf "$(BLUE)▓"
	@for i in $$(seq 1 $$(echo "scale=0; $(CURRENT_FILE) * 50 / $(TOTAL_FILES)" | bc 2>/dev/null || echo "25")); do printf "▓"; done
	@printf "$(RESET)\n"
	@$(CC) $(CFLAGS) -Ilibraries/libft -Iincludes -c $< -o $@

$(LIBFT):
	@echo "$(MAGENTA)🔨 Building libft...$(RESET)"
	@make -C libft --quiet

$(MLX):
	@echo "$(MAGENTA)🔨 Building MLX42...$(RESET)"
	@cmake -S MLX42 -B MLX42/build
	@cmake --build MLX42/build

clean:
	@echo "$(RED)🧹 Cleaning object files...$(RESET)"
	@rm -rf $(OBJDIR)
	@make -C libft clean --quiet
	@echo "$(RED)✅ Clean complete!$(RESET)"

fclean: clean
	@echo "$(RED)🔥 Full clean...$(RESET)"
	@rm -f $(NAME)
	@make fclean -C libft --quiet
	@echo "$(RED)✅ Full clean complete!$(RESET)"

re: fclean all

bonus: $(NAME)

.PHONY: all clean fclean re bonus

# Progress indicator
.SILENT: $(OBJS)