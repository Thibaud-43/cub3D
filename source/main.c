#include "cub3D.h"

int		main(void)
{
	void	*mlx;
	void	*win;

	mlx = mlx_init();
	win = mlx_new_window(mlx, 700, 800, "mlx_project");
	mlx_loop(mlx);
}
