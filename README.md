# ITBA - 72.11 - Sistemas Operativos - TP02
## jOSe 2.0
### Grupo 07

El repositorio es una extensión del sistema operativo Pure64, aplicando los conocimientos y conceptos aprendidos durante las clases teóricas y prácticas en la materia.
Además, permite ejecutar programas que se detallarán más adelante.
El desarrollo es una continuación del sistema implementado el cuatrimestre anterior, en la materia 72.08 - Arquitectura de computadoras. Si desea consultarlo, el proyecto se encuentra disponible en el siguiente enlace: https://github.com/JoseMenta/TPE.


## Instrucciones

### Requerimientos
#### General
* Descargar la imagen Docker agodio/itba-so:1.0
```shell 
docker pull agodio/itba-so:1.0
```

* Contar con el emulador QEMU: https://www.qemu.org/

#### Linux GUI
* Contar con una versión de Docker en el dispositivo.
* Contar con permisos de superusuario.

#### MacOS
* Contar con una versión de Docker en el dispositivo.
* Contar con multipass, un sistema similar a WSL para MacOS (ver más en https://multipass.run).
* El mismo debe configurarse para poder conectarse utilizando el protocolo ssh y transmitir un entorno gráfico mediante el programa XQuartz (ver más en: https://www.xquartz.org)
* Contar con permisos de superusuario en la instancia de multipass.

#### Windows
* Tener configurado WSL 2.
* Contar con una distribución de Linux.
* Contar con una versión de Docker de Windows.
* Contar con el entorno gráfico XServer (ver más en: https://sourceforge.net/projects/vcxsrv/).


### Instalación

1. Descargar el repositorio del proyecto, el cual se encuentra en el siguiente enlace: https://github.com/JoseMenta/TP2_SO.
2. Desempaquetar el archivo .zip.

### Compilación

1. Abrir una terminal en el directorio donde se descomprimió el archivo. 
* En el caso de MacOS, la terminal debe ser dentro de _multipass_.
* En el caso de Windows, la terminal debe ser dentro de _WSL_.
2.   Abrir el contenedor de Docker.
````shell
docker run -v "${PWD}:/root" --privileged --rm -ti agodio/itba-so:1.0
````
3.   Moverse al directorio _root_.
````shell 
cd ./root
````
4.   Compilar el proyecto.
````shell
make all
````
*   Alternativamente, en el caso de querer usar el manejador de memoria Buddy, compilar con _mm=buddy_.
````shell 
make all mm=buddy
````
5.   Cerrar el contenedor.
````shell
exit
````

### Ejecución
1. Ejecutar el proyecto.
````shell
make run
````
2. Escribir la contraseña de superusuario.


## Programa
### shell
Es el intérprete de comandos del sistema operativo. Cada vez que se inicie la máquina, este será el programa que se ejecutará inicialmente por defecto.
![Mensaje de bienvenida al ejecutar el intérprete de comandos](images/shell_1.png?raw=true)

Mediante este programa podrá ejecutar el resto de programas que ofrece el sistema operativo. Incluso, puede ejecutar una nueva instancia de la shell ingresando el comando _bash_.
![Ejecución de una nueva instancia de la shell](images/shell_2.png?raw=true)

````shell
bash
````

#### Background & Pipes
El intérprete de comandos permite ejecutar programas en background si se agrega el carácter ‘&’ al final del comando. De igual manera, es posible definir un pipe entre dos procesos escribiendo _<prog_a> | <prog_b>_, siendo _prog_a_ el programa, junto a sus argumentos, que redirigirá su salida estándar y _prog_b_ el programa, junto a sus argumentos, que redirigirá su entrada estándar. Esto permite, por ejemplo, redirigir la salida de wc para que su resultado se imprima sin vocales escribiendo el comando _wc | filter_. Cabe aclarar que si se utiliza ‘&’ y ‘|’ en el mismo comando, ambos programas se ejecutarán en background.
![Redirigiendo la salida estándar de wc a la entrada estándar de filter](images/pipes_1.png?raw=true)
![Redirigiendo la salida estándar de ps a la entrada estándar de filter, y en background](images/back&pipes_1.png?raw=true)

````shell
<prog_a> <| <prog_b>> <&>
````

### help
Este programa permite conocer todos los programas con los que cuenta el sistema operativo. Al ejecutar el comando _help_ en la shell, el programa imprimirá un listado de los programas disponibles, el cual indica el comando a ejecutar y una descripción de su funcionamiento.
![Listado de los programas disponibles; a la izquierda, se detalla el comando a ejecutar y, a la derecha, una descripción del programa](images/help_1.png?raw=true)

````shell
help
````

### mem
Otorga un detalle del estado de la memoria dinámica. El mismo indica el algoritmo utilizado, el espacio total de la memoria en bytes, la cantidad de bytes ocupados, la cantidad de bloques/nodos ocupados y la cantidad de bytes libres. Para ejecutarlo, se debe usar el comando _mem_.
![Ejecución de mem](images/mem_1.png?raw=true)

````shell
mem
````

### ps
Otorga un detalle de los procesos en ejecución (EXECUTE), en la cola de listos (READY), detenidos (BLOCKED) y finalizados (FINISHED) al momento de ejecutar el programa. Al ejecutar el comando _ps_, se imprime un listado de los procesos, indicando su pid, su nombre, su estado, su nivel de prioridad, su base pointer, su stack pointer y un booleano que indica si está en foreground o no.
![Ejecución de ps en dos instantes distintos](images/ps_1.png?raw=true)

````shell
ps
````

### loop
Es un programa simple, el cual solamente imprime un saludo e indica su pid infinitamente. Este programa debe recibir un único argumento que indique la cantidad de segundos que debe detenerse hasta volver a imprimir el mensaje. Para frenar su ejecución, se debe usar el comando que mata procesos, la tecla **ESC**.
![Ejecución de loop imprimiendo su mensaje cada 2 segundos](images/loop_1.png?raw=true)

````shell
loop <seconds>
````

### kill
Este programa permite finalizar la ejecución de procesos indicando el pid del proceso.
![Utilizando kill para “matar” el proceso test-processes](images/kill_1.png?raw=true)

````shell
kill <pid>
````

### nice
Permite modificar el nivel de prioridad de un proceso, indicando su pid y el nuevo nivel de prioridad.
![Modificando el nivel de prioridad de test-processes de 3 a 0, usando nice](images/nice_1.png?raw=true)

````shell
nice <pid> <0-4>
````


### block & unblock
Estos programas permiten modificar el estado de un proceso entre bloqueado y desbloqueado, respectivamente. Para ello, se debe indicar el pid del proceso que se quiere bloquear o desbloquear.
![Bloqueando el proceso test-processes](images/block_1.png?raw=true)
![Desbloqueando el proceso test-processes](images/unblock_1.png?raw=true)

````shell
block <pid>

unblock <pid>
````

### sem
Imprime el estado de los semáforos activos, indicando su nombre, su valor, el pid de los procesos bloqueados por el semáforo y el pid de los procesos conectados al semáforo. Si el semáforo no tiene nombre (unnamed semaphore), aparecerá la frase “sin nombre”.
![Listado de los semáforos activos](images/sem_1.png?raw=true)

````shell
sem
````

### info.pipe
Similar a _sem_ pero, en este caso, imprime el estado de los pipes activos en el sistema operativo. Indica el nombre del pipe, el índice de lectura y de escritura, el pid de los procesos bloqueados (por lectura y escritura) y el pid de los procesos conectados al pipe. Si el pipe no tiene nombre (unnamed fifo), aparecerá la frase “sin nombre”. El comando debe recibir un argumento, el cual indica la cantidad de pipes que se desea consultar su estado.
![Estado del pipe de teclado](images/info.pipe_1.png?raw=true)

````shell
info.pipe <amount>
````

### cat
Es un programa que recibe caracteres por entrada estándar (STDIN), e imprime lo recibido por salida estándar (STDOUT) cuando lee el carácter ‘\n’. Este programa se detiene al leer el carácter especial EOF (CTRL+D).
![Ejecución de cat](images/cat_1.png?raw=true)

````shell
cat
````


### filter
Es un programa similar a _cat_, pero con la diferencia de que no imprime por salida estándar las vocales que recibe por entrada estándar. De igual manera, finaliza al leer EOF.
![Ejecución de filter](images/filter_1.png?raw=true)

````shell
filter
````

### wc
Este programa recibe los caracteres por entrada estándar, pero no los imprime por salida estándar. En cambio, al finalizar su ejecución por EOF, imprime un análisis de los caracteres ingresados. Indica la cantidad de caracteres leídos (bytes), la cantidad de palabras leídas (words) y la cantidad de líneas leídas (lines).
![Ejecución de wc](images/wc_1.png?raw=true)

````shell
wc
````

### phylo
Es una extensión del problema _The Dining Philosophers_, ya que permite aumentar o reducir la cantidad de filósofos de manera dinámica, es decir mientras se ejecuta el programa. Para aumentar la cantidad de filósofos, se debe presionar la tecla A, y para reducir se debe presionar la tecla R. Para finalizar el programa se debe presionar la tecla Q. Los filósofos podrán estar en tres estados: comiendo (C), pensando (P) o con hambre (H). Pero nunca podrán haber dos filósofos contiguos comiendo. Cabe aclarar que, como mínimo, debe haber dos filósofos y, como máximo, debe haber 15 filósofos. Y siempre empieza su ejecución siendo 5 filósofos.
![Estado inicial de phylo](images/phylo_1.png?raw=true)
![Aviso del programa de que se está agregando un filósofo](images/phylo_2.png?raw=true)
![Aviso del programa de que se está removiendo un filósofo](images/phylo_3.png?raw=true)
![Ejecución de phylo con 15 filósofos](images/phylo_4.png?raw=true)
![Ejecución de phylo con 2 filósofos](images/phylo_5.png?raw=true)


````shell
phylo
````

## Soporte

En caso de necesitar información adicional o querer conocer detalles de la implementación, se sugiere acceder al repositorio de GitHub público del proyecto. Alternativamente, puede contactarse con cualquiera de los desarrolladores.

### Link al repositorio público
https://github.com/JoseMenta/TP2_SO

### Contacto de desarrolladores:

* Axel Facundo Preiti Tasat: https://github.com/AxelPreitiT
* Gastón Ariel Francois: https://github.com/francoisgaston
* José Rodolfo Mentasti: https://github.com/JoseMenta

