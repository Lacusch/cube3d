CC = cc
CFLAGS = -Wall -Wextra -Werror
GLFW3 = lib/MLX42/build/_deps/glfw-build/src/libglfw3.a
LIBMLX42 = lib/MLX42/build/libmlx42.a
FRAMEWORK = -framework Cocoa -framework OpenGL -framework IOKit
SOURCE = src/free.c \
		src/init.c \
		src/main.c \
		src/parcing.c \
		src/draw.c
OBJECT = $(SOURCE:.c=.o)
LIBFT = lib/libft/libft.a
NAME = cub3D

all: $(NAME)

$(LIBMLX42):
	@if [ -d ./lib/MLX42/glfw_lib ]; \
    then echo "glfw3 already Exists"; \
    else \
	echo "Creating Makefiles." && \
	sleep 1 && \
	cmake -S lib/MLX42/ -B lib/MLX42/build && \
	echo "Building glfw3 and MLX42." && \
	sleep 1; \
	make -C lib/MLX42/build; \
	fi

$(LIBFT):
	git submodule update --init --recursive --remote
	@make -C lib/libft

$(NAME): $(LIBFT) $(LIBMLX42) $(OBJECT)
	@$(CC) $(LIBFT) $(OBJECT) $(LIBMLX42) $(GLFW3) $(FRAMEWORK) -o $(NAME)
	@echo "$(NAME) created."

clean:
	@echo "Cleaning."
	@rm -rf src/*.o
	@make clean -C lib/libft
ifneq (,$(wildcard ./lib/MLX42/build))
	@make clean -C ./lib/MLX42/build/_deps/glfw-build
	@make clean -C ./lib/MLX42/build
else
	
endif

fclean: clean
	@echo "Removing executable."
	@rm -rf src/*.o
	@make fclean -C lib/libft
	@rm -rf ./lib/MLX42/build $(GLFW3) $(LIBMLX42) $(NAME)
re: fclean all

run: $(NAME)
	@echo "Running $(NAME) with example map"
	@./$(NAME) maps./example.cub && \
	echo "Thanks for playing!"
.PHONY:
	all clean fclean re run
