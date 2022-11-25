/***************************************
* S22 ? Assignment 2 *
* Author: Patel,Aum *
* Email: aump@my.yorku.ca *
* eecs_username: aump *
* York num:218153338
****************************************/

#include <stdio.h>
#include <ctype.h>  // for tolower
#include <string.h>
#include <stdlib.h>

#define SIZE 42
#define fieldLength 250



struct db_type
{
   char name[fieldLength];

   int age;

   int height;   // cm
   float bmi;
   char status[fieldLength] ;
};


char prompt_menu(void);
void enterNew(struct db_type * pArr[]);
void init_list(struct db_type * pArr[]);
void displayDB(struct db_type * pArr[]);
void sortDB(struct db_type * pArr[]);
void updateRecord(struct db_type * pArr[]);
void removeRecord(struct db_type * pArr[]);
void clearDB(struct db_type * pArr[]);


int main(int argc, char *argv[])
{

    struct db_type * db_pArr[SIZE];  // main db storage

    init_list(db_pArr);  // set to NULL

    char choice;
    for(; ;){
      choice = prompt_menu();
      switch (choice)
      {
         case 'n': enterNew(db_pArr); break;
         case 'd': displayDB(db_pArr); break;

         case 's': sortDB(db_pArr); break;

         case 'c': clearDB(db_pArr); break;

         case 'u': updateRecord(db_pArr); break;
         case 'r': removeRecord(db_pArr);break;

         case 'q': exit(1); // terminate the whole program
       }

     }
     return 0;
}


char prompt_menu(void){
  char s[80];
  while(1){
    printf("\n-----------------------------------------------------------------\n");
    printf("|    %-20s","(N)ew record");
    printf("%-20s","(R)emove record");
    printf("(U)pdate record\t|\n");
    printf("|    %-20s","(S)ort database");
    printf("%-20s","(C)lear database");
    printf("(D)isplay database\t|\n");

    printf("|    %-20s","(Q)uit");
    printf("*Case Insensitive*\t\t\t|\n");
    printf("-----------------------------------------------------------------\n");
    printf("choose one: ");

    fgets(s,50, stdin); // \n added
    //scanf("%s", s);
    if (strlen(s) == 2 && strchr("edlsuqrcwnvpr", tolower(*s)))
       return tolower(*s); // s[0], return the first character of s
    //else
    printf("not a valid input!\n");

 }
}


void init_list(struct db_type * pArr[]){
  int t;
  for (t=0; t<SIZE; t++)
  {
     pArr[t]= NULL;
  }
}

/* delete all the records in the database */
void clearDB(struct db_type * pArr[]){
   char yn[3];
   printf("are you sure to clear database? (y) or (n)? ");

   fgets(yn,3,stdin);

   // complete the function by calling init_list();
   if(strcmp("y\n",yn)==0)
    init_list(pArr);

}


/* input items into the database */
/* hint: need malloc */
void enterNew(struct db_type * pArr[SIZE])
{
   int ht,wt,ag;
   float Bmi;
   char Name[fieldLength];

   printf("name: ");
   scanf("%[^\n]s",Name);
   //[^\n]s by this we can accept whole sentence as string
   printf("age: ");
   scanf("%d",&ag);

   printf("height (cm): ");
   scanf("%d",&ht);

   printf("weight (kg): ");
   scanf("%d",&wt);
   //BMI calculating
   Bmi = (float)wt/(ht*ht);
   Bmi = 10000*Bmi;
getchar();

   struct db_type *newNode = malloc(sizeof(struct db_type));
   strcpy(newNode->name,Name);
   newNode->age = ag;
   newNode->height = ht;
   newNode->bmi = Bmi;
if(Bmi<18.5){
    strcpy(newNode->status,"Underweight");
}
else if(Bmi>=18.5 && Bmi<=24.999){
    strcpy(newNode->status,"Normal weight");
}
else if(Bmi>=25.0 && Bmi<=29.999){
    strcpy(newNode->status,"Overweight");

}
else if(Bmi>=30.0 && Bmi<=34.999){
    strcpy(newNode->status,"Obese class I");
}
else if(Bmi>=35.0 && Bmi<=39.999){
     strcpy(newNode->status,"Obese class II");
}
else if(Bmi>=40.0){
    strcpy(newNode->status,"Obese class III");
}
//joining node to main list
int i;
for(i=0;i<SIZE;i++){
    if(pArr[i]==NULL){
        pArr[i] = newNode;
        break;
    }
    i++;
}

}


/* remove an existing item from the database */
void removeRecord (struct db_type * pArr[])
{
char Name[fieldLength] ;
int k,l;


   printf("enter full name to remove: ");
   scanf("%[^\n]s",Name);
   getchar();

   int b=0;
   for(k=0;k<SIZE;k++){
    if(pArr[k]!=NULL && strcmp(pArr[k]->name,Name)==0){
       l = k;

        while(l<SIZE-1){
            pArr[l] = pArr[l+1];
            l++;
        }
        b = 1;
    }
   }

if(b==1){
    printf("record [%s] removed successfully\n",Name);
}
else{
    printf("record not found!");
}


}

/* display all the records in the database. Generate output with the same formaing as the sample output
 use \t to align well
*/
void displayDB(struct db_type * pArr[]){

  int t,c;
  c = 0;
  printf("===============================\n");
  for (t=0; t <SIZE ; t++)
  {
     if( pArr[t] != NULL)
     {
        printf("\nname:\t%s\nage:\t%d\nheight:\t%d\nBMI:\t%.1f\nstatus:\t%s",   pArr[t]->name,pArr[t]->age,pArr[t]->height,pArr[t]->bmi,pArr[t]->status );
        //....
        c++;
        printf("\n");
     }
    // ....

  }

 printf("========== %d records ==========",c);
}


 /* modify an existing item */
void updateRecord (struct db_type * pArr[])	{
 //  ...
 char Name[fieldLength] ;
int k,b;
float newWt,newBmi;
b = 0;
  printf("enter full name to search: ");
 scanf("%[^\n]s",Name);
   getchar();
k=0;

while(k<SIZE){
    if(pArr[k]!=NULL && strcmp(pArr[k]->name,Name)==0){
        b=1;
        break;
       }
       k++;
}
if(b==1){
    printf("record found, enter new weight (kg): ");
    scanf("%f",&newWt);
    getchar();
    int ht = pArr[k]->height;
    newBmi = newWt/(ht*ht);
   newBmi = 10000*newBmi;
pArr[k]->bmi = newBmi;
if(newBmi<18.5){
    strcat(pArr[k]->status," -> Underweight");
}
else if(newBmi>=18.5 && newBmi<=24.999){
    strcat(pArr[k]->status," -> Normal weight");
}
else if(newBmi>=25.0 && newBmi<=29.999){
    strcat(pArr[k]->status," -> Overweight");

}
else if(newBmi>=30.0 && newBmi<=34.999){
    strcat(pArr[k]->status," -> Obese class I");
}
else if(newBmi>=35.0 && newBmi<=39.999){
     strcat(pArr[k]->status," -> Obese class II");
}
else if(newBmi>=40.0){
    strcat(pArr[k]->status," -> Obese class III");
}
printf("record [%s] updated successfully.",Name);
}
else{
    printf("record not found!");
}
}


// sort the record, either by name or BMI, prompt use for choice
void sortDB(struct db_type * pArr[])
{

  printf("sort by name (n) or BMI (b)? ");
  char nb[3];
  scanf("%[^\n]s",nb);
   getchar();

}

