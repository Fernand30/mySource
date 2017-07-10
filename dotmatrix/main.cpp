#include "maindialog.h"
#include <QApplication>
#include "mainwindow.h"
#include "qicon.h"
#include "qpixmap.h"


class MyApplication : public QApplication {
     public:
      MyApplication(int& argc, char ** argv) :
        QApplication(argc, argv) { }
      virtual ~MyApplication() { }

      // reimplemented from QApplication so we can throw exceptions in slots
      virtual bool notify(QObject * receiver, QEvent * event) {
        try {
          return QApplication::notify(receiver, event);
        } catch(std::exception& e) {
          qCritical() << "Exception thrown:" << e.what();
        }
        return false;
      }
};

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(images);

    MyApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.openImage(":/images/qt.png");
    return a.exec();
}
