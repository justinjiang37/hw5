#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool scheduleHelper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    vector<int> workerShifts,
    int day,
    int shift
);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0){
        return false;
    }
    sched.clear();
    // Add your code below

    // init dimensions for sched
    for (int i = 0; i < avail.size(); i++) {
        vector<Worker_T> temp; 
        for (int j = 0; j < dailyNeed; j++) {
            temp.push_back(-1);
        }
        sched.push_back(temp);
    }
    // init all vals in workerShifts to 0
    vector<int> workerShifts(avail[0].size(), 0);
    return scheduleHelper(avail, dailyNeed, maxShifts, sched, workerShifts, 0, 0);
}

bool scheduleHelper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    vector<int> workerShifts,
    int day,
    int shift
)
{
    // reached all successfully placed
    if (day == avail.size()) {
        return true;
    }
    
    // loop through all the workers availabilities
    for (int w = 0; w < avail[0].size(); w++) {
        // check contraints
        if (workerShifts[w] < maxShifts && avail[day][w] == 1) {

            // Check if already working
            bool scheduled = false;
            for (int i = 0; i < shift; i++) {
                // if current worker w is already found
                if (w == sched[day][i]) {
                    scheduled = true;
                    break;
                }
            }
            if (scheduled) {
                continue;
            }

            workerShifts[w]++;
            sched[day][shift] = w;

            bool nextPosWorks = false;
            // Current filled, move to next slot
            if (shift == dailyNeed-1) {
                // for (int i = 0; i < sched.size(); i++) {
                //     for (int j = 0; j < sched[0].size(); j++) {
                //         cout << sched[i][j] << " ";
                //     }
                //     cout << endl;
                // }
                // cout << "===============" << endl;
                nextPosWorks = scheduleHelper(avail, dailyNeed, maxShifts, sched, workerShifts, day+1, 0);
            } else {
                // for (int i = 0; i < sched.size(); i++) {
                //     for (int j = 0; j < sched[0].size(); j++) {
                //         cout << sched[i][j] << " ";
                //     }
                //     cout << endl;
                // }
                // cout << "===============" << endl;
                nextPosWorks = scheduleHelper(avail, dailyNeed, maxShifts, sched, workerShifts, day, shift+1);
            }

            if (nextPosWorks) {
                return true;
            }

            // backtrack to previous location
            // remove from current location
            sched[day][shift] = -1;
            workerShifts[w]--;
        }
    }

    // no worker works, there for unsolvable
    return false;
}
