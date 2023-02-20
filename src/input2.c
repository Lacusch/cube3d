
#include "../includes/cube3d.h"

void	invalid_rgb(t_cube3d	*data)
{
	write(STDERR_FILENO, INVALID_RGB, 19);
	data->input_error = true;
}

void	could_be_valid(char	*str, t_cube3d	*data)
{
	int	total;
	int	size;

	total = 0;
	size = 0;
	terminate_str(str);
	if (*str == 'F' || *str == 'C')
		str++;
	else
		return (set_error(data));
	while (*str == ' ' && *str)
		str++;
	if (ft_strlen(str) > (size_t)11)
	{
		printf("%s", RGB_LONG);
		return (set_error(data));
	}
	digit_check(data, 0, 0, str);
}

void	invalid_error2(t_cube3d	*data)
{
	write(STDERR_FILENO, INVALID_CHAR, 32);
	data->input_error = true;
}

void	set_error(t_cube3d	*data)
{
	data->input_error = true;
}

void	digit_check(t_cube3d	*data, int loop, int start, char	*str)
{
	int	total;

	total = start;
	while (total < start + 4 && str[total] != '\0')
	{
		if (ft_isdigit(str[total]) || str[total] == ',')
			total++;
		else
			return (invalid_error2(data));
		if (str[total] == ',')
			break ;
	}
	if (str[total] == '\0')
		return ;
	if (ft_isdigit(str[total]) || str[total] == ',')
		total++;
	else
		return (invalid_error2(data));
	loop++;
	if (loop < 3)
		digit_check(data, loop, total, str);
}
