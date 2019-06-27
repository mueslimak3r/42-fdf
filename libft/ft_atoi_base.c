#include "libft.h"

static int	is_radix(char c, unsigned int base)
{
	if (base <= 10)
		return (c >= '0' && c <= '0' + (char)base);
	return ((c >= '0' && c <= '9')
		|| (c >= 'A' && c <= ('A' + (char)base - 10)));
}

/*
**	Eats any leading whitespace, then any combination of signs.
**	If I find a negative sign, you get a negative number. No bullshit.
**	Eats until a character inappropriate for the given base (or NULL) is found.
*/

int			ft_atoi_base(char *str, const int base)
{
	int		value;
	int		sign;
	char	x;

	value = 0;
	sign = 1;
	if (base <= 1 || base > 36)
		return (0);
	while (ft_isspace(*str))
		str++;
	while (*str == '-' || *str == '+')
		if (*(str++) == '-')
			sign = -1;
	while ((x = ft_toupper(*(str++))) && is_radix(x, base))
		if (x - 'A' >= 0)
			value = value * base + x - 'A' + 10;
		else
			value = value * base + x - '0';
	return (value * sign);
}