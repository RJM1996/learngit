#include "date.h"

void Date_cal(char* arg)
{
    size_t year = 0;
    size_t month = 0;
    size_t day = 0;
    int num = 0;
    // year=2018&month=7&day=19&nums=100
    sscanf(arg, "year=%lu&month=%lu&day=%lu&nums=%d", &year, &month, &day, &num); 
    Date d1(year, month, day);
    Date d2 = d1 + num;
    printf("%lu-%lu-%lu\nafter %d days is:\n", year, month, day, num);
    d2.Display();
}
