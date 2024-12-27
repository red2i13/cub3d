/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysahraou <ysahraou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 10:06:28 by ysahraou          #+#    #+#             */
/*   Updated: 2024/12/26 10:18:47 by ysahraou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

void intialize_data(t_data *data, char **map, void *mlx, void *mlx_win)
{
    t_img_info *minimap_img;
    t_img_info *frame;
    t_img_info *game_frame;

    data->mouse_x = 0;
    minimap_img = malloc(sizeof(t_img_info));
    frame = malloc(sizeof(t_img_info));
    game_frame = malloc(sizeof(t_img_info));
    minimap_img->img_height =  get_map_height(map) * TILE_SIZE;
    minimap_img->img_width = get_map_width(map) * TILE_SIZE;
    // printf("get map height = %li\nget map width = %li\n", get_map_height(map), get_map_width(map));
    // exit(0);
    // printf("height = %i\nwidth = %i\n", minimap_img->img_height, minimap_img->img_width);
    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
    minimap_img->img = mlx_new_image(mlx, minimap_img->img_width, minimap_img->img_height);
    minimap_img->addr = mlx_get_data_addr(minimap_img->img, &minimap_img->bits_per_pixel, &minimap_img->line_length, &minimap_img->endian);
    frame->img_height = FRAME_HEIGHT;
    frame->img_width = FRAME_WIDTH;
    frame->img = mlx_new_image(mlx, frame->img_width, frame->img_height);
    frame->addr = mlx_get_data_addr(frame->img, &frame->bits_per_pixel, &frame->line_length, &frame->endian);
    game_frame->img_height = WINDOW_HEIGHT;
    game_frame->img_width = WINDOW_WIDTH;
    game_frame->img = mlx_new_image(mlx, game_frame->img_width, game_frame->img_height);
    game_frame->addr = mlx_get_data_addr(game_frame->img, &game_frame->bits_per_pixel, &game_frame->line_length, &game_frame->endian);
    data->mlx = mlx;
    data->mlx_win = mlx_win;
    data->minimap_img = minimap_img;
    data->frame = frame;
    data->game_frame = game_frame;
    data->animate_weapon = false;
    data->weapon_numb = 0;
    data->frame_index = 0;
}


void init_weapon_names(t_data *data)
{
    data->weapon_names = malloc(sizeof(char *) * 8);
    data->weapon_names[0] = strdup("./textures/SPAR/SPAR01.xpm");
    data->weapon_names[1] = strdup("./textures/Rapr/Rapr01.xpm");
    data->weapon_names[2] = strdup("./textures/RPG7/RPG01.xpm");
    data->weapon_names[3] = strdup("./textures/Gr/Grena01.xpm");
    data->weapon_names[4] = strdup("./textures/Baton/Baton01.xpm");
    data->weapon_names[5] = strdup("./textures/SabrinMK3/3Sab01.xpm");
    data->weapon_names[6] = strdup("./textures/CA-MG/CAMG01.xpm");
    data->weapon_names[7] = NULL;
}

void init_weapons(t_data *data)
{
    int i;
    int j;
    int k;
    char *filename;

    data->all_weapons = malloc(sizeof(t_weapons) * WEAPON_N);
    data->all_weapons[0] = (t_weapons){.ammo_numb = 20, .default_ammo = 20,
        .frame_numb = 38, .index_to_change = 20, .shoting_end = 8,
        .weapon = malloc(sizeof(t_img_info *) * 38)};
    data->all_weapons[1] = (t_weapons){.ammo_numb = 2, .default_ammo = 2,
        .frame_numb = 24, .index_to_change = 20, .shoting_end = 6,
        .weapon = malloc(sizeof(t_img_info *) * 24)};
    data->all_weapons[2] = (t_weapons){.ammo_numb = 1, .default_ammo = 1,
        .frame_numb = 45, .index_to_change = 19, .shoting_end = 7,
        .weapon = malloc(sizeof(t_img_info *) * 45)};
    data->all_weapons[3] = (t_weapons){.ammo_numb = -1, .default_ammo = -1,
        .frame_numb = 17, .index_to_change = 19, .shoting_end = 17,
        .weapon = malloc(sizeof(t_img_info *) * 17)};
    data->all_weapons[4] = (t_weapons){.ammo_numb = -1, .default_ammo = -1,
        .frame_numb = 8, .index_to_change = 22, .shoting_end = 8,
        .weapon = malloc(sizeof(t_img_info *) * 8)};
    data->all_weapons[5] = (t_weapons){.ammo_numb = 25, .default_ammo = 25,
        .frame_numb = 39, .index_to_change = 25, .shoting_end = 5,
        .weapon = malloc(sizeof(t_img_info *) * 39)};
    data->all_weapons[6] = (t_weapons){.ammo_numb = 20, .default_ammo = 20,
        .frame_numb = 33, .index_to_change = 21, .shoting_end = 5,
        .weapon = malloc(sizeof(t_img_info *) * 33)};
    
    i = 0;
    while(i < WEAPON_N)
    {
        j = 0;
        k = 2;
        filename = strdup(data->weapon_names[i]);
        // printf("filename = %s\n", filename);
        while (j < data->all_weapons[i].frame_numb)
        {
            data->all_weapons[i].weapon[j] = malloc(sizeof(t_img_info));
            data->all_weapons[i].weapon[j]->img_width = WINDOW_WIDTH;
            data->all_weapons[i].weapon[j]->img_height = WINDOW_HEIGHT;
            data->all_weapons[i].weapon[j]->img = mlx_xpm_file_to_image(data->mlx, filename, &data->all_weapons[i].weapon[j]->img_width, &data->all_weapons[i].weapon[j]->img_height);
            if (data->all_weapons[i].weapon[j]->img == NULL)
                printf("error in loading weapon image: filename = %s\n", filename);
            data->all_weapons[i].weapon[j]->addr = mlx_get_data_addr(data->all_weapons[i].weapon[j]->img, &data->all_weapons[i].weapon[j]->bits_per_pixel, \
                                                                    &data->all_weapons[i].weapon[j]->line_length, &data->all_weapons[i].weapon[j]->endian);
            data->all_weapons[i].weapon[j]->filename = strdup(data->weapon_names[i]);
            if (k > 9)
            {
                k = 0;
                filename[data->all_weapons[i].index_to_change] = filename[data->all_weapons[i].index_to_change] + 1;
            }
            filename[data->all_weapons[i].index_to_change + 1] = k + 48;
            j++;
            k++;
        }
        free(filename);
        i++;
    }
}
