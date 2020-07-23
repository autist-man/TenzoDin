/*
Запуск приложения, настройка размера шрифта всего приложения, кодек для
подключения русского языка.
 */
/*================================================================*/
#include <QTextCodec>
#include "mainwindow.h"
/*================================================================*/
int main(int argc, char *argv[])
{
    //Кодеки для русского языка
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForTr(codec);

    //Создание приложения
    QApplication::setStyle(new QWindowsStyle);
    QApplication::setDesktopSettingsAware(false);
    QApplication *a = new QApplication(argc, argv);

    //Создание главного окна приложения
    MainWindow *w = new MainWindow;
    QObject::connect(w,SIGNAL(sgCloseApp()),a,SLOT(closeAllWindows()));
    a->setApplicationName("УДМ-600");
    w->show();


    return a->exec();
}
/*================================================================*/
