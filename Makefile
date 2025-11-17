# **************************************************************************** #
#                                  Makefile                                    #
# **************************************************************************** #

NAME = miniRT
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -g
MINILIBX_FLAGS = -L$(MINILIBX_DIR) -lmlx -lXext -lX11 -lm -lz

# -------------------------------
#  		  Directories 
# -------------------------------

SRC_DIR = src/
OBJ_DIR = obj/
INCLUDE_DIR = include/
LIBFT_DIR = libft/
MINILIBX_DIR = minilibx/

# -------------------------------
#   Source for miniRT
# -------------------------------

SRCS = main.c parse/parse.c parse/parse_utils.c parse/ambient.c \
parse/camera.c parse/light.c parse/ft_atoi_checked.c \
parse/sphere.c parse/plane.c parse/cylinder.c parse/validate_range.c \
vector.c ray.c camera.c \
debug_print_scene.c mlx_utils.c \
color.c material.c \
sphere.c object.c plane.c cylinder.c \
render.c trace.c

# -------------------------------
#   Object & Dependency Files
# -------------------------------
OBJS = $(SRCS:%.c=$(OBJ_DIR)%.o)
DEPS = $(OBJS:%.o=%.d)
INCLUDES = -I$(INCLUDE_DIR) -I$(LIBFT_DIR) -I$(MINILIBX_DIR)
LIBFT = $(LIBFT_DIR)libft.a
MINILIBX = $(MINILIBX_DIR)libmlx.a

# **************************************************************************** #
#                                 Build Rules                                  #
# **************************************************************************** #

all: $(NAME)
	@echo "🔥 miniRT built successfully!"

libs:
	@$(MAKE) -s -C $(LIBFT_DIR)
	@$(MAKE) -s -C $(MINILIBX_DIR)

$(NAME): $(OBJS) | libs
	@$(CC) $(CFLAGS) $(OBJS) -lm $(LIBFT) $(MINILIBX_FLAGS) -o $(NAME)
	@echo "✅ miniRT object files compiled."
	@echo "🚀 $(NAME) created!"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -s -C $(LIBFT_DIR) clean
	@$(MAKE) -s -C $(MINILIBX_DIR) clean
	@echo "🗑️ $(NAME) object files removed."

fclean: clean
	@rm -rf $(NAME)
	@$(MAKE) -s -C $(LIBFT_DIR) fclean
	@echo "😒 $(NAME) and $(NAME) object files removed."

re: fclean all

-include $(DEPS)

.PHONY: all libs fclean clean re
.DELETE_ON_ERROR: