### Autores: Ignacio Bernardez, Pablo Cuesta y Álvaro Zamanillo.
Nombre del grupo: *`is_prime()`*

(se compila haciendo 'make all' y se ejecuta el juego con 'make run')

## Comandos para instalar en Ubuntu las librerías necesarias para compilar el juego
```
sudo apt-get install libsdl2-2.0
sudo apt install libsdl1.2-dev libsdl-image1.2-dev libsdl-mixer1.2-dev libsdl-ttf2.0-dev
sudo apt-get install libsdl2-mixer-dev 
sudo apt-get install libsdl2-ttf-dev 
sudo apt-get install libglu1-mesa-dev freeglut3-dev mesa-common-dev
```

## Controles dentro de la interfaz del cubo 

**Movimientos del cubo**:
* RLFBUD: son los movimientos de caras en sentido horario (mismas letras en minúscula, para los movimientos antihorarios)
* XYZxyz: rotaciones del cubo completo (mayúscula horario, minúscula antihorario)
* MESmes: mueven las capas centrales
	
Todos estos movimientos son considerados estándar y se conocen como "Singmaster notation".

**Además se puede usar**: 
* w: selecciona (pseudo)aleatoriamente una de entre todas las mezclas en el fichero scrambles.txt y pone el cronómetro a cero
* W: utiliza el algoritmo de solver.c para generar una string que resuelve el cubo, la ejecuta de una vez e imprime el cubo (resuelto)
* A: muestra en la pantalla la string generada por el solver.h, si no cabe de una vez se puede ver la siguiente parte de la solución volviendo a pulsar 'A'.
* a: resuelve el cubo ejecutando cada movimiento con una pequeña espera antes de cada uno para que se vea en la pantalla cómo el algoritmo utilizado resuelve el cubo.
* espacio: para/reinicia el cronómetro. Si el cubo está resuelto, aparece u mensaje en la pantalla, del que se sale presionando cualquier tecla.
* o: limpia la terminal y vuelve a imprimir el contenido por si hubiese ocurrido algún error.

**Solo en la interfaz de la terminal**:
* q: sale de la interfaz

**Solo en la interfaz de la biblioteca SDL**:
*  ESC: sale de la interfaz
