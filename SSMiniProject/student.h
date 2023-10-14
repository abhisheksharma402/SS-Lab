#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
// #include "auth.h"


void viewAllCourses(int cfd){
        int fd = open("courses.txt", O_RDONLY, 0744);

        if(fd==-1){
                perror("error while opening file");
                return;
        }

        struct flock lock = {F_RDLCK, SEEK_SET, 0, 0, getpid()};

        int lockst = fcntl(fd, F_SETLKW, &lock);

        if(lockst==-1){
                perror("error while locking the file");
                return;
        }

        char rbuf[1024],wbuf[10000];
        memset(rbuf, 0, sizeof(rbuf));
        memset(wbuf, 0, sizeof(wbuf));

        struct Course course;

        while(read(fd, &course, sizeof(struct Course))>0){
                char temp[1000];
                sprintf(temp, "Courses - \n\tCourse id : %d\n\tFaculty id : %d\n\tCourse Name : %s\n\tCourse Intake: %d\n\tCurrently enrolled students: %d\n\n\t*****\n\n", course.code,course.faculty_id, course.name, course.intake, course.current);
                strcat(wbuf, temp);
        }

        int writeBytes = write(cfd, wbuf, strlen(wbuf));
        if (writeBytes == -1)
        {
                perror("Error writing course record info to client!");
                return;
        }




}


void enrol(int cfd, int roll){

        char rbuf[1024],wbuf[1024];
        memset(rbuf, 0, sizeof(rbuf));
        memset(wbuf, 0, sizeof(wbuf));

        strcpy(wbuf, "Enter the id of the course you want to enrol in: ");
        int wb = write(cfd, wbuf, strlen(wbuf));

        if(wb==-1){
                perror("Error while writing course id message to socket");
                return;
        }

        int rb = read(cfd, rbuf, sizeof(rbuf));

        if(rb==-1){
                perror("error while reading course id from socket");
                return;
        }

        int id = atoi(rbuf);

        memset(rbuf, 0, sizeof(rbuf));
        memset(wbuf, 0, sizeof(wbuf));

        int fd = open("courses.txt", O_RDWR, 0744);
        if(fd==-1){
                perror("Error while opening courses file");
                return;
        }

        
        struct flock lock = {F_RDLCK, SEEK_SET, 0, 0, getpid()};

        int fs = fcntl(fd, F_SETLKW, &lock);

        if(fs==-1){
                perror("Error while attaining read lock on the couses file");
                return;
        }

        struct flock lock1 = {F_WRLCK, SEEK_CUR, 0, sizeof(struct Course), getpid()};
        struct Course course;

        bool flag=0;

        while(read(fd, &course, sizeof(struct Course))>0){
                if(course.code == id){
                    flag=1;
                    break;    
                }
        }

        if(flag==0){
                // course with the corresponding id not found
                return;
        }


        lock.l_type=F_UNLCK;

        fs = fcntl(fd, F_SETLKW, &lock);
        if(fs==-1)
        {
                perror("error while removing read lock on the course file");
                return;
        }


        int offset = lseek(fd, -sizeof(struct Course), SEEK_CUR);

        if(offset==-1){
                perror("Error while seeking to the required location in course file");
                return;
        }

        fs = fcntl(fd, F_SETLKW, &lock1);

        if(fs==-1)
        {
                perror("error while attaining a write lock on the course record");
                return;
        }

        
        if(course.intake-course.current<=0){
                strcpy(wbuf, "Course is full! You can't enrol\n");
                wb = write(cfd, wbuf, strlen(wbuf));
                if(wb==-1){
                        perror("Error while writing 'course full' message to socket");
                        return;
                }
                return;
        }


        course.current++;


        wb = write(fd, &course, sizeof(struct Course));

        

        if(wb==-1){
                perror("Error while writing course record to file");
                return;
        }


        lock1.l_type = F_UNLCK;
        fs = fcntl(fd, F_SETLKW, &lock1);
        if(fs==-1)
        {
                perror("error while removing write lock on the course record");
                return;
        }

        close(fd);

        fd = open("students.txt", O_RDWR, 0744);

        if(fd==-1){
                perror("Error while opening students file");
                return;
        }

        struct flock lock2 = {F_RDLCK, SEEK_SET, 0, 0, getpid()};

        fs = fcntl(fd, F_SETLKW, &lock2);


        struct Student student;

        while(read(fd, &student, sizeof(struct Student))>0){
                if(student.rollno == roll){
                    break;
                }
        }

        lock2.l_type=F_UNLCK;

        fs = fcntl(fd, F_SETLKW, &lock2);

        if(fs==-1){
                perror("Error while removing read lock on student file");
                return;
        }


        offset = lseek(fd, -sizeof(struct Student), SEEK_CUR);

        if(offset==-1){
                perror("Error while seeking to the required location in student file");
                return;
        }

        struct flock lock3 = {F_WRLCK, SEEK_SET, 0, 0, getpid()};

        fs = fcntl(fd, F_SETLKW, &lock3);

        if(fs==-1){
                //
                return;
        }


        if(offset==-1){
                perror("Error while seeking to the required location in student file");
                return;
        }

        for(int i=0;i<6;i++){
                if(student.courses[i]==-1){
                        student.courses[i] = id;
                        break;
                }
        }

        wb = write(fd, &student, sizeof(struct Student));

        if(wb==-1){
                perror("Error while writing student record to file");
                return;
        }

        lock3.l_type = F_UNLCK;

        fs = fcntl(fd, F_SETLKW, &lock3);
        
        if(fs==-1){
                perror("Error while removing write lock on student record");
                return;
        }


}



void studentMenu(int cfd){
	struct Student *s = studentLogin(cfd);
	if(s == NULL){
		// send message to client about invalid login
		char buf[100] = "Invalid username or password";
		int wb = write(cfd, buf, strlen(buf));
		return;
	}

        char buf[100] = "Successfully logged in!\n";
        int wb = write(cfd, buf, strlen(buf));
	// display student menu
	
        while(1){

                char menu[4096] = "....................................Welcome to Student Menu....................................\n"
                                "1. View All Courses\n"
                                "2. Enroll (pick) New Course\n"
                                "3. Drop Course\n"
                                "4. View Enrolled Course Details\n"
                                "5. Change Password\n"
                                "6. Logout and Exit\n\n"
                                "Enter your choice: ";

                int wb = write(cfd, menu, strlen(menu));

                if(wb==-1){
                        perror("Error while displaying menu: ");
                        return;
                }
                
                char chbf[1024];
                int rb = read(cfd, chbf, sizeof(chbf));
                if(rb==-1){
                        perror("Error while reading choice: ");
                        return;
                }


                int choice = atoi(chbf);

                switch(choice){
                        case 1:
                        {
                                viewAllCourses(cfd);
                                break;
                        }
                        case 2:
                        {
                                enrol(cfd, s->rollno);
                                break;
                        }
                        case 3:
                        {
                                break;
                        }
                        case 4:
                        {
                                break;
                        }
                        case 5:
                        {
                                break;
                        }
                        case 6:
                        {
                                return;
                        }
                        default:
                        {
                                // printf("Enter a valid choice!\n");
                                break;
                        }
                }

        }

}


