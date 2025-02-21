#ifdef _WIN32
    #ifdef YANDEX_SCHEDULE_EXPORTS
        #define YANDEX_SCHEDULE_API __declspec(dllexport)
    #else
        #define YANDEX_SCHEDULE_API __declspec(dllimport)
    #endif
#else
    #define YANDEX_SCHEDULE_API
#endif