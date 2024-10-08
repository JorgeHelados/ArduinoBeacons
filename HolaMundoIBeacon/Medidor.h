// -*- mode: c++ -*-

#ifndef MEDIDOR_H_INCLUIDO
#define MEDIDOR_H_INCLUIDO

// ------------------------------------------------------
// ------------------------------------------------------
class Medidor {

  // .....................................................
  // .....................................................
private:

public:

  // .....................................................
  // constructor
  // .....................................................
  Medidor(  ) {
  } // ()

  // .....................................................
  // .....................................................
  void iniciarMedidor() {
	// las cosas que no se puedan hacer en el constructor, if any
  } // ()

  // .....................................................
  // .....................................................


  // Pines analógicos para Vgas y Vref (puedes ajustar según tu placa)
  const int pinVgas = A4;   // Suponiendo que el pin 29 es A5
  const int pinVref = A5;   // Suponiendo que el pin 28 es A4

  // Valores de calibración (ajusta según el sensor que estés utilizando)
  const float Vgas0 = 1.65;  // Valor de Vgas en aire limpio (medido previamente)
  const float M = 0.1;       // Factor de calibración del sensor (ppm/V), ajusta este valor según tu sensor

  //---------------------------------------------------------
  // medirCO2() -> N
  //---------------------------------------------------------
  int medirCO2() {
    /* Descomentar esto si el sensor pilla datos */
    /*float Vgas = analogRead(pinVgas) * (3.3 / 1023.0); // Convertir la lectura a voltaje (0-3.3V)
    float Vref = analogRead(pinVref) * (3.3 / 1023.0); // Convertir la lectura a voltaje (0-3.3V)
    
    // Calcular la concentración de gas en ppm
    float gasConcentration = (Vgas - Vgas0) / M;
    if (gasConcentration >= 0) {
        int valorPos = gasConcentration * 10;
        return valorPos;
    } else if (gasConcentration < 0) {
        int valorNeg = (gasConcentration * (-1)) * 10;
        return valorNeg;
    }*/

    // Valor de retorno predeterminado en caso de que no entre en ninguna condición
    return 1122;
	  //return 235;
  } // ()

  // .....................................................
  // medirTemperatura() -> N ?
  // .....................................................
  int medirTemperatura() {
	return -12; // qué frío !
  } // ()
	
}; // class

// ------------------------------------------------------
// ------------------------------------------------------
// ------------------------------------------------------
// ------------------------------------------------------
#endif
