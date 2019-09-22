# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    srcs.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: roliveir <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/07 10:04:52 by roliveir          #+#    #+#              #
#    Updated: 2019/09/21 17:54:21 by oboutrol         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

WOLF_PATH = ./srcs/

WOLF =		wolf_main.c			\
			wolf_key_manager.c	\
			wolf_initialize.c	\
			wolf_map.c			\
			wolf_alloc.c		\
			ray_cast.c

WOLF_SRCS = $(addprefix $(WOLF_PATH),$(WOLF))
SRCS += $(WOLF_SRCS)
