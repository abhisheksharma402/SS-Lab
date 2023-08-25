#include <stdio.h>
#include <sys/stat.h>

using namespace std;

int main(){
	struct stat s;
	stat("first.txt", &s);
	printf("Inode Number: %ld\n",s.st_ino);
	printf("Number of Hard Links: %ld\n", s.st_nlink);
	printf("User ID of owner: %d\n",s.st_uid);
	printf("Group ID of owner: %d\n", s.st_gid);
	printf("Size: %ld\n",s.st_size);
	printf("Block: %ld\n", s.st_blksize);
	printf("Number of blocks: %ld\n",s.st_blocks);
	printf("Access time: %ld\n",s.st_atime);
	printf("Modified time: %ld\n",s.st_mtime);
	printf("Change time: %ld\n",s.st_ctime);

}
