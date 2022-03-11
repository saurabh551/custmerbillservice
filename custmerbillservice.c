#include<stdio.h>
#include<string.h>
#include<stdlib.h>



struct items
{
    char item[20];
    float price;
    int qty;

};

struct orders{
    char customer[50];
    char date[50];
    int numOfItems;
    struct items itm[50];
};

void generateBillHeader(char name[50], char date[30]){
    printf("\n\n");
    printf("\t       Aith Restorant");
    printf("\n\t----------------");
    printf("\nDate:%s",date);
     printf("\nInvoice To: %s",name);
      printf("\n");
       printf("--------------------------\n");
        printf("Items\t\t");
         printf("Qty\t\t");
          printf("Total\t\t");
           printf("\n--------------------------");
            printf("\n\n");
}
void generateBillBody(char item[30],int qty,float price){
    printf("%s\t\t\t",item);
    printf("%d\t\t",qty);
    printf("%.2f\t\t",qty*price);
printf("\n");
}



void generateBillFooter(float total){
    printf("\n");
    float dis = 0.1*total;
    float netTotal = total-dis;
    float cgst = 0.09*netTotal,grandTotal=netTotal +2*cgst;
    printf("--------------------------------------------\n");
    printf("Sub Total\t\t\t\t%.2f",total);
    printf("\nDiscount @10%s\t\t\t\t%.2f","%",dis);
    printf("\n\t\t\t\t\t\t-----------");
    printf("\nNet Total\t\t\t\t%.2f",netTotal);
     printf("\nCGST @9%s\t\t\t\t%.2f","%",cgst);
     printf("\nCGST @9%s\t\t\t\t%.2f","%",cgst);
     printf("\n--------------------------------------------");
      printf("\nGrand Total\t\t\t\t%.2f",grandTotal);
      printf("\n--------------------------------------------");

}

int main(){

   float total;
   struct orders ord;
   struct orders order;
    int opt,n;
    char saveBill= 'y',contFlag;
    char name[50];
    FILE *fp;

     while(contFlag!=4){
         system("clear");
         float total =0;
        int invoiceFound =0;

      printf("\t==========AITH RESTAURANT MENU=============");
      printf("\n\tSANDWICHES");
      printf("\n1.Veg Sandwich \t        45\t\t   2.Veg Cheese Sandwich \t      70");
      printf("\n3.Club Sandwich(4 Pcs)  75/85\t\t  4.Cheese corn Sandwich \t   90");
      printf("\n5.Paneer Sandwich \t  85\t\t   6.Egg Sandwich \t              70");
printf("\n\n\tCHINES");
      printf("\n1.Veg Chowmein \t         100\t\t  2.Paneer Chowmein \t         130");
      printf("\n3.Mushroom Chowmein \t  130\t\t  4.Hakka Noodles \t          70");
       printf("\n5.Veg Fried Rice \t   120\t\t  6.Paneer Fried Rice \t         130");
       printf("\n\n\tROLLS");
        printf("\n1.Veg Roll \t          60\t\t   2.Paneer Roll \t              80");
      printf("\n3.Paneer Tikka Roll  \t 100\t\t  4.Veg Kabab Roll \t            90");
       printf("\n5.Egg Roll \t         80\t\t   6.Chicken Roll \t              100");
       printf("\n\n\tSNACKS");
       printf("\n1.Paneer 65 \t         160\t\t  2.Paneer Fry \t                80");
      printf("\n3.Cheese Cigar Roll  \t 170\t\t  4.Paneer Pakoda \t          120");
       printf("\n5.Veg Pakoda \t         80\t\t   6.Crispy corn \t           150");
      printf("\n\nPlease select your prefered operation:");
    printf("\n1.Generate Invoice");
     printf("\n2.Show all Invoices");
      printf("\n3.Search Invoice");
       printf("\n4.Exit");

       printf("\n\nYour Choice:\t ");
scanf("%d",&opt);
fgetc(stdin);

switch (opt)
{
case 1:


    printf("\nPlease enter the name of a customer:\t ");
   fgets(ord.customer, 50,stdin);
   ord.customer[strlen(ord.customer)-1]=0;
  // strcpy(ord.date,_DATE_);
   printf("\nPlease enter the number of items:\t");
   scanf("%d",&n);
ord.numOfItems=n;
   for(int i=0; i<n; i++){
       fgetc(stdin);
       printf("\n\n");
       printf("Please enter the item %d:\t",i+1);
       fgets(ord.itm[i].item,20,stdin);
       ord.itm[i].item[strlen(ord.itm[i].item)-1]=0;
       printf("\nPlease enter the quantity:\t");
       scanf("%d",&ord.itm[i].qty);
       printf("Please enter the price: \t");
       scanf("%f",&ord.itm[i].price);
total +=ord.itm[i].qty * ord.itm[i].price;
   }

   generateBillHeader(ord.customer,ord.date);
   for(int i=0; i<ord.numOfItems; i++){
generateBillBody(ord.itm[i].item, ord.itm[i].qty,ord.itm[i].price);
   }
   generateBillFooter(total);
   printf("\nDo you want to save the invoice [y/n]:\t");
   scanf("%s",&saveBill);
   if(saveBill=='y'){
       fp=fopen("RestaurantBill.dat","a+");
       fwrite(&ord,sizeof(struct orders),1,fp);
       if(fwrite != 0)
       printf("\nSuccessfully saved");
       else
       printf("\nError saving");
       fclose(fp);
   }

    break;

case 2:

fp=fopen("RestaurantBIll.dat","r");
printf("\n ***Your Previous Invoices****\n");
while(fread(&order,sizeof(struct orders),1,fp)){
    float tot=0;
    generateBillHeader(order.customer,order.date);
    for(int i=0; i<order.numOfItems; i++){
        generateBillBody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
        tot+=order.itm[i].qty * order.itm[i].price;

    }
    generateBillFooter(tot);

}
fclose(fp);
break;

case 3:
printf("\n Enter the name of the customer:\t");
//fgetc(stdin);
fgets(name,50,stdin);
name[strlen(name)-1]=0;

fp=fopen("RestaurantBIll.dat","r");
printf("\t**** Invoice of %s*****\n",name);
while(fread(&order,sizeof(struct orders),1,fp)){
    float tot=0;
    if(!strcmp(order.customer,name)){
 generateBillHeader(order.customer,order.date);
    for(int i=0; i<order.numOfItems; i++){
        generateBillBody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
        tot+=order.itm[i].qty * order.itm[i].price;

    }
    generateBillFooter(tot);
invoiceFound = 1;
    }

}
if(!invoiceFound){
    printf("Sorry the invoice for %s doesnot exists", name);
}
fclose(fp);
break;

case 4:
printf("\n\t\tBye Bye :\t\t");
exit(0);
break;

default:
printf("Sorry invalid option");
break;

}
printf("\nDo you want to perform another operation?[y/n]:\t");
scanf("%s", &contFlag);
}
     printf("\n\t\tBye Bye :\t\t");
       printf("\n\n");

return 0;
}
