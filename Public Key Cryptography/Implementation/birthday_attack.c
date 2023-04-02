#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>

// Define a custom hash table entry to store input-output pairs
typedef struct Entry {
    uint64_t output;
    uint64_t input;
    struct Entry *next;
} Entry;

// Function to hash the output value (simple modulo-based hash)
uint64_t hash_output(uint64_t output, uint64_t hash_table_size) {
    return output % hash_table_size;
}

// Function to insert a new input-output pair into the hash table
void insert_entry(Entry **hash_table, uint64_t output, uint64_t input, uint64_t hash_table_size) {
    uint64_t index = hash_output(output, hash_table_size);
    Entry *new_entry = (Entry *)malloc(sizeof(Entry));
    new_entry->output = output;
    new_entry->input = input;
    new_entry->next = hash_table[index];
    hash_table[index] = new_entry;
}

// Function to search for an output value in the hash table and return the corresponding input value
uint64_t find_entry(Entry **hash_table, uint64_t output, uint64_t hash_table_size) {
    uint64_t index = hash_output(output, hash_table_size);
    Entry *entry = hash_table[index];
    while (entry) {
        if (entry->output == output) {
            return entry->input;
        }
        entry = entry->next;
    }
    return 0;
}

// Dummy one-way function for demonstration purposes (replace with your desired function)
uint64_t one_way_function(uint64_t input) {
    return input * 6364136223846793005 + 1442695040888963407; // Simple example using a linear congruential generator
}

// Function to perform the birthday attack
void birthday_attack(uint64_t (*f)(uint64_t), uint64_t hash_table_size) {
    Entry **hash_table = (Entry **)calloc(hash_table_size, sizeof(Entry *));
    while (1) {
        uint64_t x = rand(); // Generate a random input value (replace with a better random number generator if needed)
        uint64_t y = f(x); // Compute the output value

        // Check if the output value is in the hash table
        uint64_t x2 = find_entry(hash_table, y, hash_table_size);
        if (x2) {
            printf("Collision found: (x1, x2) = (%lu, %lu)\n", x, x2);
            break;
        } else {
            insert_entry(hash_table, y, x, hash_table_size);
        }
    }

    // Free memory allocated for the hash table
    for (uint64_t i = 0; i < hash_table_size; ++i) {
        Entry *entry = hash_table[i];
        while (entry) {
            Entry *next_entry = entry->next;
            free(entry);
            entry = next_entry;
        }
    }
    free(hash_table);
}

int main() {
    uint64_t hash_table_size = 10000000; // Set the hash table size
    srand(time(NULL)); // Seed the random number generator
    clock_t start = clock();
    birthday_attack(one_way_function, hash_table_size);
    clock_t end = clock();
    printf("Time: %lf\n", (double)(end - start) / CLOCKS_PER_SEC);
    return 0;
}
