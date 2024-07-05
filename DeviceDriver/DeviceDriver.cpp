#include <iostream>
#include "DeviceDriver.h"
using namespace std;

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    unsigned char result, backup_result;
    // TODO: implement this method properly
    for (int i = 0; i < READ_TRY_COUNT; i++) {
        if (i == 0) {
            backup_result = result = m_hardware->read(address);
            continue;
        }
        if (backup_result != m_hardware->read(address)) {
            //Custom Exception(ReadFailException)
            cout << "ERROR: diff result\n";
            break;
        }
    }
    return (int)backup_result;
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    if (read(address) != INIT_MEMORY_VALUE) {
        //Custom Exception(WriteFailException)
        return;
    }
    m_hardware->write(address, (unsigned char)data);
}