import numpy as np

class Mandelbrot:

	def __init__(self, draw_color, surface, xmin = -2, xmax = 1, ymin = -1, ymax = 1,
				 num_x_points = 300, num_y_points = 200, limit = 2, maxiter = 16):
		self.limit = limit
		self.maxiter = maxiter
		self.xmin, self.xmax, self.ymin, self.ymax = xmin, xmax, ymin, ymax
		self.num_x_points = num_x_points
		self.num_y_points = num_y_points
		self.color = draw_color
		self.surface = surface

	def belongsToSet(self, z, maxiter):
		c = z
		z = 0
		for i in range(maxiter):
			if abs(z) > self.limit:
				return False
			z = z ** 2 + c

		return True


	def draw_fractal(self):
		x_range = np.linspace(self.xmin, self.xmax, self.num_x_points)
		y_range = np.linspace(self.ymin, self.ymax, self.num_y_points)
		for re in x_range:
			for im in y_range:
				if self.belongsToSet(complex(re, im), self.maxiter):
					x = 400 + re * 100
					y = 400 - im * 100
					self.surface.set_at((int(x), int(y)), self.color)