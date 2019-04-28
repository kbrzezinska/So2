//#pragma once

#include <stdio.h>
#include <string.h>
#include <thread>
#include<string>
#include <errno.h>
#include <mutex>
#include <iostream>	// sleep
#include <ctime>
#include <cstdlib>
#include <vector>
#include <ncurses.h>
std::mutex m;
std::mutex m_forks;
 
void print(int id,std::string ss){

        m.lock();
        mvaddstr(id+id+1,25,ss.c_str());
          refresh();

        m.unlock();  
   
    }
void printCount(int id,std::string ss){

        m.lock();
        mvaddstr(id+id+1,45,ss.c_str());
          refresh();

        m.unlock();  
   
    }

class philosp{
	
public:
	int left;
	int right;
    std::mutex* fl;
	std::mutex* fr;
    std::string s;
	int id;
	
    philosp(){}
    philosp(int left, int right, int id, std::mutex* fl, std::mutex* fr) :
		 left(left), right(right), id(id), fl(fl), fr(fr){}


	void think()
	{ 
        s="mysli           ";print(id,s);
         
		for (int i = 1; i < 6;i++){

         std::this_thread::sleep_for(std::chrono::milliseconds(500));
         s=std::to_string(i*500);
         printCount(id,s);
	    }
        s="      ";
         printCount(id,s);
    }
	 void goForDinner(){ 
	
		
        int l = id + 1; if (l>5 - 1)l = 0;
		if (left == 0)
			{ 
				if (l != 0 || right == 1)
				{   
                  fl->lock();
				  left = 1; 
                  s="podniosl lewy"; print(id,s); std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				}
			}

			 if (right == 0)
			{  
                 fr->lock();
				 right = 1; 
                 s="podniosl prawy"; print(id,s);std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			}			
			
	 };

	void eatAndthink(){

		if (left == 1 && right == 1){
		s="je            ";print(id,s);

        for (int i = 1; i < 7;i++){

			std::this_thread::sleep_for(std::chrono::milliseconds(500));           
           s=std::to_string(i*500);
             printCount(id,s);

            }
              s="     "; 
            printCount(id,s);
            s="skonczyl jesc     ";print(id,s);
            right = 0; fl->unlock();s="odlozyl lewy ";//print(id,s);
    		left = 0; fr->unlock(); s="odlozyl prawy ";//print(id,s);

			think();
		}
	};


	void run(){ 

    //while(true)
 for (int i = 0; i < 1;i++)
{
       
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));    
		goForDinner();
        
		eatAndthink(); std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        
}
		;std::cout<<id;
            
	};

};
