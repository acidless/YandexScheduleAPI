# 📅 Yandex Schedule API

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)

C++ library for working with [Yandex Schedule API](https://yandex.ru/dev/rasp/doc/ru/). Allows to get schedules of trains, buses, planes and other transport via REST API.

## 🚀 Features
✔ Request train, bus, airplane schedules

✔ Getting information about stations

✔ Retrieve data about cities and towns

✔ Support caching of requests

✔ Easy to integrate into other C++ projects  

---

## 📦 Build and install
It requires:
- **C++17+**
- **CMake 3.10+**

```
git clone https://github.com/acidless/YandexScheduleAPI.git
cd YandexScheduleAPI
mkdir build && cd build
cmake ..
make
```

---

## 🌍 Usage
The simple code sample below demonstrates how to use the library to search for timetables between St. Petersburg (c2) and Moscow (c213).
```c++
#include <YandexScheduleAPI.h>

using namespace YandexSchedule;

int main() {
    auto api = YandexScheduleAPI("YOUR_API_KEY");

    // c2 - code of Saint-Petersburg, c213 - code of Moscow
    auto result = api.search("c2", "c213");

    std::cout << "Regular routes count: " << result.interval_segments.size() << std::endl;
    return 0;
}
```

The library uses the “Builder” pattern for convenient generation of query parameters. It allows to specify only necessary parameters of the request to avoid passing a large number of arguments in the constructor.

**📌 Usage:**
```c++
auto params = SearchRequestParamsBuilder()
    .setDate("2025-02-20")   // Setting schedule date
    .setShowTransfers(true)  // Showing routes with transfers
    .setLimit(10)            // Limiting the number of results
    .build();
auto result = api.search("c2", "c213", params);
```

---

## 🗄 Caching
To improve performance, the library supports request caching. This allows you to avoid repeated calls to Yandex API and reduce the load on the network.

1️⃣ Caching in memory (default)
In this mode, the cache runs only in RAM and is cleared when the program terminates.
```c++
auto api = YandexScheduleAPI("YOUR_API_KEY");
```

2️⃣ Caching to file
This creates a FileCache object that stores the data in cache.json. This allows reusing the cached data after restarting the program.
```c++
auto api = YandexScheduleAPI("YOUR_API_KEY", new FileCache("cache.json"));
```

---

## 📧 Contact and Support
If you have any questions or suggestions, create an [Issue](https://github.com/acidless/YandexScheduleAPI/issues) or email odkukunov@gmail.com.
