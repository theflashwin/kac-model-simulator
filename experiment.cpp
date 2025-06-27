#include <iostream>
#include <random>
#include <string>
#include <fstream>

using std::cout;
using std::endl;
using std::string;
using std::vector;

long long run_simulation(
    int num_particles, 
    std::mt19937 &rng, 
    std::uniform_int_distribution<int> &winner_dist
) {

    std::uniform_int_distribution<int> position_dist(0, num_particles);

    // array to store state
    std::vector<int> state(num_particles, 1);

    int last_collision = 1;
    long long num_iter = 0;

    while (last_collision != num_particles) {

        num_iter++;

        // find two random indices
        int position_one = position_dist(rng);
        int position_two = position_dist(rng);

        if (position_one == position_two) continue;

        // choose a winner
        int winner = winner_dist(rng);
        
        if (winner == 0) { // position one wins

            state[position_one] += state[position_two];
            last_collision = state[position_one];

            state[position_two] = 0;

        } else { // posiiton two wins

            state[position_two] += state[position_one];
            last_collision = state[position_two];
            
            state[position_one] = 0;
        }

    }

    return num_iter;
}

int main(int argc, char* argv[]) {

    // check for valid invocation
    // start_particles end_particles num_experiments step_size
    if (argc < 5) {
        std::cout << "Must provide 4 args" << std::endl;
        return 0;
    }

    // get arguments from command line
    int start_particles = std::stoi(argv[1]);
    int end_particles = std::stoi(argv[2]);
    int num_experiments = std::stoi(argv[3]);
    int step_size = std::stoi(argv[4]);

    // verify inputs
    if (start_particles > end_particles) {
        cout << "Start particles must be less than or equal to end_particles" << endl;
        return 0;
    }

    if (start_particles < 0 || end_particles < 0) {
        cout << "Number of particles cannot be negative" << endl;
        return 0;
    }

    if (num_experiments < 1) {
        cout << "Must run at least one experiment" << endl;
        return 0;
    }
    
    // create RNG, seed using hardware entropy
    std::mt19937 rng(std::random_device{}());

    // create our distributions
    // std::uniform_int_distribution<int> position_dist(0, num_particles);
    std::uniform_int_distribution<int> winner_dist(0, 1);

    int n = (end_particles - start_particles) / step_size;
    vector<long long> data(n, 0);

    // for each particle size, run x simulations
    for (int num_particles = start_particles; num_particles < end_particles; num_particles+=step_size) {

        long long sum = 0;
        for (int i = 0; i < num_experiments; i++) {
            sum += run_simulation(num_particles, rng, winner_dist);
        }
        data[num_particles / start_particles] = sum / num_experiments;

    }

    // write the data in data vector to a file
    // write the data to a CSV file
    std::ofstream outfile("output.csv");
    if (!outfile.is_open()) {
        std::cerr << "Failed to open output.csv for writing." << std::endl;
        return 1;
    }

    // write CSV header
    outfile << "num_particles,average_iterations\n";

    int idx = 0;
    for (int num_particles = start_particles; num_particles < end_particles; num_particles += step_size) {
        outfile << num_particles << "," << data[idx++] << "\n";
    }

    outfile.close();
    cout << "Simulation results written to output.csv" << endl;


}