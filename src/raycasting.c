#include "../includes/cube3d.h"

void	raycasting(mlx_image_t* img, char ***map)
{
    int     width = img->width;
    int     height = img->height;
	double	posX = 6;
	double	posY = 5;
	double	dirX = -1;
	double	dirY = 0;
	double	planeX = 0;
	double 	planeY = 0.66;
	// ---------
	double	cameraX = 0;
	double 	rayDirX = 0;
	double 	rayDirY = 0;
	double 	sideDistX = 0;
	double 	sideDistY = 0;
	double	deltaDistX = 0;
	double	deltaDistY = 0;
	double 	perpWallDist = 0;
	int		mapX = 0;
	int		mapY = 0;
	int		stepX = 0; 
    int 	stepY = 0;
	int 	hit = 0;
	int 	side = 0;
	int 	x = 0; 
	int	 	lineHeight = 0;
	int 	drawStart = 0;
	int 	drawEnd = 0;
	// ---------
	while (x < width)
	{
		hit = 0;
		side = 0;
		//----
		cameraX = 2 * x / width - 1;
		rayDirX = dirX + planeX * cameraX;
		rayDirY = dirY + planeY * cameraX;
		mapX = posX;
		mapY = posY;
		sideDistX = 0;
		sideDistY = 0;
		if (rayDirX == 0)
			deltaDistX = 100000000000;
		else 
			deltaDistX = fabs(1/rayDirX);
		if (rayDirY == 0)
			deltaDistY = 100000000000;
		else 
			deltaDistY = fabs(1/rayDirY);
		perpWallDist = 0;
		if (rayDirX < 0)
      	{
        	stepX = -1;
        	sideDistX = (posX - mapX) * deltaDistX;
      	}
      	else
      	{
        	stepX = 1;
        	sideDistX = (mapX + 1.0 - posX) * deltaDistX;
      	}
     	if (rayDirY < 0)
      	{
        	stepY = -1;
        	sideDistY = (posY - mapY) * deltaDistY;
      	}
      	else
      	{
        	stepY = 1;
        	sideDistY = (mapY + 1.0 - posY) * deltaDistY;
     	}
		while (hit == 0)
    	{	
        	if (sideDistX < sideDistY)
			{
          		sideDistX += deltaDistX;
          		mapX += stepX;
          		side = 0;
        	}
        	else
        	{
          		sideDistY += deltaDistY;
          		mapY += stepY;
          		side = 1;
       	 	}
			if (is_same_str(map[mapY][mapX], "1"))
				hit = 1;
      	}
		if (side == 0)
			perpWallDist = sideDistX - deltaDistX;
		else 
			perpWallDist = sideDistY - deltaDistY;
		if (perpWallDist == 0)
			perpWallDist = 1000000000;
		lineHeight = height / perpWallDist;
		drawStart = -lineHeight / 2 + height / 2;
	    if (drawStart < 0) 
		 	drawStart = 0;
	    drawEnd = lineHeight / 2 + height / 2;
	    if (drawEnd >= height) 
			drawEnd = height - 1;
		ft_draw_line(img, x, drawStart, x, drawEnd, 0x00FF00FF);
		x++;
	}
}
