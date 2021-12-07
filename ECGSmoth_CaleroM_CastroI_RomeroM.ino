/*
*                 UNIVERSIDAD TÉCNICA DEL NORTE
*          FACULTAD DE INGENIERÍA EN TELECOMUNICACIONES
*          CARRERA DE INGENIERÍA EN TELECOMUNICACIONES
*                     SISTEMAS EMBEBIDOS
*                 
* INTEGRANTES: Calero Melannie, Castro Ismael, Romero Marco                
* TEMA: Proyecto de Sistemas Embebidos P1 
* OBJETIVO: Resolución de los restos propuestos como Proyecto B1
* FECHA: 07/12/21
* 
* 
* Señal ECG_Signal.
* Se uso solo los 90 primeros datos debido a que si se u * todos no alcanzaria en la menoria del arduino uno
 */


#include "datos.h" //Importamos el archivo de las muestras

#define tam_ventana 17 //Definimos el filtro promedio
int centrar_ventana = tam_ventana / 2; //realizamos el filtro promedio
int tam_senal = sizeof(ECG_100Hz) / sizeof(int);
int senal_filtrada[300]; //almacenamos los valores de las muestras
int valor_derecha = 0; //aux
int valor_izquierda = 0; //aux


void setup() {
  Serial.begin(9600);
  Serial.println(tam_senal);
  
  for (int i = 0; i < 300; i++) {senal_filtrada[i] = 0;} //enceramos el vector de salida
  
  for (int i = centrar_ventana; i < tam_senal - centrar_ventana; i++) { //recorremos el vector y se encuentra el centro
    
    Serial.print((ECG_100Hz[i])); //imprime la señal original
    
    valor_derecha = i - centrar_ventana;//posicion inicial de la ventana
    valor_izquierda = i + centrar_ventana + 1; //posicion final de la ventana
    Serial.print(",");
    
    int value = calc_mean(valor_derecha, valor_izquierda); //calculo del promedio
    senal_filtrada[i] = value; //guardamos el valor en el vector de salida
    Serial.println(value);
  };

  
  float mean_input = calc_mean_snr(ECG_100Hz, 300); //se saca el promedio de la señal original
  float deviation_input = calc_stdrDeviation(ECG_100Hz, 300); //se saca la desviacion estandar 
  Serial.println("SNR Input Signal: " + String(mean_input/deviation_input)); 


  float mean_output = calc_mean_snr(senal_filtrada, 300); //relacion S/R de la señal filtrada
  float deviation_output = calc_stdrDeviation(senal_filtrada, 300); //desviacion estandar 
  Serial.println("SNR Output Signal: " + String(mean_output/deviation_output));//impresion del resultado



  
}

void loop() {
}
int calc_mean(int valor_inicial, int valor_final) {//calculo del promedio
  int suma = 0;
  for ( int i = valor_inicial; i <= valor_final; i++) { //desde el valor incial al final
    suma += ECG_100Hz[i]; //Guardamos lo que tenga la señal en todas las posiciones 
  }
  return suma / tam_ventana; //retornamos la suma / tamaño de la ventana
}

void printVector (int vector[], int n) {
  for (int i = 0; i < n; i++) {
    Serial.println(vector[i]);
  }
}


float calc_mean_snr(int vector[], int n) { //Sacar el promedio de la señal
  int suma = 0;
  for (int i = 0; i < n; i++) { //Se realiza la suma
    suma += vector[i];
  }
  return suma / n; //dividimos la suma para la longitud del vector
}


float calc_stdrDeviation(int vector[], int n) {//Sacar desviacion estandar
  float promedio = calc_mean_snr(vector, n); //Llamamos al promedio
  float sumatoria = 0; //sumatoria 
  for (int i = 0; i < n; i++) {//El vector se lo resta el promedio al cuadrado
    sumatoria += pow(vector[i] - promedio, 2);
  }
  return sqrt(sumatoria / (n - 1)); //Sacamos la raiz cuadrada para tener la desviacion.
}
