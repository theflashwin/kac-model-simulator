#include "simulator.hpp"
#include "RenderArea.hpp" // we now need the full definition
#include <QDebug>

#include <iostream>
#include <random>
#include <string>
#include <format>

void runSimulation(const QString &p1,
                   const QString &p2,
                   RenderArea *output)
{

    // Sanitize Inputs
    bool ok1 = false, ok2 = false;
    int num_particles = p1.trimmed().toInt(&ok1);
    int num_experiments = p2.trimmed().toInt(&ok2);

    if (!ok1 || !ok2)
    {
        output->setTextToDisplay("Could not Parse Inputs.");
        return;
    }

    // range checks
    if (num_experiments <= 0 || num_particles <= 0)
    {
        output->setTextToDisplay("Values must be > 0");
        return;
    }

    // run simulation
    // create RNG, seed using hardware entropy
    std::mt19937 rng(std::random_device{}());

    // create our distributions
    std::uniform_int_distribution<int> position_dist(0, num_particles);
    std::uniform_int_distribution<int> winner_dist(0, 1); // change to bitwise random

    // array to store state
    std::vector<int> state(num_particles, 1);

    int last_collision = 1;
    long long num_iter = 0;

    while (last_collision != num_particles)
    {

        num_iter++;

        // find two random indices
        int position_one = position_dist(rng);
        int position_two = position_dist(rng);

        if (position_one == position_two)
            continue;

        // choose a winner
        int winner = winner_dist(rng);

        if (winner == 0)
        { // position one wins

            state[position_one] += state[position_two];
            last_collision = state[position_one];

            state[position_two] = 0;
        }
        else
        { // posiiton two wins

            state[position_two] += state[position_one];
            last_collision = state[position_two];

            state[position_one] = 0;
        }
    }


    QString msg = QString("Simulation finished. Number of iterations: %1")
              .arg(num_iter);
output->setTextToDisplay(msg);
}
