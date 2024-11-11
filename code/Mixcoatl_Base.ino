#include <RednovaV2.h>

// Puerto de conexión de los sensores de objeto
int LSens = A6;    // Puerto de conexión del sensor izquierdo
int LFSens = A5;   // Puerto de conexión del sensor frontal izquierdo
int BackSens = A4; // Puerto de conexión del sensor trasero
int RFSens = A3;   // Puerto de conexión del sensor frontal derecho
int RSens = A2;    // Puerto de conexión del sensor derecho

// Puerto de conexión de los sensores de línea
int LQtr = A7; // Puerto de conexión del sensor de línea izquierdo
int RQtr = A1; // Puerto de conexión del sensor de línea derecho

// Último valor
int LastValue = 0;

// Puerto de conexión de los interruptores tácticos
int DS1 = 16;
int DS2 = 15;
int DS3 = 14;
int DS4 = 13;

// Puerto de conexión del botón de inicio
int StartPin = 7;

void setup()
{
    // Secuencia de inicio de Rednova
    RednovaV2.StartRednovaV2(1);

    // Sensores de objeto
    pinMode(LSens, INPUT);
    pinMode(LFSens, INPUT);
    pinMode(BackSens, INPUT);
    pinMode(RFSens, INPUT);
    pinMode(RSens, INPUT);

    // Sensores de línea
    pinMode(LQtr, INPUT_PULLUP);
    pinMode(RQtr, INPUT_PULLUP);

    // Botón de inicio
    pinMode(StartPin, INPUT);

    // Interruptores de modo
    pinMode(DS1, INPUT_PULLUP);
    pinMode(DS2, INPUT_PULLUP);
    pinMode(DS3, INPUT_PULLUP);
    pinMode(DS4, INPUT_PULLUP);
    delay(200);
}

