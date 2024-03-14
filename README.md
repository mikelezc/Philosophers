# Philosophers

- 25 febrero 2024

Comienzo investigación y documentación de la nuevas funciones sugeridas por el subject.

	Muy recomendable leer detenidamente este artículo:
	https://medium.com/@jalal92/the-dining-philosophers-7157cc05315

	Lista con algunos vídeos que he encontrado útiles para desarrollar este proyecto
	https://youtube.com/playlist?list=PLYg292oZjGzZ_vpPhy79WYf9BFqjrVqvb&si=I6MUBARIOK_JSCyx

Empiezo a plantear estructura de carpetas, makefile y philo.h

- 28 febrero 2024

Estos días atrás he terminado la parte de parsing y he seguido revisando vídeos sobre la utilización de mutex y como evitar data races, y threads.

- 6 marzo 2024

Varios días implementando la parte de "seteo del escenario", aún queda pero empiezo a avanzar en las siguientes partes del proyecto.

Planteadas las estructuras que voy a utilizar.

- 7 marzo 2024

Avanzo con el planteamiento principal de "los turnos de comidas" y reviso como hacer la monitorización de los filósofos.

- 8 marzo 2024

Pulo a fondo toda la parte de parseo para que el código sea lo más legible posible.
Amplío y modifico las estructuras.
Terminada toda la parte de inicio de mutex, seteo de las estructuras, y asignación de los tenedores. Ya se como poner la mesa entera con comensales y todo! (set_scenario).
He empezado con la parte de Peter (parte de monitoreo).

- 10 marzo 2024

Estos dos últimos días he dejado planteado (con mucho curro) las acciones de los filósofos, así como herramientas laterales (sleep, etc)


- 11-12 marzo 2024
Termino primer borrador del proyecto y pulo detalles de las funciones anteriores.

- 13 marzo 2024
Primera revisión general con ayuda, para corrección de errores.
Creo eat.c porque introduzco nuevas funciones de gestión de mutex y de lógica de reserva de tenedores para evitar deadlocks al aumentar el número de comensales.
Cambio también la forma de reservar filósofos de mi programa ya que no era muy adecuada.

- 14 marzo 2024
Segunda revisión general, limpieza y optimización del código.
Limpio la copia de variables entre mis dos estructuras al haberlas enlazado mutuamente.
Así evito redundancias en mis estructuras y las dejo lo más limpias posible.

PD: Hola Amanda! 🖖🏻
(foto si me encuentras :p) 