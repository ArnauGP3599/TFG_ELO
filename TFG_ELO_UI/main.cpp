#include "TFG_ELO_UI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TFG_ELO_UI w;
    w.show();
    return a.exec();
}
