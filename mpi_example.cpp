#include <chrono>
#include <mpi.h>
#include <iostream>
#include <thread>
#include "backward.hpp"

void bar(int rank) {
    if (rank % 2 == 0) {
        char* ptr = (char*)42;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        int v [[maybe_unused]] = *ptr;
    } else {
        MPI_Send(nullptr, 1, MPI_INT, -1, 0, MPI_COMM_WORLD);
    }
}

void foo(int rank) {
    bar(rank);
}

int main() {
    MPI_Init(NULL, NULL);
    backward::MPIErrorHandler mpi_error_handler(MPI_COMM_WORLD);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    backward::SignalHandling sh;
    foo(rank);
    MPI_Finalize();
    return 0;
}
