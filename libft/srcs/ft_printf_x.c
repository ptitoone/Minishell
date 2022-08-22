#include "./libft.h"

static void	ft_itoh(unsigned int n, char *s)
{
	char		*base;
	long int	mod;
	long int	div;
	int			i;

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

static int	ft_has_tac(t_c_data *d, t_conv *c)
{
	long int	len;

	len = ft_strlen(d->hx);
	if (ft_has_dot(c->conv) && d->preci == 0 && d->hx[0] == '0')
	{
		ft_pad_space(d->width, c);
		return (0);
	}
	if (d->preci > 0 && d->preci > len)
	{
		ft_pad_zero(d->preci - len, c);
		ft_putstr_len(d->hx, len, c);
	}
	else
		ft_putstr_len(d->hx, len, c);
	if (d->width > 0 && (d->width > d->preci || d->width > len))
	{
		if (d->width > len && d->preci > len)
			ft_pad_space(d->width - d->preci, c);
		else
			ft_pad_space(d->width - len, c);
		return (0);
	}
	return (0);
}

static int	ft_has_zero_or_no_flag(t_c_data *d, t_conv *c)
{
	long int	len;

	len = ft_strlen(d->hx);
	if (d->nb == 0 && ft_has_dot(c->conv) && d->preci == 0)
	{
		ft_pad_space(d->width, c);
		return (0);
	}
	if (d->width > len || d->width > d->preci)
	{
		if (d->preci > len)
		{
			ft_pad_space(d->width - d->preci, c);
			ft_pad_zero(d->preci - len, c);
		}
		else if ((!ft_has_dot(c->conv) || d->preci < 0)
			&& ft_has_flag(c->conv) != 0)
			ft_pad_zero(d->width - len, c);
		else
			ft_pad_space(d->width - len, c);
	}
	else if (d->preci > d->width && d->preci > len)
		ft_pad_zero(d->preci - len, c);
	ft_putstr_len(d->hx, len, c);
	return (0);
}

int	ft_x(t_conv *c, va_list *alist)
{
	t_c_data	d;

	ft_memset((void *)d.hx, 0, 17);
	d.nb = va_arg(*alist, unsigned int);
	ft_itoh(d.nb, d.hx);
	d.width = ft_has_width(c->conv);
	d.preci = ft_has_precision(c->conv);
	if (ft_has_flag(c->conv) == '-')
		ft_has_tac(&d, c);
	else
		ft_has_zero_or_no_flag(&d, c);
	ft_memset((void *)d.hx, 0, 17);
	return (0);
}
