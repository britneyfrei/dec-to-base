SOURCE=conv.c
NAME=$(basename $(SOURCE))

$(NAME): $(SOURCE)
	cc -Wall -Werror $(SOURCE) -o conv -g -lm

.PHONY: clean test
clean:
	rm -rf $(NAME) $(NAME).dSYM

