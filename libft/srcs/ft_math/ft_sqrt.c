/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 10:28:07 by npolack           #+#    #+#             */
/*   Updated: 2025/04/14 15:45:16 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_sqrt(int nb)
{
	int	i;
	int	result;

	i = 0;
	while (i <= nb)
	{
		result = i * i;
		if (result == nb)
			return (i);
		i++;
	}
	return (0);
}

float	ft_sqrtf(float x)
{
	float	guess;
	float	epsilon;

	if (x < 0.0f)
		return (-1.0f);
	if (x == 0.0f || x == 1.0f)
		return (x);
	guess = x / 2.0f;
	epsilon = 0.00001f;
	while ((guess * guess - x) > epsilon || (x - guess * guess) > epsilon)
	{
		guess = (guess + x / guess) / 2.0f;
	}
	return (guess);
}
