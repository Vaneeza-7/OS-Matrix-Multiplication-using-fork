#include<iostream>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<time.h>
#include<fstream>
using namespace std;


int findN()
{
   srand((unsigned)time(NULL));
   int random = 10 + (rand() % 90);
   
   random=random*9;
   random=390/random;
   
   int num = random % 25;
   if(num<25)
   {
       num +=15;
   }   
   
   return num;

}

int** initializeMatrix(int num)
{

   srand((unsigned)time(NULL));
   
   int** matrix= new int*[num];
   for(int i=0; i<num; i++)
   {
      matrix[i]= new int [num]; 
   }
   
   for(int i=0; i<num; i++)
   {
       for(int j=0; j<num; j++)
       {
           matrix[i][j]= rand() % 10;
           cout<<matrix[i][j]<<" ";
       }
       cout<<endl;
   }

   cout<<"Matrix of size "<<num<<"x"<<num<<" Created! "<<endl;
   
   //save matrix to a text file 
  
   fstream file("Matrix.txt");
   //file.open("Matrix.txt");
   for(int i=0; i<num; i++)
   {
       for(int j=0; j<num; j++)
       {
           file<<matrix[i][j]<<",";
       }
       file<<endl;
   }
   
   file.close();
     
   return matrix;
}




int main()
{
    pid_t pid;
    int n = findN();
    int** matrix = initializeMatrix(n);   
    string filename;
    int id, placeholder;
    char ch;
    
    int** matrix2= new int*[n];
    for(int i=0; i<n; i++)
    {
      matrix2[i]= new int [n]; 
    }
    
    //multiply
    for (int i=0; i< n; i++) {
        //fork our process
        if (pid > 0)
            pid = fork();
        
        //child process runs following
        if(pid == 0) {
//           placeholder=i;
//           filename=to_string(placeholder);
//           filename += ".txt";
//           fstream file(filename);
            for (int j=0; j < n; j++) {
                int cellValue = 0;
                //file<<getpid();
                //file<<endl;
                for (int z=0; z < n; z++) {
                    cellValue += matrix[i][z] * matrix[z][j];
                     cout<<cellValue<<" "; 
                     
                }
                matrix2[i][j] = cellValue;
                cout<<endl;
                //child is done,
               //file.close();
                exit(0); 
            }
           
        }
    }
//for(int i=0; i<n; i++)
//    {
//    cout<<"Imhere";
//       filename=to_string(i);
//       ifstream file(filename);
//       while(file>>ch)
//       {
//          cout<<ch;
//       }
//       cout<<endl;
//       file.close();
//    }
    //parent wait for child processes to end
    int status;
    wait(&status);
    
    
     
}




