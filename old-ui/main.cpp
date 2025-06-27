// main.cpp
#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "RenderArea.hpp"   // ← new
#include "simulator.hpp"    // runSimulation declaration

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // ---------- window shell ----------
    QWidget window;
    window.setWindowTitle("Simulation UI");
    window.resize(800, 450);

    // ---------- sidebar ----------
    QVBoxLayout* sidebarLayout = new QVBoxLayout;

    QLineEdit* input1 = new QLineEdit;
    QLineEdit* input2 = new QLineEdit;

    input1->setPlaceholderText("Parameter 1");
    input2->setPlaceholderText("Parameter 2");

    QPushButton* runButton = new QPushButton("Run");

    sidebarLayout->addWidget(input1);
    sidebarLayout->addWidget(input2);
    sidebarLayout->addWidget(runButton);
    sidebarLayout->addStretch();

    QWidget* sidebarWidget = new QWidget;
    sidebarWidget->setLayout(sidebarLayout);
    sidebarWidget->setFixedWidth(200);

    // ---------- render area on the right ----------
    RenderArea* renderArea = new RenderArea;   // our custom widget

    // ---------- top-level layout ----------
    QHBoxLayout* mainLayout = new QHBoxLayout;
    mainLayout->addWidget(sidebarWidget);
    mainLayout->addWidget(renderArea, /*stretch=*/1); // stretch so it grows
    window.setLayout(mainLayout);

    // ---------- hook up the Run button ----------
    QObject::connect(runButton, &QPushButton::clicked, [&]() {
        runSimulation(input1->text(),      // param 1
                      input2->text(),      // param 2
                      renderArea);         // where to display results
    });

    window.show();
    return app.exec();
}
