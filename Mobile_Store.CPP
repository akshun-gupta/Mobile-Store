#include<iostream>
#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<fstream>
#include<string>
#include<cstdlib>

using namespace std;

// The classs for the I/O and creating instances for the mobile

class product
{
	int pno;
	char name[50];
	char brand[50];
	float price,qty,tax,dis;
 
	public:
	
		void create_product(){
			cout<<"\nPlease Enter The Product No. of The mobile "<<endl;
			cin>>pno;
		
			cout<<"\nPlease enter the brand of mobile"<<endl;
			cin>>brand;
		
			cout<<"\n\nPlease Enter The Name of The mobile "<<endl;
			cin>>name;
		
			cout<<"\nPlease Enter The Price of The mobile "<<endl;
			cin>>price;
		
			cout<<"\nPlease Enter The Discount (%) "<<endl;
			cin>>dis;
		}


		void show_product(){
			cout<<"\nThe Product No. of The Product : "<<pno;
		
			cout<<"\nThe brand of mobile is : ";
			cout<<brand;
		
			cout<<"\nThe Name of The Product : ";
			cout<<name;
		
			cout<<"\nThe Price of The Product : "<<price;
		
			cout<<"\nDiscount : "<<dis<<" %";
		}

		int retpno(){
			return pno;
		}

		float retprice(){
			return price;
		}

		char* retname(){
			return name;
		}

		char* retbrand(){
			return brand;
		}

		int retdis(){
			return dis;
		}

};




	fstream fp;
	product pr;

//Function to write the product(instance of the class) to a file

void write_product(){
	
    fp.open("Shop.dat",ios::app|ios::binary);
    
	pr.create_product();
    
	fp.write((char*)&pr,sizeof(product));
    
	fp.close();
    
	cout<<"\n\nThe Product Has Been Created ";
    
	getch();
}


//Function to display all the products stored in the binary file

void display_all(){
	
    system("cls");
    cout<<"\n\n\n\t\tDISPLAYING ALL RECORDS !!!\n\n";
    
	fp.open("Shop.dat",ios::in|ios::binary);
    
	while(fp.read((char*)&pr,sizeof(product))){
		pr.show_product();
		cout<<"\n\n====================================\n";
		getch();
	}
    
	fp.close();
    
	getch();
}


//Read the details of a particular product from the binary file

void display_sp(int n){

	int flag=0;
    
	fp.open("Shop.dat",ios::in|ios::binary);
    
	while(fp.read((char*)&pr,sizeof(product))){

		if(pr.retpno()==n){
			system("cls");
			pr.show_product();
			flag=1;
		}
	}
    
	fp.close();

	if(flag==0)
	cout<<"\n\nrecord not exist";
    
	getch();
}


//Modify the specific details for a particular product (mobile) stored in a binary file

void modify_product(){
	
    int no,found=0;
    
	system("cls");
    cout<<"\n\n\tTo Modify ";
    
	cout<<"\n\n\tPlease Enter The Product No. of The Product";
    cin>>no;
    
	fp.open("Shop.dat",ios::in|ios::out|ios::binary);
	
    //Reading the produt from the binary file
	while(fp.read((char*)&pr,sizeof(product)) && found==0){
		
		//Checking for eqaulity of the product number
		if(pr.retpno()==no){
			
			pr.show_product();
		    cout<<"\nPlease Enter The New Details of Product"<<endl;
		    
			pr.create_product();
		    
			int pos=-1*sizeof(pr);
		    fp.seekp(pos,ios::cur);
		    fp.write((char*)&pr,sizeof(product));
		    
			cout<<"\n\n\t Record Updated";
		    found=1;
		}

    }
    
	fp.close();
    
	if(found==0)
    cout<<"\n\n Record Not Found ";
    
	getch();
}


//Deleting a particular product stored in the binary file

void delete_product(){
    
	int no;
    
	system("cls");
    
	cout<<"\n\n\n\tDelete Record";
    
	cout<<"\n\nPlease Enter The product no. of The Product You Want To Delete"<<endl;
    cin>>no;
    
	fp.open("Shop.dat",ios::in|ios::out|ios::binary);
    fstream fp2;
    
	fp2.open("Temp.dat",ios::out|ios::binary);
    
	fp.seekg(0,ios::beg);
    
	while(fp.read((char*)&pr,sizeof(product))){
		if(pr.retpno()!=no){
			fp2.write((char*)&pr,sizeof(product));
		 }
	}
	
    fp2.close();
    fp.close();
    
	remove("Shop.dat");
    rename("Temp.dat","Shop.dat");
    
	cout<<"\n\n\tRecord Deleted ..";
    getch();

}


//Showing the details of all the created products to the customer

