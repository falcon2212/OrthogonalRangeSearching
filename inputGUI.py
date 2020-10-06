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
pygame.display.set_caption("Input taker")
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
tmpQueries = []
bottomQ = (-1, -1)
while run_program:
	screen.fill((255,255,255))
	draw_rect(width/6,height/50,100,30,"Add Points",0 )
	draw_rect(width/2,height/50,200,30,"Add Query Rectangles",0 )

	for i in points:
		pygame.draw.circle(screen, (0,0,255),i, 3)
	for i in queries:
		bottom = i[0]
		point = i[1]
		left = bottom[0]
		W = point[0]-bottom[0]
		H = point[1]-bottom[1]
		top = bottom[1]
		pygame.draw.rect(screen, green, [left, top, W, H], 1)
	if(QUERY == 2):
		# print(bottomQ)
		point = pygame.mouse.get_pos()
		left = bottomQ[0]
		W = point[0]-bottomQ[0]
		H = point[1]-bottomQ[1]
		top = bottomQ[1]
		pygame.draw.rect(screen, red, [left, top, W, H], 1)

	pygame.display.update()
	x = width/6
	y = height/50
	w = 100
	h = 30
	xq = width/2
	yq = height/50
	wq = 100
	hq = 30
	for event in pygame.event.get():
		if event.type == pygame.QUIT:
			run_program = False
		if(pygame.key.get_pressed()[pygame.K_q]):
			run_program = False
		elif(pygame.mouse.get_pressed()[0]):
			point = pygame.mouse.get_pos()
			if(point[1] > height/50+50):
				if(POINTS):
					points.append(point)
				elif(QUERY == 2):
					# print("HERE")
					queries.append([bottomQ, point])
					QUERY = 1
					bottomQ = (0,0)
				elif(QUERY == 1):
					bottomQ = point
					QUERY = 2	
			elif(point[0]>=x and point[0] <= x+w and point[1]>=y and point[1]<=y+h):
				POINTS = True
				QUERY = 0
			elif(point[0]>=xq and point[0] <= xq+wq and point[1]>=yq and point[1]<=yq+hq):	
				QUERY = 1
				POINTS = False
				bottomQ =(0,0)
			pass
print len(points)			
for i in points:
	print i[0],i[1]
print len(queries)
for i in queries:
	print min(i[0][0], i[1][0]), min(i[0][1], i[1][1]), max(i[0][0], i[1][0]), max(i[0][1], i[1][1])				