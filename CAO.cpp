#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

double process_stage1(double data) {
    return pow(data, 2) * log(data + 1);
}

double process_stage2(double data) {
    return sqrt(data) + sin(data) * cos(data);
}

double energy_monitor() {
    return (rand() % 20 + 80) / 10.0; // Simulated energy consumption between 8 and 10 units
}

double adaptive_threshold(int data_size) {
    return data_size > 500000 ? 0.5 : 1.5;
}

int main() {
    int num_trials = 10;
    int data_sizes[] = {100000, 200000, 300000, 400000, 500000, 600000, 700000, 800000, 900000, 1000000};
    double execution_times[num_trials];
    double energy_consumptions[num_trials];
    int num_threads = 8;
    
    srand(time(NULL)); // Initialize random seed
    omp_set_num_threads(num_threads); // Set thread count once before execution

    for (int t = 0; t < num_trials; t++) {
        int data_size = data_sizes[t];
        double *data = (double *)malloc(data_size * sizeof(double));
        double *processed_data = (double *)malloc(data_size * sizeof(double));

        if (!data || !processed_data) {
            printf("Memory allocation failed\n");
            exit(1);
        }
        
        for (int i = 0; i < data_size; i++) {
            data[i] = sin(i) + cos(i / 2.0);
        }
        
        double start_time = omp_get_wtime();
        double start_energy = 0.0, end_energy = 0.0;

        double threshold = adaptive_threshold(data_size);
        
        #pragma omp parallel
        {
            double local_energy = 0.0; // Per-thread energy monitoring
            #pragma omp for schedule(dynamic)
            for (int i = 0; i < data_size; i++) {
                local_energy += energy_monitor(); // Simulated per-operation energy
                if (data[i] > threshold) {
                    processed_data[i] = process_stage1(data[i]);
                } else {
                    processed_data[i] = process_stage2(data[i]);
                }
            }
            #pragma omp atomic
            end_energy += local_energy; // Accumulate energy usage
        }

        double execution_time = omp_get_wtime() - start_time;
        
        execution_times[t] = execution_time;
        energy_consumptions[t] = end_energy - start_energy; // Proper energy tracking
        
        free(data);
        free(processed_data);
    }

    printf("Data Size\tExecution Time (s)\tEnergy Consumption (units)\n");
    for (int t = 0; t < num_trials; t++) {
        printf("%d\t\t%f\t\t%f\n", data_sizes[t], execution_times[t], energy_consumptions[t]);
    }

    return 0;
}
