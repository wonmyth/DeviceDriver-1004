#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../DeviceDriver/DeviceDriver.cpp"

using namespace testing;
using namespace std;

class FrashMock : public FlashMemoryDevice {
public:
	MOCK_METHOD(unsigned char, read, (long), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};
TEST(DeviceDriverTest, FlashMockRead) {
	FrashMock mock;
	long addr = 0x1234;

	EXPECT_CALL(mock, read(addr))
		.Times(5) // behavior Verification
		.WillRepeatedly(Return(1)); //stub Verification

	DeviceDriver driver(&mock);
	EXPECT_THAT(driver.read(addr), Eq(1)); // state Verification
}
TEST(DeviceDriverTest, FlashMockWrite) {
	FrashMock mock;
	long addr = 0x1234;
	unsigned char data = 0xAA;

	EXPECT_CALL(mock, read(addr))
		.Times(5) // behavior Verification
		.WillRepeatedly(Return(0xFF)); //stub Verification
	EXPECT_CALL(mock, write(addr, data));

	DeviceDriver driver(&mock);
	driver.write(addr, (int)data);
}