CC = cc
CFLAGS = -Wall -Wextra -Werror -g
GLFW3 = lib/MLX42/build/_deps/glfw-build/src/libglfw3.a
LIBMLX42 = lib/MLX42/build/libmlx42.a
FRAMEWORK = -framework Cocoa -framework OpenGL -framework IOKit
EXAMPLE_MAP = maps/pdf_example.cub
SOURCE = src/check_map.c 			\
		src/debug.c 				\
		src/free.c 					\
		src/get_map.c				\
		src/handle_buffer.c 		\
		src/init.c 					\
		src/input_utils.c 			\
		src/input.c 				\
		src/input2.c 				\
		src/main.c 					\
		src/errors.c 				\
		src/errors2.c 				\
		src/errors3.c 				\
		src/errors4.c 				\
		src/map_utils.c 			\
		src/flood_fill.c 			\
		src/draw_utils.c			\
       	src/draw_2d.c 				\
        src/draw_3d.c 				\
        src/key_handler.c 			\
		src/key_handler_utils.c     \
		src/raycaster_3d.c 			\
		src/raycaster_cast_cf.c 	\
		src/raycaster_cast_t.c 		\
		src/raycaster_init.c     	\
		src/raycaster_utils.c 		\
		src/raycaster_utils2.c 		\
		src/raycaster.c 			\
        src/cube_utils.c 			\
        src/rgba_utils.c 			\
        src/calculation_utils.c 	\
        src/safe_check.c 			\
		src/mlx_utils.c 			\
        src/utils.c
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
	cmake -S lib/MLX42/ -B lib/MLX42/build -DGLFW_FETCH=1 && \
	echo "Building glfw3 and MLX42." && \
	sleep 1; \
	make -C lib/MLX42/build; \
	fi

$(LIBFT):
	git submodule update --init --recursive --remote
	@make -C lib/libft

$(NAME): $(LIBFT) $(LIBMLX42) $(OBJECT)
	@$(CC) $(LIBFT) -fsanitize=address $(OBJECT) $(LIBMLX42) $(GLFW3) $(FRAMEWORK) -o $(NAME)
	@echo "$(NAME) created."

clean:
	@echo "Cleaning."
	@rm -rf src/*.o
	@make clean -C lib/libft

fclean: clean
	@echo "Removing executable."
	@rm -rf src/*.o
	@make fclean -C lib/libft
	@rm -rf ./lib/MLX42/build $(GLFW3) $(LIBMLX42) $(NAME)
re: fclean all

run: $(NAME)
	@echo "Running $(NAME) with: $(EXAMPLE_MAP)"
	@./$(NAME) $(EXAMPLE_MAP) && \
	echo "Thanks for playing!"
.PHONY:
	all clean fclean re run
