//
//  errcount.cpp
//
//
//  Created by aljohara on 4/27/15.
//
//

#include <stdio.h>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<string>
#include<cassert>
#include<iomanip>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <list>
using namespace std;

//NT array elemnts
class lelm {
public:
    int start, end, e;
    lelm();
};

lelm::lelm() {
    
    start=-1;
    end=-1;
    e=-1;
};


//NT array elemnts
class melm {
public:
    string rule;
    int e;
    melm();
};

melm::melm() {
    
    rule="";
    e=-1;
};

int findlast(lelm X[56])
{
    int i=0;
    while (X[i].e>-1)
        i++;
    return i;
    
    
}



//Declearing 2D array for each NT
int S[56][56]= {-1}, P1[56][56]= {-1}, P2[56][56]= {-1}, TATA0[56][56]= {-1}, TATA1[56][56]= {-1}, TATA2[56][56]= {-1}, TATA3[56][56]= {-1}, TATA4[56][56]= {-1}, TATA5[56][56]= {-1}, A2[56][56]= {-1}, A3[56][56]= {-1}, A4[56][56]= {-1}, A5[56][56]= {-1}, A6[56][56]= {-1}, A7[56][56]= {-1}, A8[56][56]= {-1}, A9[56][56]= {-1}, A10[56][56]= {-1}, A11[56][56]= {-1}, A12[56][56]= {-1}, A13[56][56]= {-1}, A14[56][56]= {-1}, A15[56][56]= {-1}, A16[56][56]= {-1}, A17[56][56]= {-1}, A18[56][56]= {-1}, A19[56][56]= {-1}, TTGACA0[56][56]= {-1},TTGACA1[56][56]= {-1}, TTGACA2[56][56]= {-1},TTGACA3[56][56]= {-1}, TTGACA4[56][56]= {-1}, TTGACA5[56][56]= {-1},F2[56][56]= {-1}, F3[56][56]= {-1}, F4[56][56]= {-1}, F5[56][56]= {-1}, F6[56][56]= {-1}, F7[56][56]= {-1}, F8[56][56]= {-1}, F9[56][56]= {-1}, F10[56][56]= {-1}, F11[56][56]= {-1}, F12[56][56]= {-1}, F13[56][56]= {-1}, F14[56][56]= {-1}, BASE[56][56]= {-1}, BA[56][56]= {-1}, BT[56][56]= {-1}, BG[56][56]= {-1}, BC[56][56]= {-1};


//set error for each grammar rule, 19 and 15 middle space are counted as two error because they are less likely to be found. 
int ERR[75]={0,0,2,1,0,1,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1};

void ini(int (&array) [56][56]){

    for(int i=0; i<56; i++)
        for(int j=0; j<56; j++)
            array[i][j]=999;

}

melm gram[74][74];  //to store entered grammar


int np;       //np-> number of productions


