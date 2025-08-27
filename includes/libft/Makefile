# Compiler and tools
CC = cc
AR = ar rcs
CFLAGS = -Wall -Wextra -Werror

# Library name
NAME = libft.a

# Source files
SRCS = ft_bzero.c \
       ft_isalnum.c \
       ft_isalpha.c \
       ft_isascii.c \
       ft_isdigit.c \
       ft_isprint.c \
       ft_memcpy.c \
       ft_memmove.c \
       ft_memset.c \
       ft_strlcat.c \
       ft_strlcpy.c \
       ft_strlen.c \
       ft_substr.c \
       ft_toupper.c \
       ft_tolower.c \
       ft_strchr.c \
       ft_strrchr.c \
       ft_strncmp.c \
       ft_memchr.c \
       ft_memcmp.c \
       ft_strnstr.c \
       ft_atoi.c \
       ft_calloc.c \
       ft_strdup.c \
       ft_strjoin.c \
       ft_strtrim.c \
       ft_itoa.c \
       ft_putchar_fd.c \
       ft_putnbr_fd.c \
       ft_putendl_fd.c \
       ft_putstr_fd.c \
       ft_striteri.c \
       ft_strmapi.c \
       ft_split.c

BONUS_SRCS = ft_lstnew_bonus.c \
             ft_lstadd_front_bonus.c \
             ft_lstsize_bonus.c \
             ft_lstlast_bonus.c \
             ft_lstadd_back_bonus.c \
             ft_lstdelone_bonus.c \
             ft_lstclear_bonus.c \
             ft_lstiter_bonus.c \
             ft_lstmap_bonus.c

# Object files and directories
OBJ_DIR = libft_builds/
OBJS = $(SRCS:%.c=$(OBJ_DIR)%.o)
BONUS_OBJS = $(BONUS_SRCS:%.c=$(OBJ_DIR)%.o)

# Default target
all: $(NAME)

# Create library
$(NAME): $(OBJS)
	@$(AR) $(NAME) $(OBJS)

# Create bonus library
bonus: $(BONUS_OBJS)
	@$(AR) $(NAME) $(BONUS_OBJS)

# Compile source files into object files
$(OBJ_DIR)%.o: %.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

# Clean object files
clean:
	@rm -rf $(OBJ_DIR)

# Clean everything including the library
fclean: clean
	@rm -f $(NAME)

# Rebuild everything
re: fclean all

# Phony targets
.PHONY: all clean fclean re bonus
