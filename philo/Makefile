# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror $(INCLUDES) -fsanitize=thread -g #-fsanitize=address -g #-std=c99
INCLUDES = -Iinc

# Output executable
NAME = philo

# Colors for output
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m
ORANGE = \033[0;38;5;166m

# Source files
SRCDIR = src/

SRCS_FIL = \
			main.c \
			utils.c \
			libft.c \
			routine.c

SRCS = $(addprefix $(SRCDIR), $(SRCS_FIL))

# Object files
OBJDIR = objs/
OBJS = $(patsubst $(SRCDIR)%.c, $(OBJDIR)%.o, $(SRCS))

# Build targets
all: $(OBJDIR) $(NAME)

bonus: all

$(OBJDIR):
	@mkdir -p $(OBJDIR) $(addprefix $(OBJDIR), $(dir $(SRCS_FIL)))

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) && echo "$(GREEN)$(NAME) was created$(RESET)"

$(OBJDIR)%.o: $(SRCDIR)%.c
	@$(CC) $(CFLAGS) -c $< -o $@ && echo "$(GREEN)object files were created$(RESET)"

# Cleanup
RM = rm -rf

clean:
	@$(RM) $(OBJDIR) && echo "$(ORANGE)object files were deleted$(RESET)"

fclean: clean
	@$(RM) $(NAME) && echo "$(ORANGE)$(NAME) was deleted$(RESET)"

re: fclean all

.PHONY: all clean fclean re bonus