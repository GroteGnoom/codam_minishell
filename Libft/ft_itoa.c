#include "libft.h"
static int	ft_numlen(int nbr);

static char	*ft_numcpy(long nbr, int len, char *str);

char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	long	nbr;

	nbr = n;
	len = ft_numlen(nbr);
	if (nbr < 0)
		len++;
	str = malloc(len + 1);
	if (str == 0)
		return (0);
	if (nbr < 0)
	{
		str[0] = '-';
		nbr *= -1;
	}
	if (nbr == 0)
		str[0] = '0';
	str[len] = '\0';
	ft_numcpy(nbr, len, str);
	return (str);
}

static int	ft_numlen(int nbr)
{
	int	i;

	i = 0;
	if (nbr == 0)
		i++;
	if (nbr < 0)
		nbr *= -1;
	while (nbr != 0)
	{
		nbr = nbr / 10;
		i++;
	}
	return (i);
}

static char	*ft_numcpy(long nbr, int len, char *str)
{
	while (nbr > 0)
	{
		len--;
		str[len] = nbr % 10 + '0';
		nbr /= 10;
	}
	return (str);
}
