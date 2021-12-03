#include <iostream>
#include "graph.h"
#include "queue.h"
#include<fstream>
#include <string>
#include <vector> 
#include <stdlib.h>
#include <bits/stdc++.h> 
using namespace std;

int find(string word, vector<string>& v);
bool allVisited(bool array[],int num);
void fillGraph(char* filename, Graph<string>& myGraph,vector<string>& vertices);
void printSorted(vector<string>& v, int num);
int findMin(int distances[],bool marked[], int numVertices);
void declareZero(bool marked[],int numVertices);
void declareMax(int distances[],int numVertices);

int main(int argc, char* argv[])
{
	if(argc==1)
	{
		cerr<<"No Command Line Input Found. Try Again."<<endl;
		return 1;
	}	
  char* fileName=argv[1];  //will be checked in fill Graph method
  
 	Graph<string> myGraph(50);
	Queue<string> myQ(50);
  vector<string> vertices;
  
  fillGraph(fileName,myGraph,vertices);
  
  int numVertices=vertices.size();
  bool marked[numVertices];    //build bool array of marked vertices (start all as false)
  declareZero(marked,numVertices);
  
  int distances[numVertices];  //array for ints of distances used in reaching the vertex (start all as infinity)
  declareMax(distances,numVertices);
    
  string prevVisit[numVertices];
  printSorted(vertices,numVertices); //print opening and available vertices

  cout<<"Please input your starting vertex: ";
  string start;
  cin>>start;
  
  while(find(start,vertices)==-1)  //check start is valid if not reask
  {
    cerr<<"Invalid Input. \n Please enter a valid starting vertex: ";
    cin>>start;
  }
  
  distances[find(start,vertices)]=0;
  prevVisit[find(start,vertices)]="N/A";
  
  cout<<"------------------------------------------------------------------"<<endl;
  cout<<"\t Vertex \t\t Distance \t\t Previous"<<endl;
  //Dijkstra's algorithm
  while(!allVisited(marked,numVertices))
  {
    marked[find(start,vertices)]=1;
    cout<<"\t "<<start<<" \t\t "<<distances[find(start,vertices)]<<" \t\t\t "<<prevVisit[find(start,vertices)]<<endl;
    myGraph.GetToVertices(start,myQ); //enqueue neighbors
    while(!myQ.isEmpty())
    {
      if(marked[find(myQ.getFront(),vertices)]==false)//if neighbor one not marked
      {
        if(distances[find(myQ.getFront(),vertices)]>myGraph.WeightIs(start, myQ.getFront()) + distances[find(start,vertices)] )
        {
          distances[find(myQ.getFront(),vertices)]=myGraph.WeightIs(start, myQ.getFront()) + distances[find(start,vertices)] ;
          prevVisit[find(myQ.getFront(),vertices)]=start;
        }
      }
      myQ.dequeue();
    }
    
    start=vertices[findMin(distances,marked,numVertices)];
  }  
  
	return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void declareMax(int distances[],int numVertices)
{
  for(int i=0; i<numVertices;i++)
  {
    distances[i]=INT_MAX;
  }
}
void declareZero(bool marked[],int numVertices)
{
  for(int i=0; i<numVertices;i++)
  {
     marked[i]=0;
  }
}
int findMin(int distances[],bool marked[], int numVertices)
{
  int min=INT_MAX;
    int minPos=0;
    for(int i=0;i<numVertices;i++)
    {
      if(distances[i]<min && marked[i]==false)
      {
        min=distances[i];
        minPos=i;
      }
    }
    return minPos;
}
int find(string word, vector<string>& v)
{
  int found=-1;
  vector<string> temp=v;
  for(int i=0;i<temp.size();i++)
  {
    if(v[i]==word)
    {
      found=i;
    }
  }
  return found;
}
bool allVisited(bool array[],int num)
{
  for(int i=0;i<num;i++)
  {
    if(array[i]==false)
    {
      return false;
    }
  }
  return true;
}
void fillGraph(char* filename, Graph<string>& myGraph,vector<string>& vertices)
{
  bool trueFile=false;
  fstream infile;
  while(trueFile==false)
  {
	  infile.open(filename);
    if (infile.fail()) 
    {
      cerr<<"File does not exist. Enter another file name."<<endl;
      cin>>filename;
    }
    else
    {
      trueFile=true;
    }
   }
  string line;
  bool first=true;
	while(getline(infile,line))
	{
     int pos=line.find(";");
     string origin=line.substr(0,pos);
     if(find(origin,vertices)==-1 || first==true)
     {
       myGraph.AddVertex(origin);  //send origin as vertex
       vertices.push_back(origin);
       first=false;
     }
     line=line.substr(pos+1);
     pos=line.find(";");
     string dest=line.substr(0,pos);
     if(find(dest,vertices)==-1)
     {
       myGraph.AddVertex(dest);  //send destination as vertex
       vertices.push_back(dest);
     }
     string tripLength=line.substr(pos+1);
     int tripLenNum=atoi(tripLength.c_str()); //convert string to int
     myGraph.AddEdge(origin,dest,tripLenNum);
	}
}
void printSorted(vector<string>& v, int num)
{
    cout<<"^^^^^^^^^^^^^^^^    DIJKSTRA'S ALGORITHM    ^^^^^^^^^^^^^^^^"<<endl;
    cout<<"A Weighted Graph Has Been Built For These 7 Cities :"<<endl;
    sort(v.begin(),v.end());
    for(int i=0; i<num;i++)
    {
      if(i%3==0 && i!=0)
      {
        cout<<endl;
      }
      cout<<v[i]<<"\t\t";
    }
    cout<<endl;
}
