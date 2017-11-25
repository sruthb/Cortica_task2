#include <iostream>
#include "RushHourMgmt.h"

using std::min;
using std::max;
using std::unique_ptr;
using std::cerr;
using std::endl;
using std::prev;

/**
 *   IsRushHour   O(logn)
 *
 *   Returns true if given time is within the time frame of a time span in the map
 *   Uses Map upper_bound() to get the position in which given time span would be inserted,
 *   were it to be inserted, and checks the neighbour element to see if it contains given time.
 *
 * @param time
 * @return true if given time is within the time frame of a time span in the map
 */
bool RushHourMgmt::IsRushHour(float time) {

    if(!isTimeValid(time)) {
        cerr << "Given time " << time << " is not valid. Skipping " << endl;
        return false;
    }

    bool isRush = false;
    // get the first element with startTime > time
    auto i = _map->upper_bound(time);
    // if beginning of _map was returned, then given time is not in any time span
    if(i != _map->begin()){
        // get the previous element
        auto &prev_i = *prev(i);
        // check if given time is in range
        isRush = (prev_i.second >= time);
    }
    return isRush;
}

/**
 *
 *   AddTimeSpan    O(logn)
 *
 *    Adds a time span such that there are no duplicates.
 *    Uses Map upper_bound() to get the position in which given time span would be inserted,
 *    and merges overlapping elements if necessary.
 *
 * @param start_time
 * @param end_time
 */
void RushHourMgmt::AddTimeSpan(float start_time, float end_time){

    if(end_time < start_time) {
        cerr << "AddTimeSpan: end_time " << end_time << " is earlier than start_time " << start_time << ", skipping " << endl;
        return;
    }
    if(!isTimeValid(start_time)) {
        cerr << "Given time " << start_time << " is not valid. Skipping " << endl;
        return;
    }
    if(!isTimeValid(end_time)) {
        cerr << "Given time " << end_time << " is not valid. Skipping " << endl;
        return;
    }

    float new_end = end_time;
    float new_start = start_time;

    // get the first element with start time > x, for x = start_time, x = end_time
    auto i = _map->upper_bound(start_time);
    auto j = _map->upper_bound(end_time);

    if(i != _map->begin()){
        // look at the previous element and check if start_time is within its range
        auto &prev_i = *prev(i);
        // calculate the new effective start time
        if(start_time <= prev_i.second)
            new_start = min(start_time, prev_i.first);
    }
    if(j != _map->begin()){
        // look at the previous element and check if end_time is within its range
        auto &prev_j = *prev(j);
        // calculate the new effective end time
        if(end_time >= prev_j.first)
            new_end = max(end_time, prev_j.second);
    }

    _map->erase(i,j); // erase uneeded elemets
    (*_map)[new_start] = new_end;  // create/update new element
}

/**
 *
 * @param time
 * @return
 */
bool RushHourMgmt::isTimeValid(float time){
    return (time >= 0 && time < 24);
}

// for testing
int RushHourMgmt::GetSize() {
    return _map->size();
}

RushHourMgmt::RushHourMgmt() {
    _map = unique_ptr<FloatMap>(new FloatMap());
}
