// -*-c++-*-

// --------------------------------------------------------------
//
// Jordi Bataller i Mascarell
// 2019-07-07
//
// --------------------------------------------------------------

// https://learn.sparkfun.com/tutorials/nrf52840-development-with-arduino-and-circuitpython

// https://stackoverflow.com/questions/29246805/can-an-ibeacon-have-a-data-payload

// --------------------------------------------------------------
// --------------------------------------------------------------
#include <bluefruit.h>

#undef min // vaya tela, están definidos en bluefruit.h y  !
#undef max // colisionan con los de la biblioteca estándar

// --------------------------------------------------------------
// --------------------------------------------------------------
#include "LED.h"
#include "PuertoSerie.h"

// --------------------------------------------------------------
// --------------------------------------------------------------
namespace Globales {
  
  LED elLED ( /* NUMERO DEL PIN LED = */ 7 );

  PuertoSerie elPuerto ( /* velocidad = */ 9600 ); // 115200 o 9600 o ...

  // Serial1 en el ejemplo de Curro creo que es la conexión placa-sensor 
};

// --------------------------------------------------------------
// --------------------------------------------------------------
#include "EmisoraBLE.h"
#include "Publicador.h"
#include "Medidor.h"


// --------------------------------------------------------------
// --------------------------------------------------------------
namespace Globales {

  Publicador elPublicador;

  Medidor elMedidor;

}; // namespace

// --------------------------------------------------------------
// inicializarPlaquita()
// --------------------------------------------------------------
void inicializarPlaquita () {

  // de momento nada

} // ()

// --------------------------------------------------------------
// setup()
// --------------------------------------------------------------
void setup() {

  Globales::elPuerto.esperarDisponible();

  // 
  // 
  // 
  inicializarPlaquita();

  // Suspend Loop() to save power
  // suspendLoop();

  // 
  // 
  // 
  Globales::elPublicador.encenderEmisora();

  // Globales::elPublicador.laEmisora.pruebaEmision();
  
  // 
  // 
  // 
  Globales::elMedidor.iniciarMedidor();

  // 
  // 
  // 
  esperar( 1000 );

  Globales::elPuerto.escribir( "---- setup(): fin ---- \n " );

} // setup ()

// --------------------------------------------------------------
// lucecitas()    (Esta funcion controla el tiempo de encendido/Apagado de la luz de la placa)
// --------------------------------------------------------------
inline void lucecitas() {
  using namespace Globales;

  elLED.brillar( 100 ); // 100 encendido
  esperar ( 400 ); //  100 apagado
  elLED.brillar( 100 ); // 100 encendido
  esperar ( 400 ); //  100 apagado
  Globales::elLED.brillar( 100 ); // 100 encendido
  esperar ( 400 ); //  100 apagado
  Globales::elLED.brillar( 1000 ); // 1000 encendido
  esperar ( 1000 ); //  100 apagado
} // ()

// --------------------------------------------------------------
// loop ()
// --------------------------------------------------------------
namespace Loop {
  uint8_t cont = 0;
};

// --------------------------------------------------------------
// loop ()
// --------------------------------------------------------------
void loop () {

  using namespace Loop;
  using namespace Globales;

  cont++;

  elPuerto.escribir( "\n---- loop(): empieza " );
  elPuerto.escribir( cont );
  elPuerto.escribir( "\n" );


  lucecitas();

  // 
  // mido y publico
  // 
  int valorCO2 = elMedidor.medirCO2();
  Serial.print("Concentración de gas: ");
    Serial.print(valorCO2);
    Serial.println(" ppm");
  elPublicador.publicarCO2( valorCO2,
							cont,
							1000 // intervalo de emisión
							);
  
  // 
  // mido y publico
  // 
  /*int valorTemperatura = elMedidor.medirTemperatura();
  
  elPublicador.publicarTemperatura( valorTemperatura, 
									cont,
									1000 // intervalo de emisión
									);
*/
  // 
  // prueba para emitir un iBeacon y poner
  // en la carga (21 bytes = uuid 16 major 2 minor 2 txPower 1 )
  // lo que queramos (sin seguir dicho formato)
  // 
  // Al terminar la prueba hay que hacer Publicador::laEmisora privado
  // 

  char datos[21] = {
	'H', 'o', 'l', 'a',
	'H', 'o', 'l', 'a',
	'H', 'o', 'l', 'a',
	'H', 'o', 'l', 'a',
	'H', 'o', 'l', 'a',
	'H'
  };

  /*char datos[21] = {
    0x4C, 0x00, 0x02, 0x15,                 // Prefijo iBeacon (4 bytes)
    0xE2, 0xC5, 0x6D, 0xB5, 0xDF, 0xFB,     // Parte del UUID (6 bytes)
    0x48, 0xD2, 0xB0, 0x60, 0xD0, 0xF5,     // Parte del UUID (6 bytes)
    0xA7, 0x10,                             // Major (2 bytes)
    0x00, 0x01,                             // Minor (2 bytes)
    0xC5                                    // TX Power (1 byte)
  };*/
  // elPublicador.laEmisora.emitirAnuncioIBeaconLibre ( &datos[0], 21 );
  //elPublicador.laEmisora.emitirAnuncioIBeaconLibre ( "MolaMolaMolaMolaMolaM", 21 );
  //Serial.println("HE llegado hasta aquí!!");
  Globales::elPublicador.laEmisora.emitirAnuncioIBeaconLibre ( datos, 21 );

  esperar( 4000 );

  elPublicador.laEmisora.detenerAnuncio();
  
  // 
  // 
  // 
  elPuerto.escribir( "---- loop(): acaba **** " );
  elPuerto.escribir( cont );
  elPuerto.escribir( "\n" );
  
} // loop ()
// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
