# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aahri <aahri@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/25 19:13:22 by aahri             #+#    #+#              #
#    Updated: 2021/08/26 16:09:52 by aahri            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re create_dir

NAME = philo

SRC_DIR = .
OBJ_DIR = ./obj
INCLUDES = .

FLAGS = -g -Wall -Wextra -Werror

HEADER_FILES = philo.h
SRCS =	main.c standart_funcs.c acts.c

OBJECTS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
HEADERS = $(addprefix $(INCLUDES)/, $(HEADER_FILES))

all: create_dir $(NAME)

create_dir:
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@gcc  $(FLAGS) -c $< -I $(INCLUDES) $() -o $@
$(NAME): $(OBJECTS) $(HEADERS)
	@gcc $(FLAGS) $(OBJECTS) -o $@ 
	@echo "${NAME} created."

clean:
	@rm -rf obj
	
fclean: clean
	@rm -f $(NAME)

re: fclean all