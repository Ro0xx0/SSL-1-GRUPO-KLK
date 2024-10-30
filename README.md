# SSL Micro Scanner

Scanner para el lenguaje Micro como está definido en el libro del profesor Muchnik de Sintaxis y Semántica de los Lenguajes

## Integrantes del grupo
-Kevin Cadenas <br>
-Ignacio Jubilla<br>
-Lucio De Goñi<br>
-Simón Rojas Pereira<br>
-Máximo Sarba
-Leandro Chen
-Zoe Ana Ines Yusti
-Ariel Gerardo Vaca
-Tomas Valentin Parisi
-GastÓn CÉsar Mongelos

## Instrucciones para compilar
 mingw32-make 

## Instrucciones para probar
 - cd a la carpeta scanner, donde esta el Makefile  
 - mingw32-make test

## Diagrama de transición
![AutomataFinito](TT.png)

## Qué cambios hicimos y por qué

- Primero redefinimos el Token en el scanner.h con enum para que cada Token tenga un número asignado.
  ```C++
  typedef enum {
      INICIO, FIN, LEER, ESCRIBIR, ID, CONSTANTE, PARENIZQUIERDO,  
      PARENDERECHO, PUNTOYCOMA, COMA, ASIGNACION, SUMA, RESTA, FDT,
  } TOKEN;
  ```
  > se utiliza enum pues trabajaremos cn una estructura swicth

- Completamos las funciones:

  ```C++
    void LimpiarBuffer (void);
  ```
  De manera que el residuo de una cadena no pise a la siguiente.
  
  ```C++
    TOKEN EsReservada(void);
  ```
  Discrimina el caso en el que la cadena es una palabra reservada.
  
- Insertamos :

  La tabla de transiciones que define al AFD.
  ```C++
      static ESTADO TT[15][13] = {
    {  1,  3,  5,  6,  7,  8,  9, 10, 11, 14, 13,  0, 14 },
    {  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2,  2 },
    { 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99 },
    {  4,  3,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4,  4 },
    { 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99 },
    { 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99 },
    { 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99 },
    { 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99 },
    { 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99 },
    { 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99 },
    { 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99 },
    { 14, 14, 14, 14, 14, 14, 14, 14, 14, 12, 14, 14, 14 },
    { 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99 },
    { 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99 },
    { 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99 },};
  ```

- Modificamos:
  El archivo Makefile para que pueda correr en Windows pues la mayoria contamos con ese sistema operativo.
  
  La funcion scanner:
  ```C++
  while((c = getchar()) != EOF) {}
  ```
  Para que no itere infinitamente.
  
  Añadimos cmd /c "mmc < test.ok.micro" al Makefile en test: clean mmc para 
  que corra el tes.ok.micro.

  Para reconocer los errores lexicos, si la columna pertenece a la de un elemento no reconocido la funcion Transicion devolvera -1.
  y dentro de la funcion scanner si el valor que se le asigna a estado es -1 se imprime un mensaje de error, se limpia el buffer y 
  el estado vuelve a 0.