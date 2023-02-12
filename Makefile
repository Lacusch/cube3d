CC = cc
CFLAGS = -Wall -Wextra -Werror
GLFW3 = lib/MLX42/build/_deps/glfw-build/src/libglfw3.a
LIBMLX42 = lib/MLX42/build/libmlx42.a
FRAMEWORK = -framework Cocoa -framework OpenGL -framework IOKit
SOURCE = src/free.c \
		src/init.c \
		src/main.c \
		src/parcing.c
OBJECT = $(SOURCE:.c=.o)

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

$(NAME): $(LIBMLX42) $(OBJECT)
	@$(CC) $(OBJECT) $(LIBMLX42) $(GLFW3) $(FRAMEWORK) -o $(NAME)
	@echo "$(NAME) created."
clean:
	@echo "Cleaning."
	@make clean -C /Users/slaszlo-/42/cube3d/lib/MLX42/build/_deps/glfw-build
	@make clean -C /Users/slaszlo-/42/cube3d/lib/MLX42/build
	@rm -rf src/*.o
fclean:
	@echo "Removing executable."
	@rm -rf lib/MLX42/build $(GLFW3) $(LIBMLX42) $(NAME)
re: fclean all

run: $(NAME)
	@echo "Running $(NAME) with example map"
	@./$(NAME) maps./example.cub && \
	echo "Thanks for playing!"
.PHONY:
	all clean fclean re run
