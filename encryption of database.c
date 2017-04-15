
#include<stdio.h>
#include<strings.h>
#include<math.h>
#include<malloc.h>


#define size 3
float msg [4][size];
float key [3][3]; // private key = inverse of public key
char a[size*3];

void encryption();// encrypts data using matrix method and tranpose the mssg or do some other similar operation
void decryption();// decrypts data using inverse of matrix technique and do reverse transpose 
void decrypt();// decrpts data back from ap,gp,agp form
void crypt();// assigns data to caeserian crpto uging ap,gp,agp or series
void matmult(float a[4][size],float b[3][3]);


struct emp_det
{
	char empid[9]; // employee id
	char emp_name[20]; // employee name
	int dob[3];  // date of birth
	char add[60]; // address
	int doc[3]; // date of commencment
	char nok[20];//next of kin
	int cn; // contact 
	char jp[15]; // job profile
	char pos[15]; // position
};

struct node
{
	struct emp_det obj; // nesting 
	struct node *link; // link field
}*top,*head=NULL,*prev,*last,*delnode,*newnode,*temp;

void getnode();
void readnode();
void create();
//int insertlast();
//int dellast();
void display();

void main()          // main function
{    
   int c,a=0;
	do{
		create();
		//insertlast();
		printf("enter 1 to encrypt data: ");
     	scanf("%d",&a);
	    if(a==1)
	    {
	
	    encryption();
	    c=1;
        }
    
	    else
	    printf("wrong choice , try again !");
		printf("want to enter again ,enter 1 : ");
		scanf("%d",&c);
		}
	     while(c==1);
	     display();
        getch();	
}





void decryption()          // function to decrypt by mssg using secret private key ;
{
	int i=0,t=0,j=0;
	printf("enter the private key matrix :\n");
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			scanf("%f",&key[i][j]);
		}
		printf("\n");
	}
	printf("enter the secret message : \n");
	
		for(i=0;i<4;i++)
	{
		for(j=0;j<size;j++)
		{
			scanf("%f",&msg[i][j]);
		}
		printf("\n");
	}
	
	printf("decoding matrix step 1...\n");
	matmult(msg,key);
	
	printf("here's how it looks like after step 1 :\n");
	
	for(i=0;i<4;i++)
    {
    	for(j=0;j<size;j++)
    	{
    		msg[i][j]=round(msg[i][j]);
    		printf("%f\t",msg[i][j]);
    	}
    	printf("\n");
    }
    getch();
	printf("decrypting mssg step 2...\n");
	decrypt();
	
	printf("here's how it looks like after step 2 :\n");
	
	for(i=0;i<4;i++)
    {
    	for(j=0;j<size;j++)
    	{
    		printf("%f\t",msg[i][j]);
    	}
    	printf("\n");
    }
    getch();
	printf("here is your decrypted message :\n");
	for(i=0;i<3;i++)
    {
	for(j=0;j<size;j++)
	{
		a[t]=(char)msg[i][j];
		t++;
	}
	}
printf("%s",a);
}




void decrypt()
{
	int i=0,j=0,k=1,a1,d;
	a1=(int)msg[3][1];
	d=(int)msg[3][2];
	if( msg[3][0]=='A')
	{
		for(i=0;i<3;i++)
		{
			for(j=0;j<size;j++)
			{
				msg[i][j]=msg[i][j] -(float)( a1 + (k-1)*d);    // subtracting general term of AP to the regular characters of msg       
				k++;            
			}
		
		 
	   }
	
   }
   else if(msg[3][0]=='G')
   {
   		for(i=0;i<3;i++)
		{
			for(j=0;j<size;j++)
			{
				msg[i][j]=msg[i][j] - (float)(a1*pow(d,k-1));    // subtracting general term of GP to the regular characters of msg       
				k++;            
			}
		
	
        }
   }
}




