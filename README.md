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

- 15 marzo 2024
Pulido eat.c
Experimento con diferentes valores como input de usleep para ganar velocidad.
Limpieza de finish.c

- 16 marzo 2024
Pruebas finales, pulido de algunas variables y eliminación de código innecesario.
Listo para entrega!

- 20 marzo 2024
Hoy he hecho mi primera corrección y todo ha salido bien.
Sin embargo me he dado cuenta de un pequeño detalle repasando alguna cosa a posteriori.
Cuando hay un comensal, el programa no salía porque faltaba la segunda comprobación de la condición del while de ph_acquire_forks.
Es comprobar si mi bool me daba como que el comensal había terminado y así no se quedaba pillado al haber un comensal, puesto que en ese caso solo se maneja un tenedor. Un fallo tonto y casi imperceptible (ya que el programa realmente daba el resultado esperado con un comensal) pero que no quería dejar pasar por alto.
He decidido cancelarlo y volver a presentarlo.

- 23 marzo 2024
He aprovechado estos días hasta que me deja hacer retry para seguir profundizando en diferentes tests. 
También agrego un límite de hasta 200 comensales, y mínimo de 60 milisegundos en cada una de las acciones de los argumentos después de haber visto la hoja de correcciones.





PD: Hello Amanda! 🖖🏻🖖🏻🖖🏻 xD
(saluda si me encuentras) 
