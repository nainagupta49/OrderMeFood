#include<iostream>
#include<fstream>
#include<string>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<climits>
#include<cwchar>
using namespace std;

class dish{
    public:
    string dname;
    int dprice;
    int dtime;
    string dno;
    dish()
    {
        dno=" ";
    }
};
class cuisine{
    string cname;
    dish *d[7];
};

class hotel{
    string hname;
    string location;
    cuisine *c[5];
};

class user{
    string pin;
    string userId;
    string fname;
    string lname;
    string location;
    string code;           //LX
    public:
    void userLogin();
    void createNewUser();
};

struct Gnode{
    struct Gnode *next;
    string cd;
    int d;
};
int countRL(){
    ifstream fin;
    fin.open("area_map.txt");
    if(!fin)
        cout<<"area_map.txt not opened";
    int l=0;            //total land marks
    string lin;         //to store each line for counting purpose
    while(fin){
        l++;
        getline(fin,lin);
    }
    l=l-1;
       //as file handling counts last line twice so we do -1
    fin.close();
    return l;
}

Gnode * createGraph(){
    int l=countRL();
    struct Gnode * G=new struct Gnode[l];
    ifstream fin;
    fin.open("area_map.txt");
    int c=0,nt=0;
    string st;
    int n;
    struct Gnode * k;
    while(c!=l){
        fin>>st;
        k = &G[c];
        G[c].cd=st;
        G[c].d=nt;
        nt++;
        G[c].next=0;
        while(fin){
            fin>>st;
            if(st!="e"){
                struct Gnode *t=new struct Gnode;
                t->next=0;
                t->cd=st;
                fin>>n;
                t->d=n;
                k->next=t;
                k=t;
            }
            else
                break;
        }
        c+=1;
    }
    //for(int j=0;j<l;j++)
      //  cout<<G[j].cd<<" ";
    return G;
}
int minDistance(int dist[], int sptSet[],int V)
{
   // Initialize min value
   int min = 10000,min_index;

   for (int v = 0; v < V; v++)
     if (sptSet[v] == 0 && dist[v] <= min)
         min = dist[v], min_index = v;

   return min_index;
}
void printRestaurants(int dist[], int l,struct Gnode * G,string d[],int rnum)
{
    struct Gnode * tmp;
    int rt;
   cout<<"Restaurant\t\t\tdistance\n";
   for (int i = 0; i < rnum; i++){
        tmp=G;
        for(int j=0;j<l;j++){
        if(tmp[j].cd==d[i]){
            rt=tmp[j].d;
            break;
        }
    }
    cout<<"\t"<<d[i]<<"\t\t\t\t"<<dist[rt]<<endl;
   }
}
void dijkstra(string s,string d[],int rnum){
    struct Gnode * G= createGraph();
    int l=countRL();
    int src;
    struct Gnode * tmp=G;
    for(int i=0;i<l;i++){
    if(tmp[i].cd==s){
        src=tmp[i].d;
        break;
        }
    }
    int * dist=new int[l];
    int * sptSet=new int[l];
    for(int i=0;i<l;i++){
        dist[i]=100;
        sptSet[i]=0;
        }

    dist[src]=0;
    int v;
    Gnode * tmpk;
     for (int count = 0; count < l-1; count++) {
        int u = minDistance(dist, sptSet,l);
        sptSet[u] = 1;
       // Update dist value of the adjacent vertices of the picked vertex.
       tmp=G[u].next;
       while(tmp){
        tmpk=G;
        for(int i=0;i<l;i++){
            if(tmpk[i].cd==tmp->cd){
                v=tmpk[i].d;
                break;
                }
            }
         if (!sptSet[v] && dist[u] != INT_MAX && dist[u]+tmp->d < dist[v]){
            dist[v] = dist[u] + tmp->d;}
        tmp=tmp->next;
     }
     }
     // print the constructed distance array
     printRestaurants(dist,l,G,d,rnum);
}
void menu(string loc,string uid){
    string a;
    dish D;
    dish d1;
    cout<<"\n\n\t\t\t\t\t\t\t=====EXPLORE YOUR FAVOURITE CUISINES====="<<endl;
    cout<<"\n\n\n\t===========================\t\t\t==========================\t\t\t\t==========================="<<endl;
    cout<<"\n[1] NORTH INDIAN\n[2] MUGHLAI\n[3] CHINESE\n[4] CONTINENTAL\n[5] SOUTH INDIAN\n[6] HYDERABADI\n[7] THAI\n[8] ITALIAN\n===========================\t\t\t==============================\t\t\t\t===========================\n\n\n\t\t\t\t\t\t\t\t[9] EXIT"<<endl;
    cout<<"\n\t======================================================================================================================================="<<endl;
    cout<<"Enter cuisine number:";
    cin>>a;
    string cno="C"+a;
    system("clear");
    ifstream fin;
    fin.open("Rcuisines.txt");
    if(!fin)
        cout<<"Not found Rcuisines"<<endl;
    string Rt,num="0";
    string Rarr[6];
    int rnum=0;
    fin>>Rt;
    while(fin){
        while(num[0]!='R' && fin){
            fin>>num;
            if(num==a){
                //cout<<Rt<<" ";
                Rarr[rnum++]=Rt;
            }
        }
        Rt=num;
        num="0";
    }
    fin.close();
    dijkstra(loc,Rarr,rnum);
    //--------------------------------
    ifstream fiin;
    string sa,c="C"+a,rloc;
    cout<<"Enter restaurant of your choice:   ";
    cin>>sa;
    rloc=sa;
    system("clear");
    sa=sa+".txt";
    string sb=sa;
    fiin.open(sa);
    if(!fiin)
        cout<<"not open";
    while(fiin){
        fiin>>sa;
        if(sa==c){
            cout<<"\t\t\t\t\tORDER-ORDER\n\n\n";
            while(D.dno[0]!='C'){
                fiin>>D.dno>>D.dname>>D.dprice>>D.dtime;
                if(D.dno[0]!='C')
                cout<<D.dno<<" "<<D.dname<<" "<<D.dprice<<" "<<D.dtime<<endl;
            }
            break;
        }
    }
    fiin.close();
    int qty;
    char ch='Y';
    string d;
    dish ordered;
    int bill=0;
    int ocount=0;
    string odish[5];
    int oqty[5];
    while((ch=='Y'||ch=='y')&& ocount<=5){
        ocount++;
        cout<<"Enter dish number you want to order:\t"<<endl;
        cin>>d;
        cout<<"Enter quantity:\t"<<endl;
        cin>>qty;
        fiin.open(sb);
     while(fiin){
        fiin>>sa;
        if(sa==c){
            D.dno="X";
            while(D.dno[0]!='C'){
                fiin>>D.dno>>D.dname>>D.dprice>>D.dtime;
                if(D.dno[0]!='C'){
                if(D.dno==d){
                    ordered.dno=D.dno;
                    ordered.dname=D.dname;
                    odish[ocount-1]=D.dname;
                    oqty[ocount-1]=qty;
                    ordered.dprice=D.dprice*qty;
                    cout<<"\nDish Price: "<<ordered.dprice<<" ";
                    ordered.dtime=D.dtime;
                }
                }
            }
            break;
        }
    }
    fiin.close();
    bill+=ordered.dprice;

       cout<<"\n\nWants to order more?[y/n]";
       cin>>ch;
       cout<<endl;
    }

    cout<<"------------BILL-------------\n";
    cout<<"ordered dishes\t\tquantity\n";
    for(int dco=0;dco<ocount;dco++)
        cout<<"\n\n"<<odish[dco]<<"\t\t\t"<<oqty[dco];
    cout<<"\nTotal bill: "<<bill<<endl;
    //------writing order in user file for future suggestions---------------
    ifstream feedin;
    fstream feedout;
    feedin.open("userHistory.txt");
    feedout.open("tempHistory.txt",ios::out);
    if(!feedin)
      cout<<"userHistory file not opened\n";
    if(!feedout)
      cout<<"tempHistory file not opened\n";
    string uidd,cnam;
    int ccno=8;
    int cprice,ff;
    int ccount;
    int tdsum=0;
    for(int dco=0;dco<ocount;dco++)
        tdsum+=oqty[dco];
    while(feedin>>uidd){
      feedout<<"\n"<<uidd<<" ";
      for(int i=1;i<=ccno;i++){
        feedin>>cnam>>cprice>>ccount;
        //ff=((int)cnam[1])-48;
        if(uidd==uid && cno==cnam){
          cprice+=bill;
          ccount+=tdsum;
      }
        feedout<<cnam<<" "<<cprice<<" "<<ccount<<" ";
    }
    }
    feedin.close();
    feedout.close();
    remove("userHistory.txt");
    rename("tempHistory.txt","userHistory.txt");

    //-------------writing all order in one file for future rating purpose-----------------
    fstream foout;
    foout.open("ordered.txt", ios::out | ios::app);
    if(!foout){
    cout<<"ordered.txt not opened";
    }
    foout<<"\n"<<uid<<" "<<rloc<<" "<<cno<<" "<<bill<<" "<<ocount<<" ";
    for(int dco=0;dco<ocount;dco++)
        foout<<odish[dco]<<" "<<oqty[dco]<<" ";
    foout.close();
    //-------------writing order in specific restaurant file to apply stenner algo-----------------
    string x1=rloc+"orders.txt";
    foout.open(x1, ios::out | ios::app);
    if(!foout){
    cout<<rloc<<"orders.txt not opened\n";
    }
    foout<<"\n"<<loc<<" "<<" "<<uid<<" "<<ocount<<" ";
    for(int dco=0;dco<ocount;dco++)
        foout<<odish[dco]<<" "<<oqty[dco]<<" ";
    foout<<bill;
    foout.close();
}

