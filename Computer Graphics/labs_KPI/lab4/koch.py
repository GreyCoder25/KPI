from drawline import *
from pygame import draw

class KochSnowflake:

	def __init__(self, surface, color, points, n):
		self.surface = surface
		self.color = color
		self.p1, self.p2, self.p3 = points
		self.n = n

	def draw_triangle(self):
		DDA_line(self.surface, self.p1, self.p2, self.color)
		DDA_line(self.surface, self.p1, self.p3, self.color)
		DDA_line(self.surface, self.p3, self.p2, self.color)

	def fractal(self, p1, p2, p3, n):
		if (n > 0):
			x1, y1 = p1
			x2, y2 = p2
			x3, y3 = p3

			x4, y4 = (2 * x1 + x2) / 3, (2 * y1 + y2) / 3
			x5, y5 = (2 * x2 + x1) / 3, (2 * y2 + y1) / 3

			xc, yc = (x1 + x2) / 2, (y1 + y2) / 2
			x6, y6 = (4 * xc - x3) / 3, (4 * yc - y3) / 3

			p4, p5, p6 = (x4, y4), (x5, y5), (x6, y6)
			DDA_line(self.surface, p4, p6, self.color)
			DDA_line(self.surface, p6, p5, self.color)

			pt = (2 * x1 + x3) / 3, (2 * y1 + y3) / 3
			self.fractal(p1, p4, pt, n - 1)
			pt = (2 * x2 + x3) / 3, (2 * y2 + y3) / 3
			self.fractal(p5, p2, pt, n - 1)
			self.fractal(p4, p6, p5, n - 1)
			self.fractal(p6, p5, p4, n - 1)


	def draw_snowflake(self):
		self.draw_triangle()
		self.fractal(self.p1, self.p2, self.p3, self.n)
		self.fractal(self.p2, self.p3, self.p1, self.n)
		self.fractal(self.p1, self.p3, self.p2, self.n)


class KochCross:

	def __init__(self, surface, color, points, n, width):
		self.surface = surface
		self.color = color
		self.p1, self.p2, self.p3, self.p4 = points
		self.n = n
		self.width = width

	def fractal(self, p1, p2, p3, p4, width, n):
		if (n > 0):
			x1, y1, x2, y2, x3, y3, x4, y4 = p1, p2, p3, p4
			draw.line(self.surface, self.color, ((x1 + x2) / 2 - width / 4, ))
			self.fractal()


		
	def draw(self):
		draw.line(self.surface, self.color, self.p1, self.p2, self.width)
		draw.line(self.surface, self.color, self.p3, self.p4, self.width)
		self.fractal(self.p3, self.p1, self.p2, self.p4, self.width / 2, self.n)
		self.fractal(self.p2, self.p3, self.p4, self.p1, self.width / 2, self.n)
		self.fractal(self.p1, self.p4, self.p3, self.p2, self.width / 2, self.n)
		self.fractal(self.p4, self.p2, self.p1, self.p3, self.width / 2, self.n)

	

