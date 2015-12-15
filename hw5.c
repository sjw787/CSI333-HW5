// Sam Wylock SW549498
#include <stdio.h> // included libraris for proper program execution
#include <stdlib.h> 
#include <string.h>

int main(int argc, char * argv[]){

  FILE * ifp; // FILE * for input file
  FILE * ofp; // FILE * for output file
  unsigned char curr,  count; // used for holding the count of ascii chars and the current char
  char next; // for holding the next char read from file
  
  if(argc != 4){ // makes sure correct amount of args were entered
    printf("Usage: a.out Flag InputFile OutputFile Flag\n");exit(1); //print message and exit otherwise
  }
  if(strcmp(argv[1],"z") != 0 && strcmp(argv[1],"d")!=0){// makes sure proper flags were used
    printf("Usage: a.out Flag InputFile OutputFile\n");exit(1);// print message and exit otherwise
  }
  if((ifp=fopen(argv[2],"r"))==NULL){ // makes sure input file an be opened
    printf("Error opening file %s\n", argv[1]);exit(1); //print message and exit otherwise
  } 
  if((ofp=fopen(argv[3],"w"))==NULL){ // makes sure output file can be opened
    printf("Error opening file %s\n",argv[2]);exit(1); //print message and exit otherwise
  }

  if(!strcmp(argv[1],"z")){ // begin compression functionality
    curr = fgetc(ifp); //gets first char from file
    next = fgetc(ifp); // gets second
    while(next != EOF){ // runs function until the next char is EOF
      if(curr == next){ // if the current and next characters are equal
       fprintf(ofp,"%c%c",curr, curr);  // print the two
       while(curr == next){ // while the two are equal
            if(count == 255){ //is the count 255(unsigned char max)
              fprintf(ofp,"%c", 255); // if so print the 255 char and restart the count
              count = 0;
            }else{ // if not then just get the next char to compare and increment the count
              curr = next;
              next = fgetc(ifp);
              ++count;
            }
        }
        fprintf(ofp,"%c", count-1); // print the count value to the outfile
        count = 0; // reset the count to 0
      }else{ // if the two values are not equal then just print out the current char
        fprintf(ofp, "%c", curr);
      }
      curr = next; //get the next char
      next = fgetc(ifp);// ^^^^^^^^^
      count = 0;// reset count if it hasnt been already
    }
    if(curr != 255){ // 
      fprintf(ofp,"%c", curr);
    }
  }// end compression

  if(!strcmp(argv[1],"d")){ // begin decompression functionality
    curr = fgetc(ifp); // get the first char and put it in curr 
    next = fgetc(ifp); // get the second car and put it in next
    while(next != EOF){ // run until the end of file is reached
      if(curr != next){ // if the two chars are not equal then just print curr out
        fputc(curr,ofp); 
      }else{ //otherwise they are equal
        count = fgetc(ifp); // and the next char to come after is the count
        if(count == 255){ // if it is 255 then there is another count after it
          while(count == 255){ // run while the count is still 255
            while(count > 0){ // this way it will keep knowing that there is still another count to come in the next char
              fputc(curr, ofp); // print 255 of the current char
              count--;
            }
            count = fgetc(ifp); // get that next count
          }
        }// done with the 255 chars
        if(count != 255){ //now the count is the last count for the given stream of identical chars
            while(count>0){ //print the remaining number of chars
              fputc(curr, ofp);
              count--;
            }
            fputc(curr, ofp); // print one more
          }
      }
      curr = next; // get the next char
      next = fgetc(ifp); //^^^^^^^^^^
    }//EOF reached
    fputc(curr, ofp); // print out the last char held in curr
  }//end decomp

  fclose(ifp); // close the input file
  fclose(ofp); // close the output file
  exit(0);
}


