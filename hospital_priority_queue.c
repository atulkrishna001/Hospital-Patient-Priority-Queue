#include <stdio.h>
#include <string.h>

#define MAX 100

struct Patient {
    char name[50];
    int priority;
};

struct Patient heap[MAX];
int size = 0;

// Swap two patients
void swap(struct Patient *a, struct Patient *b) {
    struct Patient temp = *a;
    *a = *b;
    *b = temp;
}

// Add a patient to the priority queue
void addPatient(char name[], int priority) {
    if (size >= MAX) {
        printf("Queue is full!\n");
        return;
    }

    strcpy(heap[size].name, name);
    heap[size].priority = priority;

    int i = size;
    size++;

    // Move patient upward according to priority
    while (i > 0) {
        int parent = (i - 1) / 2;

        if (heap[parent].priority <= heap[i].priority)
            break;

        swap(&heap[parent], &heap[i]);
        i = parent;
    }

    printf("Patient %s added successfully.\n", name);
}

// Treat the patient with highest priority
void treatNextPatient() {
    if (size == 0) {
        printf("No patients waiting.\n");
        return;
    }

    printf("Treating Patient: %s | Priority: %d\n",
           heap[0].name, heap[0].priority);

    // Replace root with last patient
    heap[0] = heap[size - 1];
    size--;

    // Move patient downward
    int i = 0;

    while (1) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;

        if (left < size &&
            heap[left].priority < heap[smallest].priority)
            smallest = left;

        if (right < size &&
            heap[right].priority < heap[smallest].priority)
            smallest = right;

        if (smallest == i)
            break;

        swap(&heap[i], &heap[smallest]);
        i = smallest;
    }
}

int main() {
    // Step 3 test data
    addPatient("P1", 3);
    addPatient("P2", 1);
    addPatient("P3", 2);
    addPatient("P4", 1);
    addPatient("P5", 3);
    addPatient("P6", 2);

    printf("\nTreatment Order:\n");

    while (size > 0) {
        treatNextPatient();
    }

    // Second test
    printf("\nSecond Test:\n");

    addPatient("P1", 3);
    addPatient("P2", 2);
    addPatient("P3", 3);

    printf("\nTreating 2 patients:\n");
    treatNextPatient();
    treatNextPatient();

    // New emergency patient
    printf("\nAdding new Emergency Patient:\n");
    addPatient("Emergency_Patient", 1);

    printf("\nRemaining Treatment Order:\n");

    while (size > 0) {
        treatNextPatient();
    }

    return 0;
}
