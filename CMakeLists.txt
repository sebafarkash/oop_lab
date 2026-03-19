cmake_minimum_required(VERSION 3.20)
project(oop_lab)

set(CMAKE_CXX_STANDARD 17)

add_executable(Lab_2_3_combinated
        Lab_2_3_combinated/main.cpp
        Lab_2_3_combinated/Product.cpp
        Lab_2_3_combinated/Customer.cpp
        Lab_2_3_combinated/Order.cpp
)

add_executable(lab_4_combinated
        lab_4_combinated/main.cpp
        lab_4_combinated/Entity.cpp
        lab_4_combinated/Product.cpp
        lab_4_combinated/PhysicalProduct.cpp
        lab_4_combinated/DigitalProduct.cpp
        lab_4_combinated/Customer.cpp
        lab_4_combinated/RegularCustomer.cpp
        lab_4_combinated/PremiumCustomer.cpp
        lab_4_combinated/Order.cpp
        lab_4_combinated/Order.h
)