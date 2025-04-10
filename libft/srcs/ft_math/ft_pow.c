/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 22:24:47 by npolack           #+#    #+#             */
/*   Updated: 2025/04/10 12:08:46 by npolack          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

float ft_powf(float base, float exponent)
{
    if (base <= 0.0f)
		return -1.0f; // crude domain check
    return ft_expf(exponent * ft_logf(base));
}
