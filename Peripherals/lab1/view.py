from model import *
import pygame

ready_arrow_start_point = (DLU_coords[0] + elem_width, DLU_coords[1] + 50)
ready_arrow_end_point = (OBJ_coords[0], DLU_coords[1] + 50)

control_arrow_start_point = (DLU_coords[0] + elem_width, DLU_coords[1] + 150)
control_arrow_end_point = (OBJ_coords[0], DLU_coords[1] + 150)

indicator = Indicator(OBJ_elem, indicator_coords, indicator_size)

app_running = True
while app_running:
 	for e in pygame.event.get():
		if e.type == pygame.QUIT:
 			app_running = False
		if e.type == pygame.MOUSEBUTTONDOWN:
			if e.button == 1:
				if not device_ON and check_start_click():
					button_start_colour = buttondown_colour
					button_stop_colour = buttonup_colour
					arrow_ready_colour = line_on_colour
					device_ON = True
				elif device_ON and check_stop_click():
					button_start_colour = buttonup_colour
					button_stop_colour = buttondown_colour
					arrow_ready_colour = line_colour
					arrow_control_colour = line_colour
					device_ON = False

 	window.blit(screen, (0, 0))
	
 	screen.blit(CPU_elem, CPU_coords)
 	screen.blit(DLU_elem, DLU_coords)
 	screen.blit(OBJ_elem, OBJ_coords)
 	

 	OBJ_elem.blit(obj_start_button, obj_start_button_coords)
 	OBJ_elem.blit(obj_stop_button, obj_stop_button_coords)
 	obj_start_button.fill(button_start_colour)
 	obj_stop_button.fill(button_stop_colour)
 	obj_start_button.blit(button_font.render('Start', 1, font_colour), (5, 10))
 	obj_stop_button.blit(button_font.render('Stop', 1, font_colour), (5, 10))

	ready_arrow = HorizontalArrow(screen, arrow_ready_colour,
							  	  ready_arrow_start_point, ready_arrow_end_point, arrow_width, direction = 'left')
	control_arrow = HorizontalArrow(screen, arrow_control_colour,
									control_arrow_start_point, control_arrow_end_point, arrow_width, direction = 'right')

	indicator.draw(device_ON)	
	ready_arrow.draw()
	control_arrow.draw()
	
 	screen.blit(button_font.render('Readyness', 1, font_colour), (DLU_coords[0] + elem_width, DLU_coords[1] + 30))
 	screen.blit(button_font.render('Control', 1, font_colour), (DLU_coords[0] + elem_width, DLU_coords[1] + 130))

 	if device_ON == True:
 		indicator.blink()
 		arrow_control_colour = line_blink(arrow_control_colour)

 	pygame.time.delay(100)

 	pygame.display.flip()

