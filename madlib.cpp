/***********************************************************************
* Program:
*    Project MadLib
* Summary: 
*    This is the program that will make the MadLib and prompt users
*    for certain answers. At the end, it will display the file with 
*    the answers prompted from the user into the file.        
*
************************************************************************/

#include <iostream>
using namespace std;
#include <fstream>
#include <ctype.h>
#include <cstring>

/*****************************************************
 * This function will check if the user still wants to 
 * play the game again after playing it.
 *****************************************************/
char ifplay()
{  
   char play;
   cout << "Do you want to play again (y/n)? ";
   cin >> play;
   if ( play == 'n')  
      cout << "Thank you for playing." << endl; 
   return play; 
}


/*****************************************************
 * This function will process the questions and prompt
 * the user for answers.
 *****************************************************/
void processQuestions(char data[],char answer[])
{
   
   
   if (data[1] != ' ')
   {
      cout << data << ' ';
      //cin >> answer;
      
      //cin.ignore();
      cin.getline(answer, 32);
      //cout << endl;
      
   }

}

/******************************************************************
 * This function will get the data from the file that is read.
 * It will get the questions and fix the special mark.
 *****************************************************************/
void askQuestions(char data[])
{
   char ans[32]; 
   if (data[0] == '<')
   {
      data[0] = '\t';
      for (int i = 0; data[i]; i++)
      {
         if ( data[i] == '>')
            data[i] = ':';
         if ( data[i] == '_')
            data[i] = ' ';      
         if ( data[i] == '#')
            data[i] = ' ';
         if ( data[i] == 123)
            data[i] = ' ';
         if ( data[i] == 125)
            data[i] = ' ';    
         if ( data[i] == '[')
            data[i] = ' '; 
         if ( data[i] == ']')
            data[i] = ' '; 
               
      }
      
      data[1] = toupper(data[1]); 
      processQuestions(data,ans);
  
    
      for (int i = 0; i < 32 ; i++)
      {
         data[i] = ans[i];
         //  cout << ans[i];
      } 
   } 
  

}

/******************************************************
 * This function will prompt the file name.
 ******************************************************/
void promptFileName(char filename[])
{
   cout << "Please enter the filename of the Mad Lib: ";
   cin >> filename;
   cin.ignore();

}

/******************************************************
 * This function will read the file input from the user.
 ******************************************************/
int readFile(char filename[], char data[], char story[][30])
{
   ifstream fin(filename);
   if (fin.fail())
      cout << "error file!";
  
   int length = 0;
   while ( !fin.eof()) 
   {
      fin >> data;
      fin.ignore();

  
            
      if ( data[1] == '#' || data[1] == 123 ||
           data[1] == 125 || data[1] == '[' ||
           data[1] == ']')
      {       
         strcpy(story[length], data);   
         askQuestions(data);
      }
  
      //cout <<"data - > "<< data <<endl;
      else
      {
         askQuestions(data);
         strcpy(story[length], data);
      }
      //cout <<"story -> "<< story[length]<<endl;
      length++;
   }
   fin.close();
   
   return length;

}



/******************************************************************
 * This function will display the result of the file description
 * with the answers prompted from the user.
 *****************************************************************/
void display(char story[][30], int count)
{
   cout << endl;
   for (int i = 0; i < count + 1 ; i++)  
   {
      if ( story[i + 1][0] == '"' || story[i + 1][0] == '\'' ||
           story[i][0] == '.' || story[i][1] == '"' || 
           story[i][0] == '"' || story[i][0] == '\'' ||
           story[i + 1][0] == '!' || story[i + 1][0] == '?' ||
           story[i][1] == '\'' ||  story[i + 1][1] == '"' ||
           story[i + 1][1] == '\'' || story[i + 1][0] == ',' ||
           story[i + 1][1] == '\'' || story[i + 1][1] == '"' ||
           story[i][0] == '"'  || story[i + 1][0] == '.' || 
           story[i][0] == '\n'  || story[i + 1][1] == '#' || 
           story[i][0] == '\0' || story[i + 1][0] == '\n')
    
         cout << story[i];
      else
         cout << story[i] << " ";    
   }
   cout << endl;

}


/***********************************************************************
 * This function will modify the special marks in the rolls of the array 
 * which catches the data before displaying it.
 ************************************************************************/
int modify(char story[][30], int length)
{
   int count = 0;
   //cout << endl;
   for (int i = 0; i < length ; i++)
   {

      if (story[i][1] == 123 && story[i - 1][0] != '\n' && 
          story[i - 1][1] != ' ')
      {
         story[i][0] = ' ';
         story[i][1] = '"';
         story[i][2] = '\0';
      }
      else if (story[i][1] == 123 && story[i - 1][0] != '\n' && 
               story[i - 1][1] == ' ' )
      {
         story[i][0] = '"';
         story[i][1] = '\0';
         story[i][2] = '\0';
      }   
       
         
      else if (story[i][1] == 123 && story[i - 1][0] == '\n')
      {
         story[i][0] = '"';
         story[i][1] = '\0';
         story[i][2] = '\0'; 
      }
      
      
      else if ( story[i][1] == 125 && story[i + 1][1] != '#')   
      {
         story[i][0] = '"';
         story[i][1] = ' ';
         story[i][2] = '\0';
      }
      else if ( story[i][1] == 125 && story[i + 1][1] == '#')   
      {
         story[i][0] = '"';
         story[i][1] = '\0';
         story[i][2] = '\0';
      } 
      
      else if (story[i][1] == '[' && story[i - 1][0] != '\n')
      {
         story[i][0] = ' ';
         story[i][1] = '\'';
         story[i][2] = '\0';
      }
      else if (story[i][1] == '[' && story[i - 1][0] == '\n')
      {
         story[i][0] = '\'';
         story[i][1] = '\0';
         story[i][2] = '\0'; 
      }
      
      
      else if ( story[i][1] == ']' && story[i + 1][1] != '#')   
      {
         story[i][0] = '\'';
         story[i][1] = ' ';
         story[i][2] = '\0';
      }
      else if ( story[i][1] == ']' && story[i + 1][1] == '#')   
      {
         story[i][0] = '\'';
         story[i][1] = '\0';
         story[i][2] = '\0';
      } 
      
      else if (story[i][0] == '.' && (story[i + 1][1] != 125 && 
               story[i + 1][1] != ']' && story[i + 1][1] != 123 && 
               story[i + 1][1] != '[' && story[i + 1][1] != '#' ))
      {
         story[i][0] = '.';    
         story[i][1] = ' ';
         story[i][2] = '\0';

      }
      else if (story[i][1] == '#')
      { 
         story[i][0] = '\n';    
         story[i][1] = '\0';
         story[i][2] = '\0';

      }       
    
      count++;
   }
   return count;
}




/**********************************************************************
 * This is the function where the computer starts to read.
 ***********************************************************************/
int main()
{
   char play = 'y';
   
   while ( play == 'y')
   {  
      char filename[256];
      promptFileName(filename); 
  
      char story[256][30] = {}; 
      char data[256];
   
      // readFile(filename, story);
      int length = readFile(filename, data, story);      
  
      int count = modify(story, length);
      display(story, count);
   
      play = ifplay();
   
   }
   return 0;
}
