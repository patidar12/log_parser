#include<iostream>
#include<string>
#include <regex>
#include <fstream>
#include <vector>
#include <thread>
#include <mutex>
#include "include/ThreadPool.h"
#define MAX_TS_THREAD 100
#define THREADS_COUNT 9
#define PATTERN_FOR_A_THREAD 8
using namespace std;

class LogParser{

   private:	  
       mutex m;
       ThreadPool *pool;       
       static LogParser *instance;
       map<int,pair<string,regex>> tsPattern;
       map<int,pair<string,regex>> levelPattern;
       ofstream outputStream;
       LogParser();
       void storeTimestampPattern();
       void storeLevelPattern();
       void matchTimestamp(vector<int>&, string, int);
       void matchLevel(vector<int>&, string);
       bool formatPattern(vector<regex>&, vector<int>, vector<int>, string);
   public:
       ~LogParser();
       static LogParser* getInstance(mutex&);
       bool identifyPattern(vector<regex>&, string);
       bool parseLogLine(vector<regex>,string,string);
       bool processLogFile(string);
};
