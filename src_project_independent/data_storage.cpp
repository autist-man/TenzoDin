#include "data_storage.h"
/*=======================================================================*/
TDataStorage::TDataStorage(int num_arrays, unsigned int maxInitialMemory, QObject * owner)
    : QObject(owner)
{
    project_init_num_arrays = num_arrays;
    numArrays = num_arrays;
    int newSize = maxInitialMemory/(num_arrays*sizeof(double));
    allocateMemory(num_arrays);
    for(int i = 0; i < numArrays; i++)
    {
        data[i].resize(newSize);
    }
    clear();
}
/*=======================================================================*/
TDataStorage::~TDataStorage()
{
    freeMemory();
}
/*=======================================================================*/
void TDataStorage::allocateMemory(int numArrays)
{
    Q_ASSERT(numArrays > 0);
    Q_ASSERT(numArrays < MAX_ARRAYS_COUNT);
    if(numArrays < project_init_num_arrays) numArrays = project_init_num_arrays;
    data = new QVector<double>[numArrays];

    dataMin = new double;
    dataMax = new double;
    dataCount = 0;

    for(int n = 0; n < numArrays; n++){
        dataNames.append(QString("column %1").arg(n));
    }
}
/*=======================================================================*/
void TDataStorage::freeMemory()
{
    delete[] data;
    delete dataMin;
    delete dataMax;
    dataNames.clear();
}
/*=======================================================================*/
void TDataStorage::setArrayName(int index, const QString &name)
{
    if(index < numArrays) dataNames[index] = name;
}
/*=======================================================================*/
double* TDataStorage::dataPointer(int arrayIndex)
{
    Q_ASSERT(arrayIndex >= 0);
    Q_ASSERT(arrayIndex < MAX_ARRAYS_COUNT);
    Q_ASSERT(arrayIndex < numArrays);
    return data[arrayIndex].data();
}
/*=======================================================================*/
int TDataStorage::addDoubleDataFrame(double *newdata)
{
    int i;
    long newSize = ((dataCount + 1) / 100000 + 1 ) * 100000;
    if (newSize > data[0].size()) {
        for(i = 0; i < numArrays; i++){
            data[i].resize(newSize);
        }
    }
    for(i = 0; i < numArrays; i++){
        data[i][dataCount] = newdata[i];
        if(dataCount == 0){
            *dataMin = newdata[0];
            *dataMax = newdata[0];
        }else {
            if(*dataMin > newdata[0]) *dataMin = newdata[0];
            if(*dataMax < newdata[0]) *dataMax = newdata[0];
        }
    }
    dataCount++;
    return 0;
}
/*=======================================================================*/
int TDataStorage::saveDataToDevice(QIODevice *outFile)
{
    qint32 temp, IOerror = 0;

    Q_ASSERT(outFile);
    QDataStream s(outFile);
    s << (qint32)BINARY_IO_MAGIC;     if(s.status()) IOerror--;
    s << (qint32)numArrays;      if(s.status()) IOerror--;
    s << (qint32)dataCount;      if(s.status()) IOerror--;
    long dataSize = dataCount*sizeof(double);
    for(temp = 0; temp < numArrays; temp++){
        if(s.writeRawData((char *)data[temp].data(), dataSize) != dataSize)IOerror--;
    }
    return IOerror;
}
/*=======================================================================*/
int TDataStorage::loadDataFromDevice(QIODevice *inFile)
{

    qint32 temp,fileNumArrays;
    qint32 magic;

    Q_ASSERT(inFile);
    QDataStream s(inFile);
    s >> magic;
    if(magic != BINARY_IO_MAGIC) return -1;
    s >> fileNumArrays;
    s >> temp;
    if(fileNumArrays >= MAX_ARRAYS_COUNT && fileNumArrays <= 0)return -1;
    freeMemory();
    allocateMemory(fileNumArrays);
    dataCount = temp;
    long dataSize = dataCount*sizeof(double);

    for(temp = 0; temp < fileNumArrays; temp++){
        data[temp].resize(dataCount+10);
        if(data[temp].size() > dataCount)
            if(inFile->read((char *)data[temp].data(),dataSize) != dataSize){
                clear();
                return -3;
        }
    }
    recalculateMinMax();
    return 0;
}
/*=======================================================================*/
int TDataStorage::saveTextDataToDevice(QIODevice *outFile)
{
    qint32 n,i,IOerror = 0;

    Q_ASSERT(outFile);
    QTextStream s(outFile);
    s.setRealNumberNotation(QTextStream::FixedNotation);
    s.setRealNumberPrecision(3);
    for(n = 0; n < numArrays; n++){
        s << dataNames[n] << ";";
        if(s.status()) IOerror--;
        if(IOerror) break;
    }
    s <<  "\n";
    s.setRealNumberNotation(QTextStream::FixedNotation);
    s.setRealNumberPrecision(8);

    for(n = 0; n < dataCount; n++){
        for(i = 0; i < numArrays; i++){
            s << data[i][n]<< ";";
            if(s.status())IOerror--;
            if(IOerror)break;
        }
        s << "\n";
        if(s.status())IOerror--;
    }
    if(IOerror){
    }
    return IOerror;
}
/*=======================================================================*/
int TDataStorage::loadTextDataFromDevice(QIODevice *inFile)
{
    double dataPack[MAX_ARRAYS_COUNT];
    qint32 fileNumArrays,i,IOerror = 0;
    QString str;
    Q_ASSERT(inFile);
    QTextStream s(inFile);
    s.setRealNumberNotation(QTextStream::FixedNotation);
    s.setRealNumberPrecision(3);

    str = s.readLine(2048);
    QStringList strList = str.split(';',QString::SkipEmptyParts);
    fileNumArrays = strList.count();
    if(fileNumArrays > MAX_ARRAYS_COUNT) fileNumArrays = MAX_ARRAYS_COUNT;
    freeMemory();
    allocateMemory(fileNumArrays);
    for(i = 0; i < fileNumArrays; i++) setArrayName(i,strList[i]);

    while(!s.atEnd()){
        str = s.readLine(2048);
        if(s.status())IOerror--;
        strList = str.split(';');
        for(i = 0; i < numArrays; i++) dataPack[i] = strList[i].toDouble();
        addDoubleDataFrame(dataPack);
    }
    return IOerror;
}
/*=======================================================================*/
void TDataStorage::recalculateMinMax()
{
    int n;
        *dataMin = data[0][0];
       * dataMax = data[0][0];

    for(n = 1; n < dataCount; n++){
            if(*dataMin > data[0][n]) *dataMin = data[0][n];
            if(*dataMax < data[0][n]) *dataMax = data[0][n];
    }
}
/*=======================================================================*/
void TDataStorage::saveDataToFile(const QString &filename)
{
    QFile *dataFile = new QFile (filename);
    dataFile->open(QIODevice::WriteOnly);
    saveDataToDevice(dataFile);
    dataFile->close();
    delete dataFile;
}
/*================================================================*/
void TDataStorage::saveTextDataToFile(const QString &filename)
{
    QFile *dataFile = new QFile (filename);
    dataFile->open(QIODevice::WriteOnly);
    saveTextDataToDevice(dataFile);
    dataFile->close();
    delete dataFile;
}
/*================================================================*/
void TDataStorage::loadDataFromFile(const QString &filename)
{
    QFile *dataFile = new QFile (filename);
    dataFile->open(QIODevice::ReadOnly);
    loadDataFromDevice(dataFile);
    dataFile->close();
    delete dataFile;
}
/*================================================================*/
void TDataStorage::loadTextDataFromFile(const QString &filename)
{
    QFile *dataFile = new QFile (filename);
    dataFile->open(QIODevice::ReadOnly);
    loadTextDataFromDevice(dataFile);
    dataFile->close();
    delete dataFile;
}
/*================================================================*/
void TDataStorage::createAutoFileName(QString *name)
{
    if(!name){
        return;
    }
    *name = QDate::currentDate ().toString("autosave yyyy_MM_dd_")+QTime::currentTime () .toString("hh_mm_ss")+".txtd";
}
/*======================================================================*/
void TDataStorage::loadFile()
{
    QString fileName = QFileDialog::getOpenFileName(0, tr("Load File"),"./", tr("Test data (*.txtd *.euss)"));
    if(!fileName.isEmpty()){
        if(fileName.endsWith(".txtd"))loadTextDataFromFile(fileName);
        else if(fileName.endsWith(".euss"))loadDataFromFile(fileName);
    }
}
/*======================================================================*/
void TDataStorage::saveFile()
{
    QString autoName;
    createAutoFileName(&autoName);
    QString fileName = QFileDialog::getSaveFileName(0, tr("Save File"), autoName,
                                                    tr("Test data (*.txtd);;Test Data (*.euss)"));
    if(!fileName.isEmpty()){
        if(fileName.endsWith(".txtd"))saveTextDataToFile(fileName);
        else if(fileName.endsWith(".euss"))saveDataToFile(fileName);
        else {
            fileName+=".txtd";
            saveTextDataToFile(fileName);
        }
    }
}
/*======================================================================*/
void TDataStorage::clear()
{
    for(int i = 0; i < numArrays; i++){
        data[i].resize(1000);
    }
    *dataMin = 0;
    *dataMax= 0;
    dataCount = 0;
}
/*=======================================================================*/