void loop()
{
Tactics:
    // Si se presiona el botón de inicio, el robot se activa
    if (digitalRead(StartPin) == HIGH)
    {
        // Ds1 = Encendido, Ds2 = Apagado, Ds3 = Apagado, Ds4 = Apagado
        if (digitalRead(DS1) == 0 && digitalRead(DS2) == 1 && digitalRead(DS3) == 1 && digitalRead(DS4) == 1)
        {
            RednovaV2.TurnLeft(100, 37);       // Girar a la izquierda 90 grados
            RednovaV2.DualDirection(0, 0, 70); // Detener motores
            LastValue = 0;
            goto Start2;
        }
        // Ds1 = Apagado, Ds2 = Apagado, Ds3 = Apagado, Ds4 = Encendido
        else if (digitalRead(DS1) == 1 && digitalRead(DS2) == 1 && digitalRead(DS3) == 1 && digitalRead(DS4) == 0)
        {
            RednovaV2.TurnRight(100, 37);      // Girar a la derecha 90 grados
            RednovaV2.DualDirection(0, 0, 70); // Detener motores
            LastValue = 0;
            goto Start2;
        }
        // Ds1 = Encendido, Ds2 = Encendido, Ds3 = Apagado, Ds4 = Apagado
        else if (digitalRead(DS1) == 0 && digitalRead(DS2) == 0 && digitalRead(DS3) == 1 && digitalRead(DS4) == 1)
        {
            RednovaV2.TurnLeft(100, 37);           // Girar a la izquierda 90 grados
            RednovaV2.DualDirection(50, 100, 120); // Giro en arco hacia la izquierda
            goto Start;
        }
        // Ds1 = Apagado, Ds2 = Apagado, Ds3 = Encendido, Ds4 = Encendido
        else if (digitalRead(DS1) == 1 && digitalRead(DS2) == 1 && digitalRead(DS3) == 0 && digitalRead(DS4) == 0)
        {
            RednovaV2.TurnRight(100, 37);          // Girar a la derecha 90 grados
            RednovaV2.DualDirection(100, 60, 120); // Giro en arco hacia la derecha
            goto Start;
        }
        // Ds1 = Apagado, Ds2 = Encendido, Ds3 = Encendido, Ds4 = Apagado
        else if (digitalRead(DS1) == 1 && digitalRead(DS2) == 0 && digitalRead(DS3) == 0 && digitalRead(DS4) == 1)
        {
            RednovaV2.DualDirection(100, 100, 30); // Avanzar
            RednovaV2.DualDirection(0, 0, 20);     // Detener motores
            goto Start;
        }
        // Ds1 = Encendido, Ds2 = Encendido, Ds3 = Encendido, Ds4 = Encendido
        else if (digitalRead(DS1) == 0 && digitalRead(DS2) == 0 && digitalRead(DS3) == 0 && digitalRead(DS4) == 0)
        {
            RednovaV2.DualDirection(100, 100, 170); // Avanzar a gran velocidad
            RednovaV2.DualDirection(0, 0, 20);      // Detener motores
            goto Start2;
        }
        // Ds1 = Encendido, Ds2 = Encendido, Ds3 = Encendido, Ds4 = Apagado
        else if (digitalRead(DS1) == 0 && digitalRead(DS2) == 0 && digitalRead(DS3) == 0 && digitalRead(DS4) == 1)
        {
            RednovaV2.TurnRight(100, 130);         // Girar a la derecha 90 grados
            RednovaV2.DualDirection(100, 50, 120); // Giro en arco hacia la derecha
            RednovaV2.DualDirection(0, 0, 20);     // Detener motores
            goto Start2;
        }
        // Ds1 = Apagado, Ds2 = Encendido, Ds3 = Encendido, Ds4 = Encendido
        else if (digitalRead(DS1) == 1 && digitalRead(DS2) == 0 && digitalRead(DS3) == 0 && digitalRead(DS4) == 0)
        {
            RednovaV2.TurnLeft(100, 130);          // Girar a la izquierda 90 grados
            RednovaV2.DualDirection(50, 100, 120); // Giro en arco hacia la izquierda
            RednovaV2.DualDirection(0, 0, 20);     // Detener motores
            goto Start2;
        }
    }
    else{
        if (digitalRead(LFSens) == 1 || digitalRead(BackSens) == 1 || digitalRead(RFSens) == 1){
            delay(5);
            if (digitalRead(LFSens) == 1 || digitalRead(BackSens) == 1 || digitalRead(RFSens) == 1){
                RednovaV2.RGB(0, 1, 0, 1); // Rojo = Apagado, Verde = Encendido, Azul = Apagado, Ms = 1ms
            }
        }
        else if (digitalRead(RSens) == 1){
            delay(5);
            if (digitalRead(RSens) == 1)
            {
                RednovaV2.RGB(0, 0, 1, 1); // Rojo = Apagado, Verde = Apagado, Azul = Encendido, Ms = 1ms
            }
        }
        else if (digitalRead(LSens) == 1){
            delay(5);
            if (digitalRead(LSens) == 1)
            {
                RednovaV2.RGB(1, 0, 0, 1); // Rojo = Encendido, Verde = Apagado, Azul = Apagado, Ms = 1ms
            }
        }
        else if (analogRead(LQtr) < 300 || analogRead(RQtr) < 300){
            RednovaV2.RGB(1, 1, 1, 1); // Rojo = Encendido, Verde = Encendido, Azul = Encendido, Ms = 1ms
        }
        else{
            RednovaV2.RGB(0, 0, 0, 1); // Rojo = Apagado, Verde = Apagado, Azul = Apagado, Ms = 1ms
        }
    }
    goto Tactics;

Start:

    if (digitalRead(LSens) == 0 && digitalRead(LFSens) == 0 && digitalRead(BackSens) == 0 && digitalRead(RFSens) == 0 && digitalRead(RSens) == 0){
        delay(12);
        for (int i = 0; i <= 6000; i++)
        {
            if (digitalRead(LSens) == 0 && digitalRead(LFSens) == 0 && digitalRead(BackSens) == 0 && digitalRead(RFSens) == 0 && digitalRead(RSens) == 0){
                RednovaV2.DualDirection(0, 0, 1);
            }
            else{
                goto Start2;
            }
        }
        for (int i = 0; i <= 10; i++){
            if (digitalRead(LSens) == 0 && digitalRead(LFSens) == 0 && digitalRead(BackSens) == 0 && digitalRead(RFSens) == 0 && digitalRead(RSens) == 0){
                RednovaV2.DualDirection(70, 70, 1);
            }
            else{
                goto Start2;
            }
        }
    }
    else{
        delay(12);
        while (1){
        Start2:
            if (digitalRead(StartPin) == LOW){
                while (1){
                    RednovaV2.DualDirection(0, 0, 2);
                    RednovaV2.MixLed(4);
                }
            }

            if (analogRead(LQtr) < 500 && analogRead(RQtr) > 500){
                RednovaV2.Backward(70, 220);
                RednovaV2.TurnRight(70, 70);
                LastValue = 0;
            }
            else if (analogRead(LQtr) > 500 && analogRead(RQtr) < 500){
                RednovaV2.Backward(70, 220);
                RednovaV2.TurnLeft(70, 70);
                LastValue = 0;
            }

            if (digitalRead(RSens) == 1){
                delay(5);
                if (digitalRead(RSens) == 1)
                {
                    RednovaV2.DualDirection(80, -70, 1);
                    LastValue = 2;
                    RednovaV2.RGB(0, 0, 1, 1); // Rojo = Apagado, Verde = Apagado, Azul = Encendido, Ms = 1ms
                }
            }
            else if (digitalRead(LSens) == 1){
                delay(5);
                if (digitalRead(LSens) == 1){
                    RednovaV2.DualDirection(-70, 80, 1);
                    LastValue = 1;
                    RednovaV2.RGB(1, 0, 0, 1); // Rojo = Encendido, Verde = Apagado, Azul = Apagado, Ms = 1ms
                }
            }
            else if (digitalRead(LFSens) == 1 && digitalRead(RFSens) == 1){
                delay(5);
                if (digitalRead(LFSens) == 1 && digitalRead(RFSens) == 1){
                    RednovaV2.DualDirection(80, 80, 1);
                    LastValue = 0;
                    RednovaV2.RGB(0, 1, 0, 1); // Rojo = Apagado, Verde = Encendido, Azul = Apagado, Ms = 1ms
                }
            }
            else if (digitalRead(LFSens) == 1){
                delay(5);
                if (digitalRead(LFSens) == 1){
                    RednovaV2.DualDirection(40, 80, 1);
                    LastValue = 1;
                    RednovaV2.RGB(0, 1, 0, 1); // Rojo = Apagado, Verde = Encendido, Azul = Apagado, Ms = 1ms
                }
            }
            else if (digitalRead(RFSens) == 1){
                delay(5);
                if (digitalRead(RFSens) == 1){
                    RednovaV2.DualDirection(80, 40, 1);
                    LastValue = 2;
                    RednovaV2.RGB(0, 1, 0, 1); // Rojo = Apagado, Verde = Encendido, Azul = Apagado, Ms = 1ms
                }
            }
            // El sensor central detectó al oponente
            else if (LastValue == 0){ 
                RednovaV2.DualDirection(22, 22, 1);
            }
            // El sensor izquierdo detectó al oponente
            else if (LastValue == 1){ 
                RednovaV2.TurnLeft(40, 1);
            }
            // El sensor derecho detectó al oponente
            else if (LastValue == 2){ 
                RednovaV2.TurnRight(40, 1);
            }
            goto Start2;
        }
    }
    // RednovaV2.DualDirection(0, 0, 10);
    goto Start;
}
