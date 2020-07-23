#ifndef DATA_STORAGE_H
#define DATA_STORAGE_H

#include <QObject>
#include <QVector>
#include <QIODevice>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QDate>
#include <QTime>

/*=======================================================================*/
/*
 Класс для хранения данных принимаемых от оборудования.
 Кадр последних данных добавляется в конец расщиряющихся массивов "double".
 Доступ к каждому массиву может быть по указателю - для отображения на графике,
чтения и записи на диск, данные хранятся только в оперативной памяти
 */
/*=======================================================================*/
class TDataStorage : public QObject
{
    Q_OBJECT
    //Максимальное число массивов данных
    //Защитное чисто для проверки двоичных файлов
    enum{
        MAX_ARRAYS_COUNT=20,
        BINARY_IO_MAGIC = 0x12345678,
    }TDataStorageConstants;

public:
    TDataStorage(int num_arrays, unsigned int maxInitialMemory, QObject * owner = 0);
    virtual ~TDataStorage();

    //Назначить названия для данных
    void setArrayName(int index, const QString &name);

    //Получить данные из массива
    double *dataPointer(int arrayIndex);

    //Получить значение количесва данных в массиве
    long getDataCount(){return dataCount;}

    //Добавляет новую строку данных к массивам
    int addDoubleDataFrame(double *newdata);

    //Значения минимума максимума
    //используется для массива значений времени
    double *dataMin;
    double *dataMax;

public slots:
    //Сохранить и загрузить данные
    void loadFile();
    void saveFile();
    //Очистить хранилище данных
    void clear();

private:
    //Управление памятью для массивов
    void allocateMemory(int numArrays);
    void freeMemory();

    //Перерасчет значений min, max для времени
    void recalculateMinMax();

    //Работа с потоком ввода - вывода для файлов
    int saveDataToDevice(QIODevice *outFile);
    int loadDataFromDevice(QIODevice *inFile);

    //Работа с потоком ввода - вывода в текстовом режиме
    int saveTextDataToDevice(QIODevice *outFile);
    int loadTextDataFromDevice(QIODevice *inFile);

    //Работа с потоком ввода - вывода через имя файла
    //Загрузка и сохранение в двоичном формате
    void saveDataToFile(const QString &filename);
    void loadDataFromFile(const QString &filename);
    //Загрузка и созранение в техстовом формате
    void saveTextDataToFile(const QString &filename);
    void loadTextDataFromFile(const QString &filename);

    //Создает автоназвание
    void createAutoFileName(QString *name);

protected:
    //Кол-во массивов данных
    int project_init_num_arrays;
    int numArrays;
    //Массивы всех данных
    QVector<double> *data;
    //Кол-во данных в каждом массиве
    long dataCount;

    //Список имен данных
    QStringList dataNames;
};
#endif // DATA_STORAGE_H
