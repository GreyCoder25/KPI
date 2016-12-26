import pygame
from pygame import Surface

pixel_size = 5

def draw_pixel(surface, x, y, color):

	for x_coord in range(x, x + pixel_size):
		for y_coord in range(y, y + pixel_size):
			surface.set_at((x_coord, y_coord), color)


def DDA_line(surface, x0, y0, x1, y1, color):

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


def Bresenham_circle(surface, x0, y0, R, color):

	x = 0
	y = R
	error = 1 - R
	while x <= y:
		draw_pixel(surface, pixel_size * (x0 + x), pixel_size * (y0 + y), color)		
		draw_pixel(surface, pixel_size * (x0 + x), pixel_size * (y0 - y), color)
		draw_pixel(surface, pixel_size * (x0 - x), pixel_size * (y0 + y), color)
		draw_pixel(surface, pixel_size * (x0 - x), pixel_size * (y0 - y), color)
		draw_pixel(surface, pixel_size * (x0 + y), pixel_size * (y0 + x), color)
		draw_pixel(surface, pixel_size * (x0 + y), pixel_size * (y0 - x), color)
		draw_pixel(surface, pixel_size * (x0 - y), pixel_size * (y0 + x), color)
		draw_pixel(surface, pixel_size * (x0 - y), pixel_size * (y0 - x), color)

		if error > 0:
			y -= 1
			error += 2 * (x - y) + 5
		else:	
			error += 2 * x + 3
		x += 1
	

def Wu_line(surface, x0, y0, x1, y1, color):

	if x0 == x1:
		for y in range(min(y0, y1), max(y0, y1)):
			draw_pixel(surface, pixel_size * x0, pixel_size * y, color)
		return

	if y0 == y1:
		for x in range(min(x0, x1), max(x0, x1)):
			draw_pixel(surface, pixel_size * x, pixel_size * y0, color)
		return

	x = y = 0
	if x0 > x1:
		x0, x1 = x1, x0
		y0, y1 = y1, y0

	x_diff, y_diff = x1 - x0, y1 - y0

	if (abs(x_diff) >= abs(y_diff)):
		grad = y_diff / float(x_diff)

		draw_pixel(surface, pixel_size * x0, pixel_size * y0, color)
		y = y0 + grad
		for x in range (x0 + 1, x1):
			k = y - int(y)
			draw_pixel(surface, pixel_size * x, pixel_size * int(y), (color[0], int(255 * k), int(255 * k)))
			draw_pixel(surface, pixel_size * x, pixel_size * (int(y) + 1), (color[0], int(255 * (1 - k)), int(255 * (1 - k))))
			y += grad
		draw_pixel(surface, pixel_size * x1, pixel_size * y1, color)
	else:
		if (y0 > y1):
			y0, y1 = y1, y0
			x0, x1 = x1, x0

		grad = x_diff / float(y_diff)

		draw_pixel(surface, pixel_size * x0, pixel_size * y0, color)
		x = x0 + grad
		for y in range (y0 + 1, y1):
			k = x - int(x)
			draw_pixel(surface, pixel_size * int(x), pixel_size * y, (color[0], int(255 * k), int(255 * k)))
			draw_pixel(surface, pixel_size * (int(x) + 1), pixel_size * y, (color[0], int(255 * (1 - k)), int(255 * (1 - k))))
			x += grad
		draw_pixel(surface, pixel_size * x1, pixel_size * y1, color)


def name_draw(surface, color):
	''' letter "S" '''
	Bresenham_line(surface, 50, 100, 45, 100, color)
	Bresenham_line(surface, 45, 100, 45, 105, color)
	Bresenham_line(surface, 45, 105, 50, 105, color)
	Bresenham_line(surface, 50, 105, 50, 110, color)
	Bresenham_line(surface, 50, 110, 45, 110, color)

	''' letter "E" '''
	Bresenham_line(surface, 52, 100, 52, 110, color)
	Bresenham_line(surface, 52, 100, 57, 100, color)
	Bresenham_line(surface, 52, 105, 57, 105, color)
	Bresenham_line(surface, 52, 110, 57, 110, color)

	''' letter "R" '''
	Bresenham_line(surface, 59, 100, 59, 110, color)
	Bresenham_line(surface, 59, 100, 64, 100, color)
	Bresenham_line(surface, 64, 100, 64, 105, color)
	Bresenham_line(surface, 64, 105, 59, 105, color)
	Bresenham_line(surface, 59, 105, 64, 110, color)

	''' letter "H" '''
	Bresenham_line(surface, 66, 100, 66, 110, color)
	Bresenham_line(surface, 71, 100, 71, 110, color)
	Bresenham_line(surface, 66, 105, 71, 105, color)

	''' letter "I" '''
	Bresenham_line(surface, 73, 100, 73, 110, color)

	''' letter I '''
	Bresenham_line(surface, 75, 100, 75, 110, color)



'''----------------------------- Main programm ------------------------------------------------------'''

window_width = 1024
window_height = 768

screen_color = (255, 255, 255)
draw_color = (255, 0, 0)

DDA_x0, DDA_y0, DDA_x1, DDA_y1 = 0, 0, 50, 20
B_x0, B_y0, B_x1, B_y1 = 20, 0, 70, 20
B_Cx, B_Cy, B_R = 30, 50, 20
wu_x0, wu_y0, wu_x1, wu_y1 = 40, 0, 90, 20

window = pygame.display.set_mode((window_width, window_height))
pygame.display.set_caption('Computer graphics lab1')
screen = pygame.Surface((window_width, window_height))
screen.fill(screen_color)

app_running = True
while app_running:
	for e in pygame.event.get():
		if e.type == pygame.QUIT:
			app_running = False


	window.blit(screen, (0, 0))

	DDA_line(screen, DDA_x0, DDA_y0, DDA_x1, DDA_y1, draw_color)
	Bresenham_line(screen, B_x0, B_y0, B_x1, B_y1, draw_color)
	Bresenham_circle(screen, B_Cx, B_Cy, B_R, draw_color)
	Wu_line(screen, wu_x0, wu_y0, wu_x1, wu_y1, draw_color)
	name_draw(screen, draw_color)

	pygame.display.flip()


