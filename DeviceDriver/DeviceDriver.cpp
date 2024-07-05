#include <iostream>
#include <stdexcept>
#include "DeviceDriver.h"

using namespace std;

class ReadFailException : public std::exception {};
class WriteFailException : public std::exception {};

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    // TODO: implement this method properly
    return checkReadTest(address);
}

int DeviceDriver::checkReadTest(long address)
{
    unsigned char backup_result;
    for (int i = 0; i < READ_TRY_COUNT; i++) {
        if (i == 0) {
            backup_result = m_hardware->read(address);
            continue;
        }
        if (backup_result != m_hardware->read(address)) {
            //Custom Exception(ReadFailException)
            throw ReadFailException();
        }
    }
    return (int)backup_result;
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    checkWriteTest(address);
    m_hardware->write(address, (unsigned char)data);
}

void DeviceDriver::checkWriteTest(long address)
{
    if (read(address) != INIT_MEMORY_VALUE) {
        throw WriteFailException();
    }
}
