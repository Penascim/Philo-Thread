SRC = src/parsers.c src/utils.c src/philo.c \
      src/inits.c src/routine.c src/monitor.c src/time.c

NAME = philo
OBJ = $(SRC:.c=.o)
CC = cc
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror 
#-lpthread

Reset = \033[0m
G = \033[32m
R = \033[31m
Y = \033[33m
blink = \033[6;7;1;3m
image = inc/image.txt

all: $(NAME)

$(NAME): $(OBJ)
	@echo "-------------------------------------------------------------------------------------"
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "-------------------------------------------------------------------------------------"
	@echo "$(blink)$(G) ✅ $(NAME) successfully compiled $(Reset)"
	@cat $(image)

val:
	valgrind --leak-check=full --track-origins=yes ./philo 3 300 100 100 3

hell:
	valgrind --tool=helgrind ./philo 4 310 200 100
clean:
	$(RM) $(OBJ)
	@echo "$(Y) 😉 Objects from the $(NAME) project have been removed $(Reset)"

fclean: clean
	@echo "-------------------------------------------------------------------------------------"
	$(RM) $(NAME)
	@echo "$(blink)$(R) ❌ removed $(NAME) executable $(Reset)"
	@echo "-------------------------------------------------------------------------------------"

re: fclean all

.PHONY: all clean fclean re
