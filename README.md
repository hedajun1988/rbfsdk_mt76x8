
# How to build test program

## linux
You need to install the cmake tool on your compilation host and execute the following command to compile


```
cd ${your_rbf_sdk_path}
cp ${your_rbf_sdk_path}/platform/${your_os_type}/${your_plaform}/CMakeLists.txt ./
mkdir build
cd build
cmake ..
make
```

## freertos

Since freertos has relatively large version differences, the platform code used in rbfsdk is provided in a packaged form. You can find it in ${your_rbf_sdk_path}/platform/freertos/${your_plaform}.

You need to import the header files, static libraries and platform package code in the SDK into your development project for compilation.


# For more information about rbfsdk, please refer to：
http://111.229.174.251/rbfsdk/html/index.html