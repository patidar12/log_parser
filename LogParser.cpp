#include "Pattern.h"
#include "LogParser.h"
#include <unistd.h>
#include <chrono>
using namespace std::chrono;

LogParser::LogParser(){
    pool = new ThreadPool(MAX_TS_THREAD);	
    pool->init();
    storeTimestampPattern();
    storeLevelPattern(); 
    outputStream.open ("final.log", ios::app);
    outputStream << "[" << endl;
}
LogParser::~LogParser(){
    pool->shutdown();	
    outputStream << "]" << endl;
    outputStream.close();
    cout << "Closed all the resorces!" << endl;
}
LogParser * LogParser::instance = NULL;
LogParser* LogParser::getInstance(mutex &m1) 
  {
    if (instance == NULL)  
    {
      std::lock_guard<mutex> lock(m1);
        if(instance == NULL) 
        { 
          instance = new LogParser(); 
        }
    }
    return instance; 
  }

void LogParser::storeTimestampPattern(){ 

    tsPattern[0] = make_pair(TS1,regex(TS1));
    tsPattern[1] = make_pair(TS2,regex(TS2));
    tsPattern[2] = make_pair(TS3,regex(TS3));
    tsPattern[3] = make_pair(TS4,regex(TS4));
    tsPattern[4] = make_pair(TS5,regex(TS5));
    tsPattern[5] = make_pair(TS6,regex(TS6));
    tsPattern[6] = make_pair(TS7,regex(TS7));
    tsPattern[7] = make_pair(TS8,regex(TS8));
    tsPattern[8] = make_pair(TS9,regex(TS9));
    tsPattern[9] = make_pair(TS10,regex(TS10));
    tsPattern[10] = make_pair(TS11,regex(TS11));
    tsPattern[11] = make_pair(TS12,regex(TS12));
    tsPattern[12] = make_pair(TS13,regex(TS13));
    tsPattern[13] = make_pair(TS14,regex(TS14));
    tsPattern[14] = make_pair(TS15,regex(TS15));
    tsPattern[15] = make_pair(TS16,regex(TS16));
    tsPattern[16] = make_pair(TS17,regex(TS17));
    tsPattern[17] = make_pair(TS18,regex(TS18));
    tsPattern[18] = make_pair(TS19,regex(TS19));
    tsPattern[19] = make_pair(TS20,regex(TS20));
    tsPattern[20] = make_pair(TS21,regex(TS21));
    tsPattern[21] = make_pair(TS22,regex(TS22));
    tsPattern[22] = make_pair(TS23,regex(TS23));
    tsPattern[23] = make_pair(TS24,regex(TS24));
    tsPattern[24] = make_pair(TS25,regex(TS25));
    tsPattern[25] = make_pair(TS26,regex(TS26));
    tsPattern[26] = make_pair(TS27,regex(TS27));
    tsPattern[27] = make_pair(TS28,regex(TS28));
    tsPattern[28] = make_pair(TS29,regex(TS29));
    tsPattern[29] = make_pair(TS30,regex(TS30));
    tsPattern[30] = make_pair(TS31,regex(TS31));
    tsPattern[31] = make_pair(TS32,regex(TS32));
    tsPattern[32] = make_pair(TS33,regex(TS33));
    tsPattern[33] = make_pair(TS34,regex(TS34));
    tsPattern[34] = make_pair(TS35,regex(TS35));
    tsPattern[35] = make_pair(TS36,regex(TS36));
    tsPattern[36] = make_pair(TS37,regex(TS37));
    tsPattern[37] = make_pair(TS38,regex(TS38));
    tsPattern[38] = make_pair(TS39,regex(TS39));
    tsPattern[39] = make_pair(TS40,regex(TS40));
    tsPattern[40] = make_pair(TS41,regex(TS41));
    tsPattern[41] = make_pair(TS42,regex(TS42));
    tsPattern[42] = make_pair(TS43,regex(TS43));
    tsPattern[43] = make_pair(TS44,regex(TS44));
    tsPattern[44] = make_pair(TS45,regex(TS45));
    tsPattern[45] = make_pair(TS46,regex(TS46));
    tsPattern[46] = make_pair(TS47,regex(TS47));
    tsPattern[47] = make_pair(TS48,regex(TS48));
    tsPattern[48] = make_pair(TS49,regex(TS49));
    tsPattern[49] = make_pair(TS50,regex(TS50));
    tsPattern[50] = make_pair(TS51,regex(TS51));
    tsPattern[51] = make_pair(TS52,regex(TS52));
    tsPattern[52] = make_pair(TS53,regex(TS53));
    tsPattern[53] = make_pair(TS54,regex(TS54));
    tsPattern[54] = make_pair(TS55,regex(TS55));
    tsPattern[55] = make_pair(TS56,regex(TS56));
    tsPattern[56] = make_pair(TS57,regex(TS57));
    tsPattern[57] = make_pair(TS58,regex(TS58));
    tsPattern[58] = make_pair(TS59,regex(TS59));
    tsPattern[59] = make_pair(TS60,regex(TS60));
    tsPattern[60] = make_pair(TS61,regex(TS61));
    tsPattern[61] = make_pair(TS62,regex(TS62));
    tsPattern[62] = make_pair(TS63,regex(TS63));
    tsPattern[63] = make_pair(TS64,regex(TS64));
    tsPattern[64] = make_pair(TS65,regex(TS65));
    tsPattern[65] = make_pair(TS66,regex(TS66));
    tsPattern[66] = make_pair(TS67,regex(TS67));
    tsPattern[67] = make_pair(TS68,regex(TS68));
    tsPattern[68] = make_pair(TS69,regex(TS69));
    tsPattern[69] = make_pair(TS70,regex(TS70));
    tsPattern[70] = make_pair(TS71,regex(TS71));
}

