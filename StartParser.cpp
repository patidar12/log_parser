#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <future>
#include "LogParser.cpp"
#include <experimental/filesystem>
#include "include/ThreadPool.h"
#define MAX_THREAD 100
using namespace std::experimental::filesystem;
using namespace std;
using namespace std::chrono;
int main(void){
   
    ThreadPool pool(MAX_THREAD); 
    pool.init();    
    auto startTime = high_resolution_clock::now(); 	
    mutex m;
    vector<string> fileNames;
    // get the current working directory path
    string path = current_path().string();
    path.append("/log_files");

    // store all the log files names
    for (const auto & entry : directory_iterator(path)){
        fileNames.push_back(entry.path());
    }
    vector<thread *> threads;
    LogParser *obj = LogParser::getInstance(m);
    vector<std::future<bool>> output;
    for(int i=0;i<fileNames.size();i++){
       auto func = std::bind(&LogParser::processLogFile,obj,fileNames[i]); 
       output.push_back(pool.submit(func));
    }
    for(int i=0;i<output.size();i++){
        output[i].get();
    }
    auto stopTime = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stopTime - startTime);
    cout << "sec : " << duration.count()/1000000.0 << endl;   
    pool.shutdown();
    return 0;
}
