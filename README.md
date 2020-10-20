# TrabajoPractico1TDP

Nombre: Damian Ganopolsky
Padron: 101.168  

Link al repositorio de github: https://github.com/DamianGanopolsky/TrabajoPractico1TDP

## Introduccion

En el presente trabajo se tuvo como principal objetivo poner en practica los nuevos conocimientos adquiridos sobre el uso y manejo de sockets. Ademas, se busco encapsular los distintos bloques del programa en TDAs, haciendo un buen uso de los recursos y liberandolos cuando sea necesario. Tambien, se

## Descripcion de la resolucion

Desde el inicio de la resolucion del trabajo, se priorizo el manejo del Stack por sobre el Heap a diferencia de materias anteriores. Es por esto, que u

### Diagrama de clases
![Diagrama de clases](diagrama_clases.png)

En este diagrama de clases se puede notar que tanto del lado del servidor como del lado del cliente existe una clase que se encarga de enviar los datos o de recibir los mismos. Ambas clases hacen uso de bloques de bajo nivel los cuales actuan como cajas negras, estos bloques vendrian a ser el TDA socket, y los TDAs Cesar, Vigenere y RC4.

### Diagrama de secuencia

![Diagrama de secuencia](diagrama_secuencia.png)

En este diagrama de secuencias se puede ver a gran escala como es el procedimiento mas importante realizado del lado del cliente, el cual es enviar un mensaje dado. El actor en este caso vendria a ser el archivo client_main.c , y en el presente diagrama se muestra como se delegan las distintas responsabilidades para poder hacer el envio completo del mensaje.
