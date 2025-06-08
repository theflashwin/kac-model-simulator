#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include <QString>

// forward-declare to avoid including the whole header
class RenderArea;

void runSimulation(const QString& p1,
                   const QString& p2,
                   RenderArea* output);

#endif
