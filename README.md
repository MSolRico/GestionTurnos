# Proyecto GestionTurnos

Este es un proyecto de gestión de turnos desarrollado en C++. A continuación se detallan las instrucciones para configurar el proyecto y las dependencias necesarias.

## Requisitos

Asegúrate de tener instalado lo siguiente:

- Visual Studio (versión recomendada: 2019 o superior)
- XAMPP
- Git

## Instalación de dependencias

Este proyecto depende de las siguientes bibliotecas:

1. **MySQL Connector/C++**: Para conectar con bases de datos MySQL.
   - [Descargar MySQL Connector/C++](https://dev.mysql.com/downloads/connector/cpp/)
   - Después de descargarlo, asegúrate de agregar la ruta de las bibliotecas a tu proyecto en Visual Studio.
   - Pega en tu proyecto el archivo `mysqlcppconn.lib`, que se encuentra en `\lib64\vs14`.
   - Pega en tu proyecto el archivo `libcrypto-1_1-x64.dll` o `libcrypto-3-x64.dll`, que se encuentran en `\lib64`.
   - Pega en tu proyecto el archivo `libssl-1_1-x64.dll` o `libssl-3-x64.dll`, que se encuentran en `\lib64`.

2. **MySQL Server**: Para la gestión de bases de datos.
   - [Descargar MySQL Server](https://dev.mysql.com/downloads/mysql/)
   - Asegúrate de incluir las bibliotecas `libmysql.dll` y `libmysql.lib`, que se encuentran en `\lib` del directorio de instalación de MySQL.

