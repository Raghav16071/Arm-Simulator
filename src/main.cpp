#include<bits/stdc++.h>
#include <stdlib.h>
#include <stdio.h>

//#include "myARMSim.h"

using namespace std;

void fetch(string);
void execute(string);
void writeback();
void memory();

int r[16], qq, ss ,temp, value, pp, comp, loop=0, out_arr[100], o=0, add_arr[20], ar=0, sum=0;
ofstream temp_loop, ansfib, anssum;
int pc=4100, pcm=0, beq, file1;

static int N,C,V,Z;
//memory
static unsigned char MEM[4000];

int read_word(char *mem, unsigned int address);
void write_word(char *mem, unsigned int address, unsigned int data);

char one[20]="Fibonnaci.mem", two[20]="arr_add.mem";

void loop_f(){
    while(comp!=beq){
        string line;
        ifstream myfile;
        if(file1==1)
            myfile.open("temp_loop.mem");
        else
            myfile.open("temp_add.mem");
        if(myfile.is_open())
        {
            while(getline(myfile,line))
            {
                fetch(line);
                pc+=4;
                r[15]=pc;
                cout<<"Currently pc is "<<r[15]<<endl<<endl;
            }
        }
    }
    pc=pc-pcm;
}

void writeback(){
    if(file1==1){
        //fib
        ansfib.open("ansfib.mem");
        for(int k=0;k<o;k++)
            ansfib<<out_arr[k]<<" ";
    }
    else{
    //sum
    anssum.open("anssum.mem");
    for(int k=1;k<=r[3];k++)
        anssum<<k<<" ";
    anssum<<endl;
    anssum<<(r[3]*(r[3]-1))/2;
    }
}

void write_data_memory() {
  FILE *fp;
  unsigned int i;
  fp = fopen("data_out.mem", "w");
  if(fp == NULL) {
    printf("Error opening dataout.mem file for writing\n");
    return;
  }

  for(i=0; i < 4000; i = i+4){
    //fprintf(fp, "%x %x\n", i, read_word(MEM, i));
  }
  fclose(fp);
}

