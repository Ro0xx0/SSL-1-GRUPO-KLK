# SSL Micro Scanner

Scanner para el lenguaje Micro como está definido en el libro del profesor Muchnik de Sintaxis y Semántica de los Lenguajes

## Integrantes del grupo

## Instrucciones para compilar

## Instrucciones para probar

## Diagrama de transición

## Qué cambios hicimos y por qué

- Lo primero que hicimos fue redefinir el Token en el scanner.h con enum para que cada Token tenga un número asignado
- Completamos LimpiarBuffer (para que el residuo de una cadena no pise a otra cadena) 
  EsReservada (para discriminar el caso en el que la cadena es una palabra reservada)
  Y la tabla de transiciones que define al AFD. Modificamos el archivo Makefile para que pueda correr en windows
  ya que la mayoria contamos con ese sistema operativo. En la funcion scanner agregamos que c = getchar() != EOF dentro 
  del while para que no itere infinitamente. 