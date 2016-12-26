import pygame


class SierpinskiTriangle:

	def __init__(self, surface, draw_color, bckgr_color, points_list, n_iter):
		self.n = n_iter
		self.surface = surface
		self.draw_color = draw_color
		self.bckgr_color = bckgr_color
		self.points_list = points_list


	def fractal(self, points_list, n):
		if (n > 0):
			p1, p2, p3 = points_list
			x1, y1 = p1
			x2, y2 = p2
			x3, y3 = p3

			x4, x5, x6 = (x1 + x2) / 2, (x1 + x3) / 2, x1
			y4, y5, y6 = (y1 + y2) / 2, (y1 + y3) / 2, y2
			p4, p5, p6 = (x4, y4), (x5, y5), (x6, y6)
			pygame.draw.polygon(self.surface, self.bckgr_color, (p4, p5, p6), 0)
			self.fractal((p1, p4, p5), n - 1)
			self.fractal((p4, p2, p6), n - 1)
			self.fractal((p5, p6, p3), n - 1)


	def draw(self):
		pygame.draw.polygon(self.surface, self.draw_color, self.points_list, 0)
		self.fractal(self.points_list, self.n)


class SierpinskiSquare:

	def __init__(self, surface, draw_color, bckgr_color, points_list, n_iter):
		self.n = n_iter
		self.surface = surface
		self.draw_color = draw_color
		self.bckgr_color = bckgr_color
		self.points_list = points_list

	def fractal(self, points_list, n):
		if (n > 0):
			p1, p2, p3, p4 = points_list
			x1, y1 = p1
			x2, y2 = p2
			x3, y3 = p3
			x4, y4 = p4

			p5, p6 = ((2 * x1 + x2) / 3, y1), ((2 * x2 + x1) / 3, y1)
			p7, p8 = ((2 * x4 + x3) / 3, y3), ((2 * x3 + x4) / 3, y3)
			x_delta, y_delta = (x2 - x1) / 3, (y3 - y1) / 3
			p9, p10, p11, p12 = (x1, y1 + y_delta), (x1 + x_delta, y1 + y_delta), (x1 + 2 * x_delta, y1 + y_delta), (x2, y2 + y_delta)
			p13, p14, p15, p16 = (x1, y1 + 2 * y_delta), (x1 + x_delta, y1 + 2 * y_delta), (x1 + 2 * x_delta, y1 + 2 * y_delta), (x2, y2 + 2 * y_delta)

			pygame.draw.polygon(self.surface, self.bckgr_color, (p10, p11, p15, p14), 0)
			self.fractal((p1, p5, p10, p9), n - 1)
			self.fractal((p5, p6, p11, p10), n - 1)
			self.fractal((p6, p2, p10, p9), n - 1)
			self.fractal((p9, p10, p14, p13), n - 1)
			self.fractal((p11, p12, p16, p15), n - 1)
			self.fractal((p13, p14, p7, p4), n - 1)
			self.fractal((p14, p15, p8, p7), n - 1)
			self.fractal((p15, p16, p3, p8), n - 1)


	def draw(self):
		pygame.draw.polygon(self.surface, self.draw_color, self.points_list, 0)
		self.fractal(self.points_list, self.n)