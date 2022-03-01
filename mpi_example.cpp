#include <mpi.h>
#include <iostream>
#include "backward.hpp"

int main() {
    MPI_Init(NULL, NULL);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    backward::SignalHandling sh;
    char* ptr = (char*)42;
    if (rank % 2 == 0) {
        int v [[maybe_unused]] = *ptr;
    }
    MPI_Finalize();
    return 0;
}
