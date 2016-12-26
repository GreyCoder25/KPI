import pygame
from pygame import Surface
from drawline import *

def draw_polygon(surface, x_list, y_list, color):
	for i in range(len(x_list) - 1):
		DDA_line(surface, x_list[i], y_list[i], x_list[i + 1], y_list[i + 1], color)


def flood_fill(surface, inter_x, inter_y, border_color, fill_color, bckgr_color):
	stack = []
	stack.append((inter_x, inter_y))
	while stack != []:
		(x, y) = stack.pop()
		surface.set_at((x, y), fill_color)
		if (surface.get_at((x + 1, y))[:-1]) not in set((border_color, fill_color)):
			stack.append((x + 1, y))
		if (surface.get_at((x - 1, y))[:-1]) not in set((border_color, fill_color)):
			stack.append((x - 1, y))
		if (surface.get_at((x, y + 1))[:-1]) not in set((border_color, fill_color)):
			stack.append((x, y + 1))
		if (surface.get_at((x, y - 1))[:-1]) not in set((border_color, fill_color)):
			stack.append((x, y - 1))


def list_of_edge_points_fill(surface, x_coords, y_coords, border_color, fill_color):
	y_dict = {}
	y_min, y_max = min(y_coords), max(y_coords)
	x_min, x_max = min(x_coords), max(x_coords)
	for y in range(y_min + 1, y_max):
		x_list = []
		for x in range(x_min, x_max + 1):
			if (surface.get_at((x, y))[:-1] == border_color and surface.get_at((x + 1, y))[:-1] != border_color):
					x_list.append(x)
		y_dict[y] = x_list[:]

	for key in y_dict:
		for i in range(0, len(y_dict[key]) - 1, 2):
			DDA_line(surface, y_dict[key][i] + 1, key, y_dict[key][i + 1] - 1, key, fill_color)


def xor_fill(surface, x_coords, y_coords, fill_color, bckgr_color):
	y_min, y_max = min(y_coords), max(y_coords)
	x_min, x_max = min(x_coords), max(x_coords)

	for y in range(y_min + 1, y_max):
		for x in range(x_min, x_max):
			if (surface.get_at((x, y))[:-1] == surface.get_at((x + 1, y))[:-1]):
				surface.set_at((x + 1, y), bckgr_color)
			else:
				surface.set_at((x + 1, y), fill_color)



window_width = 1024
window_height = 768

screen_color = (255, 255, 255)
draw_color = (0, 255, 0)
fill_color = (0, 255, 0)

polygon_x1 = (60, 120, 200, 260, 200, 120, 60)
polygon_x2 = (360, 420, 500, 560, 500, 420, 360)
polygon_x3 = (660, 720, 800, 860, 800, 720, 660)
polygon_y = (150, 40, 40, 150, 210, 210, 150)


window = pygame.display.set_mode((window_width, window_height))
pygame.display.set_caption('Computer graphics lab3')
screen = pygame.Surface((window_width, window_height))
screen.fill(screen_color)

draw_polygon(screen, polygon_x1, polygon_y, draw_color)
draw_polygon(screen, polygon_x2, polygon_y, draw_color)
draw_polygon(screen, polygon_x3, polygon_y, draw_color)
flood_fill(screen, 70, 150, draw_color, fill_color, screen_color)
list_of_edge_points_fill(screen, polygon_x2, polygon_y, draw_color, fill_color)
xor_fill(screen, polygon_x3, polygon_y, fill_color, screen_color)

app_running = True
while app_running:
	for e in pygame.event.get():
		if e.type == pygame.QUIT:
			app_running = False


	window.blit(screen, (0, 0))
	pygame.display.flip()
