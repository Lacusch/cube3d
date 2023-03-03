NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
GLFW3 = $$HOME/.brew/Cellar/glfw/3.3.8/lib/
LIBMLX42 = lib/MLX42/build/libmlx42.a
FRAMEWORK = -framework Cocoa -framework OpenGL -framework IOKit
EXAMPLE_MAP = maps/maze.cub
SOURCE = src/debug.c 				\
		src/free.c 					\
		src/get_map.c				\
		src/handle_buffer.c 		\
		src/is.c					\
		src/init.c 					\
		src/input_utils.c 			\
		src/input.c 				\
		src/input2.c 				\
		src/main.c 					\
		src/errors.c 				\
		src/errors2.c 				\
		src/errors3.c 				\
		src/errors4.c 				\
		src/errors5.c				\
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
	cmake -S lib/MLX42/ -B lib/MLX42/build
	make -C lib/MLX42/build

$(LIBFT):
	git submodule update --init --remote
	@make -C lib/libft

$(NAME): $(LIBFT) $(OBJECT) $(LIBMLX42)
	@$(CC) $(LIBFT) $(OBJECT) $(LIBMLX42) -lglfw -L $(GLFW3) $(FRAMEWORK) -o $(NAME)
	@echo "$(NAME) created."

clean:
	@echo "Cleaning."
	@rm -rf src/*.o
	@make clean -C lib/libft

fclean: clean
	@echo "Removing executable."
	@rm -rf src/*.o
	@make fclean -C lib/libft
	@rm -rf ./lib/MLX42/build $(LIBMLX42) $(NAME)
re: fclean all

run: $(NAME)
	@echo "Running $(NAME) with: $(EXAMPLE_MAP)"
	@./$(NAME) $(EXAMPLE_MAP) && \
	echo "Thanks for playing!"
.PHONY:
	all clean fclean re run
