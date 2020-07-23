#ifndef FIRFILTER_H
#define FIRFILTER_H

#include <QObject>
#include <QDebug>
 #include <QDialog>
#include <QLabel>
#include <QHBoxLayout>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QSettings>
#include <QPointer>
class FirFilter : public QObject
{
    Q_OBJECT
public:
    enum FILTER_INDEX{
        FILTER_O6,
        FILTER_O36,
        FILTER_O196,
    };

    FirFilter();
    ~FirFilter();
    //Функции сохранения и загрузки настроек
    void saveSettings(QSettings *settings, const QString &groupName);
    void loadSettings(QSettings *settings, const QString &groupName);
    void setValuesFirFilterFromFile(const QString &nameFile);

    //Функция фильтраци значений
    int32_t fir_filter_get_value(int32_t new_sample);

    //Возвращает номер фильтра, нужно для настройки вкладки
   //в главном окне приложения "Настройка КИХ-фильтра"
    int8_t getNumberFilter() const;

public slots:
    //Функия, меняет фильтр на другой, при переключении в настройках
    void changed(int8_t number);
private slots:
    void slCloseApp();
signals:
    void closeApp();

private:
    //Структура фильтра
    typedef struct {
        int32_t *filter;
        int32_t *samples;
        int numSamples;
        int samplePosition;
         }TFirFilter_int;

   //Название файла с коэффицентами.
   QString nameFileCoefficientsFilter;
   int8_t numberFilter;

   //Очищает значения фильтра
   void fir_filter_clear();

   TFirFilter_int *fir_filter_n;

   //Флан для установки значений фильтров,
   //если значения не установлены или изменены
   bool flagNewSamples;
};

#endif // FIRFILTER_H
