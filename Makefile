#############################################
###		 			CONFIG		          ###
#############################################

NAME			= miniRT 
INCLUDES		= -I ./includes -I ./minilibx_linux -I ./libft/incl

CC				= clang
RM				= rm -rf
CFLAGS			= -Wall -Werror -Wextra -gdwarf-4
CFLAGS			+= -O3
CFLAGS			+= $(INCLUDES)

MKDIR			= mkdir -p

SOURCE_FILES	= main.c exit_handler.c parse_data.c parse_utils.c\
				  parse_rgb.c parse_ambient_lighting.c parse_utils_free.c\
				  parse_camera.c parse_coordinates.c parse_light.c\
				  parse_sphere.c parse_plane.c parse_cylinder.c init_parsing_data.c\
				  print_parsing_result.c identifier_error_check.c\
				  print_parsing_result_shapes.c mlx_events.c draw_utils.c render.c \
				  time_utils.c vector_utils.c sphere_utils.c color_utils.c plane_utils.c \
				  quadratic.c cylinder_utils.c disk_utils.c quaternions.c parse_cone.c \
				  cone_utils.c cone_utils2.c vector_norm_utils.c ft_atof.c init_shapes.c \
				  cast_ray.c cast_shadow_ray.c shading.c vector_cross.c material.c \
				  move_rotate.c mlx_no_event.c mlx_key_events.c color_convert.c ft_ftoa.c \
				  menu_utils.c menu_page_helper.c menu_init_select_del.c \
				  menu_btn_goto_page.c menu_btn_resets.c menu_draw_elem.c \
				  menu_event_utils.c menu_nbox_apply_1.c menu_nbox_apply_2.c \
				  menu_sphere.c menu_cylinder.c menu_plane.c menu_cone.c \
				  menu_create_elem.c menu_add_elem.c\
				  menu_page_add.c menu_page_cylinder.c menu_page_del.c \
				  menu_page_end.c menu_page_home.c menu_page_plane.c \
				  menu_page_select.c menu_page_sphere.c menu_page_cone.c \
				  select_obj.c add_frame_time.c mlx_utils.c


SOURCES_DIR		= src
SOURCES			= $(addprefix $(SOURCES_DIR)/, $(SOURCE_FILES))
OBJ_DIR			= obj
OBJ				= $(addprefix $(OBJ_DIR)/, $(notdir $(SOURCES:.c=.o)))
DEPENDS			= $(OBJ:.o=.d)


TOTAL_FILES := $(words $(SOURCE_FILES))

COMPILE_COUNT = 0

#############################################
###					COLORS			      ###
#############################################

RED				= \033[0;31m
GREEN			= \033[0;32m
YELLOW			= \033[0;33m
BLUE			= \033[0;34m
MAGENTA			= \033[0;35m
CYAN			= \033[0;36m
RESET_COLOR		= \033[0m
MOVEUP			= \033[F
RESET			= \e[2K\r

#############################################
###		 			RULES	      	      ###
#############################################

all: $(NAME)

$(NAME): libft/libft.a minilibx_linux/libmlx.a $(OBJ)
	@$(CC) $(CFLAGS) -lXext -lX11 -lm -lz $(OBJ) -o $(NAME) libft/libft.a minilibx_linux/libmlx.a
	@echo "$(RESET)$(GREEN)Compiled $(NAME)$(RESET_COLOR)"

-include $(DEPENDS)

$(OBJ_DIR)/%.o: $(SOURCES_DIR)/%.c Makefile
	@$(MKDIR) $(OBJ_DIR)
	@$(CC) $(CFLAGS) -MMD -MP -c $< -o $@
	@$(eval COMPILE_COUNT=$(shell echo $$(($(COMPILE_COUNT)+1))))
	@echo -n "$(RESET)[$(YELLOW)$$(($(COMPILE_COUNT)*100/$(TOTAL_FILES)))%] Compiling $(NAME)"

libft/libft.a:
	@make -sC libft

minilibx_linux/libmlx.a:
	@make -sC minilibx_linux

clean:
	@make fclean -sC libft 
	@make clean -sC minilibx_linux
	@$(RM) $(OBJ_DIR)
	@echo "$(GREEN)Removed the object files from $(NAME)$(RESET_COLOR)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(GREEN)Removed $(NAME) and the object files$(RESET_COLOR)"

re:
	@make -s fclean
	@make -s

.PHONY:	all clean fclean re
