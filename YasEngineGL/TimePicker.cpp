#include"TimePicker.hpp"

//-----------------------------------------------------------------------------|---------------------------------------|
//                                                                            80                                     120

    TimePicker::TimePicker()
    {
        isFrequencyOfThePerformanceCounterPickedUp = (QueryPerformanceFrequency(&frequency) != 0);
        //isFrequencyOfThePerformanceCounterPickedUp = (QueryPerformanceFrequency((LARGE_INTEGER*)&frequency) != 0);
    }

    float TimePicker::getSeconds()
    {
        if(isFrequencyOfThePerformanceCounterPickedUp)
        {
            LARGE_INTEGER ticks;
            QueryPerformanceCounter(&ticks);
            return (float)(ticks.QuadPart / (double)frequency.QuadPart);
        }
        else
        {
            return GetTickCount64() / 1000.0F;
        }
    }

//                                                                            80                                     120
//-----------------------------------------------------------------------------|---------------------------------------|