void execute(string st)
{
    /* moving constant*/
    if(st[7]=='3' && st[8]=='A')
    {

        qq=st[10]-'0';

        ss=(st[11]-'0');
        if(ss < 10)
            ss=ss*pow(16,2);
        else
        {
            ss=ss-7;
            ss=ss*pow(16,2);
        }
        temp = (st[12]-'0');
        if(temp < 10)
            ss+=(st[12]-'0')*pow(16,1);
        else{
            temp=temp-7;
            ss += temp*pow(16,1);
        }
        temp = (st[13]-'0');
        if(temp < 10)
            ss+=st[13]-'0';
        else{
            temp-=7;
            ss+=temp;
        }
        cout<<"Moving "<<ss<<" to register "<<r[qq]<<endl;
        r[qq]=ss;
    }
    /* Moving register */
    else if(st[7]=='1' && st[8]=='A')
    {
        qq=st[10]-'0';

        ss=(st[11]-'0')*10;
        ss+=st[13]-'0';
        cout<<"Moving register "<<r[ss]<<" to register "<<r[qq]<<endl;
        r[qq]=r[ss];
    }
    /* Constant Addition */
    else if(st[7]=='2' && st[8]=='8')
    {
        qq=st[9]-'0';
        value=r[qq];
        pp=st[10]-'0';

        ss=(st[11]-'0');
        if(ss < 10)
            ss=ss*pow(16,2);
        else
        {
            ss=ss-7;
            ss=ss*pow(16,2);
        }
        temp = (st[12]-'0');
        if(temp < 10)
            ss+=(st[12]-'0')*pow(16,1);
        else{
            temp=temp-7;
            ss += temp*pow(16,1);
        }
        temp = (st[13]-'0');
        if(temp < 10)
            ss+=st[13]-'0';
        else{
            temp-=7;
            ss+=temp;
        }
        cout<<"Adding constant value "<<ss<<" and "<<value<<" and moving the sum to register "<<r[pp]<<endl;
        r[pp]=ss+value;
    }
    /* Register Addition */
    else if(st[7]=='0' && st[8]=='8')
    {
        qq=st[9]-'0';
        value=r[qq];
        pp=st[10]-'0';

        ss=st[13]-'0';
        cout<<"Adding register value "<<r[ss]<<" and "<<value<<" and moving the sum to register "<<r[pp]<<endl;
        r[pp]=value+r[ss];
    }
    /* Constant Subtraction */
    else if(st[7]=='2' && st[8]=='4')
    {
        qq=st[9]-'0';
        value=r[qq];
        pp=st[10]-'0';

        ss=(st[11]-'0');
        if(ss < 10)
            ss=ss*pow(16,2);
        else
        {
            ss=ss-7;
            ss=ss*pow(16,2);
        }
        temp = (st[12]-'0');
        if(temp < 10)
            ss+=(st[12]-'0')*pow(16,1);
        else{
            temp=temp-7;
            ss += temp*pow(16,1);
        }
        temp = (st[13]-'0');
        if(temp < 10)
            ss+=st[13]-'0';
        else{
            temp-=7;
            ss+=temp;
        }
        cout<<"Subtracting constant value "<<ss<<" from "<<value<<" and moving the ans to register "<<r[pp]<<endl;
        r[pp]=value-ss;
    }
    /* Register Subtraction */
    else if(st[7]=='0' && st[8]=='4')
    {
        qq=st[9]-'0';
        value=r[qq];
        pp=st[10]-'0';

        ss=st[13]-'0';
        cout<<"Subtracting register value "<<r[ss]<<" from "<<value<<" and moving the ans to "<<r[pp]<<endl;
        r[pp]=value-r[ss];
    }
    else if(st[7]=='F' && st[12]=='6' && st[13]=='B'){
        out_arr[o]=r[1];
        o++;
    }
    /* Constant Comparison */
    else if(st[7]=='3' && st[8]=='5'){
        if(r[st[9]-'0'] > st[13]-'0')
            comp = 1;
        else if ((r[st[9]-'0'] < st[13]-'0'))
            comp = -1;
        else
            comp = 0;
        cout<<"Comparing "<<r[st[9]-'0']<<" and "<<st[13]-'0'<<endl;
    }
    /* Register Comparison */
    else if(st[7]=='1' && st[8]=='5'){
        if(r[st[9]-'0'] > r[st[13]-'0'])
            comp = 1;
        else if ((r[st[9]-'0'] < r[st[13]-'0']))
            comp = -1;
        else
            comp = 0;
        cout<<"Comparing "<<r[st[9]-'0']<<" and "<<r[st[13]-'0']<<endl;
    }
     else if(st=="0x0 0xEAFFFFFE"){
        loop=0;
        pc=pc-pcm;
        loop_f();
        cout<<"Calling loop (Branching back to loop)"<<endl;
    }
    if(loop==1){
        pcm+=4;
        temp_loop<<st<<endl;
    }
    else if(st=="0x0 0xBA000000"){
        cout<<"Checking number equal, greater or lesser (Here its blt)"<<endl;
        beq=-1;
    }
    else if(st=="0x0 0xEF00006B"){
        cout<<"Printing register value "<<r[1]<<endl;
    }
    else if(st=="0x0 0xCA000000"){
        cout<<"Checking number equal, greater or lesser (Here its bgt)"<<endl;
        beq=1;
    }
    else if(st=="0x0 0xE7801002"){
        add_arr[r[2]/4] = r[1];
        cout<<"Storing register value "<<r[1]<<" int the created array."<<endl;
    }
    else if(st=="0x0 0xE7903002"){
        r[3] = add_arr[r[2]/4];
        cout<<"Loading value in register 3"<<endl;

    }
    else if(st=="0x0 0xEAFFFFFF"){
        if(file1==1)
            temp_loop.open("temp_loop.mem");
        if(file1==2)
            temp_loop.open("temp_add.mem");
        loop=1;
        cout<<"Loop is Initiated"<<endl;
    }
}

