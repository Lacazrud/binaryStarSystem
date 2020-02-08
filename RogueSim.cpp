#include <iostream>
#include <cstdlib>
#include "cpgplot.h"
#include <math.h>


using namespace std;

int main(){

  cout <<   "Initializing Rogue Planet Simualtion... " << endl;

  

  //Global Parameters
    //Number of steps
  int step = 300000;                          
    //Size of steps
  float dt = 0.00001;                       
    //Gravitational constant
  float G = 1;  

  //Solar Parameters
    //Solar mass
  float M = 150000;


  //Rogue planet Parameters
    //Rogue planet mass
  float m;
    //Rogue planet x and y position
  float x[step+1];
  float y[step+1];
    //Rogue planet x and y velocity
  float vx[step+1];
  float vy[step+1];  
    //Rogue planet x and y acceleration
  float ax[step+1];
  float ay[step+1];

  
  cout << "**Please input rogue planet parameters: " << endl;


  cout << "Input rogue planet mass" << endl;
  cin >> m; 
  cout << "Input rogue planet x value" << endl;
  cin >> x[0];
  cout << "Input rogue planet y value" << endl;
  cin >> y[0];
  cout << "Input rogue planet velocity in the x-axis" << endl;
  cin >> vx[0];
  cout << "Input rogue planet velocity in the y-axis" << endl;
  cin >> vy[0];




//Earth Parameters
      //Earth mass
  float mo;
      //Earth x and y positions
  float xo[step+1];
  float yo[step+1];
      //Earth x and y velocity
  float vxo[step+1];
  float vyo[step+1];
      //Earth x and y acceleration
  float axo[step+1];
  float ayo[step+1];
  
  mo = 1;
  xo[0] = 20;
  yo[0] = 0;
  vxo[0] = 0;
  vyo[0] = -88;
  axo[0] = 0;
  ayo[0] = 0;

//cpgplot
  if (!cpgopen("/XWINDOW")) return 1;
  cpgenv(-50.,50,-50.,50.,1,1); 
  cpglab("x", "y", "Orbit Simulation: Rogue Planet Enters Solar System"); 


  for (int i = 1 ; i < step ; i++){ 

    //Rogue Planet Trajectory Calculation:
      
    //accelerations
    ax[i] = -G*(M+m)*(x[i-1] / pow(sqrt ( pow(x[i-1],2) + pow(y[i-1],2)),3) ) - (mo*xo[i-1] / pow(sqrt(pow(xo[i-1],2) + pow(yo[i-1],2)),3)) + mo*G*(xo[i-1] - x[i-1]) / (sqrt((pow(xo[i-1]-x[i-1],2) + (pow(yo[i-1] - y[i-1],2)))));
    ay[i] = -G*(M+m)*(y[i-1] / pow(sqrt ( pow(x[i-1],2) + pow(y[i-1],2)),3) ) - (mo*yo[i-1] / pow(sqrt(pow(xo[i-1],2) + pow(yo[i-1],2)),3)) + mo*G*(yo[i-1] - y[i-1]) / (sqrt((pow(xo[i-1]-x[i-1],2) + (pow(yo[i-1] - y[i-1],2)))));
  	
    //velocities
    vx[i] = vx[i-1] + ax[i] * dt * 0.5;
    vy[i] = vy[i-1] + ay[i] * dt * 0.5;
	
    //positions
    x[i] = x[i-1]+vx[i]*dt;
    y[i] = y[i-1]+vy[i]*dt;
   
	//accelerations
    ax[i] = -G*(M+m) * (x[i] / pow(sqrt ( pow(x[i],2) + pow(y[i],2)),3) );
    ay[i] = -G*(M+m) * (y[i] / pow(sqrt ( pow(x[i],2) + pow(y[i],2)),3) );
 	
    //velocities
    vx[i] = vx[i] + ax[i] * dt * 0.5;
    vy[i] = vy[i] + ay[i] * dt * 0.5;

    
    //Earth Trajectory Calculation:
    
    
    //accelerations
    axo[i] = -G*(M+mo)*(xo[i-1] / pow(sqrt(pow(xo[i-1],2) + pow(yo[i-1],2)),3) ) - (m*x[i-1] / pow(sqrt(pow(x[i-1],2) + pow(y[i-1],2)),3)) + m*G*(x[i-1] - xo[i-1]) / (sqrt((pow(x[i-1]-xo[i-1],2)) + (pow(y[i-1] - yo[i-1],2))));
    ayo[i] = -G*(M+mo)*(yo[i-1] / pow(sqrt(pow(xo[i-1],2) + pow(yo[i-1],2)),3) ) - (m*y[i-1] / pow(sqrt(pow(x[i-1],2) + pow(y[i-1],2)),3)) + m*G*(y[i-1] - yo[i-1]) / (sqrt((pow(x[i-1]-xo[i-1],2)) + (pow(y[i-1] - yo[i-1],2))));
 
 	//velocities
    vxo[i] = vxo[i-1] + axo[i] * dt * 0.5;
    vyo[i] = vyo[i-1] + ayo[i] * dt * 0.5;
	
    //positions
    xo[i] = xo[i-1]+vxo[i]*dt;
    yo[i] = yo[i-1]+vyo[i]*dt;
   
	//accelerations
    axo[i] = -G*(M+mo) * (xo[i] / pow(sqrt ( pow(xo[i],2) + pow(yo[i],2)),3) );
    ayo[i] = -G*(M+mo) * (yo[i] / pow(sqrt ( pow(xo[i],2) + pow(yo[i],2)),3) );
 	
    //velocities
    vxo[i] = vxo[i] + axo[i] * dt * 0.5;
    vyo[i] = vyo[i] + ayo[i] * dt * 0.5;
   
  }


  //Trace Earth, Color (7) = Yellow
  cpgsci(7);
  cpgline(step, xo, yo);

  //Trace Rogue Planet, Color (8) = Orange
  cpgsci(8);
  cpgline(step, x, y);  
  
  cpgclos();
 
  return 0;

}




