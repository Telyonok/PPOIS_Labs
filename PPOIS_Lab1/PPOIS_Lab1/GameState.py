from typing import List
from Animal import Animal

class GameState:
    __extinctionList: List[str] = ["Gazelle", "Tiger"]
    __speciesDictionary = dict(Gazelle = 0, Tiger = 0)
    __animalList = []
    
    staticmethod
    def getSpeciesDictionary():
        return GameState.__speciesDictionary
    
    staticmethod
    def getExtinctionList():
        return GameState.__extinctionList

    staticmethod
    def getAnimalList():
        return GameState.__animalList

    staticmethod
    def addAnimal(animal: Animal):
        GameState.__speciesDictionary[animal.name] += 1
        GameState.__animalList.append(animal)
        if (GameState.__speciesDictionary[animal.name] == 3):
            GameState.__extinctionList.remove(animal.name)

    staticmethod
    def removeAnimal(animal: Animal):
        GameState.__speciesDictionary[animal.name] -= 1
        GameState.__animalList.remove(animal)
        if (GameState.__speciesDictionary[animal.name] == 2):
            GameState.__extinctionList.append(animal.name)



