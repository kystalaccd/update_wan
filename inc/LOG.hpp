#ifndef __LOG_HPP__
#define __LOG_HPP__

#define _DEBUG_

#include <iostream>

namespace micagent{
using namespace std;

#ifdef _DEBUG_
#define DEBUG_MSG(Message) cout<<"[DEBUG]"<<__FILE__<<"; "<<__FUNCTION__<<"; "<<__LINE__<<"----> "<<Message<<endl;
#define ERROR_MSG(Message) cerr<<"[ERROR]"<<__FILE__<<"; "<<__FUNCTION__<<"; "<<__LINE__<<"----> "<<Message<<endl;
#endif

}


#endif