void feedback(string uid){
  ifstream fin;
  fstream fout;
  fin.open("ordered.txt");
  fout.open("tempord.txt",ios::out);
  if(!fin)
    cout<<"ordered.txt file not found for FEEDBACK\n";
  if(!fout){
    cout<<"tempord.txt not opened for FEEDBACK\n";
    }
  string id;
  int tbill,tdish,dqty[10];
  string rloc,cusi,dname[10];
  while (fin>>id) {
      float fd;
      fin>>rloc>>cusi>>tbill>>tdish;
      for(int i=0;i<tdish;i++){
        fin>>dname[i]>>dqty[i];
      }
      if(id==uid){
      cout<<"\n\t\t ******** Time For Some FEEDBACK ********\n\n";
      cout<<"Rate your previous dishes out of 5: \n";
      cout<<"Restaurant :"<<rloc;
      cout<<"\n\tYou ordered "<<tdish<<"dishes :\n";
      for(int i=0;i<tdish;i++){
        cout<<dname[i]<<"\t"<<dqty[i]<<endl;
      }
      cout<<"You Paid:  "<<tbill<<endl;
      cout<<"Enter your rating [out of 5]: ";
      cin>>fd;
      ifstream feedin;
      fstream feedout;
      feedin.open("feedbackAll.txt");
      feedout.open("tempfeedback.txt",ios::out);
      if(!feedin)
        cout<<"feedbackAll file not opened\n";
      if(!feedout)
        cout<<"tempfeedback file not opened\n";
      string rname,cname;
      int peoplect;
      float rating;
      while(feedin>>rname){
        feedin>>cname>>rating>>peoplect;
        if(rloc==rname && cname==cusi){
          peoplect+=1;
          rating+=fd;
        }
        feedout<<"\n"<<rname<<" "<<cname<<" "<<rating<<" "<<peoplect;
      }
      feedin.close();
      feedout.close();
      remove("feedbackAll.txt");
      rename("tempfeedback.txt","feedbackAll.txt");
      }
      else{
        fout<<"\n"<<id<<" "<<rloc<<" "<<cusi<<" "<<tbill<<" "<<tdish<<" ";
        for(int i=0;i<tdish;i++){
          fout<<dname[i]<<" "<<dqty[i]<<" ";
        }
      }
  }
fout.close();
fin.close();
remove("ordered.txt");
rename("tempord.txt","ordered.txt");
}
void suggestion(string userId){
  //to give suggestions
  cout<<"\n\n\n\n\n\t****SUGGESTIONS for you****";
}
void user::userLogin(){
    system("clear");
    cout<<"\t\t\t\t If new user enter id=0 and pass=0"<<endl;
    cout<<"Enter ID:";
    cin>>userId;
    cout<<"Enter pin:";
    cin>>pin;
    if(pin=="0" && userId=="0"){
        createNewUser();
        }
    else{
        ifstream fin;
        string f,l,i,p,loc,cd;
        bool userExist=false;
        fin.open("user_detail.txt");
        if(!fin)
        cout<<"file not found";
        while (fin) {
            fin>>f>>l>>i>>p>>loc>>cd;
            if(i==userId && p==pin){
            cout<<"Welcome "<<f<<" "<<l<<endl;
            userExist=true;
            break;
            }
        }
    fin.close();

    if(!userExist){
        cout<<"Invalid Pin or UserId\n1.try again\n2.exit";
    int ch;
    cin>>ch;
    if(ch==1)
        userLogin();
    else
        exit(0);
    }
    else{
        feedback(userId);
        suggestions(userId);
        menu(cd,userId);
        }
    }
}

