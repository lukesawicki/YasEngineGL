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


    
//uint64_t _glfwPlatformGetTimerValue(void)
//{
//    if (_glfw.timer.win32.hasPC)
//    {
//        uint64_t value;
//        QueryPerformanceCounter((LARGE_INTEGER*) &value);
//        return value;
//    }
//    else
//        return (uint64_t) timeGetTime();
//}