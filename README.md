### Autores: Álvaro Zamanillo, Ignacio Bernardez y Pablo Cuesta

(se compila haciendo 'make all' y se ejecuta el juego actual con 'make run')

## Controles dentro de la interfaz del cubo :

**Movimientos del cubo**:
* RLFBUD: son los movimientos de caras en sentido horario (mismas letras en minúscula, para los movimientos antihorarios)
* XYZxyz: rotaciones del cubo completo (mayúscula horario, minúscula antihorario)
* MESmes: mueven las capas centrales
	
Todos estos movimientos son considerados estándar y se conocen como "Singmaster notation".

**Además se puede usar**: 
* w: selecciona (pseudo)aleatoriamente una de entre todas las mezclas en el fichero scrambles.txt
* W: utiliza el algoritmo de solver.c para generar una string que resuelve el cubo, la ejecuta de una vez e imprime el cubo (resuelto)
* A: muestra en la pantalla la string generada por el solver.h
* a: resuelve el cubo ejecutando cada movimiento con una pequeña espera antes de cada uno para que se vea en la pantalla cómo el algoritmo utilizado resuelve el cubo.

**Solo en la interfaz de la terminal**:
* q sale de la interfaz

**Solo en la interfaz de la biblioteca SDL**:
*  ESC sale de la interfaz
