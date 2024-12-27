/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 10:21:38 by ysahraou          #+#    #+#             */
/*   Updated: 2024/12/26 09:59:35 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

double normalizeAngle(double angle)
{
    while (angle < 0.0000)
        angle += 360;
    while (angle >= 360.0)
        angle -= 360;
    return angle;
}

void weapon_action_keys(int keycode, t_data *data)
{
    if (keycode == ZERO)
        data->weapon_numb = 0;
    else if (keycode == ONE)
        data->weapon_numb = 1;
    else if (keycode == TWO)
        data->weapon_numb = 2;
    else if (keycode == THREE)
        data->weapon_numb = 3;
    else if (keycode == FOUR)
        data->weapon_numb = 4;
    else if (keycode == FIVE)
        data->weapon_numb = 5;
    else if (keycode == SIX)
        data->weapon_numb = 6;
    else if (keycode == R)
        data->weapon_reload = true;
}

int key_p(int keycode, void *data1)
{
    t_data *data;

    // printf("keycode = %i\n", keycode);
    data = (t_data *)data1;
    if (keycode == KEY_A || keycode == KEY_D)
        data->player.is_move_side = 1;
    if (keycode == KEY_W || keycode == KEY_UP || keycode == KEY_D)
        data->player.walkDirection = 1;
    else if (keycode == KEY_S || keycode == KEY_DOWN || keycode == KEY_A)
        data->player.walkDirection = -1;
    else if (keycode == KEY_LEFT)
        data->player.turnDirection = -1;
    else if (keycode == KEY_RIGHT)
        data->player.turnDirection = 1;
    else if (keycode == ESC)
        close_win(data);
    else if (keycode == SPACE || keycode == 1)
        data->animate_weapon = true;
    weapon_action_keys(keycode, data);
    data->player.rotationAngle += data->player.turnDirection * data->player.rotationSpeed;
    data->player.rotationAngle = normalizeAngle(data->player.rotationAngle);
    return 0;
}

int key_r(int keycode, void *var)
{
    t_data *data;

    data = (t_data *)var;
    if (keycode == KEY_W)
        data->player.walkDirection = 0;
    else if (keycode == KEY_UP)
        data->player.walkDirection = 0;
    else if (keycode == KEY_A)
        data->player.walkDirection = 0;
    else if (keycode == KEY_S)
        data->player.walkDirection = 0;
    else if (keycode == KEY_DOWN)
        data->player.walkDirection = 0;
    else if (keycode == KEY_D)
        data->player.walkDirection = 0;
    else if (keycode == KEY_LEFT)
        data->player.turnDirection = 0;
    else if (keycode == KEY_RIGHT)
        data->player.turnDirection = 0;
    if (keycode == KEY_A || keycode == KEY_D)
        data->player.is_move_side = 0;
    return 0;
}

int mouse_hook(int x, int y, t_data *data)
{
    (void)y;
    if (data->mouse_x < x)
        data->player.turnDirection = 1;
    else if (data->mouse_x > x)
        data->player.turnDirection = -1;
    data->player.rotationAngle += data->player.turnDirection * MOVE_SPEED_MOUSE;
    data->player.rotationAngle = normalizeAngle(data->player.rotationAngle);
    data->mouse_x = x;
    // printf("turnDirection = %f\n", data->player.turnDirection);
    data->player.turnDirection = 0;
    return (0);
}

int mouse_down(int button, int x, int y, t_data *data)
{
    (void)x;
    (void)y;
    if (button == 1)
        data->animate_weapon = true;
    return (0);
}