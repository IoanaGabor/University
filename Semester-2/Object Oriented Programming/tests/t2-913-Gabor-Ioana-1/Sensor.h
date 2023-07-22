//
// Created by ioana on 12.05.2023.
//

#ifndef T2_913_GABOR_IOANA_1_SENSOR_H
#define T2_913_GABOR_IOANA_1_SENSOR_H


#include <string>
#include <vector>

class Sensor {
protected:
    std::string producer;
public:
    const std::string &getProducer() const;

protected:
    std::vector<double> recordings;
public:
    Sensor(const std::string &producer, const std::vector<double> &recordings);
    virtual bool sendAlert()=0;
    virtual double getPrice()=0;
    virtual std::string toString();
};


#endif //T2_913_GABOR_IOANA_1_SENSOR_H
