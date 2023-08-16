#include<bits/stdc++.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

using namespace std;

int main(){
	int res = open("check1.txt", O_RDWR|O_CREAT);
	cout<<res<<'\n';
	if(res==-1){
		cout<<"Error number: " << errno <<'\n';
		perror("Program");
	}
}
