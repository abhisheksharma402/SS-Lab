#include<stdio.h>
#include<unistd.h>
#include<string.h>


struct Student{
	char* name;
	char* rollno;
	struct Course courses[6];
	char* username;
	char* password;
	bool isActivated;
	bool isBlocked
}


bool login(char* username, char* password) {
    int fd = open("students.txt", O_RDONLY|O_CREAT);
    if (fd == -1) {
        perror("Error opening file");
        return false;
    }

    struct Student student;
    while (read(fd, &student, sizeof(struct Student)) > 0) {
        if (strcmp(student.username, username) == 0 && strcmp(student.password, password) == 0) {
            close(fd);
            return true;
        }
    }

    close(fd);
    return false;
}


void addStudent(){
	
	int fd = open("students.txt", O_WRONLY|O_CREAT, 0744);
	
	if (fd == -1) {
        	perror("Error opening file");
    	}


	struct Student s;
	printf("Enter the Name: ");
	scanf("%s",s.name);

	printf("Enter the Roll number: ");
        scanf("%s",s.rollno);

	printf("Enter the username: ");
        scanf("%s",s.username);

	printf("Enter the password: ");
        scanf("%s",s.password);
	
	int wb = write(fd, &s, sizeof(struct Student));
	if(wb<0){
		printf("Could not write into the file\n");
		return;
	}

}




void viewStudents(){

        int fd = open("students.txt", O_RDONLY|O_CREAT, 0744);

        if (fd == -1) {
                perror("Error opening file");
        }


        struct Student s;

        while(read(fd, &s, sizeof(struct Student)) > 0){
		printf("%s\t%s\n",s.name,s.rollno);
		//print courses taken up by the student as well
	}

}



void activateStudent(char* roll){
	int fd = open("students.txt", O_RDONLY, 0744);

        if (fd == -1) {
                perror("Error opening file");
        }


        struct Student s;

        while(read(fd, &s, sizeof(struct Student)) > 0){
		if(strcmp(roll, s.rollno)==0){
			s.isActivated = true;
			return;
		}	
	}

	printf("No entry with the given roll number found!\n");

}


void blockStudent(char* roll){
	int fd = open("students.txt", O_RDONLY, 0744);

        if (fd == -1) {
                perror("Error opening file");
        }


        struct Student s;

        while(read(fd, &s, sizeof(struct Student)) > 0){
                if(strcmp(roll, s.rollno)==0){
                        s.isBlocked = true;
                        return;
                }
        }

        printf("No entry with the given roll number found!\n");


}




void modifyStudentDetails(char* roll){
	int fd = open("students.txt", O_RDONLY, 0744);

        if (fd == -1) {
                perror("Error opening file");
        }


        struct Student s;

        while(read(fd, &s, sizeof(struct Student)) > 0){
                if(strcmp(roll, s.rollno)==0){
                   	
                        return;
                }
        }

        printf("No entry with the given roll number found!\n");

}




int main(){

	

}
