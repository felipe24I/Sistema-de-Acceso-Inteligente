# Diagrama de Contexto
![Imagen de WhatsApp 2025-03-05 a las 16 35 15_918a26f7](https://github.com/user-attachments/assets/d28708ec-3eb0-4e88-9048-6630a63459af)


## Descripción
Muestra las interacciones del sistema con los actores externos:

### Actores
- **Usuario Local**: Interactúa directamente con el teclado matricial
  - Comandos principales: #*A*# (abrir), #*C*# (cerrar), #*1*# (estado), B (limpiar)
- **Usuario Remoto**: Envía comandos a través del ESP01/WiFi
- **PC Host**: Terminal de monitoreo y control vía UART2
- **ESP01**: Módulo WiFi para control remoto vía UART3

### Sistema de Acceso Inteligente
- Procesa comandos desde múltiples interfaces
- Proporciona feedback visual (display OLED y LEDs)
- **Controla físicamente** la puerta mediante un servomotor
- Mantiene comunicación bidireccional con sistemas externos
