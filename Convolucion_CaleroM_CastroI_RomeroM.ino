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
*/

//---------------------------------------------------------------------Convolucion 

#include "datos.h" //importar los datos de las muestras tomadas
#define tam_ventana 7 //Tamaño de la ventana 
#define ventana_central (tam_ventana/2) // Hallamos el centro de la ventana

float kernel[tam_ventana] = {0.2, 0.2, 0.2, 0.2, 0.2};  //Encontramos el kernell de la ventana 1/5; 
float temp_vector[tam_ventana] = {0, 0, 0, 0, 0}; //Creamos un vector temporal de ceros

//Calculamos el tamaño del vector y obtenemos el .length
int tam_senal = sizeof(ECG_100Hz) / sizeof(int);

void setup() {
  Serial.begin(9600);
  for (int i = ventana_central; i < tam_senal - ventana_central; i++) {//recorremos el vector y se encuentra el centro
    int valores_derecha = i - ventana_central; //Tomamos los n valores a la derecha
    int valores_izquierda = i + ventana_central + 1; //Tomamos los n valores hacia a izquierda
    Serial.print(ECG_100Hz[i]); //Imprimimos la señal original
    float value = convolve(valores_derecha, valores_izquierda);//Realizamos la convolucion
    Serial.print(",");
    Serial.println(value); //imprimimos en el terminal
  }
}

void loop() {
  }

void printVector (int vector[], int n) {
  for (int i = 0; i < n; i++) {
    Serial.print(vector[i]);
    Serial.print(" ");
  }
  Serial.println("");
}
//convolucion
float convolve(int inicio, int fin) {
  int j = 0;
  for (int i = inicio; i <= fin; i++) {//desde el valor inicial al final en el vector de ceros se cambian los valores por nuestra señal original 
    if ( j < tam_ventana) {
      temp_vector[j] = ECG_100Hz[i];
      j++;
    } 
    else {
      j = 0;
    }
  }
  float multiplicacion[tam_ventana]; //multiplicamos los valores reemplados por el valor del kernell
  float suma = 0;
  for (uint8_t i = 0; i < tam_ventana; i++){//Se realiza la multiplicacion por los valores del kernell
    multiplicacion[i] = temp_vector[i]*kernel[i];
    suma += multiplicacion[i]; //sumamos los valores 
    }
  return suma; //retornamos la suma
}
