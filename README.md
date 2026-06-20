*Este proyecto ha sido creado como parte del currículo de 42 por alcristo*

# get\_next\_line

## Descripción

En este proyecto la función `get_next_line` lee una línea de un descriptor de archivos. Si se ejecuta de forma recursiva lee las líneas posteriores en el descriptor de archivos. De esta forma se puede leer un descriptor de archivos si se llama a la función recursivamente. Esta función será útil en futuros proyectos, pues permitirá leer descriptores de archivos como la salida de errores.

Su principal finalidad didáctica es la comprensión y uso de las variables estáticas. Éstas son variables que se mantienen constantes a lo largo de toda la ejecución del programa.

### Funcionamiento

La función `get_next_line` se ejecuta con el siguiente formato:

```vim
char *get_next_line(int fd);
```

Esto significa que únicamente tiene una variable de entrada, siendo un número entero representando un descriptor de archivos; y una variable de salida: una cadena de caracteres conteniendo la línea leída, o nulo si ha habido un fallo o si la lectura del archivo ha concluido.

La cabecera `get_next_line.h` define una macro "BUFFER\_SIZE", que indica el número de caracteres del buffer que se van a leer cada vez que se ejecuta el comando `read`. Por defecto son 4096, que tiene el máximo rendimiento para buffers pequeños en Linux.

La función utiliza como variable estática una cadena de caracteres denominada `stsh` (stash) en el código o "residuo" en este README, en donde se guardará la línea. Si no existe, la crea duplicando una cadena vacía utilizando la función `ft_strdup`, la cual reserva memoria. Si es la primera vez que se ejecuta el programa, va leyendo el archivo hasta encontrar un salto de línea. Si no es la primera vez, comprueba, mediante la función `ft_strchr`, que no haya saltos de línea antes de volver a leer. Si los hay, extrae la siguiente línea sin leer el archivo. Finalmente, el programa devuelve la línea si existe.

El programa puede devolver nulo si:

- El descriptor de archivos usado como parámetro de entrada no es válido.
- El tamaño de buffer no es un número natural (ni negativo no 0).
- La reserva de memoria del residuo falla.
- Si la línea no existe. En este caso, se libera el residuo antes de devolver nulo.

Para leer el archivo primero se asigna memoria a un buffer de tamaño BUFFER\_SIZE + el carácter nulo. Luego se va leyendo el archivo, poniendo el carácter nulo al final del buffer, ya sea en su última posición o en el final del archivo si llega. Después crea una variable temporal que guarda el residuo para ser liberado tras juntar el residuo con el buffer con `ft_strjoin`. Esto se hace a fin de evitar fugas de memoria. Finalmente, si `ft_strchr` detecta un salto de línea o el número de bytes leídos es menor al tamaño del buffer, se libera el buffer y se crea la línea.

La lectura del archivo puede devolver nulo si:

- Falla la reserva de memoria del buffer.
- El número de bytes leídos es negativo. En este caso, libera el buffer.
- Por alguna razón desconocida la lectura escapa del bucle, a pesar de que no debería hacerlo sin crear la línea, liberando el buffer.

Para crear la línea primero se crea una variable temporal copia del residuo con `ft_strdup` para evitar errores. Dicha variable temporal se libera cuando se encuentra con un iterador un salto de línea o el final de la cadena. Luego se crea la línea con el comando `ft_substr`, empezando desde su posición inicial y terminando en el salto de línea o el final de la cadena. Después se vuelve a crear una variable temporal para cortar la cadena desde el carácter posterior al salto de línea o nulo hasta su final. En el último caso, el residuo estará vacio. Finalmente devuelve la línea. El residuo estará guardado para futuras llamadas de `get_next_line`.

La creación de la línea devuelve nulo únicamente si la línea creada está vacía.

Nótese que tanto para la lectura de línea como para su creación la variable de entrada no es el residuo, sino su dirección de memoria. Esto se hace para que el residuo se guarde entre líneas.

### Parte bonus

Como ejercicios adicionales se han creado los mismos archivos con el sufijo `_bonus.c/h`. Dichos archivos requieren:

- El uso de una única variable estática.
- La capacidad de leer múltiples descriptores de archivos simultáneamente, sin perder la información de ninguno de ellos entre llamadas.

Para el primer requisito no se realizaron cambios debido a que ya se estaba utilizando una sola variable estática, el residuo.

Para el segundo requisito se declaró como variable estática un array de 1024 cadenas de caracteres:

```vim
static char	*stsh[1024];
```

Finalmente, para que decida el descriptor de archivos concreto se realizó la sustitución `stsh` por `stsh[fd]` en la función `get_next_line` sin reemplazar en las funciones estáticas. En la finalización del programa no es necesario liberar el array; simplemente se libera la cadena del descriptor de archivos correspondiente en el array.

