Pequeña explicación del juego hasta ahora. 

(se compila haciendo 'make all' y se ejecuta el juego actual con 'make game')

Por ahora el juego como tal consta del loop que hay en el fichero cube_interface.c, donde se utiliza el "cube.h" (donde se encuentra la estructura del cubo y se definen las funciones que lo mueven); y el "solver.h", que se encarga de generar la solución del cubo; y el "print_c.h", donde están definidas las funciones que imprimen el cubo en la terminal. 

Todavía falta mejorar la interfaz y, sobre todo, la comunicación con el usuario, e dicha interfaz habrá mensajes que faciliten al usuario los comandos que se pueden usar.

Por ahora, al ejecutar, con 'make game', aparece el cubo en la pantalla. El juego recibe letras escritas desde el teclado:

	q: termina el juego
Movimientos del cubo:
	RLFBUD: son los movimientos de caras en sentido horario (mismas letras en minúscula, para los movimientos antihorarios)
	XYZxyz: rotaciones del cubo completo (mayúscula horario, minúscula antihorario)
	MESmes: mueven las capas centrales
Todos estos movimientos son considerados estándar y se conocen como "Singmaster notation".

Además se puede usar: 
	w: selecciona (pseudo)aleatoriamente una de entre todas las mezclas en el fichero scrambles.txt
	W: utiliza el algoritmo de solver.c para generar una string que resuelve el cubo, la ejecuta de una vez e imprime el cubo (resuelto)
	A: muestra en la pantalla la string generada por el solver.h
	a: resuelve el cubo ejecutando cada movimiento con una pequeña espera antes de cada uno para que se vea en la pantalla cómo el algoritmo utilizado resuelve el cubo.
