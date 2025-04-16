/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhervoch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 20:53:33 by jhervoch          #+#    #+#             */
/*   Updated: 2025/04/14 16:51:15 by jhervoch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"
#include <stdio.h>
#include <math.h>

int	main(int ac, char **av)
{
	if (ac <= 0)
	{
		(void)av;
		return (0);
	}
	ft_printf("empty main test in srcs\n");
	
//	float test[] = {0.5f, 1.0f, 10.5f, 20.0f, 3.0f, 50.0f, 100.0f};
//    int i;
//    for (i = 0; i < (int)(sizeof(test)/sizeof(test[0])); i++)
//    {
//        float x = test[i];
//        printf("x = %f\n", x);
//        printf("vrai powf(x) = %f\n", powf(x));
//        printf("ft_powf(x)  = %f\n", ft_powf(x));
//        printf("erreur = %e\n\n", ft_powf(x) - powf(x));
//    }


	float base[] = {2.0f, 3.0f, 5.0f, 10.0f};
    float expo[] = {2.0f, 3.0f, 0.5f, -1.0f};

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            float x = base[i];
            float y = expo[j];
            float res_std = powf(x, y);
            float res_ft = ft_powf(x, y);
            float err = res_ft - res_std;

            printf("x = %.4f, y = %.4f | powf(x,y) = %.6f | ft_powf = %.6f | erreur = %.2e\n",
                   x, y, res_std, res_ft, err);
        }
    }
	return (0);
}
