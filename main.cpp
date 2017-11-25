#include <iostream>
#include "RushHourMgmt.h"

int main() {
    void test0();
    test0();

    void test1();
    test1();

    void test2();
    test2();

    return 0;
}

void test2(){

    RushHourMgmt mgmt;
    mgmt.AddTimeSpan(1.00, 3.00);
    mgmt.AddTimeSpan(5.00, 7.00);
    mgmt.AddTimeSpan(9.00, 11.00);
    mgmt.AddTimeSpan(13.00, 15.00);
    mgmt.AddTimeSpan(17.00, 19.00);
    mgmt.AddTimeSpan(21.00, 23.00);

    if(!(mgmt.GetSize() == 6))
        std::cout << mgmt.GetSize() << " 6" << std::endl;

    mgmt.AddTimeSpan(0.00, 23.00);

    if(!(mgmt.GetSize() == 1))
        std::cout << mgmt.GetSize() << " 1" << std::endl;

    std::cout << "Finished test 2" << std::endl;
}


void test1(){

    RushHourMgmt mgmt;
    mgmt.AddTimeSpan(1.00, 3.00);
    mgmt.AddTimeSpan(5.00, 7.00);
    mgmt.AddTimeSpan(9.00, 11.00);
    mgmt.AddTimeSpan(13.00, 15.00);
    mgmt.AddTimeSpan(17.00, 19.00);
    mgmt.AddTimeSpan(21.00, 23.00);

    if(!(mgmt.GetSize() == 6))
        std::cout << mgmt.GetSize() << " 6" << std::endl;

    mgmt.AddTimeSpan(0.00, 2.00);
    mgmt.AddTimeSpan(2.50, 5.00);
    mgmt.AddTimeSpan(7.00, 10.00);
    mgmt.AddTimeSpan(10.50, 13.30);
    mgmt.AddTimeSpan(14.00, 18.00);
    mgmt.AddTimeSpan(18.90, 21.30);
    mgmt.AddTimeSpan(20.00, 23.50);

    if(!(mgmt.GetSize() == 1))
        std::cout << mgmt.GetSize() << " 1" << std::endl;

    std::cout << "Finished test 1" << std::endl;
}

