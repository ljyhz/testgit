#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef int bool;

typedef struct bookinfo
{
    char number[15];/*产品编号*/
    char name[30];/*产品名称*/
    float price;/*单价*/
    char auther[20];/*作者*/
    bool isExit;/*存在状态*/
    char lendername[20];/*借书人姓名*/
    char lendersex[2];/*借书人性别*/
    char lendernum[15];/*借书人学号*/
}BOOKINFO;

void menu()
{
    printf("\n\n\n");
    printf("\t\t\t图书管理系统\n\n");
	printf("\t\t===========================\n\n");
    printf("\t\t1:新进图书基本信息的输入\n\n");
    printf("\t\t2:显示全部记录\n\n");
    printf("\t\t3:根据图书名称查询图书基本信息\n\n");
    printf("\t\t4:根据图书名称对撤销的图书信息进行删除\n\n");
    printf("\t\t5:按照图书名称从小大到排序\n\n");
    printf("\t\t6:统计某价格以上的图书数量\n\n");
    printf("\t\t7:列出所有未借出去的图书信息\n\n");
    printf("\t\t8:退出\n");
    }
void choice_1_input_new()/*输入新进的图书信息*/
{
    char choice;
    FILE *p;
    BOOKINFO newbook;

    system("cls");
    while(1)
      {
      printf("输入图书编号:");
      gets(newbook.number);
          
      printf("输入图书名称:");
      gets(newbook.name);    
      
      printf("输入图书单价:");
      scanf("%f",&newbook.price);
      while(getchar()!='\n');
          
      printf("输入图书的作者:");
      gets(newbook.auther);    
      
      printf("输入借书人姓名:");
      gets(newbook.lendername);    
      
      printf("输入借书人性别:");
      gets(newbook.lendersex);    
      
      printf("输入借书人学号:");
      gets(newbook.lendernum);
      
      printf("是否保存该条书目?(Y/N)\n");
      choice=getch();
      while(choice!='Y'&&choice!='y'&&choice!='N'&&choice!='n')
        choice=getch();
      if(choice=='Y'||choice=='y') 
        {
        newbook.isExit=1;/*将图书状态设置成1，表示没有借出*/
        
        p=fopen("c:\\bookinfo.data","ab");
        fwrite(&newbook,sizeof(BOOKINFO),1,p);
        fclose(p);    
        
        printf("\n该条书目已添加到c:\\bookinfo.data文件中!\n");
        }     
      else  
        {
        printf("\n本条书目未保存!\n");    
        }
      printf("\n是否继续添加书目?(Y/N)\n");
      choice=getch();
      while(choice!='Y'&&choice!='y'&&choice!='N'&&choice!='n')
        choice=getch();
      if(choice=='Y'||choice=='y')
        continue;
      else 
        break;      
      }
    }
void choice_2_display_all()/*显示全部图书信息*/
{
    FILE *p;
    int n;
    BOOKINFO bookinfo[100];
    int booknumber=0;

    system("cls");
    p=fopen("c:\\bookinfo.data","rb");
    while(!feof(p))
      {
      fread(&bookinfo[booknumber],sizeof(BOOKINFO),1,p);
      booknumber++;    
      }
    /*booknumber--;使用feof()函数会多读一行，因此需要booknumber自减一次，使书目的数量正确*/
    fclose(p);  
    booknumber--;
    if(booknumber==0)
      {
      printf("没有任何图书信息!\n\n");
      }
    else
      {
      n=0;
      printf("                              图书信息如下\n");
      printf("                   图书信息                |         借书人信息   \n");
      printf("编号  名称        单价    作者    图书状态 | 姓名        性别    学号\n");
      while(n<booknumber) 
        {
        printf("%-6s%-12s%-8.1f%-8s%-9d| %-12s%-8s%-8s\n",
                                        bookinfo[n].number,bookinfo[n].name,bookinfo[n].price,
                                        bookinfo[n].auther,bookinfo[n].isExit,bookinfo[n].lendername,
                                        bookinfo[n].lendersex,bookinfo[n].lendernum);
        n++;                                    
        }
      }  
    printf("\n\n按任意键回到主菜单!\n");
    getch();      
}

