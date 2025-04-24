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

// helper function to assign workers for a single day
bool assignDay(
    size_t idx,
    const AvailabilityMatrix& avail,
    size_t dailyNeed,
    size_t maxShifts,
    DailySchedule& sched,
    std::vector<int>& shifts,
    size_t day,
    std::vector<Worker_T>& today,
    size_t numWorkers
);

// recursive backtracking function to fill schedule day by day
bool backtrack(
    const AvailabilityMatrix& avail,
    size_t dailyNeed,
    size_t maxShifts,
    DailySchedule& sched,
    std::vector<int>& shifts,
    size_t day
)
{
    // base case - all days are filled
    if (day == avail.size()) {
        return true;
    }

    // prep to fill current day
    size_t numWorkers = avail[0].size();
    std::vector<Worker_T> today;

    // assign d workers for current day
    return assignDay(0, avail, dailyNeed, maxShifts, sched, shifts, day, today, numWorkers);
}

// recursive function to assign workers for a given day
bool assignDay(
    size_t idx,
    const AvailabilityMatrix& avail,
    size_t dailyNeed,
    size_t maxShifts,
    DailySchedule& sched,
    std::vector<int>& shifts,
    size_t day,
    std::vector<Worker_T>& today,
    size_t numWorkers
)
{
    // if selected enough workers for the day
    if (today.size() == dailyNeed) {
        // add today's workers to schedule
        sched.push_back(today);
        
        // recursively do it for next day
        if (backtrack(avail, dailyNeed, maxShifts, sched, shifts, day + 1)) {
            return true;
        }
        // if not, backtrackd
        sched.pop_back();
        return false;
    }

    // tries every worker for the current day
    for (Worker_T w = 0; w < numWorkers; ++w) {
        if (avail[day][w] && shifts[w] < (int)maxShifts && std::find(today.begin(), today.end(), w) == today.end()) {
            today.push_back(w);
            shifts[w]++;
            if (assignDay(idx + 1, avail, dailyNeed, maxShifts, sched, shifts, day, today, numWorkers)) {
                return true;
            }
            // backtrack
            today.pop_back();
            --shifts[w];
        }
    }
    return false;
}
// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    
    // checks if there's an empty matrix
    if (avail[0].empty()) return false;

    size_t numWorkers = avail[0].size();

    //tracks the number of shifts per worker
    std::vector<int> shifts(numWorkers, 0);

    return backtrack(avail, dailyNeed, maxShifts, sched, shifts, 0);
}

