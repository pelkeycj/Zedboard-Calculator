#include <iostream>
#include <cstdlib>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <cmath>
#include "Zedboard.h"
using namespace std;

Zedboard::Zedboard()
{
  pBase = Initialize();
  //check error
  if (pBase == MAP_FAILED)
  {
    cerr << "Mapping I/O memory failed - Did you run with 'sudo'\n";
    exit(1);
  }
}

Zedboard::~Zedboard()
{
  Finalize();
}

void Zedboard::RegisterWrite(int offset, int value)
{
  * (int *) (pBase + offset) = value;
}

int Zedboard::RegisterRead(int offset)
{
  return * (int *) (pBase + offset);
}

void Zedboard::SetLedNumber(int value)
{
  RegisterWrite(gpio_led1_offset, value % 2);
  RegisterWrite(gpio_led2_offset, (value / 2) % 2);
  RegisterWrite(gpio_led3_offset, (value / 4) % 2);
  RegisterWrite(gpio_led4_offset, (value / 8) % 2);
  RegisterWrite(gpio_led5_offset, (value / 16) % 2);
  RegisterWrite(gpio_led6_offset, (value / 32) % 2);
  RegisterWrite(gpio_led7_offset, (value / 64) % 2);
  RegisterWrite(gpio_led8_offset, (value / 128) % 2);
}

int Zedboard::PushButtonGet(int states[])
{
  for (int i = 0; i < 5; i++)
  {
    if (RegisterRead(gpio_pbtnl_offset + 4*i) != states[i])
    {
      states[i] = RegisterRead(gpio_pbtnl_offset + 4*i);
      if (states[i] == 1)
        return i + 1;
    }
  }
  return 0;
}

char* Zedboard::Initialize()
{
  fd = open("/dev/mem", O_RDWR);
  return (char *) mmap(NULL,
                    gpio_size,
                    PROT_READ | PROT_WRITE,
                    MAP_SHARED,
                    fd,
                    gpio_address);
}

void Zedboard::Finalize()
{
  munmap(pBase, gpio_size);
  close(fd);
}
