#include "linear_converter_f.h"
/*================================================================*/
float lc_convert_adc_to_value(const float *adc, float *ref_adc , float *ref_value, const int *num_ref_points )
{
    float k;
    //Поиск куска, внутри которого находится значение АЦП
    //экстраполирует в меньшую сторону по крайнему отрезку
    for(int i = 1; i < *num_ref_points; i++){
        if(*adc < ref_adc[i]){
            //Наклон прямой
            k = (ref_value[i] - ref_value[i-1]) / (ref_adc[i] - ref_adc[i-1]);
            return ref_value[i-1] + k * ((*adc)-ref_adc[i-1]);
            }
    }
    k = (ref_value[(*num_ref_points)-1] - ref_value[(*num_ref_points)-2])
            / (ref_adc[(*num_ref_points)-1] - ref_adc[(*num_ref_points)-2]);
    return ref_value[(*num_ref_points)-2] + k * ((*adc)-ref_adc[(*num_ref_points)-2]);
}
/*================================================================*/
