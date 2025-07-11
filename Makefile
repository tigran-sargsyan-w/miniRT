# **************************************************************************** #
#                                  Makefile                                    #
# **************************************************************************** #

NAME = miniRT
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
LD_FLAGS = -lreadline

# -------------------------------
#  		  Directories 
# -------------------------------

SRC_DIR = src/
OBJ_DIR = obj/
INCLUDE_DIR = include/
LIBFT_DIR = libft/

# -------------------------------
#   Source for miniRT
# -------------------------------

SRCS = main.c

# -------------------------------
#   Object & Dependency Files
# -------------------------------
OBJS = $(SRCS:%.c=$(OBJ_DIR)%.o)
DEPS = $(OBJS:%.o=%.d)
INCLUDES = -I$(INCLUDE_DIR) -I$(LIBFT_DIR)
LIBFT = $(LIBFT_DIR)libft.a

# **************************************************************************** #
#                                 Build Rules                                  #
# **************************************************************************** #

all: $(NAME)
	@echo "🔥 miniRT built successfully!"

libs:
	@$(MAKE) -s -C $(LIBFT_DIR)

$(NAME): $(OBJS) | libs
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@echo "✅ miniRT object files compiled."
	@echo "🚀 $(NAME) created!"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -s -C $(LIBFT_DIR) clean
	@echo "🗑️ $(NAME) object files removed."

fclean: clean
	@rm -rf $(NAME)
	@$(MAKE) -s -C $(LIBFT_DIR) fclean
	@echo "😒 $(NAME) and $(NAME) object files removed."

re: fclean all

-include $(DEPS)

.PHONY: all libs fclean clean re
.DELETE_ON_ERROR: