NAME := philo
CC := cc

SRCS_PATH := srcs

INC_FLAGS := -Iincludes
CFLAGS := -Wall -Wextra -Werror $(INC_FLAGS)
MAKEFLAGS += --no-print-directory

SRCS := $(SRCS_PATH)/main.c \
		$(SRCS_PATH)/parsing.c \
		$(SRCS_PATH)/utils/ft_atoi.c \
		$(SRCS_PATH)/utils/ft_isspace.c \
		$(SRCS_PATH)/utils/ft_putstr_fd.c \
		$(SRCS_PATH)/utils/ft_isdigit.c
		

OBJS := $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@printf "Compiling binary...\n"
	@$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	@printf "Done.\n"

clean:
	@printf "Cleaning up object files...\n"
	@rm -f $(OBJS)
	@printf "Done.\n"

fclean: clean
	@printf "Cleaning up binary...\n"
	@rm -f $(NAME)
	@printf "Done.\n"

re: fclean all

.PHONY: all clean fclean re 

.SILENT: $(OBJS) $(OBJS_BONUS)