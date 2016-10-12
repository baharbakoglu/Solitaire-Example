#include <iostream>
#include <fstream>
#include <string>

#include "Card.h"

using namespace std;

int findnumber(string arr){ // find card number
	int k= arr.length();
	for(int i=0;i<k;i++)
	{
		arr[i]=arr[i+1];
	}
	int j=((arr[0] - '0')*10) +(arr[1] - '0');
	return (j);
}
int find(string waste[9][3]){ //in waste array, find the last value that is not equal to the space
	int i=8,j=0;
	for(i=8;i>=0;i--){
		if(waste[i][j]!="   "){
			break;
		}
	}
	return (i);
}
int find_long(int n,string arr[19][13]){//find pile's long that is not empty
	int i=0;
	while(i<19){
		if(arr[i][n]!="   "){
			i++;
		}
		else{break;}
	}
	return (i);
}
int find_max(int pile0,int pile1,int pile2,int pile3,int pile4,int pile5,int pile6){//find piles max long
	int max=pile0;
	if(pile1>max){max=pile1;}
	if(pile2>max){max=pile2;}
	if(pile3>max){max=pile3;}
	if(pile4>max){max=pile4;}
	if(pile5>max){max=pile5;}
	if(pile6>max){max=pile6;}
	return (max);
}
int check(string str, string st)//check card's number 
{
	int i = findnumber(str);
	int j = findnumber(st);
	if(i==j+1){return 1;}
	else{ return -1;}
}
string findstring(string str, int i){ //find the foundation's previous value
	char p =(i-1)+'0';
	string st="DEF";
	if(i<=10){
		st[0]=str[0];
		st[1]=str[1];
		st[2]=p;
	}
	return (st);
}
int main(int argc, char *argv[] )

