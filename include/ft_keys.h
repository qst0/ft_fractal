/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keys.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myoung <myoung@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 09:24:31 by myoung            #+#    #+#             */
/*   Updated: 2016/11/18 06:57:50 by myoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_KEYS_H
# define FT_KEYS_H

# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_SEMI 41
# define KEY_PLUS 69
# define KEY_MINUS 78
# define KEY_SPACE 49
# define KEY_A 0
# define KEY_B 11
# define KEY_C 8
# define KEY_D 2
# define KEY_E 14
# define KEY_F 3
# define KEY_G 5
# define KEY_H 4
# define KEY_I 34
# define KEY_J 38
# define KEY_K 40
# define KEY_L 37
# define KEY_M 46
# define KEY_N 45
# define KEY_O 31
# define KEY_P 35
# define KEY_Q 12
# define KEY_R 15
# define KEY_S 1
# define KEY_T 17
# define KEY_U 32
# define KEY_V 9
# define KEY_W 13
# define KEY_X 7
# define KEY_Y 16
# define KEY_Z 6

typedef struct	s_keys
{
	int			space:1;
	int			semi:1;
	int			i:1;
	int			j:1;
	int			k:1;
	int			l:1;
	int			m:1;
	int			n:1;
	int			o:1;
	int			p:1;
	int			x:1;
	int			y:1;
	int			z:1;
	int			q:1;
	int			w:1;
	int			e:1;
	int			a:1;
	int			s:1;
	int			d:1;
	int			left:1;
	int			up:1;
	int			right:1;
	int			down:1;
	int			plus:1;
	int			minus:1;
}				t_keys;

#endif
