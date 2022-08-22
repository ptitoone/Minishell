#include "./libft.h"

static int	ft_has_tac(t_c_data *d, t_conv *c)
{
	if (d->preci < d->intlen)
		d->preci = 0;
	else if (d->preci > 0 && d->preci > d->intlen)
		ft_pad_zero(d->preci - d->intlen, c);
	ft_putnbr_pf(d->nb, 1, c);
	if (d->width == d->preci)
		return (0);
	else if (d->width > d->preci && d->preci != 0)
		return (ft_pad_space(d->width - d->preci, c));
	else if (d->width > 0 && d->preci == 0)
		return (ft_pad_space(d->width - d->intlen, c));
	return (ft_pad_space(d->width - d->preci, c));
}

static void	ft_has_zero(t_c_data *d, t_conv *c)
{
	long long int	n;

	n = d->nb;
	if (d->width > d->intlen || d->width > d->preci)
	{
		if (!ft_has_dot(c->conv) || d->preci < 0)
			ft_pad_zero(d->width - d->intlen, c);
		else if (ft_has_dot(c->conv) && d->preci > d->intlen)
		{
			ft_pad_space(d->width - d->preci, c);
			ft_pad_zero(d->preci - d->intlen, c);
		}
		else
			ft_pad_space(d->width - d->intlen, c);
	}
	else if (d->preci > d->intlen)
		ft_pad_zero(d->preci - d->intlen, c);
	ft_putnbr_pf(n, 1, c);
}

static void	ft_has_no_flag(t_c_data *d, t_conv *c)
{
	long long int	n;

	n = d->nb;
	if (ft_has_dot(c->conv))
	{
		if (d->width > d->preci || d->width > d->intlen)
		{
			if (d->preci < d->intlen)
				ft_pad_space(d->width - d->intlen, c);
			else
				ft_pad_space(d->width - d->preci, c);
			if (d->preci > d->intlen)
				ft_pad_zero(d->preci - d->intlen, c);
		}
		else if (d->width <= d->preci)
			ft_pad_zero(d->preci - d->intlen, c);
	}
	else if (d->width > d->intlen)
		ft_pad_space(d->width - d->intlen, c);
	ft_putnbr_pf(n, 1, c);
}

int	ft_u(t_conv *c, va_list *alist)
{
	t_c_data	d;

	d.nb = va_arg(*alist, unsigned int);
	d.width = ft_has_width(c->conv);
	d.preci = ft_has_precision(c->conv);
	d.intlen = ft_int_len(d.nb);
	if (ft_strlen(c->conv) == 2)
	{
		ft_putnbr_pf(d.nb, 1, c);
		return (0);
	}
	else if (!d.preci && !d.nb && ft_has_dot(c->conv))
		return (ft_pad_space(d.width, c));
	else if (ft_has_flag(c->conv) == '-'
		|| (ft_has_flag(c->conv) == '0' && ft_has_flag(c->conv) == '-'))
		ft_has_tac(&d, c);
	else if (ft_has_flag(c->conv) == '0' && ft_has_flag(c->conv) != '-')
		ft_has_zero(&d, c);
	else
		ft_has_no_flag(&d, c);
	return (0);
}