{
    string st,st1,deck[52], pile[7][7], pile_p[19][13], stock[24], stock_s, waste[9][3],foundation_h,foundation_d,foundation_s,foundation_c,command,str;
    int i=51, j, k, findnum, temp=0, f=0,pile0,pile1,pile2,pile3,pile4,pile5,pile6;
	ifstream input1;//for command file
	foundation_h="___";
	foundation_c="___";
	foundation_d="___";
	foundation_s="___";
	for(int i=0;i<3;i++){//define first waste line  
		waste[0][i]="___";		
	}
	for(int i=1;i<9;i++){//define other waste line
		for(int j=0;j<3;j++){
			waste[i][j]="   ";
		}
	}
	int value=0;
	ifstream input (argv[1]);//for deck file
    while(input)
    {
		input >> deck[i];//Save entries in the array
		i--;		
    }
	i=0;
	while((i>=0)&&(i<52)){
		Card card(deck[i]);
		if((card.getSuit()=='C')||(card.getSuit()=='S')||(card.getSuit()=='H')||(card.getSuit()=='D')){//Check whether the input is incorrect
			i++;
		}
		else{
			cout<<"Incorrect input"<<endl;
			exit(0);//if we have incorrectly entered, close program
		}
	}
    for(int i=0;i<19;i++){//all the piles emptied
        for(int j=0;j<13;j++){
            pile_p[i][j]="   ";
        }
    }
    pile[0][0]=deck[0];pile[0][1]=deck[1];pile[0][2]=deck[2];pile[0][3]=deck[3];pile[0][4]=deck[4];pile[0][5]=deck[5];pile[0][6]=deck[6];pile[1][1]=deck[7];
    pile[1][2]=deck[8];pile[1][3]=deck[9];pile[1][4]=deck[10];pile[1][5]=deck[11];pile[1][6]=deck[12];pile[2][2]=deck[13];pile[2][3]=deck[14];pile[2][4]=deck[15];
    pile[2][5]=deck[16];pile[2][6]=deck[17];pile[3][3]=deck[18];pile[3][4]=deck[19];pile[3][5]=deck[20];pile[3][6]=deck[21];pile[4][4]=deck[22];pile[4][5]=deck[23];
    pile[4][6]=deck[24];pile[5][5]=deck[25];pile[5][6]=deck[26];pile[6][6]=deck[27];//cards distributed
	j=28;
	for(int i=0;i<24;i++){//Saving a stock series of cards remaining
		stock[i]=deck[j];
		j++;
	}	
    pile_p[0][0]=deck[0];pile_p[1][2]=deck[7];pile_p[2][4]=deck[13];pile_p[3][6]=deck[18];pile_p[4][8]=deck[22];pile_p[5][10]=deck[25];pile_p[6][12]=deck[27];//cards distributed another array
    for(int i=2;i<13;i+=2){//closed cards entered in the array 
        pile_p[0][i]="@@@";
    }
    for(int i=4;i<13;i+=2){
        pile_p[1][i]="@@@";
    }
    for(int i=6;i<13;i+=2){
        pile_p[2][i]="@@@";
    }
    for(int i=8;i<13;i+=2){
        pile_p[3][i]="@@@";
    }
    for(int i=10;i<13;i+=2){
        pile_p[4][i]="@@@";
    }
	pile_p[5][12]="@@@";   
	findnum = find(waste);//find waste line to be printed
	ofstream output (argv[3]);//for output file
	output<<"\n@@@ "<<waste[findnum][0]<<" "<<waste[findnum][1]<<" "<<waste[findnum][2]<<"         "<<foundation_h<<" "<<foundation_d<<" "<<foundation_s<<" "<<foundation_c<<"\n\n";
    for(int i=0;i<8;i++){
        for(int j=0;j<13;j++){
			output<<pile_p[i][j];
        }
		output<<"\n";
    }//printed area
	input1.open(argv[2]);//for command file
	while(!input1.eof())
	{
		getline(input1, command);//read line
		output<<command<<endl;//write line in output
		if(command =="exit"){//if command is exit closed program
			output<<"\n****************************************\n\nGame Over!"<<endl;
			break;
		}
		if((command[0]=='m')&&(command[5]=='t')&&(command[8]=='f')&&(command[19]=='p')){//if command equals "move to foundation pile"
			k=command[24] - '0';//char to int
			i=18;
			if(pile_p[0][2*k]=="   "){//if pile is empty printed a wrong messega
				output<<"\nInvalid Move!"<<endl;
			}
			else {while(pile_p[i][2*k]=="   "){//find pile's value
				i--;
			}
			}
			str = pile_p[i][2*k];
			if(str[0]=='D'){//if first character is D, print this pile in foundation_d
				if(((foundation_d =="___")&&(findnumber(str)==1))||(check(str,foundation_d)==1)){//controlled card's status
						foundation_d =str;
						pile_p[i][2*k]="   ";}
				else{output<<"\nInvalid Move!"<<endl;}
			}
			else if(str[0]=='C'){//if first character is C, print this pile in foundation_d
				if(((foundation_c =="___")&&(findnumber(str)==1))||(check(str,foundation_c)==1)){//controlled card's status
					foundation_c= str;
					pile_p[i][2*k]="   ";}
				else{output<<"\nInvalid Move!"<<endl;}
			}
			else if(str[0]=='H'){//if first character is H, print this pile in foundation_d
				if(((foundation_h =="___")&&(findnumber(str)==1))||(check(str,foundation_h)==1)){//controlled card's status
					foundation_h=str;
					pile_p[i][2*k]="   ";}
				else{output<<"\nInvalid Move!"<<endl;}
			}
			else if(str[0]=='S'){//if first character is S, print this pile in foundation_d
				if(((foundation_s =="___")&&(findnumber(str)==1))||(check(str,foundation_s)==1)){//controlled card's status
					foundation_s=str;
					pile_p[i][2*k]="   ";}
				else{output<<"\nInvalid Move!"<<endl;}
			}
		}
		if((command[0]=='m')&&(command[5]=='t')&&(command[8]=='f')&&(command[19]=='w')){//if command equals to "move to foundation waste"
			findnum=find(waste);//find last waste line which is not empty
			i=2;
			while(i>=0){
				if(waste[findnum][i]!="___"){//find which card is going foundation area
					break;
				}
				else {i--;}
			}
			str = waste[findnum][i];
			if(str[0]=='D'){//if first character is D, print this pile in foundation_d
				if(((foundation_d =="___")&&(findnumber(str)==1))||(check(str,foundation_d)==1)){//controlled card's status
					foundation_d =str;
					waste[findnum][i] ="___";}
				else{output<<"\nInvalid Move!"<<endl;}
			}
			else if(str[0]=='C'){//if first character is C, print this pile in foundation_d
				if(((foundation_c =="___")&&(findnumber(str)==1))||(check(str,foundation_c)==1)){//controlled card's status
					foundation_c= str;
					waste[findnum][i] ="___";}
				else{output<<"\nInvalid Move!"<<endl;}
			}
			else if(str[0]=='H'){//if first character is H, print this pile in foundation_d
				if(((foundation_h =="___")&&(findnumber(str)==1))||(check(str,foundation_h)==1)){//controlled card's status
					foundation_h=str;
					waste[findnum][i] ="___";}
				else{output<<"\nInvalid Move!"<<endl;}
			}
			else if(str[0]=='S'){//if first character is S, print this pile in foundation_d
				if(((foundation_s =="___")&&(findnumber(str)==1))||(check(str,foundation_s)==1)){//controlled card's status
					foundation_s=str;
					waste[findnum][i] ="___";}
				else{output<<"\nInvalid Move!"<<endl;}
			}
		}
		if((command[0]=='m')&&(command[5]=='p')){//if command equals to "move pile"
			k=command[10]-'0';//find moved from the card
			int a, b;
			if(command[13]==' '){//find a>10 or not
			a=command[12]-'0';//find how many cards will be moved
			b=command[14]-'0';}//find where the card will be moved
			else{
				a=10*(command[12]-'0')+(command[13]-'0');
				b=command[15]-'0';
				}
			i=18;
			j=0;
			while(pile_p[i][2*k]=="   "){
				i--;
			}
			while(pile_p[j][2*b]!="   "){
				j++;
			}
			if(j!=0){
				st1 =pile_p[j-1][2*b];
			}
			else{
				st1=pile_p[j][2*b];
			}
			st =pile_p[i-a][2*k];
			int s = findnumber(st1);
			int m = findnumber(st);	
			if(((st[0]=='D')&&((st1[0]!='H')&&(st1[0]!='D')))||((st[0]=='H')&&((st1[0]!='D')&&(st1[0]!='H')))||((st[0]=='C')&&((st1[0]!='S')&&(st1[0]!='C')))||((st[0]=='S')&&((st1[0]!='C')&&(st1[0]!='S')))){//controlled cards status
				if(((m==13)&&(pile_p[j][2*b]=="   "))||(s==m+1)){//controlled cards numbers
					while(a>-1){
						pile_p[j][2*b]=pile_p[i-a][2*k];
						pile_p[i-a][2*k]="   ";
						j++;
						a--;
					}				
				}
				else
				{
					output<<"\nInvalid Move!"<<endl;
				}
			}
			else 
			{
				output<<"\nInvalid Move!"<<endl;
			}
			
		}
		if((command[0]=='m')&&(command[5]=='w')){//if command equals to "moev waste"
			findnum=find(waste);//find the last waste line which is not empty
			i=2;
			j=0,
			k=command[11]-'0';//find where the card will be moved 
			while(i>=0){//find which card will be moved
				if(waste[findnum][i]!="___"){
					break;
				}
				else {i--;}
			}
			str = waste[findnum][i];
			while(pile_p[j][2*k]!="   "){
				j++;
			}
			if(j!=0){
				st1 =pile_p[j-1][2*k];
			}
			else{
				st1=pile_p[j][2*k];
			}
			int s = findnumber(st1);
			int m = findnumber(str);
			if(((str[0]=='D')&&((st1[0]!='H')&&(st1[0]!='D')))||((str[0]=='H')&&((st1[0]!='D')&&(st1[0]!='H')))||((str[0]=='C')&&((st1[0]!='S')&&(st1[0]!='C')))||((str[0]=='S')&&((st1[0]!='C')&&(st1[0]!='S')))){//controlled cards status
				if(((m==13)&&(pile_p[j][2*k]=="   "))||(s==m+1)){//controlled cards number
					pile_p[j][2*k]=str;
					waste[findnum][i] ="___";
				}
				else{output<<"\nInvalid Move!"<<endl;}
			}
			else{output<<"\nInvalid Move!"<<endl;}
			
		}
		if((command[0]=='m')&&(command[5]=='f')){//if command equals to "move foundation"
			if(command[16]=='0'){//controlled which foundation area
				i=0;
				k=command[18]-'0';//find which pile
				while(pile_p[i][2*k]!="   "){
					i++;
				}
				str=pile_p[i-1][2*k];
				int s = findnumber(str);
				int m = findnumber(foundation_h);
				if((str[0]!='H')&&(str[0]!='D')){//controlled cards status
					if(((m==13)&&(pile_p[i][2*k]=="   "))||(s==m+1)){//controlled cards numbers
						pile_p[i][2*k]=foundation_h;
						foundation_h=findstring(foundation_h,m);//change the previous value
					}
				else{output<<"\nInvalid Move!"<<endl;}
			}
			else{output<<"\nInvalid Move!"<<endl;}
				
			}
			if(command[16]=='1'){//controlled which foundation area
				i=0;
				k=command[18]-'0';//find which pile
				while(pile_p[i][2*k]!="   "){
					i++;
				}
				str=pile_p[i-1][2*k];
				int s = findnumber(str);
				int m = findnumber(foundation_d);
				if((str[0]!='D')&&(str[0]!='H')){//controlled cards status
					if(((m==13)&&(pile_p[i][2*k]=="   "))||(s==m+1)){//controlled cards numbers
						pile_p[i][2*k]=foundation_d;
						foundation_d=findstring(foundation_d,m);//change the previous value
					}
				else{output<<"\nInvalid Move!"<<endl;}
			}
			else{output<<"\nInvalid Move!"<<endl;}
			}
			if(command[16]=='2'){//controlled which foundation area
				i=0;
				k=command[18]-'0';//find which pile
				while(pile_p[i][2*k]!="   "){
					i++;
				}
				str=pile_p[i-1][2*k];
				int s = findnumber(str);
				int m = findnumber(foundation_s);
				if((str[0]!='S')&&(str[0]!='C')){//controlled cards status
					if(((m==13)&&(pile_p[i][2*k]=="   "))||(s==m+1)){//controlled cards numbers
						pile_p[i][2*k]=foundation_s;
						foundation_s=findstring(foundation_s,m);//change the previous value
					}
				else{output<<"\nInvalid Move!"<<endl;}
			}
			else{output<<"\nInvalid Move!"<<endl;}
			}
			if(command[16]=='3'){//controlled which foundation area
				i=0;
				k=command[18]-'0';//find which pile
				while(pile_p[i][2*k]!="   "){
					i++;
				}
				str=pile_p[i-1][2*k];
				int s = findnumber(str);
				int m = findnumber(foundation_c);
				if((str[0]!='C')&&(str[0]!='S')){//controlled cards status
					if(((m==13)&&(pile_p[i][2*k]=="   "))||(s==m+1)){//controlled cards numbers
						pile_p[i][2*k]=foundation_c;
						foundation_c=findstring(foundation_c,m);//change the previous value
					}
				else{output<<"\nInvalid Move!"<<endl;}
			}
			else{output<<"\nInvalid Move!"<<endl;}
			}

		}
		if((command[0]=='o')&&(command[5]=='f')){//if command equals to "open from stock"
			int test=0;
			for(j=0;j<24;j++){//controlled stock is empty or not
				if(stock[j]==""){
					test++;
				}
			}
			if(test==24){// if stock is empty find cards in waste array and entry stock 
				j=0;
				for(int i=0;i<9;i++){
					for(int n=0;n<3;n++){
						if((waste[i][n]!="   ")&&(waste[i][n]!="___")){
							stock[j]=waste[i][n];
							j++;
							}
						}
				}
				for(int i=0;i<3;i++){
					waste[0][i]="___";		
				}
				for(int i=1;i<9;i++){
					for(int j=0;j<3;j++){
						waste[i][j]="   ";
					}
				}
				temp=0;
				f=0;
			}
			else{//stock is not empty
				temp+=1;
				findnum=find(waste);// find last waste line which is not empty
				i=0;
				while(i<3){//give value of waste array from stock
					if(temp==1){
						waste[0][i]=stock[f];
						i++;
						stock[f].clear();
						f++;
					}
					else{
						waste[findnum+1][i]=stock[f];
						i++;
						stock[f].clear();
						f++;
					}
				}
			}
		}
		else if(command[0]=='o'){//if command equals to "open"
			k=command[5] - '0';//find which pile's card open
			i=7;
			while(pile_p[i][2*k]=="   "){//find not empty pile value
				i--;
			}
			if(pile_p[i][2*k]=="@@@"){//controlled this card's close or not
				pile_p[i][2*k]=pile[i][k];}
			else{output<<"\nInvalid Move!"<<endl;}
		}
		findnum = find(waste);// find last waste line which is not empty
		for(int k=0;k<3;k++){//if waste is empty, this waste value is changed "___"
			if(waste[findnum][k]==""){
				waste[findnum][k]="___";}
		}
		int test=0;
		if(findnum!=0){
			for(int k=0;k<3;k++){
				if(waste[findnum][k]=="___"){
					test++;}
			}
		}
		if(test==3){//if all waste value equals "___" printed previous waste line
			findnum=findnum-1;}
		test=0;
		for(int j=0;j<24;j++){//controlled stock is empty or not
			if(stock[j]==""){
				test++;
			}
		}
		if(test==24){stock_s="___";}
		else{stock_s="@@@";}
		pile0=find_long(0,pile_p);
		pile1=find_long(2,pile_p);
		pile2=find_long(4,pile_p);
		pile3=find_long(6,pile_p);
		pile4=find_long(8,pile_p);
		pile5=find_long(10,pile_p);
		pile6=find_long(12,pile_p);
		int max = find_max(pile0,pile1,pile2,pile3,pile4,pile5,pile6);// find max not empty pile long
		output<<"\n****************************************\n"<<endl;
		output<<stock_s<<" "<<waste[findnum][0]<<" "<<waste[findnum][1]<<" "<<waste[findnum][2]<<"         "<<foundation_h<<" "<<foundation_d<<" "<<foundation_s<<" "<<foundation_c<<"\n\n";
		for(int i=0;i<max;i++){//printed piles less then max pile long
			for(int j=0;j<13;j++){
				output<<pile_p[i][j];
			}
			output<<"\n";
		}output<<"\n";
	}
	if((foundation_c=="C13")&&(foundation_d=="D13")&&(foundation_h=="H13")&&(foundation_s=="S13")){//controlled game is over or not
			output<<"\n****************************************\n\nYou Win!\n\nGame Over!"<<endl;
		}
	input.close();//close deck file
	input1.close();//close command file
	output.close();//close output file
    return 0;
}
