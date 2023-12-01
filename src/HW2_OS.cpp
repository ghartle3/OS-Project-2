//===========================//
// Garrett Hartley
// Operating Systems HW2
// Fall 2023
//==========================//

#include <iostream>
#include <fstream>
using namespace std;

// Function prototype
void BankersAlgorithm(int num_process, int num_resource, int allocation[][3], int max[][3], int available[3]);

int main() {
    int num_process, num_resource;

    // Open the input file
    ifstream input_file("input.txt");
    if (!input_file.is_open()) {
        cerr << "Error opening the input file." << endl;
        return 1;
    }

    // Read the number of processes and resources
    input_file >> num_process >> num_resource;

    // Declare and read matrices and arrays
    int allocation[5][3], max[5][3], available[3];

    // Read allocation matrix
    for (int i = 0; i < num_process; ++i)
        for (int j = 0; j < num_resource; ++j)
            input_file >> allocation[i][j];

    // Read max matrix
    for (int i = 0; i < num_process; ++i)
        for (int j = 0; j < num_resource; ++j)
            input_file >> max[i][j];

    // Read available resources
    for (int i = 0; i < num_resource; ++i)
        input_file >> available[i];

    // Close the input file
    input_file.close();

    // Call BankersAlgorithm function
    BankersAlgorithm(num_process, num_resource, allocation, max, available);

    return 0;
}

void BankersAlgorithm(int num_process, int num_resource, int allocation[][3], int max[][3], int available[3]) {
    
    // Delcare array to hold flags
    int flag_array[num_process];
    for(int i = 0; i < num_process; ++i){
        flag_array[i] = 0;
    }

    // Declare array to hold the safe sequence 
    int safe_sequence[num_process];
    int ind = 0;

    // Calculate the need matrix
    int need[num_process][num_resource];
    for (int i = 0; i < num_process; ++i)
        for (int j = 0; j < num_resource; ++j)
            need[i][j] = max[i][j] - allocation[i][j];

    // Iterate through processes to find a safe sequence
    for (int i = 0; i < 5; ++i) {
        for (int process_index = 0; process_index < num_process; ++process_index) {
            if (flag_array[process_index] == 0) {
                int flag = 0;
                for (int resource_index = 0; resource_index < num_resource; ++resource_index) {
                    if (need[process_index][resource_index] > available[resource_index]) {
                        flag = 1;
                        break;
                    }
                }

                if (flag == 0) {
                    safe_sequence[ind++] = process_index;
                    for (int y = 0; y < num_resource; ++y)
                        available[y] += allocation[process_index][y];
                    flag_array[process_index] = 1;
                }
            }
        }
    }

    // Check if the sequence is safe and print the result
    int safe_flag = 1;
    for (int process_index = 0; process_index < num_process; ++process_index) {
        if (flag_array[process_index] == 0) {
            safe_flag = 0;
            cout << "Unsafe sequence";
            break;
        }
    }

    if (safe_flag == 1) {
        cout << "Safe sequence order:" << endl;
        for (int process_index = 0; process_index < num_process - 1; ++process_index)
            cout << " process:" << safe_sequence[process_index] << " ,";
        cout << " process:" << safe_sequence[num_process - 1] << endl;
    }
}
