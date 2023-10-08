#include<stdio.h>
#include<unistd.h>

struct Course{
	char* code;
	char* name;
};

void viewAll(){
	int fd = open("courses.txt", O_RDONLY);
    	if (fd == -1) {
        	perror("Error opening file");
        	return;
    	}

    	struct Course course;

    	while(read(fd, &course, sizeof(struct Course)) > 0) {
    		printf("Course Code: %s\tCourse Name: %s\n",course.code,course.name);
	}

    	close(fd);
    	return false;

}

