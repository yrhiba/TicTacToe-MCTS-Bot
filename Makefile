NAME = tictactoe

files = tictactoe.cpp

$(NAME):
	g++ --std=c++17 $(files) -o $(NAME)

run:
	./$(NAME)

clean:
	rm -rf $(NAME)
