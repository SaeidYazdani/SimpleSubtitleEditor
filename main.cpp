#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QDebug>

#include "cue.h"
#include "vttparser.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "SimpleSubtitleEditor_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }


    auto printCue = [&](const Cue& c){
        qDebug().nospace() << "Cue #" << c.index()
                           << "\tBegin: " << c.begin().count()
                           << "\t\tEnd: " << c.end().count()
                           << "\t\tDuration: " << c.duration().count()
                           << "\tText Length: " << c.text().length();
    };


    Cue cue{1, 100ms, 137ms, "hahaha"};
    printCue(cue);
    cue.reduceBy(50ms);
    printCue(cue);
    cue.increaseBy(100ms);
    printCue(cue);

    std::vector<Cue> cv;
    qDebug() << "Before parsing vector size is: " << cv.capacity();
    getCues("d:\\test.vtt", cv);
    qDebug() << "After parsing vector size is: " << cv.capacity();






    MainWindow w;
    w.show();

    return a.exec();
}
