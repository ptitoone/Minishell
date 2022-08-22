#ifndef LIBFT_H
# define LIBFT_H
# define BUFFER_SIZE 32
# include <stdlib.h>
# include <unistd.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <limits.h>
# include <string.h>
# include <errno.h>
# include <stdarg.h>

typedef enum e_ribool
{
	T_FALSE,
	T_TRUE,
	T_MAYBE
}				t_ribool;

typedef enum e_flow
{
	OUT,
	IN
}				t_flow;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

typedef struct s_buffer
{
	char		buffer[BUFFER_SIZE];
	ssize_t		readlen;
	ssize_t		buffinc;
}				t_buffer;

typedef struct s_conv {
	char	*conv;
	int		count;
	int		i;
	int		j;
}				t_conv;

typedef struct s_c_data {
	char		ch;
	char		hx[17];
	char		*s;
	void		*p;
	long int	nb;
	int			width;
	long int	preci;
	long int	intlen;
}				t_c_data;

t_ribool		ft_close_fd(int *fd);
t_ribool		ft_unlink_file(char *file);

t_ribool		ft_malloc_char(int size, char **ptr);
t_ribool		ft_malloc_int(int size, int **ptr);
t_ribool		ft_malloc_float(int size, float **ptr);
t_ribool		ft_malloc_double(int size, double **ptr);
t_ribool		ft_malloc_t_ribool(int size, t_ribool **ptr);

t_ribool		ft_malloc_char_2(int size, char ***ptr);
t_ribool		ft_malloc_int_2(int size, int ***ptr);
t_ribool		ft_malloc_float_2(int size, float ***ptr);
t_ribool		ft_malloc_double_2(int size, double ***ptr);
t_ribool		ft_malloc_t_ribool_2(int size, t_ribool ***ptr);

t_ribool		ft_free_char(char **ptr);
t_ribool		ft_free_int(int **ptr);
t_ribool		ft_free_float(float **ptr);
t_ribool		ft_free_double(double **ptr);
t_ribool		ft_free_t_ribool(t_ribool **ptr);
void			ft_free_anon_array(void **array, int len);

t_ribool		ft_free_char_2_pre(char ***ptr, int delet);
t_ribool		ft_free_int_2_pre(int ***ptr, int delet);
t_ribool		ft_free_float_2_pre(float ***ptr, int delet);
t_ribool		ft_free_double_2_pre(double ***ptr, int delet);
t_ribool		ft_free_t_ribool_2_pre(t_ribool ***ptr, int delet);

t_ribool		ft_free_char_2_post(char ***ptr, int delet);
t_ribool		ft_free_int_2_post(int ***ptr, int delet);
t_ribool		ft_free_float_2_post(float ***ptr, int delet);
t_ribool		ft_free_double_2_post(double ***ptr, int delet);
t_ribool		ft_free_t_ribool_2_post(t_ribool ***ptr, int delet);

double			ft_atof(const char *str);
int				ft_atoi(const char *str);
long int		ft_atol(const char *str);
void			ft_bzero(void *s, size_t n);
t_ribool		ft_calloc(size_t count, size_t size, void *ptr);
void			*fr_realloc(void *ptr, size_t size);
t_ribool		ft_error(const char *msg, const char *msg2);
t_ribool		ft_freerror(const char *msg, const char *msg2);
t_ribool		ft_memerror(const char *forfree);
int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
t_ribool		ft_strisdigit(char *str);
t_ribool		ft_strisnumber(char *str);
t_ribool		ft_long_overflow(const char *src);
void			ft_ltoa_init(long n, long *clclen, \
					int *strlen, int *posinega);
char			*ft_ltoa(long n);
void			ft_itoa_init(int n, int *clclen, \
					int *strlen, int *posinega);
char			*ft_itoa(int n);
int				ft_isprint(int c);
int				ft_issigned(int c);
int				ft_isspace(int c);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memset(void *b, int c, size_t len);
void			ft_putchar_fd(char c, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
void			ft_putstr_fd(char *s, int fd);
char			*ft_strchr(const char *s, int c);
char			*ft_strdup(const char *s1);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
int				ft_strlen(const char *s);
int				ft_strlen_2(const char **s);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strnstr(const char *haystack, const char *needle, \
					size_t len);
char			*ft_strrchr(const char *s, int c);
void			ft_strrev(char *str);
int				ft_tolower(int c);
int				ft_toupper(int c);
char			**ft_split(char const *s, char c);
char			*ft_itoa(int n);
char			*ft_strjoin(char const *s1, char const *s2);
t_ribool		ft_strjoin_all(int ac, char **av, char c, char **str);
t_ribool		ft_strjoin_all_malloc(int ac, char **av, char c, char **str);
void			ft_strjoin_all_copy(int ac, char **av, char c, char *str);
int				s1_index0_not_exist(char **str);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char			*ft_substr(char const *s, unsigned int start, size_t len);
t_list			*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **alst, t_list *new);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **alst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void*));
void			ft_lstclear(t_list **lst, void (*del)(void*));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *), \
					void (*del)(void *));
t_ribool		ft_gnl_status(int error, const char *file, char *line);
int				ft_gnl_return_value(t_buffer *buff);
int				ft_gnl_line_maker(t_buffer *buff, ssize_t *linelen,
					char **line);
int				get_next_line(int fd, char **line);

int				ft_printf(const char *format, ...);
int				ft_int_len(long int n);
int				ft_handle_conv(t_conv *c, va_list *alist);
int				ft_c(t_conv *c, va_list *alist);
int				ft_s(t_conv *c, va_list *alist);
int				ft_p(t_conv *c, va_list *alist);
int				ft_i(t_conv *c, va_list *alist);
int				ft_u(t_conv *c, va_list *alist);
int				ft_x(t_conv *c, va_list *alist);
int				ft_ux(t_conv *c, va_list *alist);
void			ft_replace_asterisk(char **conv, va_list *alist);
int				ft_pad_zero(int len, t_conv *cv);
int				ft_pad_space(int len, t_conv *cv);
void			ft_putstr_len(const char *s, size_t len, t_conv *cv);
void			ft_putnbr_pf(long int n, int fd, t_conv *cv);
void			ft_putchar_pf(char c, int fd, t_conv *cv);
int				ft_check(const char c);
int				ft_is_spec(const char c);
int				ft_parse_conv(const char *fmt, t_conv *c);
int				ft_check(const char c);
int				ft_is_spec(const char c);
int				ft_isdigit(int c);
int				ft_has_width(const char *conv);
int				ft_has_asterisk(const char *s);
int				ft_has_flag(const char *conv);
int				ft_has_precision(const char *conv);
int				ft_has_dot(const char *s);
int				ft_parse_conv(const char *fmt, t_conv *c);
int				ft_get_conv_type(const char *conv);

void			ft_affect_to_tab_2(void ***array, ...);

#endif
