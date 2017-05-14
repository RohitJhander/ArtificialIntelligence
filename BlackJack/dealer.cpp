#include "dealer.h"

using namespace std;

vector<map<int,double> > dealerTable;

///// helper and debug functions 
bool terminate(vector<pair<int,double> > prob)
{
	typedef vector<pair<int,double> >::iterator it;
	for(it iterator = prob.begin(); iterator != prob.end(); iterator++)
	{
		if(iterator->first<17)
			return false;
	}
	return true;
}

void print_vector(vector<pair<int,double> > prob)
{
	cout<<"prob is >>>>>>>>>>"<<endl;
	typedef vector<pair<int,double> >::iterator it;
	for(it iterator = prob.begin(); iterator != prob.end(); iterator++)
	{
		cout<<iterator->first<<" "<<iterator->second<<endl;
	}
	cout<<">>>>>>>>>>>>>>>>>>>"<<endl;
}

void print_map(map<int,double> probmap)
{
	double totl=0;
	cout<<"probmap is >>>>>>>>>>"<<endl;
	typedef map<int,double>::iterator it;
	for(it iterator = probmap.begin(); iterator != probmap.end(); iterator++)
	{
		cout<<iterator->first<<" "<<iterator->second<<endl;
		totl+=iterator->second;
	}
	cout<<">>>>>>>>>>>>>>>>>>>"<<totl<<endl;
}

///////////////////////

map<int,double> getDealerTransitions(int c) //c is the card of dealer
{
	vector<pair<int,double> > prob;
	
	int dealerCard;
	dealerCard=c;

	if(dealerCard==11){
		dealerCard=1;
	}

	if (dealerCard==1)
		prob.push_back(make_pair(11,1.0));
	else
		prob.push_back(make_pair(dealerCard,1.0));

	while(!terminate(prob))
	{
		// print_vector(prob);
		vector<pair<int,double> > temp;temp.resize(0);
		for(int x=0;x<prob.size();x++)
		{
			int this_sum=prob[x].first;
			double this_p=prob[x].second;
			if(this_sum>=17)
				temp.push_back(make_pair(this_sum,this_p));
			else
			{
				if(this_sum<=10)
				{
					for(int i=2;i<=11;i++)
					{
						if(i==10)
							temp.push_back(make_pair(this_sum+i,this_p*probabilityOfFaceCard));
						else
							temp.push_back(make_pair( this_sum+i,this_p*((1-probabilityOfFaceCard)/9) ));
					}
				}
				else if(this_sum>10)
				{

					for(int i=1;i<=10;i++)
					{
						if(i==10)
							temp.push_back(make_pair(this_sum+i,this_p*probabilityOfFaceCard));
						else
							temp.push_back(make_pair( this_sum+i,this_p*((1-probabilityOfFaceCard)/9) ));
					}	
				}
			}
		}
		prob=temp;
	}
	map<int,double> probmap;
	for(int x=17;x<=26;x++)
	{
		probmap[x]=0;
	}
	for(int x=0;x<prob.size();x++)
	{
		int number=prob[x].first;
		double probability=prob[x].second;
		probmap[number]+=probability;	
	}
	return probmap;
}

void createDealerTable(){

	for(int i=0;i<=11;i++){
		map<int,double> transitionMap;
		if(i==0 || i==1){
			dealerTable.push_back(transitionMap);	
		}else{
			transitionMap = getDealerTransitions(i);
		//	cout<<"FOR DEALER CARD "<<i<<endl;
		//	print_map(transitionMap);
			dealerTable.push_back(transitionMap);
		}
	}
}