void choice_3_search_according_name()/*根据图书名称显示图书的信息*/
{
    char search[20]="";/*search用来存放要查询的书名*/
    int n;
    FILE *p;
    char choice;
    BOOKINFO bookinfo[100];
    int booknumber=0;
    
    system("cls");
    p=fopen("c:\\bookinfo.data","rb");
    while(!feof(p))
      {
      fread(&bookinfo[booknumber],sizeof(BOOKINFO),1,p);
      booknumber++;    
      }
    booknumber--;/*使用feof()函数会多读一行，因此需要booknumber自减一次，使书目的数量正确*/
    fclose(p); 
    while(1)
    {
    printf("输入要查询的书本名称:");
    gets(search);
    if(booknumber==0)
      {
      printf("书库中没有任何信息!\n\n");
      printf("按任意键回到主菜单!\n\n");
      getch();
      break;    
      }/*if结束*/
    else
      {
      for(n=0;n<booknumber;n++)
        if(strcmp(bookinfo[n].name,search)==0)
          {
          printf("该书的详细信息如下:\n");
          printf("                   图书信息                |         借书人信息   \n");
          printf("编号  名称        单价    作者    图书状态 | 姓名        性别    学号\n");
          printf("%-6s%-12s%-8.1f%-8s%-9d| %-12s%-8s%-8s\n",
                                        bookinfo[n].number,bookinfo[n].name,bookinfo[n].price,
                                        bookinfo[n].auther,bookinfo[n].isExit,bookinfo[n].lendername,
                                        bookinfo[n].lendersex,bookinfo[n].lendernum);
          break;                            
          }
      if(n>=booknumber)
        printf("没有查找该书的任何信息!\n");
      printf("\n\n是否继续查询?(Y/N)\n");
      choice=getch();
      while(choice!='Y'&&choice!='y'&&choice!='N'&&choice!='n')
         choice=getch();
      if(choice=='Y'||choice=='y')
        continue;
      else 
        break;              
        }/*else结束*/
      }/*while(1)结束*/  
    }
void choice_4_delete_according_name()/*根据图书名称对图书信息进行删除*/
{
    char search[20]="";/*search用来存放要删除的书名*/
    int n,i;
    FILE *p;
    char choice;
    BOOKINFO bookinfo[100];
    int booknumber;
    
    system("cls");
    while(1)
      {
      printf("输入要删除的书本名称:");
      gets(search);
      p=fopen("c:\\bookinfo.data","rb");
      booknumber=0;
      while(!feof(p))
        {
        fread(&bookinfo[booknumber],sizeof(BOOKINFO),1,p);
        booknumber++;    
        }
      booknumber--;/*使用feof()函数会多读一行，因此需要booknumber自减一次，使书目的数量正确*/
      fclose(p); 
      if(booknumber==0)
        {
        printf("书库中没有任何信息!\n\n");
        printf("按任意键回到主菜单!\n\n");
        getch();
        break;   
        }/*if结束*/
      else
        {    
        for(n=0;n<booknumber;n++)
          if(strcmp(bookinfo[n].name,search)==0)
            {
            break;
            }
        if(n>=booknumber)
           printf("没有查找该书的任何信息!\n");
        else
           {
           printf("是否确认需要删除该条书目?(Y/N)");
           choice=getch();
             while(choice!='Y'&&choice!='y'&&choice!='N'&&choice!='n')
             choice=getch();
           if(choice=='Y'||choice=='y')      
             {
             for(i=n;i<booknumber-1;i++)
               bookinfo[i]=bookinfo[i+1];    
             booknumber--;
           
             p=fopen("c:\\bookinfo.data","wb");
             for(n=0;n<booknumber;n++)
               fwrite(&bookinfo[n],sizeof(BOOKINFO),1,p);
             fclose(p);
           
             printf("删除成功!\n");
             }
           else
              printf("\n\n该条书目没有被删除!"); 
           }    
         printf("\n\n是否继续进行删除操作?(Y/N)\n");
         choice=getch();
         while(choice!='Y'&&choice!='y'&&choice!='N'&&choice!='n')
           choice=getch();
         if(choice=='Y'||choice=='y')
           continue;
         else 
           break;              
        }/*else结束*/
      }/*while(1)结束*/
    }
void choice_5_sort_according_name()/*根据图书名称排序*/
{
    FILE *p;
    int m,n;
    BOOKINFO temp;
    BOOKINFO bookinfo[100];
    int booknumber;
    
    p=fopen("c:\\bookinfo.data","rb");
    booknumber=0;
    system("cls");
    while(!feof(p))
      {
      fread(&bookinfo[booknumber],sizeof(BOOKINFO),1,p);
      booknumber++;    
      }
    booknumber--;/*使用feof()函数会多读一行，因此需要booknumber自减一次，使书目的数量正确*/
    fclose(p);  
    if(booknumber==0)
      {
      printf("没有任何图书信息!\n\n");
      }
    else
      {
      for(m=0;m<booknumber-1;m++)
        for(n=m+1;n<booknumber;n++)
          if(strcmp(bookinfo[m].name,bookinfo[n].name)>0)
            {
            temp=bookinfo[m];
            bookinfo[m]=bookinfo[n];
            bookinfo[n]=temp;    
            }
      p=fopen("c:\bookinfo.data","wb");
      for(m=0;m<booknumber;m++)
        fwrite(&bookinfo[m],sizeof(BOOKINFO),1,p);
      fclose(p);        
      printf("\n\n完成排序!\n\n");      
      }
    printf("按任意键回到主菜单!\n");
    getch();  
}

