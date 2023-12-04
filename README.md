## YFINANCE (C++)

<p align="center">
  <img src="https://upload.wikimedia.org/wikipedia/commons/3/37/Yahoo_Finance_Logo_2019.png" width=220 />
</p>

### Quick Start
This is a quick and simple repository which is still in development. Its aim is to simplify the interaction between the **_Yahoo Finance_** API and **_C++_**. 

This project uses [CMake](https://cmake.org/) as its build system.

It depends on two other projects:

* [C++ Requests: Curl for People (cpr)](https://github.com/libcpr/cpr)
* [JSON for Modern C++](https://github.com/nlohmann/json)

This project uses the [Boost Libraries](http://www.boost.org/).

If you don't have [C++ Requests: Curl for People (cpr)](https://github.com/libcpr/cpr) and/or [JSON for Modern C++](https://github.com/nlohmann/json) you can use CMake's FetchContent to add them. Just add something like

```cmake
include(FetchContent)

FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/libcpr/cpr.git
                         GIT_TAG 0817715923c9705e68994eb52ef9df3f6845beba) # The commit hash for 1.10.x. Replace with the latest from: https://github.com/libcpr/cpr/releases
FetchContent_MakeAvailable(cpr)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)
```

to your CMakeLists.txt. Check out this project's [CMakeLists.txt](CMakeLists.txt) to see how to do it.


### Version Updates
**_v-0.1 (09-30-2022)_**:
Added the `get_quotes` and `get_options` member functions for the `Symbol` class.

**_v-0.2 (10-05-2022)_**:
Added the `get_profile` and `get_summary` member functions for the `Symbol` class. 

**_v-0.3 (10-23-2022)_**:
Added the `get_news` member functions for the `Symbol` class. 

### Approach
The core element of the **_"pseudo"_** library is the `Symbol` class which is initialized through the asset's symbol. An exemple with the keyword *new*, therefore a pointer to the `Symbol` class is initialized:
```c++ 
yfinance::Symbol* sym = new yfinance::Symbol("GS");
```
In order to load **_quotes_** from the `Symbol` object you call the member function `get_quotes` with arguments ***interval***, ***start*** and ***end***. The ***interval*** argument is mandatory. If ***start*** or ***end*** are not specified the last available amount of data will be queried.
```c++ 
Structures::Quotes quotes = sym->get_quotes("5m");
```
In order to load **_options_** from the `Symbol` object you call the member function `get_options` wich does not take arguments:
```c++ 
std::vector<Structures::Option> options = sym->get_options();
```

Working within the *quoteSummary endpoint*, to load the  **_assetProfile_**  from the `Symbol` object you call the member function `get_profile` wich does not take arguments:
```c++ 
Structures::Profile profile = sym->get_profile();
```
Otherwise, if you want to extract some module from the *quoteSummary endpoint*, call the the member function `get_summary` with the name of the module as argument:
```c++ 
nlohmann::json financials = sym->get_summary("financialData");
```
