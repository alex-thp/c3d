#include "cub3d.h"

int     appuyer(int keycode, int ptr)
{
    ptr++;
    write (1, "lol\n", 4);
    printf("\n%d\n", keycode);
    return (0);
}

int     fermer(t_map *ptr)
{
    mlx_destroy_window(ptr->mlx.ptr, ptr->mlx.win);
    exit(0);
}

int			close_win(t_map *scene)

{

	mlx_destroy_window(scene->mlx.ptr, scene->mlx.win);

	//ft_free(scene);

	exit(0);

}

int     main(void)
{
    t_map   *tab;
    static int     i = 0;

    if (!(tab = (t_map*)malloc(sizeof(t_map))))
        return (-1);

    if (i == 0)
    {
        i += 1;
        tab->first_round = 1;
        tab->mlx.ptr = mlx_init();
        tab->mlx.win = mlx_new_window(tab->mlx.ptr, 1000, 800, "Cub3d");
        tab->mlx.img = mlx_new_image(tab->mlx.ptr, 1000, 800);
        tab->mlx.var = (int*)mlx_get_data_addr(tab->mlx.img, &i, &i, &i);
    }
    mlx_key_hook(tab->mlx.win, appuyer, 0);
    mlx_hook(tab->mlx.win, 17, 0, fermer, 0);
    mlx_hook(tab->mlx.win, 17, 0, close_win, tab);
    mlx_loop(tab->mlx.ptr);
}