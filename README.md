# AXSEM SDCC Development Environment

Docker-based development environment for AXSEM microcontrollers using SDCC 3.6.0 compiler.



# Contents

The axsem libraries are available inside the container at:

```
/opt/axsem/
|-- libax5031
|   |-- arm
|   |-- buildarm
|   |-- buildiar
|   |-- buildkeil
|   |-- buildkeilx
|   |-- buildsdcc
|   |-- doc
|   |-- iar
|   |-- include
|   |-- keil
|   |-- keil2
|   |-- sdcc
|   `-- source
|-- libax5042
|   |-- arm
|   |-- buildarm
|   |-- buildiar
|   |-- buildkeil
|   |-- buildkeilx
|   |-- buildsdcc
|   |-- doc
|   |-- iar
|   |-- include
|   |-- keil
|   |-- keil2
|   |-- sdcc
|   `-- source
|-- libax5043
|   |-- arm
|   |-- buildarm
|   |-- buildiar
|   |-- buildkeil
|   |-- buildkeilx
|   |-- buildsdcc
|   |-- doc
|   |-- iar
|   |-- include
|   |-- keil
|   |-- keil2
|   |-- sdcc
|   `-- source
|-- libax5051
|   |-- arm
|   |-- buildarm
|   |-- buildiar
|   |-- buildkeil
|   |-- buildkeilx
|   |-- buildsdcc
|   |-- doc
|   |-- iar
|   |-- include
|   |-- keil
|   |-- keil2
|   |-- sdcc
|   `-- source
|-- libaxdsp
|   |-- buildiar
|   |-- buildkeil
|   |-- buildkeilx
|   |-- buildsdcc
|   |-- builtsource
|   |-- doc
|   |-- iar
|   |-- include
|   |-- keil
|   |-- keil2
|   |-- sdcc
|   `-- source
|-- libaxdvk2
|   |-- arm
|   |-- buildarm
|   |-- buildiar
|   |-- buildkeil
|   |-- buildkeilx
|   |-- buildsdcc
|   |-- builtsource
|   |-- doc
|   |-- iar
|   |-- include
|   |-- keil
|   |-- keil2
|   |-- sdcc
|   `-- source
|-- libmf
|   |-- arm
|   |-- buildarm
|   |-- buildiar
|   |-- buildkeil
|   |-- buildkeilx
|   |-- buildsdcc
|   |-- builtsource
|   |-- doc
|   |-- iar
|   |-- include
|   |   `-- CMSIS_5
|   |       |-- CMSIS
|   |       |   |-- Core
|   |       |   |   `-- Include
|   |       |   `-- Utilities
|   |       |       |-- Linux-gcc-4.4.4
|   |       |       |-- Linux-gcc-4.8.3
|   |       |       `-- Win32
|   |       `-- Device
|   |           `-- ARM
|   |               |-- ARMCM0plus
|   |               |   |-- Include
|   |               |   `-- Source
|   |               |       |-- ARM
|   |               |       |-- GCC
|   |               |       `-- IAR
|   |               `-- SVD
|   |-- keil
|   |-- keil2
|   |-- sdcc
|   `-- source
|       `-- CMSIS_5
|           |-- CMSIS
|           |   |-- Core
|           |   |   `-- Include
|           |   `-- Utilities
|           |       |-- Linux-gcc-4.4.4
|           |       |-- Linux-gcc-4.8.3
|           |       `-- Win32
|           `-- Device
|               `-- ARM
|                   |-- ARMCM0plus
|                   |   |-- Include
|                   |   `-- Source
|                   |       |-- ARM
|                   |       |-- GCC
|                   |       `-- IAR
|                   `-- SVD
|-- libmfcrypto
|   |-- arm
|   |-- buildarm
|   |-- buildiar
|   |-- buildkeil
|   |-- buildkeilx
|   |-- buildsdcc
|   |-- doc
|   |-- iar
|   |-- include
|   |-- keil
|   |-- keil2
|   |-- sdcc
|   `-- source
|-- libmfdbg
|-- libmfdbg-devel
|   `-- include
|       |-- lib
|       |   `-- pkgconfig
|       |-- libmfdbg
|       `-- sigc++-2.0
|           `-- sigc++
|               |-- adaptors
|               `-- functors
`-- libreent
    |-- buildsdcc
    |-- sdcc
    `-- source
```