# OSAL (Operating System Abstraction Layer)

A lightweight and portable OS abstraction layer for embedded systems.

This module provides a simple interface to isolate OS-specific features
such as delays, locking, and ISR detection from application and driver code.

---

## ✨ Features

- Works with:
  - Bare-metal systems
  - FreeRTOS
  - Zephyr (future support)
- Minimal API
- Easy to port
- No dynamic memory required
- Optional features (only implement what you need)

---

## 📂 Project Structure

```plaintext
osal/
├── include/
│ └── osal.h
├── src/
│ └── osal.c
├── template/
│ ├── osal_baremetal.c.example
│ └── osal_freertos.c.example

```

---

## 🚀 Getting Started

### 1. Copy OSAL into your project

```

Modules/
└── osal/

```
### 2. Choose your platform

```c
Copy the template:

Bare-metal
cp template/osal_baremetal.c.example port/osal/osal_baremetal.c
FreeRTOS
cp template/osal_freertos.c.example port/osal/osal_freertos.c

```
### 3. Include in build

Add to your build system:

include/osal.h
src/osal.c
port/osal/osal_<platform>.c

### 🧩 Usage Example

#include "osal.h"

static osal_t osal;

void app_init(void)
{
    osal_init(&osal, &get_osal_freertos_ops());

    osal.ops->delay_ms(10);
}
### 🧠 API Overview
Initialize
osal_init(&osal, &osal_ops);
Delay
osal.ops->delay_ms(100);
Lock / Unlock
osal.ops->lock();
osal.ops->unlock();
ISR check
if (osal.ops->is_isr())
{
    // ISR context
}
### ⚙️ Design Notes
The OSAL uses a function pointer table (osal_ops_t)
Each platform provides its own implementation
Core code remains OS-independent
### 🔧 Custom Porting

To add support for a new platform:

Copy a template file
Implement required functions
Provide your osal_ops_t
### 📌 Notes
delay_ns() is optional (not supported on most RTOS)
lock() / unlock() can use:
interrupt disable (bare-metal)
mutex / critical section (RTOS)
### 📜 License
This project is licensed under the MIT License. See LICENSE