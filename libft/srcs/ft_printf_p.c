#include "./libft.h"

static void	ft_itoh(unsigned long int n, char *s)
{
	char				*base;
	unsigned long int	mod;
	unsigned long int	div;
	int					i;

	base = ft_strdup("0123456789abcdef");
	i = 0;
	div = n / 16;
	mod = n % 16;
	s[i++] = base[mod];
	while (div > 0)
	{
		mod = div % 16;
		s[i++] = base[mod];
		div /= 16;
	}
	ft_strrev(s);
	free(base);
}

static void	ft_has_tac(t_c_data *d, t_conv *c)
{
	int	len;

	len = ft_strlen(d->hx);
	ft_putstr_len("0x", 2, c);
	ft_putstr_len(d->hx, len, c);
	if (d->width > len)
		ft_pad_space((d->width - len) - 2, c);
}

int	ft_p(t_conv *c, va_list *alist)
{
	t_c_data	d;
	int			len;

	ft_memset((void *)d.hx, 0, 17);
	d.nb = va_arg(*alist, unsigned long int);
	ft_itoh(d.nb, d.hx);
	len = ft_strlen(d.hx);
	d.width = ft_has_width(c->conv);
	if (ft_has_flag(c->conv) == '-')
		ft_has_tac(&d, c);
	else
	{
		if (d.width > len)
			ft_pad_space((d.width - len) - 2, c);
		ft_putstr_len("0x", 2, c);
		ft_putstr_len(d.hx, len, c);
	}
	ft_memset((void *)d.hx, 0, 17);
	return (0);
}
