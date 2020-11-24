//before main
#include <chrono>
chrono::time_point<chrono::steady_clock> cl;
double current_time() { return (chrono::steady_clock::now() - cl).count() / 1e9; }



// at the beginning of main
cl = chrono::steady_clock::now();

// check time with
double cur_seconds = current_time();
