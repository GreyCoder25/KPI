import pygame

device_ON = False

# global objects parameters
window_width = 1024
window_height = 768

elem_width = 200
elem_height = 300

button_width = 50
button_height = 50

elem_colour = (200, 200, 200)
font_colour = (0, 0, 0)
screen_colour = (255, 255, 255)
buttonup_colour = (150, 150, 150)
indicator_on_colour = (0, 255, 0)
indicator_off_colour = (255, 0, 0)
buttondown_colour = (100, 100, 100)
line_colour = (0, 0, 0)
line_on_colour = (0, 255, 0)

elem_name_coords = (70, 120)

# creating graphic window and game screen
window = pygame.display.set_mode((window_width, window_height))
pygame.display.set_caption('Microprocessor control system')
screen = pygame.Surface((window_width, window_height))
screen.fill(screen_colour)

# creating fonts
pygame.font.init()
elem_font = pygame.font.SysFont('Arial', 32)
button_font = pygame.font.SysFont('Arial', 14)

# local objects parameters
CPU_coords = (60, 200)
DLU_coords = (470, 200)
OBJ_coords = (750, 200)
obj_start_button_coords = (30, 170)
obj_stop_button_coords = (120, 170)
indicator_coords = (100, 100)
indicator_size = 20
indicator_width = 0

# creating onjects
CPU_elem = pygame.Surface((elem_width, elem_height))
CPU_elem.fill(elem_colour)
CPU_elem.blit(elem_font.render('CPU', 1, font_colour), elem_name_coords)

DLU_elem = pygame.Surface((elem_width, elem_height))
DLU_elem.fill(elem_colour)
DLU_elem.blit(elem_font.render('DLU', 1, font_colour), elem_name_coords)

OBJ_elem = pygame.Surface((elem_width, elem_height))
OBJ_elem.fill(elem_colour)
OBJ_elem.blit(elem_font.render('OBJ', 1, font_colour), (70, 20))

screen.blit(pygame.image.load('buses.png'), (CPU_coords[0] + elem_width, CPU_coords[1] + 50))

# creating indicator
indicator_colour = indicator_off_colour
#pygame.draw.circle(OBJ_elem, indicator_colour, indicator_coords, indicator_size, indicator_width)

# creating OBJ buttons
button_start_colour = buttonup_colour
button_stop_colour = buttonup_colour

obj_start_button = pygame.Surface((button_width, button_height))
obj_start_button.fill(button_start_colour)
obj_start_button.blit(button_font.render('Start', 1, font_colour), (5, 10))

obj_stop_button = pygame.Surface((button_width, button_height))
obj_stop_button.fill(button_stop_colour)
obj_stop_button.blit(button_font.render('Stop', 1, font_colour), (5, 10))


arrow_ready_colour = line_colour
arrow_control_colour = line_colour
arrow_width = 3

def check_start_click():
	cursor_x, cursor_y = pygame.mouse.get_pos()
	button_x, button_y = OBJ_coords[0] + obj_start_button_coords[0], OBJ_coords[1] + obj_start_button_coords[1]

	if (cursor_x - button_x >= 0 and cursor_x - button_x <= button_width
			and cursor_y - button_y >= 0 and cursor_y - button_y <= button_height):
		return True

def check_stop_click():
	cursor_x, cursor_y = pygame.mouse.get_pos()
	button_x, button_y = OBJ_coords[0] + obj_stop_button_coords[0], OBJ_coords[1] + obj_stop_button_coords[1]

	if (cursor_x - button_x >= 0 and cursor_x - button_x <= button_width
			and cursor_y - button_y >= 0 and cursor_y - button_y <= button_height):
		return True

def line_blink(colour):
	if colour == line_colour:
		return line_on_colour
	return line_colour

class HorizontalArrow:

	def __init__(self, surface, colour, start_pos, end_pos, width, direction):
		self.surface = surface
		self.colour = colour
		self.start_pos = start_pos
		self.end_pos = end_pos
		self.width = width
		self.direction = direction

	def draw(self):
		pygame.draw.line(self.surface, self.colour, self.start_pos, self.end_pos, self.width)

		if self.direction == 'left':
			p1 = self.start_pos
			p2 = (p1[0] + 5, p1[1] - 5)
			p3 = (p1[0] + 5, p1[1] + 5)
		elif self.direction == 'right':
			p1 = self.end_pos
			p2 = (p1[0] - 5, p1[1] - 5)
			p3 = (p1[0] - 5, p1[1] + 5)

		pygame.draw.line(self.surface, self.colour, p1, p2, self.width)
		pygame.draw.line(self.surface, self.colour, p1, p3, self.width)


class Indicator:

	def __init__(self, surface, coords, size):
		self.surface = surface
		self.on_colour = (0, 255, 0)
		self.off_colour = (255, 0, 0)
		self.coords = coords
		self.size = size
		self.draw_colour = self.off_colour

	def draw(self, device_on):
		if device_on:
			pygame.draw.circle(self.surface, self.draw_colour, self.coords, self.size, 0)
		else:
			pygame.draw.circle(self.surface, self.off_colour, self.coords, self.size, 0)

	def blink(self):
		if self.draw_colour == self.off_colour:
			self.draw_colour = self.on_colour
		else:
			self.draw_colour = self.off_colour

