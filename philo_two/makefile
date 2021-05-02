# ENVS
NAME=philo_one

CC=gcc
CFLAGS=-g -Wall -Wextra -Werror
CFLAGS+= -I.

SRC_DIR=./
OBJ_DIR=objs/
SRCS= main.c \
	  check.c \
	  clean.c \
	  exec.c \
	  init.c \
	  time.c \
	  utils.c

OBJS=$(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

# TARGETS
.PHONY:			all
all: 			$(OBJ_DIR) $(NAME)

$(OBJ_DIR):		
				@mkdir -p $(OBJ_DIR)


$(OBJ_DIR)%.o:	$(SRC_DIR)%.c
				@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): 	$(OBJS)
				@printf "Building $(NAME)..."
				@$(CC) $(CFLAGS) $(LFLAGS) $(OBJS) -o $@
				@printf " ✔︎\n"

# RULES

.PHONY:			clean
clean:
				@printf "cleaning..."
				@rm -rf $(OBJ_DIR)
				@rm -rf $(NAME)
				@printf " ✔︎\n"

.PHONY:			fclean
fclean: 		clean
				@rm -rf $(OBJ_DIR)

.PHONY:			re
re: 			fclean all