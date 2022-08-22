#include "./libft.h"

static void	ft_is_neg(long long int *n, t_conv *c)
{
	ft_putchar_pf('-', 1, c);
	*n = -(*n);
}

static int	ft_has_tac(t_c_data *d, t_conv *c)
{
	long long int	n;

	n = d->nb;
	if (n < 0)
		ft_is_neg(&n, c);
	if (d->preci < d->intlen)
		d->preci = 0;
	if (d->preci >= d->intlen && d->nb >= 0)
		ft_pad_zero(d->preci - d->intlen, c);
	else if (d->preci >= d->intlen && d->nb < 0)
		ft_pad_zero(d->preci - (d->intlen - 1), c);
	ft_putnbr_pf(n, 1, c);
	if (d->width > d->preci)
	{
		if (d->preci >= d->intlen && d->nb >= 0)
			ft_pad_space(d->width - d->preci, c);
		else if (d->preci >= d->intlen && d->nb < 0)
			ft_pad_space((d->width - 1) - d->preci, c);
		else
			ft_pad_space(d->width - d->intlen, c);
	}
	return (0);
}

static void	ft_has_zero(t_c_data *d, t_conv *c)
{
	long long int	n;

	n = d->nb;
	if (d->preci == 0 && ft_has_dot(c->conv) && d->width > 0)
		ft_pad_space(d->width - d->intlen, c);
	if (n < 0)
		ft_is_neg(&n, c);
	if (d->width > d->intlen && (!ft_has_dot(c->conv) || d->preci < 0))
		ft_pad_zero(d->width - d->intlen, c);
	ft_putnbr_pf(n, 1, c);
}

static void	ft_has_no_flag(t_c_data *d, t_conv *c)
{
	long long int	n;

	n = d->nb;
	if (d->preci < d->intlen)
		d->preci = 0;
	if (d->width > d->preci)
	{
		if (d->preci >= d->intlen && d->nb >= 0)
			ft_pad_space(d->width - d->preci, c);
		else if (d->preci >= d->intlen && d->nb < 0)
			ft_pad_space((d->width - 1) - d->preci, c);
		else
			ft_pad_space(d->width - d->intlen, c);
	}
	if (n < 0)
		ft_is_neg(&n, c);
	if (d->preci >= d->intlen && d->nb >= 0)
		ft_pad_zero(d->preci - d->intlen, c);
	else if (d->preci >= d->intlen && d->nb < 0)
		ft_pad_zero(d->preci - (d->intlen - 1), c);
	ft_putnbr_pf(n, 1, c);
}

int	ft_i(t_conv *c, va_list *alist)
{
	t_c_data	d;

	d.nb = va_arg(*alist, int);
	d.width = ft_has_width(c->conv);
	d.preci = ft_has_precision(c->conv);
	d.intlen = ft_int_len(d.nb);
	if (ft_strlen(c->conv) == 2)
	{
		ft_putnbr_pf(d.nb, 1, c);
		return (0);
	}
	if (d.preci == 0 && ft_has_dot(c->conv) && d.nb == 0)
		return (ft_pad_space(d.width, c));
	if (ft_has_flag(c->conv) == '-'
		|| (ft_has_flag(c->conv) == '0' && ft_has_flag(c->conv) == '-'))
		ft_has_tac(&d, c);
	else if (ft_has_flag(c->conv) == '0' && d.preci <= 0)
		ft_has_zero(&d, c);
	else
		ft_has_no_flag(&d, c);
	return (0);
}
