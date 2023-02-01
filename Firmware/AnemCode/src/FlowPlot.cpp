#include <Arduino.h>
#include <GyverOLED.h>
#include "FlowPlot.h"

template <uint8_t _counts>
FlowPlot<_counts>::FlowPlot() {}

template <uint8_t _counts>
FlowPlot<_counts>::~FlowPlot() {}

template <uint8_t _counts>
bool FlowPlot<_counts>::init(uint8_t _height, float _v_min, float _v_max, boolean _auto_expand) {
    height_= _height;
    counter_ = 0;
    auto_expand_ = _auto_expand;
    return setRanges(_v_min, _v_max);
}


template <uint8_t _counts>
uint8_t FlowPlot<_counts>::get_point_height(uint16_t _flow) {
    uint8_t flow_point_height;

    if (_flow >= v_max_range_) {
        flow_point_height = 0;
    }
    else if (_flow <= v_min_range_) {
        flow_point_height = height_;
    }
    else {
        flow_point_height = (uint16_t)height_*(uint16_t)(v_max_range_ - _flow)/(uint16_t)(v_max_range_ - v_min_range_);
    }
    return flow_point_height;
}

template <uint8_t _counts>
void FlowPlot<_counts>::pushValue(float _flow) {
    uint16_t flow_int;

    flow_int = _flow * 10;
    flow_sum_ += flow_int;

    if (auto_expand_) {
        v_min_range_ = min(v_min_range_, flow_int);
        v_max_range_ = max(v_max_range_, flow_int);
        for (uint8_t i=0; i < counter_; i++) {
            points_[i] = get_point_height(values_[i]);
        }
    }
    
    if (counter_ < _counts-1) {
        counter_++;
    }
    else {
        flow_sum_ -= values_[0];
        for (uint8_t i = 0; i < counter_; i++) {
            values_[i] = values_[i+1];
            points_[i] = points_[i+1];
        }
    }
    values_[counter_] = flow_int;
    points_[counter_] = get_point_height(flow_int);
    
    mean_flow_ = flow_sum_/counter_;
}

template <uint8_t _counts>
void FlowPlot<_counts>::setAutoexpand(boolean _auto_expand) {
    auto_expand_ = _auto_expand;
}

template <uint8_t _counts>
float FlowPlot<_counts>::getMeanFlow(void) {
    return (float)mean_flow_/10.0;
}

template <uint8_t _counts>
float FlowPlot<_counts>::getMinRange(void) {
    return (float)v_min_range_/10.0;
}

template <uint8_t _counts>
float FlowPlot<_counts>::getMaxRange(void) {
    return (float)v_max_range_/10.0;
}

template <uint8_t _counts>
bool FlowPlot<_counts>::setRanges(float _v_min, float _v_max) {
    if(_v_min >= _v_max) {
        v_min_range_ = 0;
        v_max_range_ = _v_min * 10;
        auto_expand_ = true;
    }
    else {
        v_min_range_ = _v_min * 10;
        v_max_range_ = _v_max * 10 + 10;
    }

    for (uint8_t i=0; i < counter_; i++) {
        points_[i] = get_point_height(values_[i]);
    }
    return auto_expand_;
}

template <uint8_t _counts>
void FlowPlot<_counts>::clearData (void) {
    counter_ = 0;
    for (uint8_t i = 0; i < _counts; i++) {
        values_[i] = v_min_range_;
        points_[i] = height_;
    }
}

template <uint8_t _counts>
const uint8_t* FlowPlot<_counts>::getFlows(void) const{
    return values_;
}

template <uint8_t _counts>
const uint8_t* FlowPlot<_counts>::getPoints(void) const{
    return points_;
}
