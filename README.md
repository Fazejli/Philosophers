# 🧵 Philosophers — Dining Philosophers Problem

> Solving the classic concurrency problem using threads and mutexes in C.

![Score](https://img.shields.io/badge/Score-100%2F100-brightgreen?style=flat-square)
![Language](https://img.shields.io/badge/Language-C-00599C?style=flat-square&logo=c&logoColor=white)
![School](https://img.shields.io/badge/School-42-000000?style=flat-square)

---

## 📌 Overview

The **Dining Philosophers** is a classic computer science problem illustrating the challenges of concurrent programming: synchronization, deadlocks, race conditions, and resource sharing.

Each philosopher sits at a table, alternating between **thinking**, **eating**, and **sleeping**. To eat, they need two forks — but forks are shared between neighbors. The challenge: no philosopher should starve, and no deadlock should occur.

This project covers concepts that are directly relevant to **race condition exploits** and **concurrency vulnerabilities** in cybersecurity.

---

## 🚀 Usage

```bash
git clone https://github.com/Fazejli/philosophers.git
cd philosophers/philo
make
./philo [nb_philos] [time_to_die] [time_to_eat] [time_to_sleep] [nb_meals (optional)]
```

**Example:**
```bash
./philo 5 800 200 200       # 5 philosophers, must eat before 800ms
./philo 5 800 200 200 7     # Stop after each philosopher has eaten 7 times
```

---

## ⚙️ Implementation

**Mandatory (threads + mutexes):**
- Each philosopher is a **thread** (`pthread_create`)
- Each fork is a **mutex** (`pthread_mutex_t`)
- A monitor thread checks for deaths and meal counts

**Key rules:**
- Philosophers must not die of starvation
- No **deadlock** (philosophers waiting on each other forever)
- No **data races** (concurrent access to shared data must be protected)

```
Philosopher 1: think → take fork[1] → take fork[2] → eat → sleep → ...
Philosopher 2: think → take fork[2] → take fork[3] → eat → sleep → ...
...
```

---

## 📁 Project Structure

```
philosophers/
├── Makefile
├── philo.h
├── srcs/
    ├── init.c         # Initialize philosophers & forks
    ├── main.c
    ├── monitor.c      # Death & meal count monitoring
    ├── mutex_setters.c
    ├── routine.c      # Philosopher lifecycle
    ├── utils.c
    └── utils2.c
```

---

## 🧠 Key Concepts

- **Threads** — `pthread_create`, `pthread_join`
- **Mutexes** — `pthread_mutex_lock`, `pthread_mutex_unlock`
- **Race conditions** — concurrent access to shared memory
- **Deadlocks** — circular wait prevention strategies
- **Starvation prevention**
- **Timestamp precision** — `gettimeofday`, `usleep`
- Direct relevance to **concurrency vulnerabilities** in software security
