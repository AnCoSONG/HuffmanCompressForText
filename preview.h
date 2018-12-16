#ifndef PREVIEW_H
#define PREVIEW_H

#include <QWidget>
#include <QGraphicsEffect>

namespace Ui {
class Preview;
}

class Preview : public QWidget
{
    Q_OBJECT

public:
    explicit Preview(QWidget *parent = nullptr);
    ~Preview();

private slots:
    void on_pushButton_close_clicked();

private:
    Ui::Preview *ui;
};

#endif // PREVIEW_H
