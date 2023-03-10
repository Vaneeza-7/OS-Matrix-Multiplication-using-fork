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
     
    fstream file("/home/vaneeza/i210390_OS_Assignment1/Matrix.txt", std::ios::out | std::ios::app);

  if (file)
  {
     
   for(int i=0; i<num; i++)
   {
       for(int j=0; j<num; j++)
       {
           file<<matrix[i][j]<<" ";
       }
       file<<endl;
   }
    file.close();
  }
     
   return matrix;
}




int main()
{
    pid_t pid;
    int n = findN();
    int** matrix = initializeMatrix(n);   
    string filename;
    int id, placeholder;
    string ch;
    
    int** matrix2= new int*[n];
    for(int i=0; i<n; i++)
    {
      matrix2[i]= new int [n]; 
    }
    
    //multiply
    for (int i=0; i< n; i++)
     {
        //fork our process
           
        if (pid > 0)
          {  pid = fork();
            int status;
            wait(&status);
            //cout<<"Imhere";
            filename=to_string(i);
            filename +=".txt";
            ifstream file("/home/vaneeza/i210390_OS_Assignment1/"+filename, std::ios::in);
            while(file>>ch)
            {
              getline(file,ch);
              file>>ch;
              cout<<ch;
              
            }
            cout<<endl;
            file.close();
            
    }
           
        //child process runs following
        if(pid == 0)
        {
           placeholder=i;
           filename=to_string(placeholder);
           filename += ".txt";
           fstream file("/home/vaneeza/i210390_OS_Assignment1/"+filename, std::ios::out | std::ios::app);
           file<<getpid();
           file<<endl;
            for (int j=0; j < n; j++)
            {
                   int cellValue = 0;
                   
                     for (int z=0; z < n; z++)
                     {
                      cellValue += matrix[i][z] * matrix[z][j];
                     }
                      matrix2[i][j] = cellValue;
                      file<<cellValue<<" ";
            }
           
            //child is done,
            file.close();
            exit(0); 
           
        }
     }
     

     //parent wait for child processes to end
    

   
//for(int i=0; i<n; i++)
//    {
//       cout<<"Imhere";
//       filename=to_string(i);
//       filename +=".txt";
//       ifstream file("/home/vaneeza/i210390_OS_Assignment1/"+filename, std::ios::in);
//       while(file>>ch)
//       {
//          cout<<ch;
//       }
//       cout<<endl;
//       file.close();
//    }    
     for(int i=0; i<n; i++)
     {
       for(int j=0; j<n; j++)
       {
          //cout<<matrix2[i][j]<<" ";
       }
       //cout<<endl;
     }  
}




