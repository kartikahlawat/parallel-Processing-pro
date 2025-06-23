Parallel Data Processing with Adaptive Thresholding and Energy Simulation
This project demonstrates a parallel data processing pipeline using OpenMP in C, simulating energy-aware computation with adaptive thresholds. It benchmarks performance and energy consumption across different input data sizes to analyze scalability and efficiency.

🧠 Features
Parallelized processing using OpenMP with dynamic scheduling

Adaptive thresholding based on input size

Simulated energy monitoring per thread

Dual-stage data transformation (process_stage1 and process_stage2)

Execution time and energy usage analysis across multiple data sizes

🛠 Requirements
C Compiler with OpenMP support (e.g., gcc)

Unix-based system or WSL (for timing functions)

Basic development tools (make, etc.)

📦 Compilation
To compile the code:

bash
Copy
Edit
gcc -fopenmp main.c -o energy_simulation -lm
🚀 Usage
Run the executable:

bash
Copy
Edit
./energy_simulation
You will get output like:

java
Copy
Edit
Data Size    Execution Time (s)    Energy Consumption (units)
100000       0.012345              192.500000
...
1000000      0.084532              938.300000
🧪 How It Works
Data Initialization: Each element is generated as sin(i) + cos(i/2.0)

Processing Logic:

If data > adaptive threshold → apply process_stage1

Else → apply process_stage2

Energy Simulation: Each thread simulates energy usage during computation

Parallel Execution: OpenMP handles workload distribution and energy aggregation

⚙️ Configuration
You can tweak:

Number of threads (num_threads)

Data sizes (data_sizes[])

Threshold logic (adaptive_threshold())

📊 Output Metrics
Execution Time: Measured using omp_get_wtime()

Energy Consumption: Simulated per iteration, aggregated per thread

📄 License
This project is open-source and available under the MIT License.

🙌 Acknowledgments
Inspired by energy-aware computing and parallel processing benchmarks.

Thanks to the OpenMP community and GNU tools.
