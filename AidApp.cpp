#include <cstring>
#include <new>
#include <iomanip>
#include "AidApp.h"

using namespace std;

namespace sict
{
	void AidApp::pause()const
	{
		cin.clear();
		cout<<"Press Enter to continue..."<<endl;	
    		cin.ignore(1000,'\n');
    	
	}

	int AidApp::menu()
	{
		int choice;
		cout<<"Disaster Aid Supply Management Program"<<endl;
		cout<<"1- List products"<<endl;
		cout<<"2- Display product"<<endl;
		cout<<"3- Add non-perishable product"<<endl;
		cout<<"4- Add perishable product"<<endl;
		cout<<"5- Add to quantity of purchased products"<<endl;
		cout<<"0- Exit program"<<endl;
		cout<<"> ";
		cin>>choice;
		cin.get();
		if(!cin.fail() && (choice==1||choice==2||choice==3||choice==4||choice==5||choice==0))
		{
			cin.clear();
			return choice;
		}
		else	{cin.clear(); return -1;}
	}

	void AidApp::loadRecs()
	{
		char filetostr='\0';
		int i=0;
		datafile_.open(filename_,ios::in);
		if(!datafile_.bad() && datafile_.is_open())
		{
			while(i<MAX_NO_RECS && !datafile_.eof())
			{
				
				filetostr = datafile_.get();
				if(filetostr=='N')
				{
					delete product_[i];
					product_[i] = nullptr;
					product_[i] = new AmaProduct;
					datafile_.ignore();
					product_[i]->load(datafile_);
					i++;
				}
				else if(filetostr=='P')
				{
					delete product_[i];
					product_[i] = nullptr;
					product_[i] = new AmaPerishable;
					datafile_.ignore();
					product_[i]->load(datafile_);
					i++;
				}
			}
			noOfProducts_ = i;
		}
		else
		{
			datafile_.clear();
			datafile_.close();
			datafile_.open(filename_,ios::out);
		}
		
		
		datafile_.close();
	}

	void AidApp::saveRecs()
	{
		int num = noOfProducts_ - 1;
		datafile_.open(filename_,ios::out);

		if(datafile_.good())
		{
			for(int i=0;i<noOfProducts_;i++)
			{
				if(i==num)	product_[i]->store(datafile_,false);
				else	product_[i]->store(datafile_,true);
			}
			datafile_.close();
		}
	}

	void AidApp::listProducts()const
	{
		double totalcost=0;
		int k=1;
		int i;
		cout<<endl<<" Row | SKU    | Product Name       | Cost  | QTY| Unit     |Need| Expiry   "<<endl;
 		cout<<"-----|--------|--------------------|-------|----|----------|----|----------"<<endl;
 		for(i=0;i<noOfProducts_;i++)
		{
			if(k==DISPLAY_LINES)
			{
				cout<<setw(4)<<right<<i+1<<" | "<<*product_[i]<<endl;
				pause();
			}
			else	cout<<setw(4)<<right<<i+1<<" | "<<*product_[i]<<endl;
			k++;
			
			totalcost += *product_[i];
		}
		cout<<"---------------------------------------------------------------------------"<<endl;
		
		cout<<"Total cost of support: $"<<fixed<<setprecision(2)<<totalcost<<endl<<endl;	
	}

	int AidApp::SearchProducts(const char* sku) const
	{
		int ret = -1;

		for(int i=0;i<noOfProducts_;i++)
		{
			if(*product_[i]==sku)	
			{
				ret = i;
				i=noOfProducts_;
			}
			else	ret = -1;
		}
		return ret;
	}

	void AidApp::addQty(const char* sku)
	{
		int itemn = 0;
		int search = -1;
		search = SearchProducts(sku);
		int qtyN = product_[search]->qtyNeeded();
		int quant = product_[search]->quantity();
		int tNeed = qtyN - quant;
		cout<<endl;
		if(search==-1)	cout<<"Not found!"<<endl;
		else
		{
			product_[search]->write(cout,false);
			cout<<endl<<endl<<"Please enter the number of purchased items: ";
			cin>>itemn;
			if(cin.fail())	 cout<<"Invalid quantity value! "<<endl;
			else
			{
				if(itemn<=tNeed)	*product_[search] += itemn;
				else
				{
					product_[search]->quantity(qtyN);
					cout<<"Too many items; only "<<tNeed<<" is needed, please return the extra "<<itemn - tNeed<< " items."<<endl;
				}
				cout<<endl<<"Updated!"<<endl;
			}
			saveRecs();
			cin.clear();
			cin.ignore(1000,'\n');
		}
	}

	void AidApp::addProduct(bool isPerishable)
	{
		if(isPerishable)
		{
			product_[noOfProducts_] = new AmaPerishable;
			cin>>*product_[noOfProducts_];
			if(cin.fail())
               		{
	                        cout<<product_[noOfProducts_];
        	                delete product_[noOfProducts_];
               		        product_[noOfProducts_] = nullptr;
                	}
                	else
                	{
                       		cout<<endl<<"Product added"<<endl;
                        	noOfProducts_++;
                	}
		}
		else
		{
			product_[noOfProducts_] = new AmaProduct;
			cin>>*product_[noOfProducts_];
			if(cin.fail())
                	{
                        	cout<<product_[noOfProducts_];
                        	delete product_[noOfProducts_];
                        	product_[noOfProducts_] = nullptr;
                	}
                	else
                	{
                        	cout<<endl<<"Product added"<<endl;
                        	noOfProducts_++;
                	}
		}
		saveRecs();
		cin.clear();
		cin.ignore(1000,'\n');
	}

	int AidApp::run()
	{
		int choice;
		int start=1;
		char inputmain[MAX_SKU_LEN+1];
		int search = -1;
		while(start==1)
		{
			choice = menu();
			switch(choice)
			{
			case 0:
				cout<<endl<<"Goodbye!!"<<endl;
				start=0;
				break;
			case 1:
				listProducts();
				pause();
				break;
			case 2:
				cout<<endl<<"Please enter the SKU: ";
				cin.getline(inputmain,MAX_SKU_LEN,'\n');
				cout<<endl;
				search = SearchProducts(inputmain);
				if(search==-1)	cout<<"Not found!";
				else	product_[search]->write(cout,false);
				cout<<endl<<endl;
				pause();
				break;
			case 3:
				cout<<endl;
				addProduct(false);
				loadRecs();
				cout<<endl;
				break;
			case 4:
				cout<<endl;
				addProduct(true);
				loadRecs();
				cout<<endl;
				break;
			case 5:
				cout<<endl<<"Please enter the SKU: ";
				cin.getline(inputmain,MAX_SKU_LEN,'\n');
				addQty(inputmain);
				cout<<endl;
				break;
			default:
				cin.clear();
				cout<<"===Invalid Selection, try again.==="<<endl;
				cin.ignore(1000, '\n');
				start=1;
				break;
			}
		}
		return 0;
	}

	AidApp::AidApp(const char* filename)
	{
		strncpy(filename_,filename,255);
		filename_[255] = '\0';
		for(int i=0;i<MAX_NO_RECS;i++)	product_[i] = nullptr;
		noOfProducts_ = 0;
		loadRecs();
	}
}
