#ifndef INTERFACE_HPP_
#define INTERFACE_HPP_

#ifdef _WIN32
#include "windows/vmenu.hpp"
#include "windows/hmenu.hpp"
#else
#include "linux/vmenu.hpp"
#include "linux/hmenu.hpp"
#endif /// _WIN32

#endif /// INTERFACE_HPP_