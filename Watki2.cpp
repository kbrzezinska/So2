
//#include "stdafx.h"
#include "W2.h"
#include <stdio.h>
#include <string.h>
#include <thread>
#include <atomic>
#include<string>
#include <errno.h>
#include <memory>
#include <ncurses.h>
#include <iostream>	// sleep

using namespace std;
static std::atomic<bool>run(false);
static bool v=false;
int main()
{
	srand(time(0));
	int n = 5;
    run.store(true);
	vector<std::shared_ptr<std::mutex>>f; 
	
	for (int i = 0; i < n; i++)
	{
	
		f.push_back(std::make_shared<std::mutex>());
	}
	

	//std::vector<std::shared_ptr<philosp>> philosps;
	philosp *philosps[n];
	for (int i = 0; i < n; ++i) {
		int l = i + 1; if (l>n - 1)l = 0;
		int r = i;
		//philosps.push_back(std::make_shared<philosp>(0, 0, i, f[l].get(), f[r].get()));
        philosps[i]=new philosp(0, 0, i, f[l].get(), f[r].get());
	}
    
        int row,kol;
        initscr();
        getmaxyx(stdscr,row,kol);
        mvprintw(0,2,"%s ","filozofie");
        mvprintw(0,25,"%s ","czynnosci");
        mvprintw(0,45,"%s ","czas");
        for (int i = 0; i < n; i++)
	{
		mvprintw(i+i+1,2,"%s %d","filozof",i);
	}
	



		//std::vector<std::thread> th;
        std::thread* th[n] ;
		for (int i = 0; i < n; ++i) {
			//th.push_back(std::thread(&philosp::run, philosps[i]));
            th[i]=new std::thread(&philosp::run, philosps[i]);
		}


         int c=1;
        while(run){
        
       // std::cin>>c;
        if(c==1){
        
		for (int i = 0; i < n; ++i){
          
			th[i]->join();
            delete th[i];
            delete philosps[i];
      
		} run.store(false);
          
        }
        } endwin();
}

