#include<bits/stdc++.h>
using namespace std;
#include<fstream>
#include<stdlib.h>
#include<windows.h>
COORD coord= {0,0}; // this is global variable
void build(string );
//ofstream: Stream class to write on files
//ifstream: Stream class to read from files
void gotoxy(int x,int y)//change Cursor Location
{
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
class Bus
{
public:
    string Name;
    string number;
    void bus_info(string s,int n)
    {
        cout<<"Bus Name   : "<<Name<<endl;
        cout<<"Bus Number : "<<number<<endl;
    }
} bus[20];

class Passenger
{
public:
    int booking ;

    string Name;
    string Phone_Number;
    string Destination ;
public:
    void display()
    {
        cout<<"\n\n";
        cout<<"  User  Name   : "<<Name<<endl;
        cout<<"  Phone Number : "<<Phone_Number<<endl;
        cout<<"  Travel From  : "<<Destination<<endl;
        cout<<endl<<endl;
    }
} seat[50];

class Shedule
{
public:
    string date;
    string Time;
    void Display_Shedule()
    {
        cout<<" Journey Time : "<<Time<<endl;
        cout<<" Date : "<<date<<endl;
    }
} TIME[24];

string ROUTE(int condition)
{
    ifstream file;
    file.open("Route.text");
    vector<string> root;
    string line;
    int cnt=0,i=1;
    system("cls");
    while(getline(file,line))
    {
        gotoxy(40,cnt++);
        if(cnt==1)
            cout<<"__Available Route__\n"<<endl,gotoxy(40,cnt++);
        cout<<i++<<" . "<<line<<endl;
        root.push_back(line);
    }
    file.close();
    if(condition==1)
    {
        ofstream myfile;
        myfile.open("Route.text");
        gotoxy(40,cnt++);

        cout<<"Enter From and To"<<endl;
        gotoxy(40,cnt++);
        cout<<"-----------------"<<endl;
        string from,to,dis;
        gotoxy(40,cnt++);
        cin>>from>>to;
        dis=from+" To "+to;
        root.push_back(dis);
        for(int i=0; i<root.size(); i++)
        {
            myfile<<root[i]<<endl;
        }
        myfile.close();
    }
    else
    {
        gotoxy(40,cnt++);
        int choice;
        cout<<"Enter Your Choice : ";
        cin>>choice;
        system("cls");
        return root[choice-1];
    }

}


void Bus_Display()
{
    int i,j=3;
    gotoxy(50,0);
    cout<<"  __________";
    gotoxy(50,1);
    cout<<" |       (+)|";
    gotoxy(50,2);
    cout<<" |      ____|";
    char c='A';
    for(i=0; i<40; i++)
    {
        gotoxy(50,j++);

        cout<<c<<"| "<<seat[i].booking;
        i++;
        cout<<" "<<seat[i].booking;
        i++;
        cout<<"  "<<seat[i].booking;
        i++;
        cout<<" "<<seat[i].booking<<" |";
        c++;
    }
    gotoxy(50,j);
    cout<<" |__________|";
    gotoxy(0,1);
}
void Bus_Details(string BUS)
{
    ifstream file;
    file.open(BUS+".text");
    string line;
    cout<<"Bus Schedule (Time) "<<endl;
    cout<<"--------------------"<<endl;
    int cnt=0,i=0;
    while(getline(file,line))
    {
        if(cnt%2==0)
        {
            cnt++;
            bus[i].Name=line;
        }
        else
        {
            cnt++;
            bus[i].number=line;
            i++;
        }
    }
    file.close();
    cout<<"Enter Bus Name : ";
    cin>>bus[i].Name;
    cout<<"Enter Number : ";
    cin>>bus[i].number;
    ofstream myfile;
    myfile.open(BUS+".text");
    int     j=i;
    for(int i=0; i<j; i++)
    {
        myfile<<bus[i].Name<<endl;
        myfile<<bus[i].number<<endl;
    }
    myfile.close();
}
string Date(string route, int per)
{
    vector<string>dt;
    ifstream file;
    string filename=route+"date.text";
    file.open(filename);
    string line;
    int i=0;
    while(getline(file,line))
    {
        if(i==0)
        {
            cout<<"  Date  (dd/mm/yy)"<<endl;
            cout<<"------------------"<<endl;
        }
        dt.push_back(line);
        cout<<++i<<". "<<line[0]<<line[1]<<"/"<<line[2]<<line[3]<<"/20"<<line[4]<<line[5]<<endl;
    }
    file.close();
    if(per==1)
    {
        cout<<"Enter Choice "<<endl;
        int cho;
        cin>>cho;
        return dt[cho-1];
    }

    cout<<"Do You want to Add new Date? (y/n)"<<endl;
    string ck;
    int choice=0;
    cin>>ck;
    if(ck=="y")
    {
        getchar();
        cout<<"Enter Date (dd/mm/yy)"<<endl;
        string s;
        getline(cin,s);
        dt.push_back(s);
    }
    else
    {
        cout<<"Enter Choice "<<endl;
        cin>>choice;
        return dt[choice-1];
    }
    ofstream dtw;
    dtw.open(filename);
    for( i=0; i<dt.size(); i++)
        dtw<<dt[i]<<endl;

    dtw.close();
    return dt[i-1];
}
string Time_Schedule( string date,int per)
{
    string filename=date+"time.text";
    ifstream file;
    file.open(filename);
    vector<string> root;
    string line;
    int index=0;
    while(getline(file,line))
    {
        root.push_back(line);
        if(line=="\0")
            continue;
        if(index==0)
        {
            cout<<"Bus Schedule Time "<<endl;
            cout<<"------------------"<<endl;
        }
        cout<<++index<<" . "<<line[0]<<line[1]<<" : "<<line[2]<<line[3]<<endl;
    }
    file.close();
    if(per==1)
    {
        cout<<"Enter Your Choice : "<<endl;
        int i;
        cin>>i;
        return root[i-1];
    }

    if(index!=0)
    {
        string ck;
        cout<<"Do You Want To Add New Time?(y/n)"<<endl;
        getchar();
        cin>>ck;
        if(ck=="n")
        {
            cout<<"Enter Your Choice : "<<endl;
            int i;
            cin>>i;
            return root[i-1];
        }
    }
    ofstream myfile;
    myfile.open(filename);
    //getchar();
    cout<<" Time (hh : mm) "<<endl;
    string t;
    getline(cin,t);
    root.push_back(t);
    for(int i=0; i<root.size(); i++)
    {
        myfile<<root[i]<<endl;
    }
    myfile.close();
    return t;
}
void fileopen(string route)
{
    ifstream myfile;
    myfile.open(route);
    int cnt=0,i=-1;
    string line;
    while(getline(myfile,line))
    {
        cnt++;
        if(cnt%4==1)
        {
            i++;
            if(line=="0")
                seat[i].booking=0;
            else
                seat[i].booking=1;
        }
        else if(cnt%4==2)
        {
            seat[i].Name=line;
        }
        else if(cnt%4==3)
        {
            seat[i].Phone_Number=line;
        }
        else if(cnt%4==0)
        {
            seat[i].Destination=line;
        }

    }
    myfile.close();
}
void New_Bus()
{
    system("cls");
    string route=ROUTE(2);// find the route
    string date=Date(route,0);
    string co=route+date;
    string time=Time_Schedule(co,0);//bus start time

    string name=route+date+time+".text";
    ifstream file;
    file.open(name);
    string line;
    vector<string>v;
    while(getline(file,line))
    {
        v.push_back(line);
    }

    file.close();
    string namE,nuM;
    system("cls");
    cout<<"From "<<route<<endl<<endl;
    cout<<"Enter Bus Name : ";
    cin>>namE;
    cout<<"Enter Bus Number : ";
    getchar();
    cin>>nuM;
    v.push_back(namE);
    v.push_back(nuM);

    ofstream write;
    write.open(name);
    for(int i=0; i<v.size(); i++)
    {
        write<<v[i]<<endl;
        i++;
        write<<v[i]<<endl;
    }
    write.close();

    string busfile=route+date+time+nuM;
    build(busfile);
}
string BUS_num(string s)
{
    ifstream file;
    file.open(s);
    string line;
    int i=0,ind=0;
    while(getline(file,line))
    {
        if(i%2==0)
            bus[ind].Name=line;
        else
            bus[ind++].number=line;
        i++;
    }
    system("cls");
    cout<<"Available Buses"<<endl;
    for(int j=0; j<ind; j++)
    {
        cout<<j+1<<" . "<<bus[j].Name<<endl;
    }
    cout<<"Enter Your Choice : ";
    int b;
    cin>>b;
    return bus[b-1].number;
}
bool Password()
{
    system("cls");
    ifstream myfile;
    myfile.open("Password.text");
    string line;
    string password;
    getline(myfile,line);
    myfile.close();
    gotoxy(35,7);
    cout<<"----Welcome To Admin Panel----\n";
    gotoxy(37,9);
    cout<<"Password : ";
    cin>>password;
    system("cls");
    if(password==line)
    {
        return true;
    }
    return false;
}
void Change_Password()
{
    cout<<"Enter Code \n";
    string code;
    cin>>code;
    if(code!="9655")
    {
        cout<<"Wrong Code\n";
        system("Pause");
        return;
    }
    ofstream myfile;
    myfile.open("Password.text");
    cout<<"Enter New Password : ";
    string pass;
    cin>>pass;
    myfile<<pass;
    myfile.close();
    return;
}
void Check_info()
{

    while(1)
    {
        system("cls");
        string dis=ROUTE(2);
        string date=Date(dis,1);
        string time=Time_Schedule(dis+date,1);
        string loc=dis+date+time+".text";
        string bus_no=BUS_num(loc);
        string m_file=dis+date+time+bus_no+".text";
        fileopen(m_file);
        system("cls");
        Bus_Display();
        string  s;
        cout<<"From "<<dis<<endl;
        cout<<"Enter Seat Number : (A-J,1-4)\n";
        cin>>s;
        int d=s[0]-65,e=s[1]-49;
        int sit=d*4+e;
        if(sit>=0&&sit<40)
        {
            if(seat[sit].booking==1)
            {
                seat[sit].display();
            }
            else
                cout<<"Not Booked Yet"<<endl;
        }
        else
        {
            cout<<"Wrong Seat Number"<<endl;
        }
        cout<<"Do You Want To Check Again ? (y/n)"<<endl;
        cin>>s;
        if(s=="n")
            return;
        system("cls");
    }
}
void build(string dis)
{
    ofstream myfile;
    myfile.open(dis+".text");
    for(int i=0; i<4*40; i++)
    {
        if(i%4==0)
            myfile<<"0\n";
        else
            myfile<<"\n";
    }
    myfile.close();
}
void Seat_Booking()
{
    system("cls");
    gotoxy(0,2);
    getchar();
    string name,direction,phonenumber;
    int chose=1;
    string route=ROUTE(2);
    string date=Date(route,1);
    string time=Time_Schedule(route+date,1);

    string bus_number=BUS_num(route+date+time+".text");

    string location=route+date+time+bus_number+".text";

    system("cls");
    cout<<" From "<<route<<endl;
    fileopen(location);
    Bus_Display();
    getchar();
    cout<<" Enter Name : ";
    getline(cin,name);
    cout<<" Enter Number : ";
    getline(cin,phonenumber);
    while(chose==1||chose==3)
    {
        system("cls");
        Bus_Display();
        gotoxy(0,2);
        if(chose==3)
        {
            cout<<"Seat Already Booked "<<endl;
            cout<<"Do you want to continue Booking ?(y/n)"<<endl;
            string ck;
            cin>>ck;
            if(ck=="n")
                return;
        }
        cout<<"Enter Seat Number : ";
        string s;
        cin>>s;
        if(s=="-1")
            break;
        int d=s[0]-65,e=s[1]-49;
        int sit=d*4+e;
        if(seat[sit].booking==0)
        {
            cout<<"Confirm Booking \n  1. Yes   2. No \n";
            cin>>chose;
            if(chose==1)
            {
                seat[sit].booking=1;
                seat[sit].Name=name;
                seat[sit].Phone_Number=phonenumber;
                seat[sit].Destination=route;
                break;
            }
            else
                return;
        }
        else if(seat[sit].booking==1)
        {
            chose=3;

        }
    }
    ofstream myfile;
    myfile.open(location);
    for(int i=0; i<40; i++)
    {
        myfile<<seat[i].booking<<"\n";
        myfile<<seat[i].Name<<"\n";
        myfile<<seat[i].Phone_Number<<"\n";
        myfile<<seat[i].Destination<<"\n";
    }
    myfile.close();
}
void Check_Pass()
{
    system("cls");
    Bus_Display();
    cout<<"Enter Code \n";
    string code;
    cin>>code;
    if(code!="9655")
    {
        cout<<"Wrong Code\n";
        system("Pause");
        return;
    }
    ifstream myfile;
    myfile.open("Password.text");
    string line;
    getline(myfile,line);
    cout<<"Your Password : "<<line<<endl;
    myfile.close();
    system("Pause");
    return;
}
void Admin_Panel()
{
    while(Password()==false)
    {
        gotoxy(35,7);
        cout<<"----Welcome To Admin Panel----\n";
        gotoxy(37,9);
        cout<<"Wrong Password"<<endl;
        gotoxy(37,10);
        cout<<"Do You Want to Try Again ? (y/n)";
        gotoxy(37,11);
        string s;
        cin>>s;
        if(s=="n")
        {
            return;
        }
    }
    system("cls");
    //Bus_Display();
    gotoxy(35,3);
    cout<<"----Welcome To Admin Panel----\n";
    gotoxy(40,5);
    cout<<"1. Seat Query\n";
    gotoxy(40,6);
    cout<<"2. Change Password\n";
    gotoxy(40,7);
    cout<<"3. Add New Route\n";
    gotoxy(40,8);
    cout<<"4. Add New Bus\n";
    gotoxy(40,9);
    cout<<"5. Main Menu\n";
    gotoxy(40,10);
    cout<<"Enter : ";

    int  choice;
    cin>>choice;
    if(choice==1)
        Check_info();
    else if(choice==2)
        Change_Password();
    else if(choice==3)
        ROUTE(1);
    else if(choice==4)
        New_Bus();
    else if(choice==5)
        return;
    else
        Admin_Panel();

}
int main()
{
    while(1)
    {
        system("cls");
        gotoxy(40,8);
        cout<<"1. Seat Booking \n";
        gotoxy(40,9);
        cout<<"2. Admin Panel \n";
        gotoxy(40,10);
        cout<<"3. Exit \n";
        gotoxy(40,11);
        cout<<"Enter : ";
        string choise;
        cin>>choise;
        if(choise=="1")
        {
            Seat_Booking();
        }
        else if(choise=="2")
            Admin_Panel();
        else if(choise=="3")
        {
            system("cls");
            cout<<"Have A good Day !"<<endl;
            return 0;
        }
    }
    return 0;
}
