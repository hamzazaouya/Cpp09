NAME = RPN
SOURCES = main.cpp RPN.cpp
OBJ_PATH  = objs
SRC_PATH = ./

CC = c++
CFLAGS = -Wall -Wextra -Werror

OBJS = $(addprefix $(OBJ_PATH)/,$(SOURCES:.cpp=.o))
.PHONY: all clean fclean re

all : $(OBJ_PATH) $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -std=c++98 $(OBJS) -o  $(NAME)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.cpp $(HEADER)
	@$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_PATH):
	@mkdir objs

clean:
	rm -fr objs

fclean: clean
	rm -f $(NAME)
re : fclean all%