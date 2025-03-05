
#include "heartbeat.h"  // Se incluye el archivo de cabecera relacionado con el control del "heartbeat"
#include "main.h"        // Se incluye el archivo principal del proyecto, probablemente contiene definiciones de hardware y funciones auxiliares

// Variables privadas para el control del tiempo
static uint32_t last_heartbeat_tick = 0;  // Almacena el último tiempo en milisegundos en el que se realizó un "heartbeat"
static const uint32_t HEARTBEAT_PERIOD = 500; // Medio segundo, define el periodo entre los "heartbeats" (500 ms)
static uint8_t led_state = 0;  // Mantiene el estado actual del LED, 0 (apagado) o 1 (encendido)

// Función de inicialización del "heartbeat"
void heartbeat_init(void) {
    // Inicializa el estado del LED, lo apaga
    HAL_GPIO_WritePin(HEARTBEAT_GPIO_Port, HEARTBEAT_Pin, GPIO_PIN_RESET);  // Escribe el estado de la señal GPIO para apagar el LED
    last_heartbeat_tick = HAL_GetTick();  // Guarda el tiempo actual (en milisegundos) como el último "heartbeat"
}

// Función para actualizar el estado del "heartbeat" (blinking del LED)
void heartbeat_update(void) {
    uint32_t current_tick = HAL_GetTick();  // Obtiene el tiempo actual en milisegundos
    
    // Verifica si ha pasado el período del "heartbeat" (500 ms)
    if((current_tick - last_heartbeat_tick) >= HEARTBEAT_PERIOD) {
        // Togglear el estado del LED (si estaba apagado, lo enciende; si estaba encendido, lo apaga)
        led_state = !led_state;  // Niega el valor de `led_state` (cambia entre 0 y 1)
        
        // Actualiza el estado del LED en el puerto correspondiente
        HAL_GPIO_WritePin(HEARTBEAT_GPIO_Port, HEARTBEAT_Pin, led_state ? GPIO_PIN_SET : GPIO_PIN_RESET);
        
        // Actualiza el último tick con el tiempo actual
        last_heartbeat_tick = current_tick;
    }
}
