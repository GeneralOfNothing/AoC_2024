# Advent of Code 2024 – C++ Solutions

This repository contains my solutions to the **Advent of Code 2024** challenges, implemented in C++.

## Getting Started

To build and run the solutions, follow these steps:

1. **Clone the Repository**  
   Clone the repository to your local machine:  
   ```bash
   git clone <repository-url>
   ```

2. **Build the Project**  
   Create a build directory and use CMake to configure and build the project:  
   ```bash
   mkdir Build
   cd Build
   ccmake ..
   cmake --build . --target BuildAll
   ```

3. **Prepare Puzzle Input**  
   Before running any solution, add your puzzle input to the `TestData` directory. Each day's solution expects an `XX_input.txt` file in the following location:  
   ```
   <BuildDirectory>/TestData/XX_input.txt
   ```
   XX should be replaced with the corresponding day. Day 5's input would be 05_input.txt for example.

## Notes

- Replace `<BuildDirectory>` with the path to your build directory (e.g., `Build` if following the example above).  
- Ensure that each `input.txt` file corresponds to the correct day's puzzle input.
