import random
import copy
import helper
from itertools import permutations 
import pygame
import math

class Train:
    def __init__(self, x, y, dx, dy, size, trainLen):
        self.x = x
        self.y = y
        self.dx = dx
        self.dy = dy
        self.size = size
        self.stopped = False
        self.trainLen = trainLen

    def __str__(self):
        return f"({self.x}, {self.y}), ({self.dx}, {self.dy})"
    
    def tick(self):
        if not self.stopped:
            self.x = (self.x + self.dx) % self.size
            self.y = (self.y + self.dy) % self.size

    def getBack(self):
        r = math.sqrt(math.pow(self.dx, 2) + math.pow(self.dy, 2)) / self.trainLen
        return ((-self.dx / r) + self.x, (-self.dy / r) + self.y)

    def stop(self):
        self.stopped = True
    
    def go(self):
        self.stopped = False

class Field:
    def __init__(self, numTrains, size, trainLen):
        def getRandomD():
            return random.random() * trainLen - trainLen  / 2

        def generateTrain():
            return Train(random.random() * size, random.random() * size, getRandomD(), getRandomD(), size, trainLen)

        self.numTrains  = numTrains
        self.trains = []
        
        for i in range(numTrains):
            self.trains.append(generateTrain()) 

    def __str__(self):
        string = ""
        for (i, train) in enumerate(self.trains):
            string = string  + f"Train {i}:"+ train.__str__() + "\n"
        return string

    def tickTest(self):
        for train in self.trains:
            train.tick()

    def tick(self):
        for train in self.trains:
            self.startAllTrains()
            self.avoid(3)
            train.tick()
    
    def startAllTrains(self):
        for train in self.trains:
            train.go()

    def simulate(self, ticks):
        simulation = copy.deepcopy(self)
        for tick in range(ticks):
            simulation.tickTest()
        return simulation.hasCollision()

    def avoid(self, ahead=1):
        for i in range(1, ahead + 1):
            sim = self.simulate(i)
            if sim != False:
                if self.trains[sim[0]].stopped:
                    self.trains[sim[1]].stop()
                else:
                    self.trains[sim[0]].stop()
                print(f"Collision Avoided between {sim[0]} and {sim[1]}")
                self.avoid(ahead)

    def hasCollision(self):
        def collision2Train(train1, train2):
            train1back = train1.getBack()
            train2back = train2.getBack()

            return helper.intersect(train1.x, train1.y, train1back[0], train1back[1], train2.x, train2.y, train2back[0], train2back[1])

        for i in range(len(self.trains)):
            for j in range(i + 1, len(self.trains)):
                couple = (self.trains[i], self.trains[j])
                if collision2Train(couple[0], couple[1]):
                    print(f"{i}, {j}")
                    return (i, j)

        return False     
    
    def drawScreen(self, screen):
        screen.fill((0, 0, 0))
        for train in self.trains:
            back = train.getBack()
            back = (back[0] * 100, back[1] * 100)
            pygame.draw.line(screen, (255, 255, 255), (train.x * 100, train.y * 100), back, 1)



if __name__ == "__main__":
    size = 10
    trainCount = 10
    trainlen = 1
    field = Field(size, trainCount, trainlen)
    if field.hasCollision() != False:
        field = Field(size, trainCount, trainlen)
    pygame.init()

    pygame.display.set_caption("trains")

    screen = pygame.display.set_mode((size * 100, size * 100))

    running = True
    
    while(field.hasCollision() == False and running):
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                # change the value to False, to exit the main loop
                running = False

            if event.type == pygame.KEYDOWN:
                paused = True
                while(paused):
                    for event in pygame.event.get():
                        if event.type == pygame.QUIT:
                            # change the value to False, to exit the main loop
                            running = False
                            paused = False

                        if event.type == pygame.KEYDOWN:
                            paused = False

        field.tick()
        field.drawScreen(screen)
        pygame.display.flip()
        pygame.time.wait(100)

    field.drawScreen(screen)
    pygame.display.flip()

    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                # change the value to False, to exit the main loop
                running = False