void menu(){
	
	system("cls");
    
	fp.open("Shop.dat",ios::in|ios::binary);
    
	if(!fp){
		cout<<"\n\n\n ERROR!!! FILE COULD NOT BE OPEN\n\n\n Go To Admin Menu to create File";
		cout<<"\n\n\n Program is closing ....";
	
		getch();
		exit(0);
	}
	
	cout<<"\n\n\t\tProduct MENU\n\n";
	cout<<"====================================================\n";
	
	cout<<"P.NO.\t\tNAME\t\tBRAND\t\tPRICE\n";
	cout<<"====================================================\n";

    while(fp.read((char*)&pr,sizeof(product))){
		cout<<pr.retpno()<<"\t\t"<<pr.retname()<<"\t\t"<<pr.retbrand()<<"\t\t"<<pr.retprice()<<endl;
	}
    
	fp.close();

}



//Function that lets the customer to place order

void place_order(){
	
	int  order_arr[50],quan[50],c=0;
    
	float amt,damt,total=0;
    
	char ch='Y';
    
	menu();
    
	cout<<"\n============================";
    cout<<"\n    PLACE YOUR ORDER";
    cout<<"\n============================\n";
    
	//Placing the order
	do{
		cout<<"\n\nEnter The Product No. Of The Product : ";
		cin>>order_arr[c];
		cout<<"\nQuantity in number : ";
		cin>>quan[c];
		c++;
		cout<<"\nDo You Want To Order Another Product? (y/n)"<<endl;
		cin>>ch;
	}while(ch=='y' ||ch=='Y');
    
	cout<<"\n\nThank You For Placing The Order";getch();system("cls");
	
	//Creating the invoice with the product and the quantities, as selected by the customer above

	cout<<"\n\n********************************INVOICE*************************\n";
    cout<<"\nPr No.\tPr Name\tQuantity \tPrice \tAmount \tAmount after discount\n";
   
	for(int x=0;x<=c;x++){
		
		fp.open("Shop.dat",ios::in|ios::binary);
		fp.read((char*)&pr,sizeof(product));
		
		while(!fp.eof()){
			
			if(pr.retpno()==order_arr[x]){
				amt=pr.retprice()*quan[x];
				damt=amt-(amt*pr.retdis()/100);
				cout<<"\n"<<order_arr[x]<<"\t"<<pr.retname()<<"\t"<<quan[x]<<"\t\t"<<pr.retprice()<<"\t"<<amt<<"\t\t"<<damt;
				total+=damt;
			}
			
			fp.read((char*)&pr,sizeof(product));
		}
		
		fp.close();
	 
	 }
	
	cout<<"\n\n\t\t\t\t\tTOTAL = "<<total;
    
	getch();
    
}


//Menu for the administrator that allows him/her to change, create and modify the detils of the products

void admin_menu(){
	char ch2,opt;
	do{
		system("cls");
		cout<<"\n\n\n\tADMIN MENU";
		cout<<"\n\n\t1.CREATE PRODUCT";
		cout<<"\n\n\t2.DISPLAY ALL PRODUCTS";
		cout<<"\n\n\t3.QUERY ";
		cout<<"\n\n\t4.MODIFY PRODUCT";
		cout<<"\n\n\t5.DELETE PRODUCT";
		cout<<"\n\n\t6.VIEW PRODUCT MENU";
		cout<<"\n\n\t7.BACK TO MAIN MENU";
		cout<<"\n\n\tPlease Enter Your Choice (1-7)  ";
		cin>>ch2;
		switch(ch2){
			case '1':	system("cls");
						write_product();
				break;
			
			case '2':  	display_all();
				break;
				
			case '3':  	int num;
						system("cls");
						cout<<"\n\n\tPlease Enter The Product Number  ";
						cin>>num;
						display_sp(num);
				break;
				
			case '4':  	modify_product();
				break;
		
			case '5':  	delete_product();
				break;
			
			case '6':  	menu();
						getch();
				break;	
			
			case '7':  	
				break;
			default	:  admin_menu();
		   
		}
		
		cout<<"\n\n Another Query (Y/N)?"<<endl;
		cin>>opt;
		
	}while(opt=='y'||opt=='Y');

}




int main(){
	char ch;
	
	string pass;
	
	do{
		system("cls");
		
		//The main menu allows the user to toggle betweenn the customer and admin menu
		//If the user chooses the admin menu, they have to enter a valid password to access the menu
		
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t01. CUSTOMER";
		cout<<"\n\n\t02. ADMINISTRATOR";
		cout<<"\n\n\t03. EXIT";
		
		cout<<"\n\n\tPlease Select Your Option (1-3) ";
		cin>>ch;
		
		switch(ch){
			case '1': 	system("cls");
						place_order();
						getch();
				break;
		  
			case '2':	cout<<"\nPlease Enter the Password:\t";
						cin>>pass;
						
						if(pass.compare("mobilestore")==0){
							admin_menu();
						}
				break;
			
			case '3':	exit(0);
		  
			default :	cout<<"Wrong choice"<<endl;
	
		}
    
	}while(ch!='3');
	
	return 0;

}