#include <miniRT.h>


void save_pixel_data(t_img *img, int width, int height, int fd)
{
    int x, y;
    int color;

    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            color = *(int *)(img->addr + (y * img->llen + x * (img->bpp / 8)));
			            // Extract color channels
            r = (color >> 16) & 0xFF;  // Red
            g = (color >> 8) & 0xFF;   // Green
            b = (color) & 0xFF;        // Blue

            // Write RGB in correct order
            write(fd, &r, 1);
            write(fd, &g, 1);
            write(fd, &b, 1);
        }
    }
}
void save_as_ppm(t_img *img, char *filename)
{
    int fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd < 0)
        return;
    
    dprintf(fd, "P6\n%d %d\n255\n", WIDTH, HEIGHT);
    save_pixel_data(img, WIDTH, HEIGHT, fd);
    close(fd);
}