void encryption()
{

int t=0,d,a1,i,j; 
 float b[3][3];
float determinant=0;
printf("enter the secret message (max 3*3 letters)  : \n");
scanf("%s",a);

for(i=0;i<3;i++)
{
	for(j=0;j<size;j++)
	{
		msg[i][j]=(float)a[t]	;
		t++;
	}
}
    printf("how the message may look in 3*3 matrix form :\n");

    for(i=0;i<3;i++)
    {
    	for(j=0;j<size;j++)
    	{
    		printf("%f\t",msg[i][j]);
    	}
    	printf("\n");
    }

getch();

printf("enter choice to encode mssg in\n1) AP\t2) GP : "); // using this we may surpass crptanalysis as 'e' ocuurence encoded differntly at different times

                                                           
scanf("%d",&a1);                                             // frequency analysis may fail
crypt(a1);


printf("how the message look after encoding it with AP/GP : \n");
    for(i=0;i<4;i++)
    {
    	for(j=0;j<size;j++)
    	{
    		printf("%f\t",msg[i][j]);
    	}
    	printf("\n");
    }

getch();
printf("enter the public secrect key 3*3 matrix \n");
for(i=0;i<3;i++)
{
	for(j=0;j<3;j++)
	{
		scanf("%f",&b[i][j]);
	}
	printf("\n");
}

    matmult( msg, b);
    printf("your mssg has been encrypted!,\n here is your encrypted mssg\n");
    
    
    for(i=0;i<4;i++)
    {
    	for(j=0;j<size;j++)
    	{
    		printf("%f\t",msg[i][j]);
    	}
    	printf("\n");
    }
    
    for(i=0;i<3;i++) // finding determinant in one go !!
      determinant = determinant + (b[0][i]*(b[1][(i+1)%3]*b[2][(i+2)%3] - b[1][(i+2)%3]*b[2][(i+1)%3]));
      if(determinant==0)
      {
      	printf("\nsorry , the inverse of this matrix does not exist , try again !");
      	return;
      }

   printf("\nYour PVT secret key is ...\nPlease note it down somewhere ! \n\n");
   for(i=0;i<3;i++)
   {
      for(j=0;j<3;j++) // finding inverse of the matrix in one go !!
           printf("%f\t",((b[(j+1)%3][(i+1)%3] * b[(j+2)%3][(i+2)%3]) - (b[(j+1)%3][(i+2)%3]*b[(j+2)%3][(i+1)%3]))/determinant);
       printf("\n");
   }

    
}



void matmult(float a[4][size],float b[3][3])
{

	float sum, a1[4][size];
	int c,d,k,j,i;
	sum=0;
	for(i=0;i<3;i++)
	{
		for(j=0;j<size;j++)
		{
			a1[i][j]=a[i][j];
		}
	}
	
	   for (c = 0; c < 3; c++)
	{
      for (d = 0; d < size; d++) 
	  {
        for (k = 0; k < 3; k++)
		 {
          sum = sum + (b[c][k]*a1[k][d]);
         }
 
        a[c][d] = sum;
        sum = 0;
      }
    }
 
		
}
	
	

void crypt(int a1)
{    
    int a,d,i=0,j=0,k=1;
	if(a1==1)
	{
		msg[3][0]=(float)'A';
		
		printf("enter the first term and common difference\n : "); // these are stored in 4th column of matrix to help in decryption
		scanf("%d",&a);
		scanf("%d",&d);
		msg[3][1]=a;
		msg[3][2]=d;
		for(i=0;i<3;i++)
		{
			for(j=0;j<size;j++)
			{
				msg[i][j]=msg[i][j] +(float) (a + (k-1)*d);    // adding general term of AP to the regular characters of msg       
				k++;            
			}
		}
		
	}
	else if(a1==2)
	{
	
	msg[3][0]=(float)'G';
	
	printf("enter the first term and common ratio : ");
	scanf("%d",&a);
	scanf("%d",&d);
	msg[3][1]=a;
	msg[3][2]=d;
	for(i=0;i<3;i++)
		{
			for(j=0;j<size;j++)
			{
				msg[i][j]=msg[i][j] +(float) (a*pow(d,k-1));    // adding general term of GP to the regular characters of msg       
				k++;            
			}
		
	
        }
    }
}



void getnode()
{
	newnode=(struct node*)malloc(sizeof(struct node));
}

