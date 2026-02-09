/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykolacze <ykolacze@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 10:41:01 by mcolin            #+#    #+#             */
/*   Updated: 2026/02/09 09:25:48 by ykolacze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIG_H
# define SIG_H

void	ft_signal_init(void);
void	ft_signal_child(void);
void	handler_sigint(int sig);
void	handler_sigint_here_doc(int sig);

#endif