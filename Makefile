NAME = IEEE_754
OBJ = main.o IEEE_754.o convert_binary.o
INC = -I inc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

%.o: $(addprefix ./src/,%.c)
	@gcc $(CFLAGS) $(INC) -c $< 

%.o: $(addprefix ./test/,%.c)
	@gcc $(CFLAGS) $(INC) -c $<

$(NAME): $(OBJ)
	@gcc -g $(CFLAGS) $(OBJ)  -o $(NAME)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all