void decode(string st){
   if(st[7]=='3' && st[8]=='A')
    {
        qq=st[10]-'0';

        ss=(st[11]-'0');
        if(ss < 10)
            ss=ss*pow(16,2);
        else
        {
            ss=ss-7;
            ss=ss*pow(16,2);
        }
        temp = (st[12]-'0');
        if(temp < 10)
            ss+=(st[12]-'0')*pow(16,1);
        else{
            temp=temp-7;
            ss += temp*pow(16,1);
        }
        temp = (st[13]-'0');
        if(temp < 10)
            ss+=st[13]-'0';
        else{
            temp-=7;
            ss+=temp;
        }
        r[qq]=ss;
    }
    /* Moving register */
    else if(st[7]=='1' && st[8]=='A')
    {
        qq=st[10]-'0';

        ss=(st[11]-'0')*10;
        ss+=st[13]-'0';

        r[qq]=r[ss];
    }
    /* Constant Addition */
    else if(st[7]=='2' && st[8]=='8')
    {
        qq=st[9]-'0';
        value=r[qq];
        pp=st[10]-'0';

        ss=(st[11]-'0');
        if(ss < 10)
            ss=ss*pow(16,2);
        else
        {
            ss=ss-7;
            ss=ss*pow(16,2);
        }
        temp = (st[12]-'0');
        if(temp < 10)
            ss+=(st[12]-'0')*pow(16,1);
        else{
            temp=temp-7;
            ss += temp*pow(16,1);
        }
        temp = (st[13]-'0');
        if(temp < 10)
            ss+=st[13]-'0';
        else{
            temp-=7;
            ss+=temp;
        }

        r[pp]=ss+value;
    }
    /* Register Addition */
    else if(st[7]=='0' && st[8]=='8')
    {
        qq=st[9]-'0';
        value=r[qq];
        pp=st[10]-'0';

        ss=st[13]-'0';

        r[pp]=value+r[ss];
    }
}

void load_program_memory(char *file_name) {
  FILE *fp;
  unsigned int address, instruction;
  fp = fopen(file_name, "r");
  if(fp == NULL) {
    printf("Error opening input mem file\n");
    exit(1);
  }
  while(fscanf(fp, "%x %x", &address, &instruction) != EOF) {
//    write_word(MEM, address, instruction);
  }
  fclose(fp);
}


void fetch(string str)
{
    cout<<"Instruction Read: "<<str<<"\n";
    execute(str);
}

int main()
{
    char stream_array[4000];
    ifstream myfile;
    string line;
    cout<<"Enter 1. for Fibonacci, 2. For Array Addition: ";
    cin>>file1;
    if(file1==1)
        myfile.open(one);
    else
        myfile.open(two);
    if(myfile.is_open())
    {
        while(getline(myfile,line))
        {
            r[15]=pc;
            cout<<"Currently pc is "<<r[15]<<endl<<endl;
            fetch(line);
            pc+=4;
        }
        myfile.close();
    }
    cout<<endl;
    writeback();
    if(file1==2)
        r[4]+=1;

    for(int k=0;k<16;k++)
        cout<<"r"<<k<<": "<<r[k]<<endl;

    cout<<endl;
    if(file1==1){
        for(int k=0;k<o;k++)
            cout<<out_arr[k]<<" ";
        cout<<endl;
    }
    return 0;
}


int read_word(char *mem, unsigned int address) {
  int *data;
  data =  (int*) (mem + address);
  return *data;
}

void write_word(char *mem, unsigned int address, unsigned int data) {
  int *data_p;
  data_p = (int*) (mem + address);
  *data_p = data;
}
