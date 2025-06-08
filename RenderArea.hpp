#ifndef RENDERAREA_HPP
#define RENDERAREA_HPP

#include <QWidget>
#include <QString>

class RenderArea : public QWidget {

    Q_OBJECT

public:
    explicit RenderArea(QWidget* parent = nullptr);
    void setTextToDisplay(const QString& text);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    QString text;

};

#endif