void readnode()
{
	printf("Enter employee details \n");
	printf("Name: ");
	scanf("%s",newnode->obj.emp_name);
	printf("Employee id: ");
	scanf("%s",newnode->obj.empid);
	printf("Date of Birth: ");
	printf("Date(dd):");
	scanf("%d",&newnode->obj.dob[0]);
	printf("Month(mm): ");
	scanf("%d",&newnode->obj.dob[1]);
	printf("Year(yyyy): ");
	scanf("%d",&newnode->obj.dob[2]);
	printf("Address: ");
	scanf("%s",newnode->obj.add);
	printf("Date of Commencement: ");
	printf("Date(dd): ");
	scanf("%d",&newnode->obj.doc[0]);
	printf("Month(mm): ");
	scanf("%d",&newnode->obj.doc[1]);
	printf("Year(yyyy) ");
	scanf("%d",&newnode->obj.doc[2]);
	printf("Next of Kin: ");
	scanf("%s",newnode->obj.nok);
	printf("Enter contact no(Mobile): ");
	scanf("%d",&newnode->obj.cn);
	printf("Job Profile: ");
	scanf("%s",newnode->obj.jp);
    printf("Position: ");
	scanf("%s",newnode->obj.pos);	
	newnode->link=newnode;
}

void create()
     {         
               int c;
                if(head!=NULL)
                {
                    printf("Linked List is already created");
                    return;
                }
                else
                {
                    do
                    {
		         	getnode();
                   	readnode();

                    if(head==NULL)
                    {
		            	head=last=newnode;
                    }

                 else
                 {
		              last->link=newnode;
                      last=last->link;
		              last->link=head;
                  }
                 printf( "Press 1 to add another node:");
                  scanf("%d",&c);
                }while(c==1);
                }
                
    }

/*insertlast()
{
    getnode();
    if(newnode==NULL)
    {
      printf("Memory Insufficient");
      return(0);
    }
    readnode();
   if(head==NULL)
    {
       head=last=newnode;
       return(0);
    }
    last->link=newnode;
    last=last->link;
    last->link=head;
}

int dellast()
{
    if(head==NULL)
    {
                  printf("\nSLL is empty:");
                  return(0);
    }
    else if(head==last)
    {
         delnode=head;
         printf("Deleted node is :%d",head->obj.empid);
         head=last=NULL;
         free(delnode);
         return(0);
}
else
 {
     last=head;
     while(last->link!=head)
     {
      prev=last;
      last=last->link;
      }
     delnode=last;
     printf("\nDeleted node is:%d",last->obj.empid);
     last=prev;
     last->link=head;
     free(delnode);
     return(0);
}
}*/

void display()
     {    int flag=0,c=0;
	       do{
	          decryption();
		  
          if(head==NULL)
          {
           printf("\nSLL is Empty");
           return;
           }
           temp=head;
           while(temp!=last)
           {
           	if(strcmp(a,temp->obj.empid)==0)
           	{
           	flag=1;
            printf("\nEmployee details \n");
         	printf(" Name:\t");
          	printf("%s",temp->obj.emp_name);
	        printf("\nEmployee id:\t");
	        printf("%s",temp->obj.empid);
	        printf("\nDate of Birth:\t");
	        printf(" Date(dd): ");
	        printf("%d",temp->obj.dob[0]);
	        printf(" Month(mm): ");
	        printf("%d",temp->obj.dob[1]);
	        printf(" Year(yyyy): ");
	        printf("%d",temp->obj.dob[2]);
	        printf("\nAddress:\t");
	        puts(temp->obj.add);
	        printf("\nDate of Commencement:\t");
	        printf(" Date(dd): ");
	        printf("%d",temp->obj.doc[0]);
         	printf(" Month(mm): ");
        	printf("%d",temp->obj.doc[1]);
        	printf(" Year(yyyy): ");
        	printf("%d",temp->obj.doc[2]);
        	printf("\nNext of Kin: ");
	        puts(temp->obj.nok);
	        printf("\nEnter contact no(Mobile):\t");
	        printf("%d",temp->obj.cn);
	        printf("\nJob Profile:\t");
        	puts(temp->obj.jp);
            printf("\nPosition:\t");
	        puts(temp->obj.pos);
			}
				
            temp=temp->link;
        
            }
            if(flag==0)
               printf("\nWrong password or emp id not found !");
               printf("Press 1 to tey again: ");
               scanf("%d",&c);
		}while(c==1);
       }