void LogParser::storeLevelPattern(){
    levelPattern[0] = make_pair(LEVEL1,regex(LEVEL1));
    levelPattern[1] = make_pair(LEVEL2,regex(LEVEL2));
    levelPattern[2] = make_pair(LEVEL3,regex(LEVEL3));
}

void LogParser::matchTimestamp(vector<int> &pattern, string logline, int id){
    
    int start = PATTERN_FOR_A_THREAD * id;
    int end = PATTERN_FOR_A_THREAD* (id+1);
    for(int i = start;i < end && i < tsPattern.size();i++){
        if(regex_search(logline, tsPattern[i].second)){	
	    pattern.push_back(i);
	}
    }	
}
void LogParser::matchLevel(vector<int> &pattern, string logline){
        
    for(int i=0;i<levelPattern.size();i++){
        if(regex_search(logline, levelPattern[i].second)){
            pattern.push_back(i);
        }
    }
}
bool LogParser::formatPattern(vector<regex> &pattern,vector<int> tsPtrn, vector<int> levelPtrn, string logLine){

	for(int i=0; i<tsPtrn.size(); i++){
	    for(int j=0; j<levelPtrn.size(); j++){
	        string finalString = "";
	        finalString.append(tsPattern[tsPtrn[i]].first).append(SPACE).append(levelPattern[levelPtrn[j]].first).append(SPACE).append(MSG);
		regex rgxPattern(finalString);
		if(regex_match(logLine, rgxPattern)){
		    pattern.push_back(rgxPattern);
		    return true;
		}
	    }
	}
	return false;
}
bool LogParser::identifyPattern(vector<regex> &pattern, string logLine){

    vector<int> tsPtrn;
    vector<int> levelPtrn;
    vector<thread *> threadStore;
    vector<std::future<void>> output;
    auto func = std::bind(&LogParser::matchLevel,this,std::ref(levelPtrn),logLine);
    output.push_back(pool->submit(func));
    for(int i = 0; i < THREADS_COUNT; i++){
	auto func = std::bind(&LogParser::matchTimestamp,this,std::ref(tsPtrn),logLine,i);
        output.push_back(pool->submit(func));
    }
    for(int i=0;i<output.size();i++){
        output[i].get();
    }
    bool result = formatPattern(pattern,tsPtrn,levelPtrn,logLine);
    return result;	
}

bool LogParser::parseLogLine(vector<regex> pattern, string logLine, string logFileName){
       
       smatch match;
       string result = "{";
       result.append(" \"FieName\": \""+logFileName+"\",");
  
       for(int i=0;i<pattern.size();i++){    
           if((regex_search(logLine, match, pattern[i]))){	   
               result.append("\"TimeStamp\": \"").append(match.str(1)).append("\", \"LEVEL\": \"").append(match.str(2)).append("\", \"Messegge\": \"").append(match.str(4)).append("\"");
	       result.append(" },");
	       {
               std::lock_guard<mutex> lock(m);
	       outputStream << result << endl;
	       }
	       return true;
	   }
       }
       return false;
}
bool LogParser::processLogFile(string logFileName){
     	
    string logLine;
    vector<regex> pattern; 
    ifstream inputStream;
    inputStream.open(logFileName);
    //ifstream inputStream(logFileName);
    while(getline(inputStream, logLine) && logLine.empty());
    auto startTime = high_resolution_clock::now();

    bool result = identifyPattern(pattern,logLine);
    
    auto stopTime = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stopTime - startTime);
    cout << "Milliseconds : " << duration.count() << " " << logFileName << endl;
    if(result == false)
    {
        cout << "Not a valid log file : "<< logFileName << endl;
        return false;
    }
   inputStream.close();
   int end_pos = 0, start_pos = 0;
   while(true){
    inputStream.open(logFileName);	    
    inputStream.seekg(0, inputStream.end);
    end_pos = inputStream.tellg();
    inputStream.seekg(start_pos, inputStream.beg);
    while (getline(inputStream, logLine)){ 
    	if(!logLine.empty()){    
        bool result = parseLogLine(pattern, logLine,logFileName);
	if(!result){		
            result = identifyPattern(pattern,logLine);
            if(result == false)
            {
              cout << "Not a valid log line : "<< logLine << endl;
            }else{
	      parseLogLine(pattern, logLine,logFileName);
            }
	  }
        }
       }
      inputStream.close();
      start_pos = end_pos;
      sleep(1);
    }
    return true;
}