## Instrucciones

Para ejecutar `get_next_line` únicamente se requiere tener los archivos .c en el directorio raíz del archivo .c que se va a ejecutar. También hay que incluir en dicho archivo .c la cabecera .h:

```vim
#include "get_next_line.h"
```

Para el correcto funcionamiento de `get_next_line`, tomando `fd` como el descriptor de archivos a leer y `line` como la siguiente línea del descriptor de archivos, dicha función habrá de ejecutarse en un bucle de la siguiente forma:

```vim
while (line)
{
	//comandos
	line = get_next_line(fd);
	//otros comandos, incluyendo posiblemente printf("%s", line)
}
```

Para ejecutar correctamente un programa con `get_next_line` variando el tamaño del buffer se tiene que ejecutar:

```bash
{CC} {CFLAGS} -D BUFFER_SIZE={int} *.c
```

En este caso, CC será el compilador (en mi caso he usado cc, pero también vale gcc), CFLAGS son las flags (en mi caso -Wall -Werror -Wextra), y finalmente {int} deberá ser sustituido por el número de bytes que se leerán cada vez que el programa lea el archivo.

Si se ejecuta sin la flag `-D` el tamaño del buffer será 4096, que es el que se define por defecto en `get_next_line.h`.

## Recursos

El subject de 42 para este proyecto enlaza al artículo de Wikipedia de las variables estáticas (https://es.wikipedia.org/wiki/Variable_est%C3%A1tica). Las páginas relacionadas con las variables locales (https://es.wikipedia.org/wiki/Variable_local) y globales (https://es.wikipedia.org/wiki/Variable_global) ayudaron a distinguir entre ambas.

Para comprobar el correcto funcionamiento de la función se ha utilizado la francinette (https://github.com/WaRtr0/francinette-image).

La página del ingeniero de software Evan Jones (https://www.evanjones.ca/read-write-buffer-size.html) justificó la elección el tamaño de buffer por defecto.

### Uso de inteligencia artificial

No se ha utilizado inteligencia artificial generativa para este proyecto, ya sea para la creación de código, la comprensión de conceptos, la creación de este README o la generación de códigos de prueba de casos límite.

## Anexo

### Variable estática vs global

El hecho de que `get_next_line` utilice variables estáticas pero que en el subject indique explícitamente el uso prohibido de las variables globales puede llevar a uno a confusión entre ambas. En este apartado se discutirán sus similitudes y diferencias.

Para empezar, las variables globales son un subconjunto de las variables estáticas. Esto significa que todas las variables globales son implícitamente estáticas. Por tanto, su vida transcurre a lo largo de la ejecución de todo el programa. Para evitar confusiones, denominaré a las variables estáticas no globales como locales.

La principal diferencia entre las variables locales y globales es su alcance. Las variables locales, como la que se ha usado en este proyecto, únicamente tienen alcance dentro de la función en donde se llama. Esto significa que no se puede llamar a la variable local en otros archivos fuente para referirse al mismo objeto.

Sin embargo, las variables globales también tienen alcance fuera de dicho programa declarándolas como `extern` al principio del archivo. Esto puede crear dependencias que pueden aumentar la complejidad del programa, por lo que su uso no está recomendado, principalmente si no son constantes matemáticas o físicas como *e* o *c*, declarándolas con nombres comprensibles sin que exista posibilidad de solapamiento con otras variables. Además, la Norma de 42 obliga a declarar las variables globales como:

```vim
const static	g_global;
```

### Sobre los descriptores de archivos

Cuando se abre un archivo, a éste se le asigna un número entero representando su descriptor de archivos. El número máximo de descriptores de archivos que puede soportar un sistema POSIX se puede mostrar en el terminal ejecutando:

```bash
ulimit -Sn
```

Normalmente suele soportar 1024 descriptores de archivos, ordenados de 0 a 1023, pero este número puede variar dependiendo del sistema.

Además, todo sistema UNIX tiene por defecto tres descriptores de archivos reservados:

- 0: La entrada estándar (stdin). Cada vez que se escribe algo en el terminal se están escribiendo caracteres sobre este descriptor de archivos.
- 1: La salida estándar (stdout). Todo el texto que está mostrando el terminal se lee escribe en este descriptor de archivos y se lee desde éste.
- 2: La salida de errores estándar (stderr): Los programas normalmente manejan muchos casos de error, que son enviados a este descriptor de archivos.

Por tanto, cuando se abre un archivo se le asigna el descriptor de archivos más bajo, empezando por el 3 y subiendo.
