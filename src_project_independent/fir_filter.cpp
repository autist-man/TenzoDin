#include "fir_filter.h"

FirFilter::FirFilter()
{
     //Характеристики цифрового фильтра
     fir_filter_n = new TFirFilter_int;
     fir_filter_n->filter = 0;
     fir_filter_n->samples = 0;
     fir_filter_n->numSamples = 0;
     fir_filter_n->samplePosition = 0;

     //Имя файла с коэффициентами фильтра, имеется
     //три файла (три разряда фильтра) с коэффициентами,
     //кофффициенты загружаются из файла, и дальше по ним
     //расчитываются характеристики фильтра
     nameFileCoefficientsFilter = "";
     numberFilter = 0;
     flagNewSamples = true;
}
/*================================================================*/
FirFilter::~FirFilter()
{
    delete fir_filter_n;
}
/*================================================================*/
void FirFilter::saveSettings(QSettings *settings, const QString &groupName)
{
    if(!settings)
    {
        return;
    }

    settings->beginGroup(groupName);
    settings->setValue("file_name_coefficient_filter", nameFileCoefficientsFilter);
    settings->setValue("number_of_filter", numberFilter);
    settings->endGroup();
}
/*================================================================*/
void FirFilter::loadSettings(QSettings *settings, const QString &groupName)
{
    if(!settings){
        return;
    }
    settings->beginGroup(groupName);
    nameFileCoefficientsFilter = settings->value("file_name_coefficient_filter",
                                                 "fir_filter_o6.txt").toString();
    numberFilter = settings->value("number_of_filter", FILTER_O6).toInt();
    settings->endGroup();

    setValuesFirFilterFromFile(nameFileCoefficientsFilter);
}
/*================================================================*/
void FirFilter::setValuesFirFilterFromFile(const QString &nameFile)
{
    if(nameFile.isEmpty())
    {
        return;
    }

        QFile file(nameFile);

        QTextStream out(&file);
       if(file.open(QFile::ReadOnly))
       {
            QString str;
            while(!out.atEnd())
            {
                QString tempStr;
                tempStr = out.readLine();
                str.append(tempStr);
            }

             QStringList listValues;
             listValues = str.split(',', QString::SkipEmptyParts);


             fir_filter_n->filter = new int32_t[listValues.size()];
             fir_filter_n->samples = new int32_t[listValues.size()];
             for(int i = 0; i < listValues.size(); ++i)
             {
                 fir_filter_n->filter[i] =  listValues.at(i).toInt();
             }
             fir_filter_n->numSamples = listValues.size();

             file.close();
       } else
       {
             QDialog *d_error = new QDialog();
             d_error->setModal(true);
             QLabel *message = new QLabel;
             message->setWordWrap(true);
             message->setText("Ошибка. Файлы с коэффициентами фильтра"
                              " не найдены в папке проекта. Пожалуйста, добавьте файлы содержащие коэффициенты с именами:"
                              "fir_filter_o6.txt, fir_filter_o36.txt, fir_filter_o196.txt");
             QHBoxLayout *layout = new QHBoxLayout;
             layout->addWidget(message);
             d_error->setLayout(layout);
             d_error->show();
             connect(d_error,SIGNAL(rejected()),this,SLOT(slCloseApp()));
       }
}
/*================================================================*/
int8_t FirFilter::getNumberFilter() const
{
    return numberFilter;
}
/*================================================================*/
void FirFilter::changed(int8_t number)
{
    nameFileCoefficientsFilter.clear();
    switch (number)
    {
        case FILTER_O6:
                    nameFileCoefficientsFilter = "fir_filter_o6.txt";
                    numberFilter = number;
            break;
        case FILTER_O36:
                    nameFileCoefficientsFilter = "fir_filter_o36.txt";
                    numberFilter = number;
            break;
        case FILTER_O196:
                    nameFileCoefficientsFilter = "fir_filter_o196.txt";
                    numberFilter = number;
            break;
    }

    flagNewSamples = true;
    fir_filter_clear();
    setValuesFirFilterFromFile(nameFileCoefficientsFilter);
}
/*================================================================*/
void FirFilter::slCloseApp()
{
    emit closeApp();
}
/*================================================================*/
void FirFilter::fir_filter_clear()
{
    delete[] fir_filter_n->filter;
    fir_filter_n->filter = 0;
    delete[] fir_filter_n->samples;
    fir_filter_n->samples = 0;
    fir_filter_n->numSamples = 0;
    fir_filter_n->samplePosition = 0;
}
/*================================================================*/
int32_t FirFilter::fir_filter_get_value(int32_t new_sample)
{
    if(flagNewSamples)
    {
        for(int i = 0; i < fir_filter_n->numSamples; ++i)
        {
              fir_filter_n->samples[i] = new_sample;
        }
        flagNewSamples = false;
    }


    fir_filter_n->samples[fir_filter_n->samplePosition] = new_sample;
    fir_filter_n->samplePosition--;
    if(fir_filter_n->samplePosition < 0) fir_filter_n->samplePosition = fir_filter_n->numSamples - 1;

    int i;
    int64_t sym = 0;
    int64_t v1, v2;
    int32_t * filt_k = fir_filter_n->filter;
    int32_t * smpls = fir_filter_n->samples+fir_filter_n->samplePosition;

    int s_pos=fir_filter_n->samplePosition;

    for (i = fir_filter_n->numSamples - s_pos; i > 0; i--){
        v1 = *(filt_k++);
        v2 = *(smpls++);
        sym +=  v1 * v2;
    }
    smpls = fir_filter_n->samples;
    for (i = s_pos; i > 0; i--){
        v1 = *(filt_k++);
        v2 = *(smpls++);
        sym +=  v1 * v2;
    }

    return sym>>16;
}
