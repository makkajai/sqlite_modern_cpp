#include <iostream>
#include <string>
#include <memory>
#include <stdexcept>
#include <sqlite_modern_cpp.h>
using namespace sqlite;
using namespace std;


int main() {
  database db(":memory:");
  db << "CREATE TABLE person (id integer primary key not null, name TEXT);";
  bool expception_thrown = false;

  try {
    db << "INSERT INTO person (id,name) VALUES (?,?)" << 1 << "jack";
    // inserting again to produce error
    db << "INSERT INTO person (id,name) VALUES (?,?)" << 1 << "jack";
  } catch (sqlite_exception& e) {
    cerr << e.get_code() << ": " << e.what() << endl;
    expception_thrown = true;
  } catch (...) {
    cerr << "Ok, we have our excpetion thrown" << endl;
    expception_thrown = true;
  }

  if(!expception_thrown) {
    exit(EXIT_FAILURE);
  }
  
  exit(EXIT_SUCCESS);
}
