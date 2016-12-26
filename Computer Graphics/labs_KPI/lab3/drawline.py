from pygame import Surface

pixel_size = 1

def draw_pixel(surface, x, y, color):

	for x_coord in range(x, x + pixel_size):
		for y_coord in range(y, y + pixel_size):
			surface.set_at((x_coord, y_coord), color)

def DDA_line(surface, point1, point2, color):
	x0, x1 = point1[0], point2[0]
	y0, y1 = point1[1], point2[1]

	x_diff, y_diff = x1 - x0, y1 - y0
	L = max(abs(x1 - x0), abs(y1 - y0))
	dx, dy = x_diff / float(L), y_diff / float(L)

	x, y = x0, y0
	for i in range(L + 1):
		draw_pixel(surface, pixel_size * int(round(x)), pixel_size * int(round(y)), color)
		x += dx
		y += dy

def Bresenham_line(surface, x0, y0, x1, y1, color):

	dy = dx = 1
	if x0 > x1:
		x0, x1 = x1, x0
		y0, y1 = y1, y0
	if y0 > y1:
		dy = -1

	x_diff, y_diff = abs(x1 - x0), abs(y1 - y0)

	if x_diff >= y_diff:

		error = 0
		delta_err = y_diff

		y = y0
		for x in range (x0, x1 + 1):
			draw_pixel(surface, pixel_size * x, pixel_size * y, color)
			error += delta_err
			if (2 * error >= x_diff):
				y += dy
				error -= x_diff
	else:
		if x0 > x1:
			dx = -1

		error = 0
		delta_err = x_diff

		x = x0
		for y in range (y0, y1 + 1, dy):
			draw_pixel(surface, pixel_size * x, pixel_size * y, color)
			error += delta_err
			if (2 * error >= y_diff):
				x += dx
				error -= y_diff