void test0(){

    float h = 0;
    void AssertNotRush(RushHourMgmt& mgmt, float h);
    void AssertRush(RushHourMgmt& mgmt, float h);
    RushHourMgmt mgmt;

    // 1. empty
    h = 0;
    AssertNotRush(mgmt, h);

    // 2.  12 -- 15
    mgmt.AddTimeSpan(12.00, 15.00);
    h = 13.00; AssertRush(mgmt, h);
    h = 12.00; AssertRush(mgmt, h);
    h = 15.00; AssertRush(mgmt, h);
    h = 11.00; AssertNotRush(mgmt, h);
    h = 16.00; AssertNotRush(mgmt, h);

    // 3. 11 -- 15
    mgmt.AddTimeSpan(11.00, 13.00);
    h = 13.00; AssertRush(mgmt, h);
    h = 11.00; AssertRush(mgmt, h);
    h = 15.00; AssertRush(mgmt, h);
    h = 10.00; AssertNotRush(mgmt, h);
    h = 16.00; AssertNotRush(mgmt, h);

    if(!(mgmt.GetSize() == 1))
        std::cout << mgmt.GetSize() << " 1" << std::endl;


    // 4. 11 -- 16
    mgmt.AddTimeSpan(14.00, 16.00);
    h = 13.00; AssertRush(mgmt, h);
    h = 11.00; AssertRush(mgmt, h);
    h = 16.00; AssertRush(mgmt, h);
    h = 10.00; AssertNotRush(mgmt, h);
    h = 17.00; AssertNotRush(mgmt, h);

    if(!(mgmt.GetSize() == 1))
        std::cout << mgmt.GetSize() << " 1" << std::endl;

    // 5. 11 -- 16
    mgmt.AddTimeSpan(14.00, 16.00);
    h = 13.00; AssertRush(mgmt, h);
    h = 11.00; AssertRush(mgmt, h);
    h = 16.00; AssertRush(mgmt, h);
    h = 10.00; AssertNotRush(mgmt, h);
    h = 17.00; AssertNotRush(mgmt, h);

    if(!(mgmt.GetSize() == 1))
        std::cout << mgmt.GetSize() << " 1" << std::endl;

    mgmt.AddTimeSpan(14.50, 14.55);
    h = 13.00; AssertRush(mgmt, h);
    h = 11.00; AssertRush(mgmt, h);
    h = 16.00; AssertRush(mgmt, h);
    h = 10.00; AssertNotRush(mgmt, h);
    h = 17.00; AssertNotRush(mgmt, h);

    if(!(mgmt.GetSize() == 1))
        std::cout << mgmt.GetSize() << " 1" << std::endl;

    // 6.  10 -- 17
    mgmt.AddTimeSpan(10.00, 17.00);

    h = 13.00; AssertRush(mgmt, h);
    h = 10.00; AssertRush(mgmt, h);
    h = 17.00; AssertRush(mgmt, h);
    h = 9.00; AssertNotRush(mgmt, h);
    h = 18.00; AssertNotRush(mgmt, h);

    if(!(mgmt.GetSize() == 1))
        std::cout << mgmt.GetSize() << " 1" << std::endl;

    // 7. 10 -- 17 , 19 -- 21
    mgmt.AddTimeSpan(19.00, 21.00);
    h = 10.00; AssertRush(mgmt, h);
    h = 15.00; AssertRush(mgmt, h);
    h = 17.00; AssertRush(mgmt, h);
    h = 19.00; AssertRush(mgmt, h);
    h = 20.00; AssertRush(mgmt, h);
    h = 21.00; AssertRush(mgmt, h);
    h = 9.00; AssertNotRush(mgmt, h);
    h = 18.00; AssertNotRush(mgmt, h);
    h = 22.00; AssertNotRush(mgmt, h);

    if(!(mgmt.GetSize() == 2))
        std::cout << mgmt.GetSize() << " 2" << std::endl;

    // 8. 10 -- 17 , 18 - 21
    mgmt.AddTimeSpan(18.00, 20.00);
    h = 10.00; AssertRush(mgmt, h);
    h = 15.00; AssertRush(mgmt, h);
    h = 17.00; AssertRush(mgmt, h);
    h = 18.00; AssertRush(mgmt, h);
    h = 20.00; AssertRush(mgmt, h);
    h = 21.00; AssertRush(mgmt, h);
    h = 9.00; AssertNotRush(mgmt, h);
    h = 17.50; AssertNotRush(mgmt, h);
    h = 22.00; AssertNotRush(mgmt, h);

    if(!(mgmt.GetSize() == 2))
        std::cout << mgmt.GetSize() << " 2" << std::endl;

    // 9. 10 -- 17.5 , 18 - 21
    mgmt.AddTimeSpan(17.00, 17.50);
    h = 10.00; AssertRush(mgmt, h);
    h = 17.00; AssertRush(mgmt, h);
    h = 15.00; AssertRush(mgmt, h);
    h = 18.00; AssertRush(mgmt, h);
    h = 20.00; AssertRush(mgmt, h);
    h = 21.00; AssertRush(mgmt, h);
    h = 17.50; AssertRush(mgmt, h);
    h = 17.55; AssertNotRush(mgmt, h);
    h = 9.00; AssertNotRush(mgmt, h);
    h = 22.00; AssertNotRush(mgmt, h);
    if(!(mgmt.GetSize() == 2))
        std::cout << mgmt.GetSize() << " 2" << std::endl;

    // 10. 10 -- 17.5 , 18 - 22
    mgmt.AddTimeSpan(18.00, 22.00);
    h = 10.00; AssertRush(mgmt, h);
    h = 17.00; AssertRush(mgmt, h);
    h = 15.00; AssertRush(mgmt, h);
    h = 18.00; AssertRush(mgmt, h);
    h = 20.00; AssertRush(mgmt, h);
    h = 22.00; AssertRush(mgmt, h);
    h = 17.50; AssertRush(mgmt, h);
    h = 17.55; AssertNotRush(mgmt, h);
    h = 9.00; AssertNotRush(mgmt, h);
    h = 23.00; AssertNotRush(mgmt, h);
    if(!(mgmt.GetSize() == 2))
        std::cout << mgmt.GetSize() << " 2" << std::endl;

    // 11. 9 -- 17.5 , 18 - 22
    mgmt.AddTimeSpan(9.00, 17.50);
    h = 9.00; AssertRush(mgmt, h);
    h = 17.00; AssertRush(mgmt, h);
    h = 15.00; AssertRush(mgmt, h);
    h = 18.00; AssertRush(mgmt, h);
    h = 20.00; AssertRush(mgmt, h);
    h = 22.00; AssertRush(mgmt, h);
    h = 17.50; AssertRush(mgmt, h);
    h = 17.55; AssertNotRush(mgmt, h);
    h = 8.88; AssertNotRush(mgmt, h);
    h = 23.00; AssertNotRush(mgmt, h);
    if(!(mgmt.GetSize() == 2))
        std::cout << mgmt.GetSize() << " 2" << std::endl;

    // 12. 9 -- 22
    mgmt.AddTimeSpan(13.00, 19.50);
    h = 9.00; AssertRush(mgmt, h);
    h = 22.00; AssertRush(mgmt, h);
    h = 17.00; AssertRush(mgmt, h);
    h = 8.00; AssertNotRush(mgmt, h);
    h = 23.00; AssertNotRush(mgmt, h);

    if(!(mgmt.GetSize() == 1))
        std::cout << mgmt.GetSize() << " 1" << std::endl;


    // 13. 6 -- 7, 9 -- 22, 22.5 - 22.67   --->  5 -- 23.5
    mgmt.AddTimeSpan(6.00, 7.00);
    mgmt.AddTimeSpan(22.50, 22.67);

    if(!(mgmt.GetSize() == 3))
        std::cout << mgmt.GetSize() << " 3" << std::endl;

    mgmt.AddTimeSpan(5.00, 23.5);
    h = 5.00; AssertRush(mgmt, h);
    h = 23.5; AssertRush(mgmt, h);
    h = 4.00; AssertNotRush(mgmt, h);
    h = 23.70; AssertNotRush(mgmt, h);

    if(!(mgmt.GetSize() == 1))
        std::cout << mgmt.GetSize() << " 1" << std::endl;

    std::cout << "Finished test 0" << std::endl;
}

void AssertNotRush(RushHourMgmt& mgmt, float h){
    if(mgmt.IsRushHour(h))
        std::cout << h << " " << mgmt.IsRushHour(h) << " 0" << std::endl;
}

void AssertRush(RushHourMgmt& mgmt, float h){
    if(!mgmt.IsRushHour(h))
        std::cout << h << " " << mgmt.IsRushHour(h) << " 1" << std::endl;
}