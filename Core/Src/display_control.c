
#include "display_control.h"   // Se incluye el archivo de cabecera de control de la pantalla (probablemente contenga funciones para manipular la pantalla OLED)
#include "main.h"               // Se incluye el archivo principal del proyecto, que puede tener definiciones de hardware y funciones auxiliares

// Se declaran las variables globales
DisplayState_t display_state = DISPLAY_IDLE;  // Variable para gestionar el estado de la pantalla (en este caso está en estado inactivo inicialmente)
uint32_t display_timer = 0;  // Temporizador para controlar el tiempo entre cambios de pantalla

// Función de inicialización de la pantalla OLED
void display_init(void) {
    ssd1306_Init();  // Inicializa la pantalla OLED
    ssd1306_Fill(Black);  // Llena la pantalla con el color negro (borrar todo)
    ssd1306_SetCursor(0, 0);  // Establece el cursor en la posición (0, 0)
    ssd1306_WriteString("Sistema Listo", Font_7x10, White);  // Muestra el texto "Sistema Listo" en color blanco
    ssd1306_UpdateScreen();  // Actualiza la pantalla para mostrar lo que se ha configurado
}

// Función para mostrar el estado en la pantalla
void display_status(const char* status) {
    ssd1306_Fill(Black);  // Limpia la pantalla
    // Mostrar estado
    ssd1306_SetCursor(0, 0);  // Coloca el cursor en la parte superior de la pantalla
    ssd1306_WriteString("Estado:", Font_7x10, White);  // Muestra "Estado:"
    ssd1306_SetCursor(0, 15);  // Coloca el cursor en la segunda línea
    ssd1306_WriteString((char*)status, Font_7x10, White);  // Muestra el estado que se pasa como argumento
    ssd1306_UpdateScreen();  // Actualiza la pantalla con el texto mostrado
    
    // Esperar un momento para que se vea el estado
    display_timer = HAL_GetTick();  // Guarda el tiempo actual (en milisegundos)
    display_state = DISPLAY_WAIT;  // Cambia el estado a "esperando"
    
    // Limpiar pantalla y dejarla lista para mostrar el código
    ssd1306_Fill(Black);  // Limpia la pantalla
    ssd1306_SetCursor(0, 0);  // Coloca el cursor en la parte superior
    ssd1306_WriteString("Ingrese codigo:", Font_7x10, White);  // Muestra "Ingrese código:"
    ssd1306_UpdateScreen();  // Actualiza la pantalla con este mensaje
}

// Función para mostrar el código ingresado en la pantalla
void display_code(ring_buffer_t *rb) {
    // Primero, limpiar SOLO el área donde se muestra el código
    ssd1306_FillRectangle(0, 20, 128, 64, Black);  // Limpia la parte de la pantalla donde se muestra el código (desde y=20 hasta y=64)
    
    // Preparar buffer para mostrar el código actual
    char display_buffer[16] = {0};  // Define un buffer para almacenar el código (máximo 16 caracteres)
    uint8_t size = ring_buffer_size(rb);  // Obtiene el tamaño del buffer de anillo (número de caracteres en el buffer)
    
    if(size > 0) {
        // Si hay datos en el buffer, los copia a display_buffer
        for(uint8_t i = 0; i < size && i < 15; i++) {
            display_buffer[i] = rb->buffer[i];  // Copia los caracteres del buffer al display_buffer
        }
        
        // Mostrar el código nuevo en la pantalla
        ssd1306_SetCursor(0, 20);  // Coloca el cursor a partir de la línea 20
        ssd1306_WriteString(display_buffer, Font_7x10, White);  // Muestra el código almacenado en display_buffer
    }
    
    ssd1306_UpdateScreen();  // Actualiza la pantalla con el código mostrado
}

// Función para mostrar un mensaje de error en la pantalla
void display_error(const char* error_msg) {
    ssd1306_Fill(Black);  // Limpia la pantalla
    
    // Mostrar mensaje de error
    ssd1306_SetCursor(0, 0);  // Coloca el cursor en la parte superior de la pantalla
    //ssd1306_WriteString("ERROR:", Font_7x10, White);  // Comentado, posiblemente para mostrar un encabezado "ERROR"
    ssd1306_SetCursor(0, 15);  // Coloca el cursor en la segunda línea
    ssd1306_WriteString((char*)error_msg, Font_7x10, White);  // Muestra el mensaje de error pasado como argumento
    ssd1306_UpdateScreen();  // Actualiza la pantalla con el mensaje de error
    
    // Esperar un momento para que se vea el error
    HAL_Delay(1000);  // Pausa de 1 segundo para mostrar el error
    
    // Limpiar pantalla y dejarla lista para nuevo código
    ssd1306_Fill(Black);  // Limpia la pantalla
    ssd1306_SetCursor(0, 0);  // Coloca el cursor en la parte superior
    ssd1306_WriteString("Ingrese codigo:", Font_7x10, White);  // Muestra "Ingrese código:"
    ssd1306_UpdateScreen();  // Actualiza la pantalla
}

// Función para mostrar el estado de la puerta en la pantalla
void display_door_status(const char* status) {
    ssd1306_Fill(Black);  // Limpia la pantalla
    
    // Mostrar estado
    ssd1306_SetCursor(0, 0);  // Coloca el cursor en la parte superior
    ssd1306_WriteString("Estado:", Font_7x10, White);  // Muestra "Estado:"
    ssd1306_SetCursor(0, 15);  // Coloca el cursor en la segunda línea
    ssd1306_WriteString((char*)status, Font_7x10, White);  // Muestra el estado de la puerta
    ssd1306_UpdateScreen();  // Actualiza la pantalla con el estado
    
    display_timer = HAL_GetTick();  // Guarda el tiempo actual
    display_state = DISPLAY_WAIT;  // Cambia el estado a "esperando"
}

// Función para gestionar la actualización de la pantalla según el estado
void display_update(void) {
    switch(display_state) {
        case DISPLAY_WAIT:
            // Si han pasado 2 segundos desde que se mostró el último estado
            if((HAL_GetTick() - display_timer) >= 2000) {
                ssd1306_Fill(Black);  // Limpia la pantalla
                ssd1306_SetCursor(0, 0);  // Coloca el cursor en la parte superior
                ssd1306_WriteString("Ingrese codigo:", Font_7x10, White);  // Muestra "Ingrese código:"
                ssd1306_UpdateScreen();  // Actualiza la pantalla
                display_state = DISPLAY_IDLE;  // Cambia el estado a "inactivo"
            }
            break;
            
        case DISPLAY_IDLE:
        default:
            // Si el estado es inactivo, no se hace nada
            break;
    }
}