#include <iostream>
class bank_worker_bad {
public:
    bool saving_account(const char* name, int num) {
        // to do something
        return true;
    }
    bool withdraw_account(const char* name, int num) {
        // to do something
        return true;
    }
    bool transfer_account(const char* one_name, const char* other_name, int num) {
        // to do something
        return true;
    }
    // to add some new functions
    bool process_credit_card(const char* id, const char* name) {
        // to do something
        return true;
    }
};

struct saving_account {
    bool operator() (const char* name, int num) {
        std::cout << "name:" << name << " save:" << num << std::endl;
        return true;
    }
};
struct withdraw_account {
    bool operator() (const char* name, int num) {
        std::cout << "name:" << name << " withdraw:" << num << std::endl;
        return true;
    }
};
struct transfer_account {
    bool operator() (const char* one_name, const char* other_name, int num) {
        std::cout << "name:" << one_name << " transfer to:" << other_name << " num:" << num << std::endl;
        return true;
    }
};
struct process_credit_card {
    bool operator() (const char* id, const char* name) {
        std::cout << "card id:" << id << " for user:" << name << "created ok!" << std::endl;
        return true;
    }
};
// not need to change
class bank_worker {
public:
    template <typename operation, typename... Args>
    bool interface(operation op, Args... args) {
        op(args...);
    }
};
int main() {
    bank_worker bw;
    bw.interface(saving_account{}, "zhangsan", 1000);
    bw.interface(withdraw_account{}, "zhangsan", 100);
    bw.interface(transfer_account{}, "zhangsan", "lisi", 1000);
    bw.interface(process_credit_card{}, "AB000001", "lisi");

    return 0;
}