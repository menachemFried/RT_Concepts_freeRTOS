# Project Rules

- All code and code comments must be written in English.
- Code must be well-commented.

# Project Structure Context

- The root directory is the main Git repository.
- `RT_Concepts_freeRTOS`: This is the target directory where CubeMX generates the project code and where the `.ioc` file is located. CubeIDE compiles the project directly from this directory.
- `RT_Concepts_freeRTOS/UserApp`: Custom user code (e.g., manual MemoryPool definitions) should be placed here to prevent it from being overwritten when CubeMX regenerates the project.
- `Cube_F7_V1.17.4`: This directory contains the shared STM32 driver libraries used by CubeMX.
- `Docs`: This directory contains the final project instructions for the course.

# Architecture Guidelines

## UART Logging (DMA-based)
- A dedicated `LoggerTask` must handle all UART transmissions.
- Other tasks must not use blocking UART calls. Instead, they should allocate memory for their string from a custom MemoryPool (in `UserApp`), write the log message, and push the pointer to a `LogQueue`.
- The `LoggerTask` will pend on the `LogQueue`, transmit the message using `HAL_UART_Transmit_DMA`, and block using a Task Notification or Binary Semaphore until the `HAL_UART_TxCpltCallback` interrupt fires.
- Once the transmission is complete, the `LoggerTask` must free the allocated MemoryPool block.
- CubeMX must be configured to enable UART TX DMA (Normal mode) and UART global interrupts.
