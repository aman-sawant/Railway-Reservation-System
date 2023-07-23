#include<stdio.h>
#include<string.h>
#include<stdlib.h>
char src[20],dst[20],date[10],avl,front=-1,rear=-1;
int psg_no;
struct traind
{
    char name[20],time[20];
    int avl;
    float price;
}t;
struct pdetails
{
    char name[20],gen[2],src[20],dst[20],tname[20],time[20],date[20];
    int age,bid;
}pd[100];
struct pdetailsw
{
    char name[20],gen[2],src[20],dst[20],tname[20],time[20],date[20];
    int age,bid;
}pdw[100];
void cancel(int x);
void readtrain();
int readconfirm();
int readwaiting();
void display();
void readtrain()
{
    FILE *fp1;
    char *sp,line[100];
    fp1=fopen("train.csv","r");
    while(fgets(line,100,fp1)!=NULL)
    {
        sp=strtok(line,",");
        strcpy(t.name,sp);
        sp=strtok(NULL,",");
        strcpy(t.time,sp);
        sp=strtok(NULL,",");
        t.avl=atoi(sp);
        sp=strtok(NULL,",");
        t.price=atof(sp);       
    }
    fclose(fp1);
}
int readconfirm()
{
    FILE *f;
    f=fopen("confirm.csv","r");    
    int j=0;
    char line[100],*sp;
    while(fgets(line,100,f)!=NULL)
    {
        sp=strtok(line,",");
        pd[j].bid=atoi(sp);
        sp=strtok(NULL,",");
        strcpy(pd[j].name,sp);
        sp=strtok(NULL,",");
        pd[j].age=atoi(sp);
        sp=strtok(NULL,",");
        strcpy(pd[j].gen,sp);
        sp=strtok(NULL,",");
        strcpy(pd[j].src,sp);
        sp=strtok(NULL,",");
        strcpy(pd[j].dst,sp);
        sp=strtok(NULL,",");
        strcpy(pd[j].tname,sp);
        sp=strtok(NULL,",");
        strcpy(pd[j].time,sp);
        sp=strtok(NULL,",");
        strcpy(pd[j].date,sp);
        j++;
    }
    return j;
}
int readwaiting()
{
    FILE *f;
    f=fopen("waiting.csv","r");    
    int j=0;
    char line[100],*sp;
    while(fgets(line,100,f)!=NULL)
    {
        if(front==-1)
        {
            front++;
        }
        sp=strtok(line,",");
        pdw[j].bid=atoi(sp);
        sp=strtok(NULL,",");
        strcpy(pdw[j].name,sp);
        sp=strtok(NULL,",");
        pdw[j].age=atoi(sp);
        sp=strtok(NULL,",");
        strcpy(pdw[j].gen,sp);
        sp=strtok(NULL,",");
        strcpy(pdw[j].src,sp);
        sp=strtok(NULL,",");
        strcpy(pdw[j].dst,sp);
        sp=strtok(NULL,",");
        strcpy(pdw[j].tname,sp);
        sp=strtok(NULL,",");
        strcpy(pdw[j].time,sp);
        sp=strtok(NULL,",");
        strcpy(pdw[j].date,sp);
        j++,rear++;
    }
}
void input()
{
    int i;
    printf("ENTER SOURCE STATION CODE\n");
    scanf("%s",src);
    printf("ENTER DESTINATION STATION CODE\n");
    scanf("%s",dst);
    printf("ENTER DATE(DD/MM/YYYY)\n");
    scanf("%s",date);
}
void train()
{
    int i=0;
    FILE *fp1;
    if(fp1==NULL)
    {
        printf("NOT WORKKING\n");
    }
    readtrain();
    printf("TRAIN NUMBER\tTRAIN NAME\t\tTIME\t\tAVAILABLITY\tPRICE\n");
    printf("%d\t\t%s\t%s\t%d\t\tRs.%f",i+1,t.name,t.time,t.avl,t.price);
    printf("\n");
    printf("ENTER NUMBER OF PASSENGERS\n");
    scanf("%d",&psg_no);
    avl=t.avl;
    t.avl=t.avl-psg_no;
    fp1=fopen("train.csv","w");
    for(i=0;i<1;i++)
    {
        fprintf(fp1,"%s,%s,%d,%f",t.name,t.time,t.avl,t.price);
        fprintf(fp1,"\n");
    }
    fclose(fp1);
}
void details()
{
    int i,id;
    struct pdetails d[psg_no];
    FILE *fp,*f,*f2,*f3;
    fp=fopen("ticket.txt","w");
    f=fopen("confirm.csv","a");
    f3=fopen("waiting.csv","a");
    f2=fopen("bookingid.txt","r");
    fscanf(f2,"%d",&id);
    fprintf(fp,"SOURCE : %s",src);
    fprintf(fp,"\nDESTINATION : %s",dst);
    fprintf(fp,"\nDATE : %s",date);
    fprintf(fp,"\nTRAIN BOOKED DETAILS : \n");
    fprintf(fp,"TRAIN NAME\t\t\tTIME\t\tPRICE\n");
    fprintf(fp,"%s\t%s\tRs.%f",t.name,t.time,t.price);
    fprintf(fp,"\nID\tNAME\tAGE\tGENDER\tSTATUS\n");
    for(i=0;i<psg_no;i++,avl--)
    {
        id++;
        printf("ENTER NAME, AGE, GENDER(M/F/O)\n");
        scanf("%s %d %s",pd[i].name,&pd[i].age,&pd[i].gen);
        if(avl>0)
        {
            fprintf(fp,"%d\t%s\t%d\t%s\tCONFIRM",id,pd[i].name,pd[i].age,pd[i].gen);
            fprintf(fp,"\n");
            fprintf(f,"%d,%s,%d,%s,%s,%s,%s,%s,%s",id,pd[i].name,pd[i].age,pd[i].gen,src,dst,t.name,t.time,date);
            fprintf(f,"\n");
        }
        else
        {
            fprintf(fp,"%d\t%s\t%d\t%s\tWAITING",id,pd[i].name,pd[i].age,pd[i].gen);
            fprintf(fp,"\n");
            fprintf(f3,"%d,%s,%d,%s,%s,%s,%s,%s,%s",id,pd[i].name,pd[i].age,pd[i].gen,src,dst,t.name,t.time,date);
            fprintf(f3,"\n");
        }
    }
    fclose(f2);
    f2=fopen("bookingid.txt","w");
    fprintf(f2,"%d",id);
    float p=psg_no*t.price;
    fprintf(fp,"TOTAL BILL : Rs.%f",p);
    fclose(fp);
    fclose(f);
    fclose(f3);
    fclose(f2);
}
void display()
{
    FILE *fp;
    char d[100];
    fp=fopen("ticket.txt","r");
    printf("********************************************************\n");
    while(!feof(fp))
    {
        fgets(d,50,fp);
        printf("%s",d);
    }
}
void cancel(int x)
{
    FILE *f,*f2;
    int n1,n2,j,pos=-1;
    n1=readconfirm();
    for (j=0;j<n1;j++)
    {
        if (pd[j].bid==x)
        {
            printf("TICKET WITH BOOKING ID %d DELETED SUCCESSFULLY\n",pd[j].bid);
            pos=j;
            break;
        }
    }
    if (j==n1)
    {
        printf("BOOKING ID NOT FOUND\n");
    }
    else
    {
    for(j=pos;j<n1;j++)
    {
        pd[j].bid=pd[j+1].bid;
        strcpy(pd[j].name,pd[j+1].name);
        pd[j].age=pd[j+1].age;
        strcpy(pd[j].gen,pd[j+1].gen);
        strcpy(pd[j].src,pd[j+1].src);
        strcpy(pd[j].dst,pd[j+1].dst);
        strcpy(pd[j].tname,pd[j+1].tname);
        strcpy(pd[j].time,pd[j+1].time);
        strcpy(pd[j].date,pd[j+1].date);
    }   
    n1--;
    n2=readwaiting();
    f=fopen("confirm.csv","w");
    f2=fopen("waiting.csv","w");
    readtrain();
    if(pdw!=NULL)
    {
        pd[n1].bid=pdw[front].bid;
        strcpy(pd[n1].name,pdw[front].name);
        pd[n1].age=pdw[front].age;
        strcpy(pd[n1].gen,pdw[front].gen);
        strcpy(pd[n1].src,pdw[front].src);
        strcpy(pd[n1].dst,pdw[front].dst);
        strcpy(pd[n1].tname,pdw[front].tname);
        strcpy(pd[n1].time,pdw[front].time);
        strcpy(pd[n1].date,pdw[front].date);
        front++;
        n1++;
    }
    for(j=0;j<n1;j++)
    {
        fprintf(f,"%d,%s,%d,%s,%s,%s,%s,%s,%s",pd[j].bid,pd[j].name,pd[j].age,pd[j].gen,pd[j].src,pd[j].dst,pd[j].name,pd[j].time,pd[j].date);
    }
    for(j=front;j<=rear;j++)
    {
        fprintf(f2,"%d,%s,%d,%s,%s,%s,%s,%s,%s",pdw[j].bid,pdw[j].name,pdw[j].age,pdw[j].gen,pdw[j].src,pdw[j].dst,pdw[j].name,pdw[j].time,pdw[j].date);
    }
    fclose(f);
    fclose(f2);
    }
}
void status(int x)
{
    int n1,n2,j,pos=-1;
    n1=readconfirm();
    n2=readwaiting();
    for (j=0;j<n1;j++)
    {
        if (pd[j].bid==x)
        {
            pos=j;
            break;
        }
    }
    if(pos==-1)
    {
        for (j=0;j<n1;j++)
    {
        if (pdw[j].bid==x)
        {
            pos=j;
            break;
        }
    }
        if(pos!=-1)
    {
        printf("SOURCE : %s",pdw[pos].src);
        printf("\n");
        printf("DESTINATION : %s",pdw[pos].dst);
        printf("\nDATE : %s",pdw[pos].date);
        printf("\n");
        printf("TRAIN BOOKED DETAILS : \n");
        printf("TRAIN NAME\t\tTIME\n");
        printf("%s\t%s",pdw[pos].tname,pdw[pos].time);
        printf("\nID\tNAME\tAGE\tGENDER\tSTATUS\n");
        printf("%d\t%s\t%d\t%s\tWAITING",pdw[pos].bid,pdw[pos].name,pdw[pos].age,pdw[pos].gen);
        printf("\n");
    }   
    }
    else {
        printf("SOURCE : %s",pd[pos].src);
        printf("\n");
        printf("DESTINATION : %s",pd[pos].dst);
        printf("\nDATE : %s",pd[pos].date);
        printf("\n");
        printf("TRAIN BOOKED DETAILS : \n");
        printf("TRAIN NAME\t\tTIME\n");
        printf("%s\t%s",pd[pos].tname,pd[pos].time);
        printf("\nID\tNAME\tAGE\tGENDER\tSTATUS\n");
        printf("%d\t%s\t%d\t%s\tCONFIRM",pd[pos].bid,pd[pos].name,pd[pos].age,pd[pos].gen);
        printf("\n");
    }
    if(pos==-1)
    {
        printf("INVALID BOOKING ID\n");
    }
}
void main()
{
    int a,choice,o;
    do
    {
        printf("**************WELCOME TO IRCTC**************\n");
        printf("ENTER\n1.TO BOOK TICKET\n2.TO CANCEL TICKET\n3.TO CHECK WHETHER TICKET OS CONFIRMED OR NOT\n4.TO EXIT\n");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
            input();
            train();
            details();
            display();
            break;
            case 2:
            printf("ENTER BOOKING ID\n");
            scanf("%d",&a);
            cancel(a);
            break;
            case 3:
            printf("ENTER BOOKING ID TO CHECK STATUS\n");
            scanf("%d",&a);
            status(a);
        }
        printf("\nENTER 1 TO CONTINUE\n");
        scanf("%d",&o);
    }
    while (o==1);
}