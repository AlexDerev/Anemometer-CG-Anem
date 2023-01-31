#ifndef FlowPlot_h
#define FlowPlot_h


template <uint8_t _counts>
class FlowPlot {
private:
    uint8_t counter_;           //текущая позиция заполнения массивов
    uint16_t flow_sum_;         //накопительная сумма для среднего значения скорости
    uint8_t points_[_counts];   //массив значений, пересчитанный в точки графика (расстояние точки от верхней границы)
    uint16_t values_[_counts];  //массив значений скоростей потока в целых, т.е. скорость * 10
    uint16_t mean_flow_;        //Среднее начение отсчетов на графике
    uint8_t height_;            //высота графика в точках, необходима для пересчета скорости в точки графика
    uint16_t v_min_range_;      //значение скорости для нижней границы графика
    uint16_t v_max_range_;      //значение скорости для верхней границы графика
    boolean auto_expand_;       //признак автоматического расширения значений границ в зависимости от отсчетов
    uint8_t get_point_height(uint16_t _flow);   //расчет расстояния точки от верхнего края в зависимости от высоты графика, переданной скорости и лимитов границ

public:
    FlowPlot();
    ~FlowPlot();
    bool init(uint8_t _height, float _v_min = 0, float _v_max = 0, boolean _auto_expand = false);   //задание начальных значений
    void pushValue(float _flow);                                                                    //добавление нового отсчета скорости в массив и пересчет в точку графика
    void setAutoexpand(boolean _auto_expand);                                                       //фиксированные границы (false), расширяемые границы (true)
    float getMeanFlow(void);                                                                        //получение среднего значения скорости
    float getMinRange(void);                                                                        //получение текущего значения для нижней границы графика
    float getMaxRange(void);                                                                        //получение текущего значения для верхней границы графика
    bool setRanges(float _v_min, float _v_max);                                                     //задание границ графика
    void clearData(void);                                                                           //"очистка" данных
    const uint8_t* getFlows(void) const;                                                            //возвращает указатель на массив значений скорости
    const uint8_t* getPoints(void) const;                                                           ////возвращает указатель на массив значений точек
};
#endif


