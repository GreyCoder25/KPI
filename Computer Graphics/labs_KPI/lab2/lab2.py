import pygame
from pygame import gfxdraw
import math

window_width = 1024
window_height = 600

screen_color = (255, 255, 255)
draw_color = (255, 0, 0)
window = pygame.display.set_mode((window_width, window_height))
pygame.display.set_caption('Computer graphics lab2')
screen = pygame.Surface((window_width, window_height))
screen.fill(screen_color)


point1 = [100, 100]
point2 = [200, 300]
point3 = [300, 100]
#point4 = [500, 500]

points = [point1, point2, point3]

t_step = 0.001
n = 3


def bezier_curve_calc(n, t_step, points):
	x = [points[i][0] for i in range(n)]
	y = [points[i][1] for i in range(n)]

	coefs = [1, 1]
	for i in range(n - 2):
		new_coefs = []
		new_coefs.append(coefs[0])
		for j in range(len(coefs) - 1):
			new_coefs.append(coefs[j] + coefs[j + 1])
		new_coefs.append(coefs[-1])
		coefs = new_coefs

	t = 0.0
	x_coords = []
	y_coords = []
	while t <= 1:
		curr_x = curr_y =  0
		for i in range(n):
			curr_x += (t ** i) * ((1 - t) ** (n - 1 - i)) * coefs[i] * x[i]
			curr_y += (t ** i) * ((1 - t) ** (n - 1 - i)) * coefs[i] * y[i]

		x_coords.append(curr_x)
		y_coords.append(curr_y)		
		t += t_step

	return x_coords, y_coords


def bezier_curve_draw(surface, x_coords, y_coords, color):
	for x, y in zip(x_coords, y_coords):
		gfxdraw.pixel(surface, int(x), window_height -  int(y), color)


def transfer(x, y, dx, dy):
	for i in range(len(x)):
		x[i] += dx
		y[i] += dy


def rotate(x, y, degrees):
	degrees *= math.pi / 180.0

	for i in range(len(x)):
		x[i] = x[i] * math.cos(degrees) - y[i] * math.sin(degrees)
		y[i] = x[i] * math.sin(degrees) + y[i] * math.cos(degrees)


def scale(points, coef):
	for i in range(1, len(points)):
		points[i][0] += (coef - 1) * (points[i][0] - points[0][0])
		points[i][1] += (coef - 1) * (points[i][1] - points[0][1])



scale(points, 2)
x, y = bezier_curve_calc(n, t_step, points)
transfer(x, y, 300, 80)
rotate(x, y, 15)


app_running = True
while app_running:
	for e in pygame.event.get():
		if e.type == pygame.QUIT:
			app_running = False

	window.blit(screen, (0, 0))

	bezier_curve_draw(screen, x, y, draw_color)

	pygame.display.flip()