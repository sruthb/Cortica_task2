#ifndef CORTICA_TASK_2_RUSHHOURMGMT_H
#define CORTICA_TASK_2_RUSHHOURMGMT_H

#include <map>
#include <memory>
#include <exception>


/**
 *
 */
class RushHourMgmt {
public:
    typedef std::map<float, float> FloatMap;

    RushHourMgmt();
    void AddTimeSpan(float start_time, float end_time);
    bool IsRushHour(float time);
    int GetSize(); // for testing

private:

    bool isTimeValid(float time);

    std::unique_ptr<FloatMap> _map;

};



#endif //CORTICA_TASK_2_RUSHHOURMGMT_H
