/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_logf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npolack <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 12:05:23 by npolack           #+#    #+#             */
/*   Updated: 2025/04/14 16:38:11 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

float ft_logf(float x)
{
    if (x <= 0.0f)
        return -1.0f / 0.0f; // retourne -inf pour x <= 0

    int e = 0;

    // Ramène x entre [1, 2)
    while (x > 2.0f) { x *= 0.5f; e++; }
    while (x < 1.0f) { x *= 2.0f; e--; }

    float y = x - 1.0f;
    float result = 0.0f;
    float term = y;
    int i = 1;
    int sign = 1;

    while (i < 50)
    {
        result += sign * term / i;
        term *= y;
        sign = -sign;
        if (term / i < 1e-6f && term / i > -1e-6f)
            break;
        i++;
    }

    // Correction : log(x) = log(m) + e * log(2)
    const float LOG2 = 0.69314718f; // log(2) en float
    return result + e * LOG2;
}