int main()
{
    int i,pt,j,l,k, n;
    string a,str,r,pr, temp;
    bool t;
    string A, B, C;
    int L1, L2, L;
    
    ini(S);
    ini(P1);
    ini(P2);
    ini(TATA0);
    ini(TATA1);
    ini(TATA2);
    ini(TATA3);
    ini(TATA4);
    ini(TATA5);
    ini(TTGACA0);
    ini(TTGACA1);
    ini(TTGACA2);
    ini(TTGACA3);
    ini(TTGACA4);
    ini(TTGACA5);
    ini(A19);
    ini(A18);
    ini(A17);
    ini(A16);
    ini(A15);
    ini(A14);
    ini(A13);
    ini(A12);
    ini(A11);
    ini(A10);
    ini(A9);
    ini(A8);
    ini(A7);
    ini(A6);
    ini(A5);
    ini(A4);
    ini(A3);
    ini(A2);
    ini(F14);
    ini(F13);
    ini(F12);
    ini(F11);
    ini(F10);
    ini(F9);
    ini(F8);
    ini(F7);
    ini(F6);
    ini(F5);
    ini(F4);
    ini(F3);
    ini(F2);
    ini(BA);
    ini(BT);
    ini(BG);
    ini(BC);
    
    np= 66;
    
    {
        
        ifstream myfile("grammar0.txt");
        
        //read word by word
        
        int counter=0;
        while (counter<70)
        {
            
            
            getline(myfile, a);
            istringstream linestream(a);
            string word;
            
            
            //get lhs non-terminal
            linestream>>word;
            gram[counter][0].rule=word;

            
            //get arrow between grammar rules
            linestream>>word;
            
            
            //read first NT/T in rhs
            linestream>>word;
            
          
            if (word=="t"||word=="g"||word=="a"||word=="c")
            {
                    gram[counter][1].rule=word;
                    gram[counter][0].e=ERR[counter];

            }
            //if there is still another NT in rhs read it
            else
            {
                linestream>>temp;
                temp= word+ ' ' + temp;
                gram[counter][1].rule = temp;
                gram[counter][0].e = ERR[counter];
            }
            
            
            

            cout<<gram[counter][0].rule<< " -> " <<gram[counter][1].rule<< "   error: "<<gram[counter][0].e<<endl;
            counter++;
        }

        
        cout<<"\nEnter string to be checked : ";
        cin >> str;
        int iLen= str.length();
        melm matrix[60][60][10];
        string st,h, temp, h2;
        
        
        
        //fill the matrix with the terminal productions
        //Note to self: Working good dont miss with it
        for (i=0; i<iLen; i++)
        {
            int x=0;
            for (int i1=0; i1<70; i1++)
            {
                if(gram[i1][1].rule.find(str[i])!=std::string::npos)
                {

                    
                //MATRIX PART
                    matrix[i][i][x].rule=gram[i1][0].rule;
                    matrix[i][i][x].e=gram[i1][0].e;
                    
                    //LIST PART
                    
                    if(gram[i1][0].rule=="F2")
                    {
                        F2[i][i]=gram[i1][0].e;
                    }
                    if(gram[i1][0].rule=="BASE")
                    {
                        BASE[i][i]=0;
                    }
                    if(gram[i1][0].rule=="BA")
                    {
                       if(gram[i1][1].rule=="a")
                           BA[i][i]=0; else BA[i][i]=1;
                    }
                    if(gram[i1][0].rule=="BT")
                    {
                        if(gram[i1][1].rule=="t")
                            BT[i][i]=0; else BT[i][i]=1;
                    }
                    if(gram[i1][0].rule=="BG")
                    {
                        if(gram[i1][1].rule=="g")
                            BG[i][i]=0; else BG[i][i]=1;
                    }
                    
                    if(gram[i1][0].rule=="BC")
                    {
                        if(gram[i1][1].rule=="c")
                            BC[i][i]=0; else BC[i][i]=1;
                    }

                    

                    
                    x++;
                   
                }
                
                
                
                
            }
         
            
        }
      
        
        
        
        string R;
        int y=0;
        int x=0;
        int z=0;
        //fill the matrix with the nonterminal productions
        
        for (int s=1; s<iLen; s++)
             for(int i1=0; i1<75; i1++)
                for(int i=0; i+s<iLen; i++)
                    for(int k=i; k<s+i; k++)
                       
                    {

                        L1=999;
                        istringstream rhs(gram[i1][1].rule);
                        rhs >> B;
                        int y=0;
                        while(B!=matrix[i][k][y].rule&& matrix[i][k][y].rule!="")
                        {y++;}
                        if(B==matrix[i][k][y].rule)
                        {
                        if(rhs>>C){
                       
                            A=gram[i1][0].rule;
                            B.erase( remove_if(B.begin(), B.end(), ::isspace ), B.end() );
                            C.erase( remove_if(C.begin(), C.end(), ::isspace ), C.end() );
                            

                            
                            //If first NT in the grammar rhs has a previous error value in LIST save the error value to L1
                            
                            if(B=="S")      if(S[i][k]!=999)        L1=S[i][k];
                            if(B=="P1")     if(P1[i][k]!=999)       L1=P1[i][k];
                            if(B=="P2")    if(P2[i][k]!=999)      L1=P2[i][k];
                            if(B== "TATA0") if(TATA0[i][k]!=999)    L1=TATA0[i][k];
                            if(B== "TATA1") if(TATA1[i][k]!=999)    L1=TATA1[i][k];
                            if(B== "TATA2") if(TATA2[i][k]!=999)    L1=TATA2[i][k];
                            if(B== "TATA3") if(TATA3[i][k]!=999)    L1=TATA3[i][k];
                            if(B== "TATA4") if(TATA4[i][k]!=999)    L1=TATA4[i][k];
                            if(B== "TATA5") if(TATA5[i][k]!=999)    L1=TATA5[i][k];
                            if(B== "TTGACA0")  if(TTGACA0[i][k]!=999)    L1=TTGACA0[i][k];
                            if(B== "TTGACA1")  if(TTGACA1[i][k]!=999)    L1=TTGACA1[i][k];
                            if(B== "TTGACA2")  if(TTGACA2[i][k]!=999)    L1=TTGACA2[i][k];
                            if(B== "TTGACA3")  if(TTGACA3[i][k]!=999)    L1=TTGACA3[i][k];
                            if(B== "TTGACA4")  if(TTGACA4[i][k]!=999)    L1=TTGACA4[i][k];
                            if(B== "TTGACA5")  if(TTGACA5[i][k]!=999)    L1=TTGACA5[i][k];
                            if(B== "A19")  if(A19[i][k]!=999)       L1=A19[i][k];
                            if(B== "A18")  if(A18[i][k]!=999)       L1=A18[i][k];
                            if(B== "A17")  if(A17[i][k]!=999)       L1=A17[i][k];
                            if(B== "A16")  if(A16[i][k]!=999)       L1=A16[i][k];
                            if(B== "A15")  if(A15[i][k]!=999)       L1=A15[i][k];
                            if(B== "A14")  if(A14[i][k]!=999)       L1=A14[i][k];
                            if(B== "A13")  if(A13[i][k]!=999)       L1=A13[i][k];
                            if(B== "A12")  if(A12[i][k]!=999)       L1=A12[i][k];
                            if(B== "A11")  if(A11[i][k]!=999 )       L1=A11[i][k];
                            if(B== "A10")  if(A10[i][k]!=999)       L1=A10[i][k];
                            if(B== "A9")   if(A9[i][k]!=999)        L1=A9[i][k];
                            if(B== "A8")   if(A8[i][k]!=999)        L1=A8[i][k];
                            if(B== "A7")   if(A7[i][k]!=999)        L1=A7[i][k];
                            if(B== "A6")   if(A6[i][k]!=999)        L1=A6[i][k];
                            if(B== "A5")   if(A5[i][k]!=999)        L1=A5[i][k];
                            if(B== "A4")   if(A4[i][k]!=999)        L1=A4[i][k];
                            if(B== "A3")   if(A3[i][k]!=999)        L1=A3[i][k];
                            if(B== "A2")   if(A2[i][k]!=999)        L1=A2[i][k];
                            if(B=="F14")     if(F14[i][k]!=-999)         L1=F14[i][k];
                            if(B=="F13")     if(F13[i][k]!=-999)         L1=F13[i][k];
                            if(B=="F12")     if(F12[i][k]!=-999)         L1=F12[i][k];
                            if(B=="F11")     if(F11[i][k]!=-999)         L1=F11[i][k];
                            if(B=="F10")     if(F10[i][k]!=-999)         L1=F10[i][k];
                            if(B=="F9")     if(F9[i][k]!=-999)         L1=F9[i][k];
                            if(B=="F8")     if(F8[i][k]!=-999)         L1=F8[i][k];
                            if(B=="F7")     if(F7[i][k]!=-999)         L1=F7[i][k];
                            if(B=="F6")     if(F6[i][k]!=-999)         L1=F6[i][k];
                            if(B=="F5")     if(F5[i][k]!=-999)         L1=F5[i][k];
                            if(B=="F4")     if(F4[i][k]!=-999)         L1=F4[i][k];
                            if(B=="F3")     if(F3[i][k]!=-999)         L1=F3[i][k];
                            if(B=="F2")     if(F2[i][k]!=-999)         L1=F2[i][k];
                            if(B== "BASE") if(BASE[i][k]!=999)      L1=BASE[i][k];
                            if(B== "BA")   if(BA[i][k]!=999)        L1=BA[i][k];
                            if(B== "BT")   if(BT[i][k]!=999)        L1=BT[i][k];
                            if(B== "BG")   if(BC[i][k]!=999)        L1=BG[i][k];
                            if(B== "BC")   if(A9[i][k]!=999)        L1=BG[i][k];
                            
                            x=0;
                            bool found=false;
                            //Look for C in matrix
                            while(matrix[k+1][i+s][x].rule!="" && matrix[k+1][i+s][x].rule!=C){

                                x++;}

                            
                                //if C found put the error value in L2
                                if(matrix[k+1][i+s][x].rule==C)
                                {
                                    
                                    
                                    L2=matrix[k+1][i+s][x].e;
                                    
                                    found=true;
                                


                                L=L1+L2+gram[i1][0].e;
                                    
                                
                                    A.erase( remove_if(A.begin(), A.end(), ::isspace ), A.end() );
                                int z=0;
                                    matrix[i][i+s][z].rule.erase(remove_if(matrix[i][i+s][z].rule.begin(), matrix[i][i+s][z].rule.end(), ::isspace ), matrix[i][i+s][z].rule.end() );
                                    while(matrix[i][i+s][z].rule!="" && matrix[i][i+s][z].rule!=A){
                                        matrix[i][i+s][z].rule.erase(remove_if(matrix[i][i+s][z].rule.begin(), matrix[i][i+s][z].rule.end(), ::isspace ), matrix[i][i+s][z].rule.end() );

                                      z++;
                                    }
                                    
                                matrix[i][i+s][z].rule=A;

                                    //if it is a new rule set the value to error sum
                                if(matrix[i][i+s][z].e==-1)
                                    matrix[i][i+s][z].e=L;
                                    
                                    //if it is not a new rule and the error found is larger than the sum, set the sum to be the new error
                                if(matrix[i][i+s][z].e>L)
                                    matrix[i][i+s][z].e=L;
                                    
                                    
                                    
                                        if(A=="S")
                                            if(S[i][i+s]>L)
                                                S[i][i+s]=L;
                                        if(A=="P1")
                                            if(P1[i][i+s]>L)
                                                P1[i][i+s]=L;
                                        if(A=="P2")
                                            if(P2[i][i+s]>L)
                                                P2[i][i+s]=L;
                                        if(A== "TATA0")
                                            if(TATA0[i][i+s]>L)
                                                TATA0[i][i+s]=L;
                                        if(A== "TATA1")
                                            if (TATA1[i][i+s]>L)
                                                TATA1[i][i+s]=L;
                                        if(A== "TATA2")
                                            if(TATA2[i][i+s]>L)
                                                TATA2[i][i+s]=L;
                                        if(A== "TATA3")
                                            if(TATA3[i][i+s]>L)
                                                TATA3[i][i+s]=L;
                                        if(A== "TATA4")
                                            if(TATA4[i][i+s]>L)
                                                TATA4[i][i+s]=L;
                                        if(A== "TATA5")
                                            if(TATA5[i][i+s]>L)
                                                TATA5[i][i+s]=L;
                                        if(A== "TTGACA0")
                                            if(TTGACA0[i][i+s]>L)
                                                TTGACA0[i][i+s]=L;
                                        if(A== "TTGACA1")
                                            if(TTGACA1[i][i+s]>L)
                                                TTGACA1[i][i+s]=L;
                                        if(A== "TTGACA2")
                                            if(TTGACA2[i][i+s]>L)
                                                TTGACA2[i][i+s]=L;
                                        if(A== "TTGACA3")
                                            if(TTGACA3[i][i+s]>L)
                                                TTGACA3[i][i+s]=L;
                                        if(A== "TTGACA4")
                                            if(TTGACA4[i][i+s]>L)
                                                TTGACA4[i][i+s]=L;
                                        if(A== "TTGACA5")
                                            if(TTGACA5[i][i+s]>L)
                                                TTGACA5[i][i+s]=L;
                                        if(A== "A19")
                                            if(A19[i][i+s]>L)
                                                A19[i][i+s]=L;
                                        if(A== "A18")
                                            if(A18[i][i+s]>L)
                                                A18[i][i+s]=L;
                                        if(A== "A17")
                                            if(A17[i][i+s]>L)
                                                A17[i][i+s]=L;
                                        if(A== "A16")
                                            if(A16[i][i+s]>L)
                                                A16[i][i+s]=L;
                                        if(A== "A15")
                                            if(A15[i][i+s]>L)
                                                A15[i][i+s]=L;
                                        if(A== "A14")
                                            if(A14[i][i+s]>L)
                                                A14[i][i+s]=L;
                                        if(A== "A13")
                                            if(A13[i][i+s]>L)
                                                A13[i][i+s]=L;
                                        if(A== "A12")
                                            if(A12[i][i+s]>L)
                                                A12[i][i+s]=L;
                                        if(A== "A11")
                                            if(A11[i][i+s]>L)
                                                A11[i][i+s]=L;
                                        if(A== "A10")
                                            if(A10[i][i+s]>L)
                                                A10[i][i+s]=L;
                                        if(A== "A9")
                                            if(A9[i][i+s]>L)
                                                A9[i][i+s]=L;
                                        if(A== "A8")
                                            if(A8[i][i+s]>L)
                                                A8[i][i+s]=L;
                                        if(A== "A7")
                                            if(A7[i][i+s]>L)
                                                A7[i][i+s]=L;
                                        if(A== "A6")
                                            if(A6[i][i+s]>L)
                                                A6[i][i+s]=L;
                                        if(A== "A5")
                                            if(A5[i][i+s]>L)
                                                A5[i][i+s]=L;
                                        if(A== "A4")
                                            if(A4[i][i+s]>L)
                                                A4[i][i+s]=L;
                                        if(A== "A3")
                                            if(A3[i][i+s]>L)
                                                A3[i][i+s]=L;
                                        if(A== "A2")
                                            if(A2[i][i+s]>L)
                                                A2[i][i+s]=L;
                                    A2[i][i+s]=L;
                                    if(A=="F14")
                                        if(F14[i][i+s]>L)
                                            F14[i][i+s]=L;
                                    if(A=="F13")
                                        if(F13[i][i+s]>L)
                                            F13[i][i+s]=L;
                                    if(A=="F12")
                                        if(F12[i][i+s]>L)
                                            F12[i][i+s]=L;
                                    if(A=="F11")
                                        if(F11[i][i+s]>L)
                                            F11[i][i+s]=L;
                                    if(A=="F10")
                                        if(F10[i][i+s]>L)
                                            F10[i][i+s]=L;
                                    if(A=="F9")
                                        if(F9[i][i+s]>L)
                                            F9[i][i+s]=L;
                                    if(A=="F8")
                                        if(F8[i][i+s]>L)
                                            F8[i][i+s]=L;
                                    if(A=="F7")
                                        if(F7[i][i+s]>L)
                                            F7[i][i+s]=L;
                                    if(A=="F6")
                                        if(F6[i][i+s]>L)
                                            F6[i][i+s]=L;
                                    if (A=="F5")
                                        if(F5[i][i+s]>L)
                                            F5[i][i+s]=L;
                                    if(A=="F4")
                                        if(F4[i][i+s]>L)
                                            F4[i][i+s]=L;
                                    if(A=="F3")
                                        if(F3[i][i+s]>L)
                                            F3[i][i+s]=L;
                                    if(A=="F2")
                                        if(F2[i][i+s]>L)
                                            F2[i][i+s]=L;
                                    
                                        if(A== "BASE")
                                            if(BASE[i][i+s]>L)
                                                BASE[i][i+s]=L;
                                        if(A== "BA")
                                            if(BA[i][i+s]>L)
                                                BA[i][i+s]=L;
                                        if(A== "BT")
                                            if(BT[i][i+s]>L)
                                                BT[i][i+s]=L;
                                        if(A== "BG")
                                            if(BG[i][i+s]>L)
                                                BG[i][i+s]=L;
                                        if(A== "BC")
                                            if(BC[i][i+s]>L)
                                                BC[i][i+s]=L;

                                }
                            
                            

                    }
                        }
                    }
        

        

        x=0;
        while(matrix[0][iLen-1][x].rule!="")
        {
   
            if(matrix[0][iLen-1][x].rule=="S")
            {
                //distance thresold is set to 7
                if(matrix[0][iLen-1][x].e>7)
                    cout<<endl<<"This string is not an E Coli promoter sequence."<< endl;
                else{
                    cout<<endl<<"This string is an E Coli promoter sequence."<< endl<<"Distance: "<<matrix[0][iLen-1][x].e<< endl;}
                
            }
            x++;
        }

        return 0;
        
        
    }
    
}


