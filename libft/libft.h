/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aronin <aronin@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 11:08:03 by kiborroq          #+#    #+#             */
/*   Updated: 2021/01/30 01:31:39 by aronin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

# define MIN_INT -2147483648
# define MIN_INT_STR "-2147483648"

# define MAX_LONG 9223372036854775807

/*
**Struct of list elemnt
*/

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/*
**Struct of printf
*/

typedef struct		s_struct
{
	char			vartype;
	char			flag;
	int				width;
	int				precision;
	char			*output;
	int				error;
}					t_struct;

/*
**Part 1 - Libc functions
*/

void				*ft_memset(void *mem, int ch, size_t n);
void				ft_bzero(void *mem, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memccpy(void *dest, const void *src, int ch, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memchr(const void *mem, int ch, size_t n);
int					ft_memcmp(const void *mem1, const void *mem2, size_t n);
size_t				ft_strlen(const char *str);
size_t				ft_strlcpy(char *dest, const char *src, size_t dest_size);
size_t				ft_strlcat(char *dest, const char *src, size_t dest_size);
char				*ft_strchr(const char *str, int ch);
char				*ft_strrchr(const char *str, int ch);
char				*ft_strnstr(const char *big, const char *little, size_t n);
int					ft_strcmp(const char *str1, const char *str2);
int					ft_strncmp(const char *str1, const char *str2, size_t n);
int					ft_strrncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *str);
int					ft_isalpha(int ch);
int					ft_isdigit(int ch);
int					ft_isalnum(int ch);
int					ft_isascii(int ch);
int					ft_isprint(int ch);
int					ft_isspace(int ch);
int					ft_isemptyline(char *line);
int					ft_toupper(int ch);
int					ft_tolower(int ch);
void				*ft_calloc(size_t nmemb, size_t size);
char				*ft_strdup(const char *str);
char				*ft_strndup(const char *str, int n);
int					ft_max(int n1, int n2);

/*
**Part 2 - Additional functions
*/

char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				**ft_split(char const *s, char c);
char				*ft_itoa(int n);
char				*ft_uitoa(unsigned int n);
char				*ft_itoa_base(unsigned long n, char *base);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putarr_fd(int **arr, int h, int w, int fd);
char				*ft_skip_spaces(char *str);
char				*ft_skip_digits(char *str);
int					ft_numdig(int **array, int height, int width, int dig);
void				ft_freeptr(void **ptr);
void				ft_free_arr(void **array, int height);

/*
**Part 3 - Bonus functions
*/

t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void*));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
void				*ft_get_next_contnt(t_list *lst);
void				*ft_get_contnt(t_list *lst, int index);
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
								void (*del)(void *));

/*
**Part 4 - Some more additional functions
*/

int					ft_printf(const char *input, ...);
long				ft_printf_coordinator(const char *input, va_list *arg,
					int result);
void				read_format(t_struct *output, const char **input,
					va_list **arg, const char *typedict);
void				get_output(t_struct **output, const char ***input,
					va_list ***arg);
int					check_ifvalid(const char *typedict, char c, int mode);
char				*ft_strdup_advanced(const char *s1, t_struct ***list,
					int precision);
int					convert_to_int(const char ***input, t_struct **output);
t_struct			create_new_struct(void);
char				*ft_itoa_ulong_base(unsigned long long n, int base,
					char vartype);
int					validate_output(t_struct *output);
long				print_output(t_struct *output, char vartype, int width,
					int precision);
long				print_delimiters(char c, int len, int target);
long				ft_putstr_advanced(char *s, char vartype, int precision,
					int maxlen);
int					max(int a, int b, int c);
int					ft_isalnum_str(char *str);
int					ft_isdigit_str(char *str);
char				*ft_strupcase(char *str);
char				*ft_strlowcase(char *str);
char				*ft_strjoin_three(char const *s1, char const *s2,
					char const *s3);

#endif