void choice_6_display_high_price()/*根据价格列出图书信息*/
{
    float price;
    FILE *p;
    int n;
    int count=0;
    BOOKINFO bookinfo[100];
    int booknumber;
    
    system("cls");
    printf("请输入价格:");
    scanf("%f",&price);
    p=fopen("c:\\bookinfo.data","rb");
    booknumber=0;
    while(!feof(p))
      {
      fread(&bookinfo[booknumber],sizeof(BOOKINFO),1,p);
      booknumber++;    
      }
    booknumber--;/*使用feof()函数会多读一行，因此需要booknumber自减一次，使书目的数量正确*/
    fclose(p);  
    if(booknumber==0)
      {
      printf("没有任何图书信息!\n\n");
      }
    else
      {
      for(n=0;n<booknumber;n++) 
        {
        if(bookinfo[n].price>=price)
          count++;
        }
      if(count==0) 
        printf("书库中没有比%.1f$价格高的图书!",price); 
      else
        {
        printf("                          价格高于%.1f$的图书信息如下\n",price);
        printf("                   图书信息                |         借书人信息   \n");
        printf("编号  名称        单价    作者    图书状态 | 姓名        性别    学号\n");
        for(n=0;n<booknumber;n++) 
          {
          if(bookinfo[n].price>=price)
            printf("%-6s%-12s%-8.1f%-8s%-9d| %-12s%-8s%-8s\n",
                                        bookinfo[n].number,bookinfo[n].name,bookinfo[n].price,
                                        bookinfo[n].auther,bookinfo[n].isExit,bookinfo[n].lendername,
                                        bookinfo[n].lendersex,bookinfo[n].lendernum);                                    
          }
        }
      }  
    printf("\n\n按任意键回到主菜单!\n");
    getch();  
    }
void choice_7_display_according_exitflag()/*根据存在状态列出图书信息*/
{
    FILE *p;
    int n;
    int count=0;
    BOOKINFO bookinfo[100];
    int booknumber;
    
    system("cls");
    booknumber=0;
    p=fopen("c:\\bookinfo.data","rb");
    while(!feof(p))
      {
      fread(&bookinfo[booknumber],sizeof(BOOKINFO),1,p);
      booknumber++;    
      }
    booknumber--;  
    fclose(p);
    if(booknumber==0)
      {
      printf("书库中没有任何书目存在!\n");
      }    
    else
      {
      for(n=0;n<booknumber;n++)
        if(bookinfo[n].isExit==1)
          count++;
      if(count==0)
        printf("书库中的书籍全部借出!\n");        
      else
        {
        printf("书库中未被借出的图书信息如下:\n\n");
        printf("                   图书信息                |         借书人信息   \n");
        printf("编号  名称        单价    作者    图书状态 | 姓名        性别    学号\n");
        for(n=0;n<booknumber;n++)
          if(bookinfo[n].isExit==1)
            {
            printf("%-6s%-12s%-8.1f%-8s%-9d| %-12s%-8s%-8s\n",
                                        bookinfo[n].number,bookinfo[n].name,bookinfo[n].price,
                                        bookinfo[n].auther,bookinfo[n].isExit,bookinfo[n].lendername,
                                        bookinfo[n].lendersex,bookinfo[n].lendernum);    
            }    
        }   
      }  
    printf("\n按任意键返回主菜单!\n");
    getch();  
}

void main()
{
    char choice;
    clock_t tm;
    FILE *p;
    if((p=fopen("c:\\bookinfo.data","rb"))==NULL)
      {
      p=fopen("c:\\bookinfo.data","wb");   
      fclose(p);
      }
    while(1)
      {
      system("cls");
      menu();
      choice=getch();
      switch(choice)
        {
        case '1':choice_1_input_new();break;/*输入新进的图书信息*/
        case '2':choice_2_display_all();break;/*显示全部图书信息*/
        case '3':choice_3_search_according_name();break;/*根据图书名称显示图书的信息*/
        case '4':choice_4_delete_according_name();break;/*根据图书名称对图书信息进行删除*/
        case '5':choice_5_sort_according_name();break;/*根据图书名称排序*/
        case '6':choice_6_display_high_price();break;/*根据价格列出图书信息*/
        case '7':choice_7_display_according_exitflag();break;/*根据存在状态列出图书信息*/
        case '8':printf("\n\n\t\t\t谢谢使用,再见!\n\t\t\t按任意键退出!\n");getch();return;
        default:
                printf("\n\n\t\t\t请输入菜单中的数字!(1~8)");    
                tm=clock();
                while(clock()<tm+1800);
                break;
        }    
      }
}