#include "RenderArea.hpp"
#include <QPainter>

RenderArea::RenderArea(QWidget* parent)
    : QWidget(parent), text("Nothing yet") {}

void RenderArea::setTextToDisplay(const QString& t) {
    text = t;
    update();  // triggers repaint
}

void RenderArea::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // fill background
    painter.fillRect(rect(), Qt::white);

    // draw text
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 16));
    painter.drawText(rect(), Qt::AlignCenter, text);

    // in future: draw shapes, graphs, etc.
}
