# Mall Management System 🏬  

## 📌 Overview  
This project is a **Mall Management System** implemented in **C++**.  
It simulates the operations of a shopping mall, including:  

- 🛡️ **Security Management** (Guards, shifts, and schedules)  
- 🏬 **Outlet Management** (Add, delete, and display outlets per floor)  
- 🎮 **Gaming Zone** (Play games, track revenue)  
- 🚗 **Parking System** (Park, remove, search vehicles in a 5x5 grid)  

The program uses **linked lists**, **stacks**, **arrays**, and **basic file handling techniques** to demonstrate **Data Structures and Algorithms (DSA)** concepts in a real-world scenario.  

---

## ⚙️ Features  

### 🔐 Security Management  
- Add guards with **validation** (alphabets only for names, digits only for contacts).  
- Auto-assign random shifts (**Morning, Afternoon, Night**).  
- Display guard schedules.  
- Rotate guard shifts using a **stack**.  

### 🏢 Outlet Management  
- Add outlets to specific floors (1–5).  
- Each floor has a different rent value.  
- Floor 3 is **restricted only for Food outlets**.  
- Delete outlets by name.  
- Display all outlets on a floor using a **linked list**.  

### 🎮 Gaming Zone  
- Available Games:  
  - Air Hockey ($5/hr)  
  - VR Racing ($10/hr)  
  - Bowling ($8/hr)  
  - Shooting Game ($6.5/hr)  
  - Arcade Basketball ($7/hr)  
- Customers can play games and revenue is calculated.  
- Total revenue tracking feature.  

### 🚙 Parking System  
- 5x5 Parking grid.  
- Prevents duplicate vehicle numbers.  
- Supports **Truck, Car, Bike** with different fee structures.  
- Enter, Exit, and Search vehicles.  
- Display current parking grid visually.  

---

## 🛠️ Technologies Used  
- **Language:** C++  
- **Data Structures:**  
  - Linked List (Outlets per floor)  
  - Stack (Guard shift rotation)  
  - Arrays (Guards, Parking Grid, Games)  

---

## ▶️ How to Run  

### 1️⃣ Clone Repository  
```bash
git clone https://github.com/yourusername/mall-management-system.git
cd mall-management-system
2️⃣ Compile the Program
bash
Copy
Edit
g++ mall_management.cpp -o mall
3️⃣ Run the Program
bash
Copy
Edit
./mall
🧑‍💻 Sample Menu
text
Copy
Edit
=== Mall Management System ===
1. Security Management
2. Outlet Management
3. Gaming Zone
4. Parking System
5. Exit
Enter your choice: 
📚 Concepts Covered
✔️ Object-Oriented Programming (Structs)
✔️ Linked Lists (Outlet Management)
✔️ Stack (Guard Shifts)
✔️ Arrays (Parking Grid, Guards, Games)
✔️ Input Validation
✔️ Real-world Simulation
