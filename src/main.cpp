#include "checksum/checksum.hpp"
#include "config/config.hpp"
#include "database/database.hpp"
#include <cstdlib>
#include <iostream>
#include <thread>  // For std::this_thread::sleep_for
#include <chrono>  // For std::chrono::seconds

using namespace std;
using namespace std::filesystem;

int main(int argc, char *argv[]) {
  Config config;
  config.parse("../config.yaml");
  Database db("database.db");
  Checksum cs(&config);

  path p = "../test_file.txt";
  string checksum;
  cs.compute_checksum(p, &checksum);
    cout << checksum << endl;
  /*db.saveData(p, checksum, "E");*/

  while (true) {
    cout << "ittr" << endl;
    string temp;
  /*cs.compute_checksum(p, &temp);*/
    if (! cs.compare_checksum(p, &checksum)) {
      system("notify-send 'File changed'");
  cs.compute_checksum(p, &checksum);
    }
    
    std::this_thread::sleep_for(std::chrono::seconds(config.get_interval()));
  }
  
}

