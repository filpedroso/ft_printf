##### MAKEFILE FOR FT_PRINTF #####

# Colors
BLACK		= \033[1;30m
RED			= \033[1;31m
GREEN		= \033[1;32m
YELLOW		= \033[1;33m
BLUE		= \033[1;34m
MAGENTA		= \033[1;35m
CYAN		= \033[1;36m
WHITE		= \033[1;37m
BOLD_RED	= \033[1;31m
NC			= \033[0m # No Color

# Compilation Variables
NAME	= compiled_ft_printf.a
CC		= cc
CFLAGS	= -Wextra -Wall -Werror
SRC		= $(FILES)
OBJ		= $(SRC:.c=.o)

# Test
TEST	= test

# Verbose flag
VB	= 0

# Check if VERBOSE is set to 1
ifeq ($(VB),1)
	AT =
else
	AT = @
endif

# Dependencies
FILES		= ft_printf.c \
			booleans.c \
			flag_works.c \
			ft_atoi.c \
			len_count_tools.c \
			printing_tools.c \

TEST_SRC	= main.c


###	Rules	#################################
$(NAME): $(OBJ)
	$(AT) ar -rcs $(NAME) $(OBJ)
	@printf "\n$(WHITE)Compiling '.a' file["
	@for i in {1..16}; do \
		sleep 0.07; \
		printf "="; \
	done
	@printf "]\n\n"
	@printf "$(BLUE)Object files created.\n"
	@printf "$(GREEN)Lib created successfully.\n"

%.o: %.c
	$(AT) $(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	$(AT) rm -f $(OBJ) $(TEST)
	@printf "$(YELLOW)Object files deleted.\n"

test: $(OBJ)
	@printf "\n$(WHITE)Compiling test dependencies["
	@for i in {1..16}; do \
		sleep 0.07; \
		printf "="; \
	done
	$(AT) $(CC) $(CFLAGS) $(OBJ) $(TEST_SRC) -o $(TEST)
	@printf "]\n\n"
	@printf "$(GREEN)Test executable created.\n"

fclean: clean
	$(AT) rm -f $(NAME)
	@printf "$(RED)Objects and executables deleted.\n"

re: fclean all

oblit:
	find . $$ -type f -o -type d $$ \
    ! -name "*.c" \
    ! -name "*.h" \
    ! -name "Makefile" \
	! -name "." \
	! -name ".." \
    -exec rm -rf {} +

verbose:
	$(MAKE) VB=1

.PHONY: all clean fclean re test



# Background Colors
# 	Background Black: \033[40m
# 	Background Red: \033[41m
# 	Background Green: \033[42m
# 	Background Yellow: \033[43m
# 	Background Blue: \033[44m
# 	Background Magenta: \033[45m
# 	Background Cyan: \033[46m
# 	Background White: \033[47m

# Other Text Effects
# 	Reset/Normal: \033[0m (this resets all attributes)
# 	Bold: \033[1m
# 	Underline: \033[4m
# 	Blink: \033[5m
# 	Reverse: \033[7m
# 	Concealed: \033[8m