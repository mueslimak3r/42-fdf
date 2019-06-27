#include "../includes/fdf.h"

int				gradient(int start, int end, int steps)
{
	int rgb[3];

	if (steps == 0)
		return (end);
	if (steps < 0)
		steps = -steps;
	rgb[0] = (start & 0xFF0000) >> 16;
	rgb[0] += (rgb[0] - ((end & 0xFF0000) >> 16)) / steps;
	rgb[1] = (start & 0x00FF00) >> 8;
	rgb[1] += (rgb[1] - ((end & 0x00FF00) >> 8)) / steps;
	rgb[2] = (start & 0x0000FF);
	rgb[2] += (rgb[2] - ((end & 0x0000FF))) / steps;
	return (255 << 16) | (255 << 8) | (255);
}
