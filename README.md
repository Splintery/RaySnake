# RaySnake
Snake but with Rays

use javac launcher/Launcher.java to compile
and java launcher.Launcher to run

BUILD WITH:
```
cmake -B build
cmake --build build
```


Idee:
On contrôle un serpent dans un monde en 2D, le but est de s'échapper du terrarium.
Lorsque l'humain n'est pas dans la pièce la lumière s'étteint et on ne peut que voir se qui se trouve directement devant nous, et quand l'humain revient la lumière est rallumé et l'on peut voir se qui se trouve en dehors du champs de vision.

Pour s'évader, il faut attendre que la lumière s'éteigne pour ne pas se faire chopper et trouver des points sensible dans les murs de l'enclos que l'on peut briser si l'on est suffisament grand(manger suffisament de pommes). Comme dans snake si l'on se prend un mur ou bien même une partie de son corps c'est gameover.

GameLoop :
Update dans le modèle nécessite un boolean pour chaque action, dans la vue si l'on veut généré une action on appel une méthode qui fait passer ce boolean à vrai puis dans l'update du model si vrai alors on réalise l'action.

Comme ça, par la suite on peut synchroniser ça avec des sémaphores autour de la variable bool ou avec une autre méthode de synchronisation.

TODO: Rethink the class described in World.hpp, make it so it doesn't hold the snake anymore(the controller will). It should hold the topology of the map the player is on, so it needs a set of Bounds to represent the various obstacles, and be able to check if a certain point is colliding with any of the bounds in the set.

TODO: Sortir le Snake du World, faire une méthode update pour world et la faire gérer les collisions et tout avec le Snake.

The controller should only hold what is needed for transitionning through states and updating/drawing them. It is the state itself that needs to hold the various objects required for it.

TODO: Make player controls structure for easy passing of player control through states

TODO: Animated Sprite that can queue specific animations or signal when an animation is done

TODO: Enhance snake changing of direction, make it more predictable (overlay of next position ???)

TODO: Sh script for easier building of project and running

TODO: Object tracker

TODO: change of how the Adapter works, to have an object from the model in the view I will create a child class of that object and make that child extend the sf::Drawable class. Each state can then store an amount of drawables that get called when drawing to the screen.

TODO: implement a logger with macros. the logger should take in a config file where information regarding where the info should be logged out to. Different levels of logs should be configurable

TODO: to allow animated sprites to signal when an animation is done playing, the method update should take in a function pointer to call when the animation is done. the function passed in parameters would flip a Boolean that will cause updates in the model when the game loop calls it.

planning for week of 15/09/2025:
* Monday: sh script
* Tuesday: snake overlay
* wednesday: snake overlay
* Thursday: snake overlay
* Friday: adapter
* Saturday: adapter
* Sunday: adapter