//
// Created by mwisniewski on 4/30/20.
//

#include <atomic>
#include <condition_variable>
#include <mutex>
#include "../Headers/Parameters.h"
#include "../Headers/Common.h"

atomic<int> no_of_ready_hairdressers = 0;
condition_variable CommonTools::cv;
mutex CommonTools::cv_m;

void CommonTools::wait_for_salons() {
    unique_lock<mutex> lk(cv_m);
    no_of_ready_hairdressers++;
    cv.wait(lk, [&] { return no_of_ready_hairdressers >= NUMBER_OF_SALONS * NUMBER_OF_HAIRDRESSERS_PER_SALON; });
    cv.notify_all();
}
