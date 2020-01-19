/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thverney <thverney@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 20:17:19 by thverney          #+#    #+#             */
/*   Updated: 2019/12/09 17:57:49 by thverney         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct		s_list
{
	char	*pos;
	char	*pos2;
	int		ret;
	int		fd_tp;
}					t_list;

int					rdline(char **line, char **str, t_list spl, char *buff);
int					checkerror_gnl(int fd, char **line);
char				*ft_strchr(const char *s, int c);
char				*sdupfr(char *s1, size_t n);
char				*ft_sjoin_free(char const *dst, char const *src, size_t n);
size_t				ft_strlen(const char *str);
int					endofline(char **str, char *pos, char *pos2, char **line);
int					posnonull(char **line, char **str, char *buff, t_list spl);
int					ft_atoi(const char *str);
void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t count, size_t size);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					isnb(int c);
int					ft_isprint(int c);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memset(void *b, int c, size_t len);
char				*ft_strdup(const char *s1);
size_t				ft_strlen(const char *s);
int					ft_strncmp(const char *s1, const char *s2, size_t size);
char				*ft_strnstr(const char *haystack, const char *needle, size_t len);
int					ft_tolower(int c);
int					ft_toupper(int c);
char				*ft_strchr(const char *s, int c);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
char				*ft_strrchr(const char *s, int c);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
char				**ft_split(char const *s, char c);
char				*ft_itoa(long long int n);
char				*ft_strtrim(char const *s1, char const *set);
size_t				ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_putchar(char c);
void				ft_putstr(char *str);
void				ft_putnbr(int nb);
char				*ft_itoa_base(long long int value, int param);

#endif
