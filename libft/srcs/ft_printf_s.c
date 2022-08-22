#include "./libft.h"

static int	ft_has_tac(t_c_data *d, t_conv *c)
{
	long int	len;

	len = ft_strlen(d->s);
	if (ft_has_dot(c->conv) && d->preci == 0)
		return (ft_pad_space(d->width, c));
	if (d->preci > 0 && d->preci < len)
		ft_putstr_len(d->s, d->preci, c);
	else
		ft_putstr_len(d->s, len, c);
	if (d->width > d->preci && d->preci > 0 && d->preci < len)
		ft_pad_space(d->width - d->preci, c);
	else
		return (ft_pad_space(d->width - len, c));
	return (0);
}

static int	ft_has_no_tac(t_c_data *d, t_conv *c)
{
	long int	len;

	len = ft_strlen(d->s);
	if (ft_has_dot(c->conv) && d->preci == 0)
		return (ft_pad_space(d->width, c));
	else if (ft_has_dot(c->conv) && d->preci > 0 && d->preci < len)
	{
		if (d->width > 0)
			ft_pad_space(d->width - d->preci, c);
		ft_putstr_len(d->s, d->preci, c);
		return (0);
	}
	else if (ft_has_dot(c->conv) && d->preci > 0 && d->preci > len)
	{
		if (d->width > 0)
			ft_pad_space(d->width - len, c);
		ft_putstr_len(d->s, len, c);
		return (0);
	}
	if (d->width > len)
		ft_pad_space(d->width - len, c);
	ft_putstr_len(d->s, len, c);
	return (0);
}

int	ft_s(t_conv *c, va_list *alist)
{
	t_c_data	d;
	char		*nl;

	d.s = va_arg(*alist, char *);
	nl = ft_strdup("(null)");
	if (d.s == NULL)
		d.s = nl;
	d.width = ft_has_width(c->conv);
	d.preci = ft_has_precision(c->conv);
	if (ft_has_flag(c->conv) == '-')
		ft_has_tac(&d, c);
	else
		ft_has_no_tac(&d, c);
	free(nl);
	return (0);
}
