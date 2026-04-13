# Sistema de Gestión de Tareas

## Descripción

Este sistema permite a los usuarios gestionar sus tareas pendientes. Los usuarios pueden registrar tareas mediante categorías creadas por ellos mismos, ver las categorías creadas, ver las tareas registradas, filtrar las tareas por categorías y más. Esta herramienta está diseñada para facilitar la organización de los quehaceres del usuario, permitiendo acceder a ellos de una manera rápida y sencilla.

## Cómo compilar y ejecutar

Este sistema ha sido desarrollado en lenguaje C y puede ejecutarse fácilmente utilizando [repl.it](https://replit.com/~). Para comenzar a trabajar con el sistema en tu equipo local, sigue estos pasos:

## Requisitos previos:
* Tener cuenta en repl.it.

## Pasos para compilar y ejecutar:
1. Descarga y descomprime el archivo `.zip` en una carpeta de tu elección.
2. Importa el proyecto en [repl.it](https://replit.com/~)
   * Inicia [repl.it](https://replit.com/~).
   * Selecciona `Importe code or design > Zip file` y seleccionas la carpeta en la que tienes el proyecto.
3. Compila el código
   * Abre la terminal integrada en [repl.it](https://replit.com/~) abriendo una nueva pestaña tipo `shell`.
   * En la terminal, compila el programa con el siguiente comando (ajusta el nombre si el archivo principal tiene otro nombre):
    ````
    gcc tdas/*.c tarea1.c -Wno-unused-result -o tarea1
    ````
4. Ejecuta el programa
   * Una vez compilado, puedes ejecutar la aplicación con:
    ````
    ./tarea1
    ````

# Funcionalidades

## Funcionando correctamente:
* Registrar diversas categorías para las tareas junto con una lista que contenga todas las tareas de cada categoría.
* Eliminar categorías (Junto con todas las tareas de esa categoría).
* Mostrar todas las categorías ingresadas en el sistema.
* Registrar tareas por categoría dentro de una cola ordenada por orden de ingreso.
* Atender la siguiente tarea, respetando el orden de ingreso.
* Visualizar todas las tareas ingresadas en el sistema, mostrando sus datos básicos.
* Filtrar las tareas ingresadas en el sistema por categorías.

## Problemas conocidos:
* El programa solo índica la hora del horario de invierno en Chile.
* El nombre de las categorías está limitado a 30 carácteres.
* La descripción de las tareas está limitada a 50 carácteres.

## A mejorar
* Implementar una interfaz de usuario amigable.
* Permitir editar las tareas.
* Crear automáticamente las categorías al ingresar tareas con categorías nuevas.

# Ejemplo de uso
**Paso 1: Registrar una nueva categoría** 
Se comienza registrando una nueva categoría para las tareas.
````
Opción seleccionada: 1) Nueva Categoría
Registrar una nueva categoría (Máximo 30 carácteres): Casa
````
El sistema registra la categoría Casa.

**Paso 2: Ver la lista de categorías**
El usuario revisa las categorías ingresadas en el sistema.
````
Opción seleccionada: 3) Mostrar Categorías
````
La lista muestra solamente la categoría casa, ya que es la única registrada.

**Paso 3: Registrar Tareas**
Se registran tareas para la categoría ingresada.
````
Opción seleccionada: 4) Registrar Tarea
Ingrese la tarea (Máximo 50 caracteres): Hacer Aseo
Ingrese la categoría de la tarea: Casa
Opción seleccionada 4) Registrar Tarea
Ingrese la tarea (Máximo 50 caracteres): Lavar los platos
Ingrese la categoría de la tarea: Casa
````
El sistema registra dos tareas con la categoría "Casa", "Hacer Aseo" y "Lavar los platos" y guarda la hora actual de registro de cada tarea.

**Paso 4: Ver la lista de tareas**
El usuario revisa todas las tareas registradas.
````
Opción seleccionada: 6) Visualización del Tablero General
````
El sistema muestra las tareas "Hacer Aseo" y "Lavar los platos", con sus categorías correspondientes y la hora de registro de las tareas.

**Paso 5: Atender Siguiente Tarea**
````
Opción seleccionada: 5) Atender Siguiente Tarea
````
El sistema muestra los datos de la tarea "Hacer Aseo", indica que fue atendida y la elimina de la cola. 

**Paso 6: Filtrar tareas por categoría**
````
Opción seleccionada: 7) Filtrado Por Categoría
Ingrese la categoría: Universidad
NO EXISTE LA CATEGORÍA.
````
En este caso, como la categoría no fue previamente registrada, el sistema indica que la categoría no existe.

**Paso 7: Eliminar categorías**
````
Opción seleccionada: 2) Eliminar Categoría
Ingrese la categoría a eliminar: Casa
````
El sistema elimina la categoría Casa y las tareas asociadas a esa categoría.
