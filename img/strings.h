/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dath <dath@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 23:51:54 by dath              #+#    #+#             */
/*   Updated: 2025/03/13 13:46:24 by dath             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRINGS_H
# define STRINGS_H

/*************************************************/
/* bitmap loading */
# define ERR_OPEN_FAILED		"Open failed."
# define ERR_READ_FAILED		"Read failed."
# define ERR_INVALID_MAGIC		"Invalid magic."
# define ERR_INVALID_SIZE		"Promised size vs actual size mismatch \
or read error."
# define ERR_INVALID_OFFSET		"Invalid data offset."
# define ERR_INVALID_DIB		"Only BITMAPCOREHEADER DIB header is supported."
# define ERR_INVALID_BPP		"Only 24 BPP is supported."
# define ERR_SIZE_OOB			"Image size too big or too small"
# define ERR_INVALID_RATIO		"Image size is invalid"
# define ERR_INVALID_CP			"Color plane value must be 1."

/* misc */
# define ERR_MALLOC				"Malloc failed"
# define ERR_FAILED_TO_LOAD		"Failed to load %s: %s"
/**************************************************/


#endif
