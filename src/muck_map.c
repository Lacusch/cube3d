#include "../includes/cube3d.h"

extern int g_map_size_y;

char	**muck_map(void)
{
	char	**res;
	res = malloc(sizeof(char **) * (g_map_size_y + 1));
	res[0] = "        1111111111111111111111111";
	res[1] = "100000000000000000000000000001";
	res[2] = "100000000000000000011111110001";
	res[3] = "100000000000000000010000010001";
	res[4] = "100000000000000000010000010001";
	res[5] = "100000000000000000010000010001";
	res[6] = "100000000000000000010000110001";
	res[7] = "100000000000N00000010000110001";
	res[8] = "100000000000000000011111110001";
	res[9] = "100000000000000000000000000001";
	res[10] = "100000000000000000000000000001";
	res[11] = "100000000000000000000000000001";
	res[12] = "100000000000000000000000000001";
	res[13] = "100000000000000000000000000001";
// 	res[14] = "100000000000000000000000000001";
// 	res[15] = "100000000000011111111111111111";
// 	res[16] = "100000000000011000000000000001";
// 	res[17] = "100000000000000000000000000001";
// 	res[18] = "100000000000000000000000000001";
// 	res[19] = "100000000000000000000000000001";
// 	res[20] = "100000000000000000000000000001";
// 	res[21] = "100000000000000000000000000001";
// 	res[22] = "100000000000000000000000000001";
// 	res[23] = "100000000000000000000000000001";
// 	res[24] = "100000000000000000000000000001";
// 	res[25] = "100000000000000000000000000001";
// 	res[26] = "100000000000000000000000000001";
// 	res[27] = "100000000000000000000000000001";
// 	res[28] = "100000000000000000000000000001";
// 	res[29] = "111111111111111111111111111111";
	res[14] = NULL;
	return (res);
}
