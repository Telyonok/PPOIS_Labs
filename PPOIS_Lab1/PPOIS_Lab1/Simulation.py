from tkinter import EXCEPTION
from Field import Field
from Stats import Stats
from Coordinates import Coordinates
from Gazelle import Gazelle
from Status import Status
from View import View
from GameState import GameState
import msvcrt
import time

class Simulation:
    def start():
        field = Field()
        try:
            while True:
                if msvcrt.kbhit():
                    key = msvcrt.getch()
                    if key == b'q':
                        break
                    elif key == b'g':
                        field.spawnAnimalAnywhere("Gazelle")
                    elif key == b't':
                        field.spawnAnimalAnywhere("Tiger")
                    elif key == b's':
                        input("Simulation is paused. Press enter to resume...")
            
                for i in range(0, field.height, 1):
                    for j in range(0, field.width, 1):
                        field.tiles[i][j].trySpawnCycle(field)

                for i in GameState.getAnimalList():
                    i.act(field)
                    i.tookTurn = False
                    i.mateCooldown -= 1
                    i.takeDamage(1, field)

                View.draw(field)
                time.sleep(1)
        except Exception as e:
            View.clear()
            print("Something gone wrong. Simulation will continue in 5 seconds.")
            time.sleep(5)