string checklocation(string loc){
    ifstream flin;
    flin.open("landmarks.txt");
    string l,cd;int f=0;
    while(flin){
        flin>>l;
        if(l==loc){
            cout<<"correct location found"<<loc;
            f=1;
            flin>>cd;
            cout<<cd;
            break;}
        }
    flin.close();
    if(f==0){
        cout<<"You entered wrong location. Renter right location:";
        cin>>loc;
        cd=checklocation(loc);
        }
        return cd;
}
void user::createNewUser(){
    ofstream fout;
    fout.open("user_detail.txt",ios::app);
    cout<<endl;
    cout<<"Enter first name: ";
    cin>>fname;
    cout<<"Enter last name: ";
    cin>>lname;
    cout<<"Enter user Id: ";
    cin>>userId;
    cout<<"Enter pin: ";
    cin>>pin;
    cout<<"Enter location: ";
    cin>>location;
    code=checklocation(location);
    fout<<fname<<" "<<lname<<" "<<userId<<" "<<pin<<" "<<location<<" "<<code<<endl;
    fout.close();
    system("clear");
    //----Enter a new entry in userHistory-------------------
    fout.open("userHistory.txt",ios::app);
    fout<<endl<<userId<<" C1 0 0 C2 0 0 C3 0 0 C4 0 0 C5 0 0 C6 0 0 C7 0 0 C8 0 0 ";
    fout.close();
    cout<<"------------Id created sucessfully.Enjoy OrderMeFood!!------------";
    menu(code,userId);
}
/*
adminu(string rid)
{
  rid2=rid+"orders.txt";
  ifstream fin;
  fin(rid2);
  if(!fin)
  {
    cout<<"restaurant does not exist";
  }
  while(fin)
  {
    str uloc[20]='0';
    str currloc;
    int index=0;
    while(getline(fin,currloc))
    {
      str getuloc=currloc[0]+currloc[1]+currloc[2];
      if(getuloc[2]==" ")
      {
        getuloc.pop_back();
      }
      uloc[index++]=getuloc;
    }
    // apply steiner on map with restaurant rid and locations in uloc array
    uloc[index]=rid;
    steiner(uloc);
  }


}
*/
int main()
{
    int var=0;
    cout<<"\n\n\n\t=============== WELCOME TO FOOD ORDERING SYSTEM ===============\n\n\n"<<endl;
    cout<<"\t\t\t\t[1] USER\n\t\t\t\t[2] ADMIN\n\t\t\t\t[3] EXIT\n\n\n\nEnter choice:  ";
    cin>>var;
    if(var==1){
        user U;
        U.userLogin();
        }
    else if(var==2){
          cout<<"Enter Restaurant\n";
          string rid;
          cin>>rid;
          //adminu(rid);

//       cout<<"Work Under Construction:";
    }
    else{
        exit(0);
    }
}
