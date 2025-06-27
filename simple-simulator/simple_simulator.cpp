#include <iostream>
#include <random>
#include <string>

void print_state(std::vector<int> &state) {

    for (int count : state) {
        std::cout << count << " ";
    }

    std::cout << std::endl;

}

int main(int argc, char* argv[]) {
        
    // check for valid invocation
    if (argc < 2) {
        std::cout << "Must provide an argument (number of initial particles)" << std::endl;
        return 0;
    }

    // get arguments from command line
    int num_particles = std::stoi(argv[1]);

    if (num_particles <= 0) {
        std::cout << "Number of Particles must be greater than 0" << std::endl;
    }
    
    // create RNG, seed using hardware entropy
    std::mt19937 rng(std::random_device{}());

    // create our distributions
    std::uniform_int_distribution<int> position_dist(0, num_particles);
    std::uniform_int_distribution<int> winner_dist(0, 1);

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
        
        if (num_iter % 10 == 0) {
            print_state(state);
        }

    }

    std::cout << "SIMULATION FINISHED" << std::endl;
    std::cout << "" << std::endl;

    std::cout << "SIMULATION FINISHED" << std::endl;
    std::cout << "Number of Iterations: " << num_iter << std::endl;

}