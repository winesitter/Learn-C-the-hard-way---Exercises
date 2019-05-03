#include "ex22.h"
#include "dbg.h"

const char *MY_NAME = "Flo Setzwein";

void scope_demo(int count)
{
  log_info("count at the beginning of <scope_demo> is: %d.", count);
  
  if (count > 10) {
    int count = 100;  // BAD! BUGS!!
    log_info("count in this scope is %d. (in if-part)", count);
  }
  log_info("count after the if-part is %d.", count);

  count = 3000;

  log_info("count is know %d at the end of <scope_demo>.", count);


}


int main(int argc, char *argv[])
{
  // test out THE_AGE accessors
  log_info("My name: %s, age: %d", MY_NAME, get_age());
  
  set_age(22);

  log_info("My age is now: %d", get_age());


  // test out THE_SIZE extern
  log_info("The size is: %d", THE_SIZE);
  print_size();

  THE_SIZE = 9;
  log_info("The size is now: %d", THE_SIZE);
  print_size();

  // test the ratio function static
  log_info("Ratio at first: %f.", update_ratio(2.0));
  log_info("Ratio again: %f.", update_ratio(10.0));
  log_info("Ratio once more: %f.", update_ratio(300.0));

  // test the SCOPE demo
  int count = 4;
  scope_demo(count);
  scope_demo(20 * count);
  log_info("count after calling scope: %d.", count);

  return 0;
}
