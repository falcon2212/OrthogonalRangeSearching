import pygame
import os
os.environ['PYGAME_HIDE_SUPPORT_PROMPT'] = "hide"
pygame.init()
pygame.display.init()
width = 800
height = 600
screen = pygame.display.set_mode((width, height))
pygame.mouse.set_visible(True)
run_program = True
pygame.display.set_caption("Output")
points = []
green = (0,255,0)
blue = (0,0,255)
white = (255,255,255)
red = (255,0,0)
yellow = (255,255,0)
peach = (255,218,185)
black = (0,0,0)
purple = (178,102,255)
dark = (127,0,255)
def draw_rect( x , y, w, h, msg, angle):
    mouse = pygame.mouse.get_pos()
    if not(( x+w > mouse[0] > x) and (y+h > mouse[1] > y)):
        pygame.draw.rect(screen, yellow, (x,y,w,h))
    def text_objects(text, color):
        textSurface = smallText.render(text, True, black)
        return textSurface, textSurface.get_rect()

    smallText = pygame.font.Font("freesansbold.ttf",15)
    textSurf, textRect =text_objects(msg, smallText)
    textRect.center = ( (x+(w/2)), (y+(h/2)) )
    textSurf = pygame.transform.rotate(textSurf,angle)
    screen.blit(textSurf, textRect)
POINTS = True
QUERY = 0
queries = []
n = input()
for i in range(n):
	p= [int(i) for i in raw_input().split(" ")]
	points.append(p)
m = input()
for i in range(m):
	q = [int(i) for i in raw_input().split(" ")]
	queries.append([(q[0], q[1]),(q[2],q[3])]) 	
while run_program:
	screen.fill((255,255,255))
	for i in points:
		point = (i[0], i[1])
		clr = (0,0,255)
		if(i[2] == 1):
			clr = (0, 255, 0)
		pygame.draw.circle(screen, clr, point, 3)
	for i in queries:
		bottom = i[0]
		point = i[1]
		left = bottom[0]
		W = point[0]-bottom[0]
		H = point[1]-bottom[1]
		top = bottom[1]
		pygame.draw.rect(screen, green, [left, top, W, H], 1)
	pygame.display.update()
	for event in pygame.event.get():
		if event.type == pygame.QUIT:
			run_program = False
