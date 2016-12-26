import pygame
from pygame import Surface
from drawline import *
import koch
import mandelbrot
import sierpinski


window_width = 1024
window_height = 768

screen_color = (255, 255, 255)
draw_color = (0, 0, 0)

window = pygame.display.set_mode((window_width, window_height))
pygame.display.set_caption('Computer graphics lab4')
screen = pygame.Surface((window_width, window_height))
screen.fill(screen_color)

koch_snowflake_points = ((200, 200), (500, 200), (350, 400))
koch_cross_points = ((100, 400), (400, 400), (250, 200), (250, 600))
sierpinski_triangle_points = ((200, 150), (100, 300), (300, 300))
sierpinski_square_points = ((100, 100), (400, 100), (400, 400), (100, 400))

#koch_snow = koch.KochSnowflake(screen, draw_color, koch_snowflake_points, 4)
#koch_snow.draw_snowflake()

mandelbrot_set = mandelbrot.Mandelbrot(draw_color, screen)
mandelbrot_set.draw_fractal()

#sierpinski_triangle = sierpinski.SierpinskiTriangle(screen, draw_color, screen_color, sierpinski_triangle_points, 4)
#sierpinski_triangle.draw()

#sierpinski_square = sierpinski.SierpinskiSquare(screen, draw_color, screen_color, sierpinski_square_points, 4)
#sierpinski_square.draw()


app_running = True
while app_running:
	for e in pygame.event.get():
		if e.type == pygame.QUIT:
			app_running = False


	window.blit(screen, (0, 0))
	pygame.display.flip()
