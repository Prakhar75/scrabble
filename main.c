
 
// this file contains code for milestone 3 , pls find dic1.txt attached .



#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
 
int weight(char *word) 
{  

    int w = 0;                                             //STORE VALUE OF LETTER
    while(*word != '\0')                                   //ITERATING LETTER
    {                                

        switch (*word) 
        {
        case 'E':
       case 'A':
       case 'I':
       case 'O':
       case 'N':
       case 'R':
       case 'T':
       case 'L':
       case 'S':
       case 'U':
           w += 1;
           break;

       case 'D':
       case 'G':
           w += 2;
           break;

       case 'B':
       case 'C':
       case 'M':
       case 'P':
           w += 3;
           break;

       case 'F':
       case 'H':
       case 'V':
       case 'W':
       case 'Y':
           w += 4;
           break;

       case 'K':
           w += 5;
           break;
   
       case 'J':
       case 'X':
           w += 8;
           break;

       case 'Q':
       case 'Z':
           w += 10;
           break;        
        }
        *word++;
    }
    return w;                                        //TO RETURN WEIGHT OF WORD
}


int pool_of_letters(char the_word[],char bag[],int n,int temp,int j)     // POOL OF LETTERS(shortlisting possible words from bag of letters)
 {                               

int i,flag=0;
if(j<=n)
 {
for(i=0;i<n;i++)
 {
if(the_word[0]==bag[i])
flag=1;
}
if(temp==1) 
{
if(the_word[0]=='A'||the_word[0]=='E'||the_word[0]=='I'||the_word[0]=='O'||the_word[0]=='U')
flag=1;
}

return flag;
}

else 
{
    return 0;
}

}

int score(int s,int word_length,int w)
 {

    int s1;
    int good=(s-1)*word_length;
    int bad = (3 * (s + 1 - word_length))>1?(3 * (s + 1 - word_length)):1;
    int mult = good - bad;
    s1=mult*w;
    return s1;                                                                       // RETURN SCORE OF THE WORD
}

 
int check_letters(char *bag,char *a)                            // function to check if word can be formed by bag of letters.
{
    int n =strlen(a);
    char word[n];
    strcpy(word,a);
    int star_count =0;

    while(*bag != '\0') 
    {
        if(*bag == '*')
        star_count++;
        else 
        {
            for(int i=0;word[i];i++) 
            {

                if(*bag == word[i]) 
                {
                    word[i] = ' ';
                    break;
                }
            }
        }
        bag++;
    }

    while(star_count>0) 
    {

        for(int i=0;word[i];i++) 
        {

            if(word[i] == 'A'|| word[i] == 'E'|| word[i] == 'I'|| word[i] == 'O'|| word[i] == 'U') 
            {
                word[i] = ' ';
                break;
            }
        }
        star_count--;
    }
   
    for(int i=0;word[i];i++) 
    {

        if(word[i] != ' ')
        return 0;
    }

    return 1;
}

 
int main()                                                         //main function.
 {  
      
         
    int n,temp=0, j, i,found = 0, good = 0;
    printf("how many letters for the bag: ");
    scanf("%d", &n);
    printf("Enter the letters with space:\n");
    char bag_of_letters[n], bag1[n];
   
    for(i=0;i<n;i++)
     {
        scanf(" %c",&bag_of_letters[i]);
        bag_of_letters[i] = toupper(bag_of_letters[i]);
    }
clock_t start = clock();	                                     // clock to check execution time of code.
    for(i=0;i<n;i++)
     {
    if(bag_of_letters[i]=='*')
    temp=1;
    }

    printf("\n");
    char ch[20];
    char highest_word[20];
    int s=0;
    FILE *fp,*fp2;
    if(n<=6)
        fp = fopen("dic1.txt","r");                       // a shorlisted dictionary based on size of words.
else
      fp = fopen("dic.txt","r");
   
    while(!feof(fp)) 
    {                                              //GOES THROUGH EVERY WORD UNTILL FINDS THE WORD  

        fscanf(fp,"%s",ch);  
        j=strlen(ch);
        if(pool_of_letters(ch,bag_of_letters,n,temp,j))
         {
           if(check_letters(bag_of_letters,ch)==1) 
           {
           
found = 1;
            printf("%s\n",ch);
          if(score(n,strlen(ch),weight(ch))>s)
           {
          good = 1;
                strcpy(highest_word,ch);
                s = score(n,strlen(highest_word),weight(highest_word));
            }
        }
        }
    }
    fclose(fp);
   
if(good == 1)
{
printf("Best word from the dictionary is :");
printf("%s",highest_word);
}
else if(found == 1)
printf("No good word found!");
else
printf("There are no words matching these letters");
printf("\nand the score is %d \n",s);

clock_t end = clock();
	
	double time= ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Processing time: %f seconds\n", time);

}
