// -*- mode: c++ -*-
// ----------------------------------------------------------
// Jordi Bataller i Mascarell
// 2019-07-17
// ----------------------------------------------------------
#ifndef SERVICIO_EMISORA_H_INCLUIDO
#define SERVICIO_EMISORA_H_INCLUIDO

// ----------------------------------------------------
#include <vector>
#include <bluefruit.h> // Asegúrate de incluir bluefruit para BLE y SecureMode_t

// ----------------------------------------------------
// alReves() utilidad
// pone al revés el contenido de una array en el mismo array
// ----------------------------------------------------
template< typename T >
T *  alReves( T * p, int n ) {
  T aux;

  for( int i = 0; i < n/2; i++ ) {
    aux = p[i];
    p[i] = p[n-i-1];
    p[n-i-1] = aux;
  }
  return p;
} // alReves()

// ----------------------------------------------------
// ----------------------------------------------------
uint8_t * stringAUint8AlReves( const char * pString, uint8_t * pUint, int tamMax ) {

  int longitudString = strlen( pString );
  int longitudCopiar = ( longitudString > tamMax ? tamMax : longitudString );

  // copio nombreServicio -> uuidServicio pero al revés
  for( int i = 0; i <= longitudCopiar - 1; i++ ) {
    pUint[ tamMax - i - 1 ] = pString[ i ];
  }

  return pUint;
} // stringAUint8AlReves()

// ----------------------------------------------------------
// ----------------------------------------------------------
class ServicioEnEmisora {

public:

  // --------------------------------------------------------
  // Callback para característica escrita
  using CallbackCaracteristicaEscrita = void ( uint16_t conn_handle,
                                               BLECharacteristic * chr,
                                               uint8_t * data, uint16_t len); 

  // --------------------------------------------------------
  class Caracteristica {
  private:
    uint8_t uuidCaracteristica[16] = { // el uuid se copia aquí (al revés) a partir de un string-c
      '0', '1', '2', '3', 
      '4', '5', '6', '7', 
      '8', '9', 'A', 'B', 
      'C', 'D', 'E', 'F'
    };

    BLECharacteristic laCaracteristica;

  public:
    // Constructor básico
    Caracteristica(const char * nombreCaracteristica_)
      : laCaracteristica(stringAUint8AlReves(nombreCaracteristica_, &uuidCaracteristica[0], 16)) {}

    // Constructor con permisos, propiedades y tamaño
    Caracteristica(const char * nombreCaracteristica_,
                   uint8_t props,
                   SecureMode_t permisoRead,  // Reemplazado BleSecurityMode
                   SecureMode_t permisoWrite, // Reemplazado BleSecurityMode
                   uint8_t tam) 
      : Caracteristica(nombreCaracteristica_) {
      (*this).asignarPropiedadesPermisosYTamanyoDatos(props, permisoRead, permisoWrite, tam);
    }

  private:
    // Asignar propiedades (escritura, lectura, notificación)
    void asignarPropiedades(uint8_t props) {
      (*this).laCaracteristica.setProperties(props);
    }

    // Asignar permisos de lectura y escritura
    void asignarPermisos(SecureMode_t permisoRead, SecureMode_t permisoWrite) { // Reemplazado BleSecurityMode
      (*this).laCaracteristica.setPermission(permisoRead, permisoWrite);
    }

    // Asignar tamaño de los datos
    void asignarTamanyoDatos(uint8_t tam) {
      (*this).laCaracteristica.setMaxLen(tam);
    }

  public:
    // Método para asignar propiedades, permisos y tamaño de los datos
    void asignarPropiedadesPermisosYTamanyoDatos(uint8_t props,
                                                 SecureMode_t permisoRead,   // Reemplazado BleSecurityMode
                                                 SecureMode_t permisoWrite,  // Reemplazado BleSecurityMode
                                                 uint8_t tam) {
      asignarPropiedades(props);
      asignarPermisos(permisoRead, permisoWrite);
      asignarTamanyoDatos(tam);
    }

    // Método para escribir datos
    uint16_t escribirDatos(const char * str) {
      return (*this).laCaracteristica.write(str);
    }

    // Método para notificar datos
    uint16_t notificarDatos(const char * str) {
      return laCaracteristica.notify(&str[0]);
    }

    // Instalar callback para escritura de la característica
    void instalarCallbackCaracteristicaEscrita(CallbackCaracteristicaEscrita cb) {
      (*this).laCaracteristica.setWriteCallback(cb);
    }

    // Activar la característica
    void activar() {
      err_t error = (*this).laCaracteristica.begin();
      Globales::elPuerto.escribir(" (*this).laCaracteristica.begin(); error = ");
      Globales::elPuerto.escribir(error);
    }

  }; // class Caracteristica

  // --------------------------------------------------------
private:
  uint8_t uuidServicio[16] = { 
    '0', '1', '2', '3', 
    '4', '5', '6', '7', 
    '8', '9', 'A', 'B', 
    'C', 'D', 'E', 'F'
  };

  BLEService elServicio;
  std::vector<Caracteristica *> lasCaracteristicas;

public:

  // Constructor del servicio
  ServicioEnEmisora(const char * nombreServicio_)
    : elServicio(stringAUint8AlReves(nombreServicio_, &uuidServicio[0], 16)) {}

  // Método para escribir el UUID del servicio
  void escribeUUID() {
    Serial.println("**********");
    for (int i = 0; i <= 15; i++) {
      Serial.print((char) uuidServicio[i]);
    }
    Serial.println("\n**********");
  }

  // Añadir característica al servicio
  void anyadirCaracteristica(Caracteristica & car) {
    (*this).lasCaracteristicas.push_back(&car);
  }

  // Activar el servicio y las características
  void activarServicio() {
    err_t error = (*this).elServicio.begin();
    Serial.print(" (*this).elServicio.begin(); error = ");
    Serial.println(error);

    for (auto pCar : (*this).lasCaracteristicas) {
      (*pCar).activar();
    }
  }

  // Conversión implícita a BLEService
  operator BLEService&() {
    return elServicio;
  }

}; // class ServicioEnEmisora

#endif // SERVICIO_EMISORA_H_INCLUIDO
