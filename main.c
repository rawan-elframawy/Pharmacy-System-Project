#include <stdio.h>
#include <stdlib.h>
#include <string.h>




typedef struct medicine {
    int id;
    char name[40];
    int quantity;
    char company[40];
    float price;
    char manu_date[15];
    char expiry_date[15];
}medicine;
int found = 0;
int choice;
int i=0;
int x;
//---------------------------------------------------------------------------------
void add_medicine(void){                                             // Add function .
    int id_special=1;
    int name_special=1;
    medicine *m;                                                     //pointer with type medicine .
    medicine m1;
    FILE *fp;
    int num,i;
    printf("Enter how many medicines you want: ");
    scanf("%d",&num);                                               // Take number of medicines to add .
    m = (medicine *)calloc(num,sizeof(medicine));                   // Memory allocation .
    for (i=0;i<num;i++){                                            // Loop to take information from user .
        printf("Enter Medicine ID:                      ");
        scanf("%d",&m[i].id);
        fflush(stdin);
        fp = fopen("medicine.txt","r" );
        while(fread(&m1, sizeof(medicine),1,fp)){                   //loop for reading file
            if(m[i].id == m1.id){
                id_special=0;
                printf("\nID is already exist . . .\n\n");
                fclose(fp);
                break;
            }
        }
        if(id_special){
            printf("Enter Medicine name:                    ");
            scanf("%[^\n]m",m[i].name);
            fp = fopen("medicine.txt","r" );
            while(fread(&m1, sizeof(medicine),1,fp)){                   //loop for reading file
                if(!strcmp(strlwr(m[i].name),strlwr(m1.name))){
                   name_special=0;
                   printf("\nName is already exist . . .\n\n");
                   fclose(fp);
                   break;
            }
            }
            if (id_special&&name_special){
                fp = fopen("medicine.txt","a" );
                printf("Enter Medicine quantity:                 ");
                scanf("%d",&m[i].quantity);
                fflush(stdin);
                printf("Enter Medicine company:                 ");
                scanf("%[^\n]m",m[i].company);
                printf("Enter Medicine price:                   ");
                scanf("%f",&m[i].price);
                printf("Enter Medicine Manufacturing date:      ");
                scanf("%s",&m[i].manu_date);
                fflush(stdin);
                printf("Enter Medicine Expiry date:             ");
                scanf("%s",&m[i].expiry_date);
                fwrite(&m[i],sizeof(medicine ),1,fp);                        // Store data in the file .
                fclose(fp);
            }
        }
     }
     fclose(fp);
}
//---------------------------------------------------------------------------------
void delete_medicine(void){
    medicine m1;                                                     //variables and file declarations
    FILE *fp,*fp1;
    fp1 = fopen("temp.txt","w");                                     //opening main file
    fclose(fp1);
    printf("1.ID or 2.Name  ?   ");
    scanf("%d",&choice);
    if (choice==1){
        int id;
        printf("Write the ID :  ");
        scanf("%d",&id);
        fp = fopen("medicine.txt","r");                             //open main file to read and temp file to write in
        fp1 = fopen("temp.txt","w");
        while(fread(&m1, sizeof(medicine),1,fp)){                  //loop for reading file
            if(m1.id == id){
                printf("\n\nDeleted successfully . . . \n");
                found = 1;
                continue;
            }
            fwrite(&m1,sizeof(medicine),1,fp1);                    //write info in temp file
        }
        fclose(fp);                                                 //closing both files
        fclose(fp1);
        fp = fopen("medicine.txt","w");
        fclose(fp);
        fp = fopen("medicine.txt","w");                             //opening medicine file to write from
        fp1 = fopen("temp.txt","r");                                //opening temp file to read info from
        while(fread(&m1, sizeof(medicine),1,fp1)){                  //loop for reading file
             fwrite(&m1,sizeof(medicine ),1,fp);                    //writing from temp file to main file
        }
        fclose(fp);                                                 //closing both files
        fclose(fp1);
    }
    else if (choice==2){
        char name[20];
        printf("Write the Name :  ");
        scanf("%s",&name);
        fp = fopen("medicine.txt","r");
        fp1 = fopen("temp.txt","w");
        while(fread(&m1, sizeof(medicine),1,fp)){
            if(!strcmp(strlwr(m1.name),strlwr(name))){
                printf("\n\nDeleted successfully . . . \n");
                found = 1;
                continue;
            }
            fwrite(&m1,sizeof(medicine),1,fp1);
        }
        fclose(fp);
        fclose(fp1);
        fp = fopen("medicine.txt","w");
        fclose(fp);
        fp = fopen("medicine.txt","w");
        fp1 = fopen("temp.txt","r");
        while(fread(&m1, sizeof(medicine),1,fp1)){
             fwrite(&m1,sizeof(medicine ),1,fp);
      }
      fclose(fp);
      fclose(fp1);
    }
    else {
        printf("\n\nNone\n\n");
    }
    if (!found){
        printf("\n\nMedicine Not Found . . .\n");
    }
}
//---------------------------------------------------------------------------------
void stock_medicine(void){
    medicine m1;
    FILE *fp;
    fp = fopen("medicine.txt","r");
    printf("\nID\t\tName\t\tQuantity\tCompany\t\tPrice\t\t\tMan Date\t\tEx date\n");
    printf("_________________________________________________________________________________________________________________________\n");
    while(fread(&m1, sizeof(medicine),1, fp)){                      //loop for reading file and printing struct
        printf("\n%d\t\t",m1.id);
        printf("%s\t\t",m1.name);
        printf("%d\t\t",m1.quantity);
        printf("%s\t\t",m1.company);
        printf("%.2f L.E\t\t",m1.price);
        printf("%s\t\t",m1.manu_date);
        printf("%s\t\t",m1.expiry_date);
        printf("\n");
    }
    fclose(fp);
}
//---------------------------------------------------------------------------------
void update_medicine(int id){                                         //id as parameter
   medicine  m1;                                                      //variables and file declarations
   FILE *fp, *fp1;
   int option;
   fp = fopen("medicine.txt","r");                                    //opening main file
    while(fread(&m1, sizeof(medicine),1,fp)){                         //loop for reading from it to search for the id user entered
        if(m1.id == id){
            found = 1;
            break;
        }
    }

    if (found)
    {
        fp=fopen("medicine.txt","r");                                //open main file to read and temp file to write in
        fp1=fopen("tmp.txt","w");
        do{                                                          //update menu
            printf("\n\n\n1. Change quantity\n");
            printf("\n2. Change price\n");
            printf("\n3. Change manufacturing date\n");
            printf("\n4. Change expiry date\n");
            printf("\n5. Change name\n");
            printf("\n6. Change company name\n");
            printf("\n0. Quit\n");
            printf("\nEnter the number of operation you want:   ");
            scanf("%d",&option);
            switch (option) {
                  case 1:                                            //case 1, i.e. change quantity
                    if(fp==NULL){
                        fprintf(stderr,"Error opening the file");
                    }
                    else {
                        while (fread(&m1,sizeof(medicine),1,fp)){     //loop for reading main file
                        if(!(m1.id==id)){                             //if not the entered id, write info in temp file
                            fwrite(&m1, sizeof(medicine), 1, fp1);
                        }
                        else{
                            printf("Enter the new quantity:\n");      //if entered id, take new info from user
                            scanf("%d",&m1.quantity);
                            fwrite(&m1, sizeof(medicine), 1, fp1);    //write info in temp file
                            }
                        }
                        fclose(fp);                                   //closing both files
                        fclose(fp1);
                        fp1 = fopen("tmp.txt", "r");                   //opening temp file to read info from
                        fp = fopen("medicine.txt", "w");               //opening main file to write in it w/ new info
                        while (fread(&m1, sizeof(medicine), 1, fp1)){  //writing from temp file to main file
                            fwrite(&m1, sizeof(medicine), 1, fp);
                        }

                    }
                        fclose(fp);                                    //closing both files
                        fclose(fp1);
                        printf("\n\nUpdated Successfully . . . !\n");    //telling user data has been updated
                        break;
           case 2:
                if(fp==NULL)
                {
                   fprintf(stderr,"Error opening the file");
                }
                else {
                    while (fread(&m1,sizeof(medicine),1,fp)){
                    if(!(m1.id==id)){
                        fwrite(&m1, sizeof(medicine), 1, fp1);
                    }
                    else{
                        printf("Enter the new price:\n");
                        scanf("%f",&m1.price);
                        fwrite(&m1, sizeof(medicine), 1, fp1);

                        }
                        }

                        fclose(fp);
                        fclose(fp1);
                        fp1 = fopen("tmp.txt", "r");
                        fp = fopen("medicine.txt", "w");
                        while (fread(&m1, sizeof(medicine), 1, fp1)){
                            fwrite(&m1, sizeof(medicine), 1, fp);
                        }

                    }
                        fclose(fp);
                        fclose(fp1);
                        printf("\n\nUpdated Successfully . . . !\n");

                        break;
            case 3:
                if(fp==NULL)
                 {
                   fprintf(stderr,"Error opening the file");
                 }
                 else {
                    while (fread(&m1,sizeof(medicine),1,fp)){
                        if(!(m1.id==id)){
                            fwrite(&m1, sizeof(medicine), 1, fp1);
                        }
                        else{
                            printf("Enter the new manufacturing date:\n");
                            scanf("%s",&m1.manu_date);
                            fwrite(&m1, sizeof(medicine), 1, fp1);

                            }
                        }
                        fclose(fp);
                        fclose(fp1);
                        fp1 = fopen("tmp.txt", "r");
                        fp = fopen("medicine.txt", "w");
                        while (fread(&m1, sizeof(medicine), 1, fp1)){
                            fwrite(&m1, sizeof(medicine), 1, fp);
                        }
                    }
                        fclose(fp);
                        fclose(fp1);
                        printf("\n\nUpdated Successfully . . . !\n");
                        break;
            case 4:
                if(fp==NULL)
                {
                   fprintf(stderr,"Error opening the file");
                }
                else {
                    while (fread(&m1,sizeof(medicine),1,fp)){
                    if(!(m1.id==id)){
                        fwrite(&m1, sizeof(medicine), 1, fp1);
                        }
                        else{
                            printf("Enter the new expiry date:\n");
                            scanf("%s",&m1.expiry_date);
                            fwrite(&m1, sizeof(medicine), 1, fp1);

                        }
                        }

                        fclose(fp);
                        fclose(fp1);
                        fp1 = fopen("tmp.txt", "r");
                        fp = fopen("medicine.txt", "w");
                        while (fread(&m1, sizeof(medicine), 1, fp1)){
                            fwrite(&m1, sizeof(medicine), 1, fp);
                        }
                    }
                        fclose(fp);
                        fclose(fp1);
                        printf("\n\nUpdated Successfully . . . !\n");
                        break;
            case 5:
                if(fp==NULL)
                {
                   fprintf(stderr,"Error opening the file");
                }
                else {
                    while (fread(&m1,sizeof(medicine),1,fp)){
                        if(!(m1.id==id)){
                            fwrite(&m1, sizeof(medicine), 1, fp1);
                        }
                        else{
                            printf("Enter the new name:\n");
                            scanf("%s",&m1.name);
                            fwrite(&m1, sizeof(medicine), 1, fp1);
                             }
                        }
                        fclose(fp);
                        fclose(fp1);
                        fp1 = fopen("tmp.txt", "r");
                        fp = fopen("medicine.txt", "w");
                        while (fread(&m1, sizeof(medicine), 1, fp1)){
                            fwrite(&m1, sizeof(medicine), 1, fp);
                        }
                    }
                        fclose(fp);
                        fclose(fp1);
                        printf("\n\nUpdated Successfully . . . !\n");
                        break;
             case 6:
                if(fp1==NULL)
                {
                   fprintf(stderr,"Error opening the file");
                }
                else {
                    while (fread(&m1,sizeof(medicine),1,fp)){
                        if(!(m1.id==id)){
                            fwrite(&m1, sizeof(medicine), 1, fp1);
                        }
                        else{
                            printf("Enter the new company name:\n");
                            scanf("%s",&m1.company);
                            fwrite(&m1, sizeof(medicine), 1, fp1);
                        }
                    }
                    fclose(fp);
                    fclose(fp1);
                    fp1 = fopen("tmp.txt", "r");
                    fp = fopen("medicine.txt", "w");
                    while (fread(&m1, sizeof(medicine), 1, fp1)){
                        fwrite(&m1, sizeof(medicine), 1, fp);
                        }
                    }
                    fclose(fp);
                    fclose(fp1);
                    printf("\n\nUpdated Successfully . . . !\n");
                        break;
            case 0:
                break;
            default:
                printf("\n\nNone\n\n");
    }
}while(option!=0);
}
    else
    {
        printf("\n\nMedicine Not Found . . . \n\n");

    }
}
//---------------------------------------------------------------------------------
void search_medicine(){
    printf("1.ID or 2.Name  ?   ");
    scanf("%d",&choice);
    if(choice==1){
        medicine m1;
        FILE *fp;
        int id;
        printf("Write the ID :  ");
        scanf("%d",&id);
        fp = fopen("medicine.txt","r");
        while(fread(&m1, sizeof(medicine),1,fp)){
            if(m1.id == id){
                found = 1;
                printf("\nID\t\tName\t\tQuantity\tCompany\t\tPrice\t\tMan Date\t\tEx date\n");
                printf("%d\t\t",m1.id);
                printf("%s\t\t",m1.name);
                printf("%d\t\t",m1.quantity);
                printf("%s\t\t",m1.company);
                printf("%.2f L.E\t\t",m1.price);
                printf("%s\t\t",m1.manu_date);
                printf("%s\t\t",m1.expiry_date);
                printf("\n\n\n");
            }
        }
        if(found==0){
            printf("\n\nMedicine not found");
        }
        fclose(fp);
    }
    else if(choice==2){
        medicine m1;
        FILE *fp;
        char name[40];
        printf("Write the name :  ");
        scanf("%s",&name);
        fp = fopen("medicine.txt","r");
            while(fread(&m1, sizeof(medicine),1,fp)){
                if(!strcmp(strlwr(m1.name),strlwr(name))){               // Comparing two names with strcmp function
                    found = 1;
                    printf("\nID\t\tName\t\tQuantity\tCompany\t\tPrice\t\tMan Date\t\tEx date\n");
                    printf("%d\t\t",m1.id);
                    printf("%s\t\t",m1.name);
                    printf("%d\t\t",m1.quantity);
                    printf("%s\t\t",m1.company);
                    printf("%.2f\t\t",m1.price);
                    printf("%s\t\t",m1.manu_date);
                    printf("%s\t\t",m1.expiry_date);
                    printf("\n\n\n");
                }
            }
        if(found==0){
            printf("Medicine not found");
        }
        fclose(fp);
    }
     else {
        printf("\n\nNone\n\n");
    }
}
//---------------------------------------------------------------------------------
void sell_medicine(void){
    FILE *fp,*fp1;
    fp1 = fopen("temp.txt","w");
    fclose(fp1);
    medicine m1;
    int answer;
    printf("1.ID or 2.Name  ?   ");                                   //asking user what to search with
    scanf("%d",&choice);                                              //taking user choice
    if(choice==1){
        medicine m1;
        FILE *fp;
        int id;
        printf("Write the ID :  ");
        scanf("%d",&id);
        fp = fopen("medicine.txt","r");                               //open main file to read and temp file to write in
        fp1 = fopen("temp.txt","w");
        while(fread(&m1, sizeof(medicine),1,fp)){
            if(m1.id == id){                                                     //searching for id, flag if found.
                found = 1;                                                       //flag
                printf("\nID\t\tName\t\tQuantity\tCompany\t\tPrice\t\t\tMan Date\t\tEx date\n");
                printf("%d\t\t",m1.id);                                          //printing its info
                printf("%s\t\t",m1.name);                                        //printing the id from the struct
                printf("%d\t\t",m1.quantity);                                    //printing the name from the struct
                printf("%s\t\t",m1.company);                                     //printing the company from the struct
                printf("%.2f L.E\t\t",m1.price);                                 //printing the price from the struct
                printf("%s\t\t",m1.manu_date);                                   //printing the manu date from the struct
                printf("%s\t\t",m1.expiry_date);                                 //printing the expiry date from the struct
                printf("\n\n\n");
                printf("Are you sure to buy medicine (1 if YES)(0 if NO)?  ");   //asking the user if he want the medicine or not
                scanf("%d",&answer);                                             //taking the answer from the user
                fflush(stdin);
                if(answer==1){
                    int sell_quan;
                    printf("what is the quantity to sell ?  ");                  //asking the user about the quantity he wants
                    scanf("%d",&sell_quan);                                      //taking the number of quantity from the user
                    m1.id=m1.id;
                    strcpy(m1.name, m1.name);                                    //coping one string to another
                    m1.quantity=m1.quantity-sell_quan;                           //decrease the quantity in the data
                    strcpy(m1.manu_date,m1.manu_date);
                    strcpy(m1.expiry_date, m1.expiry_date);
                    fwrite(&m1,sizeof(medicine),1,fp1);                           //writing from temp file to main file
                    printf("Total price : %.2f L.E \n\n",(m1.price*sell_quan));    //printing the total price
                    continue;
                }

            }
            fwrite(&m1,sizeof(medicine),1,fp1);
        }
        fclose(fp);
        fclose(fp1);
        fp = fopen("medicine.txt","w");
        fclose(fp);
        fp = fopen("medicine.txt","w");
        fp1 = fopen("temp.txt","r");
        while(fread(&m1, sizeof(medicine),1,fp1)){
            fwrite(&m1,sizeof(medicine ),1,fp);
        }
        fclose(fp);
        fclose(fp1);
    }
    else if(choice==2){
        medicine m1;
        FILE *fp;
        char name[40];
        printf("Write the name :  ");
        scanf("%s",&name);
        fflush(stdin);
        fp = fopen("medicine.txt","r");
        fp1 = fopen("temp.txt","w");
            while(fread(&m1, sizeof(medicine),1,fp)){
                if(!strcmp(strlwr(m1.name),strlwr(name))){
                    found = 1;
                    printf("\nID\t\tName\t\tQuantity\tCompany\t\tPrice\t\tMan Date\t\tEx date\n");
                    printf("%d\t\t",m1.id);
                    printf("%s\t\t",m1.name);
                    printf("%d\t\t",m1.quantity);
                    printf("%s\t\t",m1.company);
                    printf("%.2f\t\t",m1.price);
                    printf("%s\t\t",m1.manu_date);
                    printf("%s\t\t",m1.expiry_date);
                    printf("\n\n\n");
                    printf("Are you sure to buy medicine (1 if YES)(0 if NO)?  ");
                    scanf("%d",&answer);
                    fflush(stdin);
                    if(answer==1){
                        int sell_quan;
                        printf("what is the quantity to sell ?  ");
                        scanf("%d",&sell_quan);
                        m1.id=m1.id;
                        strcpy(m1.name, m1.name);
                        m1.quantity=m1.quantity-sell_quan;
                        strcpy(m1.manu_date,m1.manu_date);
                        strcpy(m1.expiry_date, m1.expiry_date);
                        fwrite(&m1,sizeof(medicine),1,fp1);
                        printf("Total price : %.2f \n\n",(m1.price*sell_quan));
                        continue;
                     }
              }
              fwrite(&m1,sizeof(medicine),1,fp1);
         }
         fclose(fp);                                         //closing the main file
         fclose(fp1);                                        //closing the temp file
         fp = fopen("medicine.txt","w");
         fclose(fp);
         fp = fopen("medicine.txt","w");
         fp1 = fopen("temp.txt","r");
         while(fread(&m1, sizeof(medicine),1,fp1)){           //reading the data from temp file
             fwrite(&m1,sizeof(medicine ),1,fp);              //writing the new data in the main file
         }
         fclose(fp);
         fclose(fp1);
    }
    if(found==0){
        printf("Medicine not found");
    }
}
//---------------------------------------------------------------------------------
int main(){
    int id;
    system("COLOR 1E");
    printf("\n\t\t\t\t\tHello , This is the pharmacy system . . .\n\n\n");
    int option;
    do{
        printf("\n\n\n\n\n1. Add medicine\n");
        printf("__________________________________________________________________________\n");
        printf("2. Delete medicine\n");
        printf("__________________________________________________________________________\n");
        printf("3. Update medicine\n");
        printf("__________________________________________________________________________\n");
        printf("4. Print medicines in stock\n");
        printf("__________________________________________________________________________\n");
        printf("5. Get medicine info\n");
        printf("__________________________________________________________________________\n");
        printf("6. Sell medicine\n");
        printf("__________________________________________________________________________\n");
        printf("0. Quit\n");
        printf("__________________________________________________________________________\n");
        printf("\nEnter number of operation you want to do .  .  .  ");
        scanf("%d",&option);
        switch (option) {
            case 1:
                add_medicine();
                break;
            case 2:
                delete_medicine();
                break;
            case 3:
                printf("Enter medicine id:     ");
                scanf("%d",&id);
                update_medicine(id);
                break;
            case 4:
                stock_medicine();
                break;
            case 5:
                search_medicine();
                break;
            case 6:
                sell_medicine();
                break;
            case 0:
                break;
            default:
                printf("\n\nNone");
                break;
        }
    }while(option!=0);
    return 0;
}
