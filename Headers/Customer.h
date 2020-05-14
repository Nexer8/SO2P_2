//
// Created by mwisniewski on 4/1/20.
//

#ifndef SO2P_2_CUSTOMER_H
#define SO2P_2_CUSTOMER_H


#include <memory>
#include <mutex>
#include "Salon.h"

static int current_customer_id = 0;

enum class Customers_state {
    WAITING_FOR_A_CUT,
    HAVING_A_HAIRCUT,
    DONE
};

/*! \class Customer
    \brief A class that imitates a client at hairdresser's salon.

    Customer that wants a haircut.
*/
class Customer {
private:
    int id;
public:
    std::shared_ptr<Salon> salon;
    std::mutex mutex;
    std::atomic<Customers_state> state;

    int get_id() { return id; }

    Customer();
};


#endif //SO2P_2_CUSTOMER_H
