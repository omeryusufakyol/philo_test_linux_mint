# 🧠 Philosophers

> A concurrency simulation of the classic *Dining Philosophers Problem*, implemented in C using POSIX threads and mutex synchronization.

---

## 📌 Project Overview

The **Dining Philosophers** problem is a classic synchronization problem often used to illustrate the challenges of multithreaded programming, such as **deadlocks**, **race conditions**, and **resource starvation**.

In this project, each philosopher is represented by a thread that cycles through **thinking**, **eating**, and **sleeping** states. They must acquire two forks (mutexes) to eat, which introduces a shared resource contention scenario — a perfect playground for solving real-world synchronization issues.

---

## 🛠️ Technologies Used

- **C programming language**
- **POSIX Threads (pthreads)**
- **Mutexes** for synchronization
- **Custom timing and printing utilities** to ensure precision
- Minimal standard library usage (in line with Ecole 42 restrictions)

---

## 🔄 Simulation Rules

Each philosopher:

- Thinks 🧠
- Takes the **left** and **right** forks 🍴
- Eats 🍝 for a defined amount of time
- Sleeps 😴
- Repeats the cycle until they die (lack of eating) or the simulation ends

The simulation ends when:

- A philosopher dies from starvation (i.e., doesn’t eat within `time_to_die`)
- All philosophers have eaten `x` times (if specified)

---

## ⚙️ How It Works

- Philosophers are created as **threads**
- Forks are shared **mutexes**, placed between each philosopher
- Custom `ft_usleep` and timestamp functions provide precise time control
- A **monitor thread** constantly checks whether a philosopher has died
- All accesses to shared variables (such as `last_meal`, `stop_simulation`) are **mutex-protected** to avoid data races

---

## 🚀 Usage

### 🧾 Compilation

```bash
make
```

To compile with ThreadSanitizer (for debugging race conditions):

```bash
make tsan
```

### ▶️ Running the simulation

```bash
./philo number_of_philos time_to_die time_to_eat time_to_sleep [number_of_times_each_philo_must_eat]
```

#### Example:

```bash
./philo 5 800 200 200
```

This runs a simulation with:

- 5 philosophers  
- Each dies if they don’t eat for 800ms  
- Eats for 200ms and sleeps for 200ms

---

## 📈 Example Output

```
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
0 3 has taken a fork
0 3 has taken a fork
0 3 is eating
1 4 has taken a fork
200 1 is sleeping
200 5 has taken a fork
200 3 is sleeping
200 4 has taken a fork
200 4 is eating
200 2 has taken a fork
200 2 has taken a fork
200 2 is eating
...
```

---

## 🧠 Learning Outcomes

- Handling **mutex deadlocks** and implementing **safe locking orders**  
- Building **thread-safe systems** in C  
- Writing **low-level timing utilities** without using `usleep` unsafely  
- Debugging with **ThreadSanitizer** and handling **data races**  
- Simulating **real-world resource contention**  

---

## 📁 Project Structure

```
philo/
├── arg_check.c
├── cleanup.c
├── init.c
├── main.c
├── Makefile
├── monitor.c
├── philo.h
├── routine.c
├── simulation.c
└── utils.c
```

---

## 👨‍💻 Author

- Ömer Yusuf Akyol  
- [LinkedIn](https://www.linkedin.com/in/%C3%B6mer-yusuf-akyol-843a62240)  
- [GitHub Profile](https://github.com/omeryusufakyol)

---

## 🏁 Status

✅ Project complete and thoroughly tested using ThreadSanitizer and edge case inputs.

---

## 📜 License

This project is part of the [Ecole 42](https://42.fr/en/homepage/) curriculum and adheres to their guidelines and restrictions.  
All code written from scratch without using disallowed standard functions.
