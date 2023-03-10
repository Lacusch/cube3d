/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaszlo- <slaszlo-@student.42heibronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 10:37:39 by segarcia          #+#    #+#             */
/*   Updated: 2023/03/08 10:25:43 by slaszlo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define WRONG_EXTENSION	"Error\nWrong file extension\n"
# define TO_MANY_ARGS		"Error\nToo many arguments\n"
# define NO_ARGS			"Error\nNo arguments\n"
# define META_ERROR			"Error\nMissing parameter: "
# define NO_ERROR			"Nordern Wall texture\n"
# define SO_ERROR			"Southern Wall texture\n"
# define WE_ERROR			"Western Wall texture\n"
# define EA_ERROR			"Eastern Wall texture\n"
# define FC_ERROR			"Floor color texture\n"
# define CC_ERROR			"Celling color texture\n"
# define NOT_PNG			" does not end in .png\n"
# define NO_FILE			"Error\nCan't open file "
# define RGB_LONG			"Error\nRGB string is too long\n"
# define INVALID_CHAR		"Error\nInvalid character in RGB\n"
# define INVALID_RGB		"Error\nInvalid RGB\n"
# define DO_NO_ERROR		"Error\nNorthern texture already defined\n"
# define DO_SO_ERROR		"Error\nSouthern texture already defined\n"
# define DO_WE_ERROR		"Error\nWestern texture already defined\n"
# define DO_EA_ERROR		"Error\nEastern texture already defined\n"
# define DO_F_ERROR			"Error\nDuplicate Floor color\n"
# define DO_C_ERROR			"Error\nDuplicate Celling color\n"
# define WRONG_CHAR_MAP		"Error\ninvalid character in map\n"
# define TO_MANY_PLAYER		"Error\nDuplicate player\n"
# define NO_PLAYER			"Error\nNo player\n"
# define INVALID_MAP		"Error\nInvalid map\n"
# define MLX_ERROR			"Error\nProblem initializing mlx\n"
# define MLX_IMG_ERROR		"Error\nProblem initializing image\n"
# define MLX_TEXTURE		"Error\nProblem loading textures\n"
# define NOT_CLOSED			"Error\nMap is not closed\n"
# define EMPTY_LINE			"Error\nEmply line inside the map\n"
# define INV_QUETE			"Error\nInvalid number of quetes in RGB\n"
# define DOUBLE_COMA		"Error\nDouble coma in RGB\n"
# define NO_MAP				"Error\nCan't open map file\n"
# define SMALL_MAP			"Error\nMap is to small\n"
#endif
