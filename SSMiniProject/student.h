#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include <sys/sem.h>
// #include "structs.h"
// #include "auth.h"

// struct Student *s;


union semun{
        int val;
        struct semid_ds *buf;
        unsigned short int *array;
};


struct Student s;

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

        lock.l_type = F_UNLCK;
        lockst = fcntl(fd, F_SETLKW, &lock);


        close(fd);

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
                close(fd);
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

        // close(fd)

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

        struct flock lock3 = {F_WRLCK, SEEK_CUR, 0, sizeof(struct Student), getpid()};

        fs = fcntl(fd, F_SETLKW, &lock3);

        if(fs==-1){
                //
                return;
        }


        // if(offset==-1){
        //         perror("Error while seeking to the required location in student file");
        //         return;
        // }

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

        close(fd);


}


struct Course getCourseDetails(int cid){
        int fd = open("courses.txt", O_RDONLY);
        struct Course course;
        course.code=-1;
        if(fd==-1){
                perror("Error while opening file");
                return course;
        }

        struct flock lock = {F_RDLCK, SEEK_SET, 0, 0, getpid()};

        int ls = fcntl(fd, F_SETLKW, &lock);
        if(ls==-1){
                perror("Error while attaining read lock on courses file");
                return course;
        }

        

        while(read(fd, &course, sizeof(struct Course))>0){
                
                if(course.code == cid){
                        close(fd);
                        return course;
                }
        }

        lock.l_type = F_UNLCK;
        ls = fcntl(fd, F_SETLKW, &lock);
        if(ls==-1){
                perror("Error while removing read lock on courses file");
        }

        close(fd);

        course.code=-1;
        return course;


}





void viewEnroledCourses(int cfd){

        char rbuf[1024],wbuf[4096];
        memset(rbuf, 0, sizeof(rbuf));
        memset(wbuf, 0, sizeof(wbuf));

        printf("roll: %d\n",s.rollno);

        // for(int i=0;i<6;i++){
        //         printf("%d\n",s.courses[i]);
        // }
        // printf("name: %s\n",s.name);
        // printf("roll: %d\n",s.rollno);


        strcpy(wbuf, "\n****************Enroled Course Details****************\n");

        int fd = open("students.txt", O_RDONLY);

        if(fd==-1){
                perror("Error while opening file");
                close(fd);
                return;
        }

        struct flock lock = {F_RDLCK, SEEK_SET, 0, 0, getpid()};

        int fs = fcntl(fd, F_SETLKW, &lock);
        if(fs==-1){
                perror("Error while attaining read lock on the students file");
                close(fd);
                return;
        }

        struct Student student;

        while(read(fd, &student, sizeof(struct Student))>0){
                if(student.rollno==s.rollno){
                        break;
                }
        }

        lock.l_type = F_UNLCK;
        fs = fcntl(fd, F_SETLKW, &lock);

        int offset = lseek(fd, -sizeof(struct Student), SEEK_CUR);
        
        if(offset==-1){
                perror("Error while seeking to the previous record");
                close(fd);
                return;
        }

        struct flock lock1 = {F_RDLCK, SEEK_CUR, 0, sizeof(struct Student), getpid()};

        fs = fcntl(fd, F_SETLKW, &lock1);
        if(fs==-1){
                perror("Error while attaining read lock on the students record");
                close(fd);
                return;
        }

        bool flag=0;

        for(int i=0;i<6;i++){
                if(student.courses[i]==-1)continue;
                flag=1;
                struct Course c;
                c = getCourseDetails(student.courses[i]);

                char temp[1024];

                sprintf(temp, "\nCourse Id: %d\nCourse Name: %s\nFaculty Id: %d\nStudents Enrolled: %d\n\n",c.code, c.name, c.faculty_id, c.current);

                strcat(wbuf, temp);

        }

        if(flag==0){
                memset(wbuf, 0, sizeof(wbuf));
                strcpy(wbuf, "No courses enroled!");
                int wb = write(cfd, wbuf, strlen(wbuf));
                if(wb==-1){
                        perror("Error while writing to socket");
                        close(fd);
                        return;
                }
                return;
        }

        int wb = write(cfd, wbuf, strlen(wbuf));
        if(wb==-1){
                perror("Error while writing to socket");
                close(fd);
                return;
        }
        close(fd);

}



void dropCourse(int cfd){

        char rbuf[1024],wbuf[4096];
        
        memset(rbuf, 0, sizeof(rbuf));
        memset(wbuf, 0, sizeof(wbuf));

        strcpy(wbuf, "Enter the id of the course you want to drop: ");
        int wb = write(cfd, wbuf, strlen(wbuf));

        if(wb==-1){
                perror("Error while writing to socket");
                return;
        }

        int rb = read(cfd, rbuf, sizeof(rbuf));
        if(rb==-1){
                perror("Error while reading to socket");
                return;
        }
        // rbuf[rb]='\0';
        int id = atoi(rbuf);
        printf("id in drop course: %d\n",id);

        int fd = open("students.txt", O_RDWR);

        if(fd==-1){
                perror("Error while opening students file");
                return;
        }

        struct Student student;
        while(read(fd, &student, sizeof(struct Student))>0){
                if(s.rollno==student.rollno){
                        break;
                }
        }

        bool flag=0;

        for(int i=0;i<6;i++){
                printf("**%d\n",student.courses[i]);
                if(student.courses[i]==id){
                        flag=1;
                        student.courses[i]=-1;
                        break;
                }
        }

        memset(rbuf, 0, sizeof(rbuf));
        memset(wbuf, 0, sizeof(wbuf));

        if(!flag){
                strcpy(wbuf, "\nCourse Id not found!\n");
                wb = write(cfd, wbuf, strlen(wbuf));
                if(wb==-1){
                        perror("Error while writing to socket");
                        return;  
                }
                return;
        }

        int offset = lseek(fd, -sizeof(struct Student), SEEK_CUR);
        if(offset==-1){
                perror("Error while seeking to the required record");
                return;
        }

        struct flock lock = {F_WRLCK, SEEK_CUR, 0, sizeof(struct Student), getpid()};

        int fs = fcntl(fd, F_SETLKW, &lock);
        if(fs==-1){
                perror("Error while attaining lock on the student record");
                return;
        }

        wb = write(fd, &student, sizeof(struct Student));

        if(wb==-1){
                perror("Error while writing into the students file");
                return;
        }

        lock.l_type=F_UNLCK;

        fs = fcntl(fd, F_SETLKW, &lock);
        if(fs==-1){
                perror("Error while removing lock on the student record");
                return;
        }
        close(fd);

        int fd1 = open("courses.txt", O_RDWR);
        printf("courses fd: %d\n",fd1);
        if(fd1==-1){
                return;
        }

        struct Course course;

        while(read(fd1, &course, sizeof(struct Course))>0){
                if(course.code==id){
                        break;
                }
        }

        offset = lseek(fd1, -sizeof(struct Course), SEEK_CUR);
        if(offset==-1){
                perror("error while seeking to previous record");
                return;
        }

        struct flock lock1 = {F_WRLCK, SEEK_CUR, 0, sizeof(struct Course), getpid()};

        fs = fcntl(fd1, F_SETLKW, &lock1);
        if(fs==-1){
                perror("error while attaining write lock on courses file");
                return;
        }

        course.current-=1;



        wb = write(fd1, &course, sizeof(struct Course));
        if(wb==-1){
                return;
        }

        lock1.l_type=F_UNLCK;
        fs = fcntl(fd1, F_SETLKW, &lock1);
        if(fs==-1){
                return;
        }
        close(fd1);

        strcpy(wbuf, "Course Dropped Successfully");
        wb = write(cfd, wbuf, strlen(wbuf));
        if(wb==-1){
                return;
        }

        return;

}



bool changePassword(int cfd){

        key_t key = ftok(".",'f');
        printf("%d\n",key);
        union semun arg;
        int semid = semget(key, 1, IPC_CREAT|0744);
        arg.val = 1;
        semctl(semid,0,SETVAL, arg);

        struct sembuf buf;
        buf.sem_num=0;
        buf.sem_flg=0;

        char rbuf[1024],wbuf[4096];
        
        memset(rbuf, 0, sizeof(rbuf));
        memset(wbuf, 0, sizeof(wbuf));

        strcpy(wbuf, "Enter new password: ");
        int wb = write(cfd, wbuf, strlen(wbuf));
        if(wb==-1){
                perror("error while writing to client");
                return false;
        }

        int rb = read(cfd, rbuf, sizeof(rbuf));
        if(rb==-1){
                perror("error while reading from client");
                return false;
        }

        rbuf[rb]='\0';

        int fd = open("students.txt", O_RDWR);
        if(fd==-1){
                perror("Error while opening students file");
                close(fd);
                return false;
        }

        struct Student student;

        int offset = lseek(fd, s.rollno*sizeof(struct Student), SEEK_SET);
        if(offset==-1){
                perror("error while seeking to the required record");
                close(fd);
                return false;
        }

        
        // getchap
        // r();

        buf.sem_op=-1;
        semop(semid, &buf, 1);

        rb = read(fd, &student, sizeof(struct Student));

        if(rb==-1){
                perror("error while reading the student record");
                close(fd);
                return false;
        }

        memset(student.password, 0, 50);
        strcpy(student.password, rbuf);

        offset = lseek(fd, s.rollno*sizeof(struct Student), SEEK_SET);
        if(offset==-1){
                perror("error while seeking to start of record");
                close(fd);
                return false;
        }

        wb = write(fd, &student, sizeof(struct Student));

        if(wb==-1){
                perror("Error while writing the modified record to file");
                close(fd);
                return false;
        }



        buf.sem_op = 1;
        semop(semid, &buf, 1);


        memset(wbuf, 0, sizeof(wbuf));
        strcpy(wbuf, "Password changed successfully!\n");
        wb = write(cfd, wbuf, strlen(wbuf));
        if(wb==-1){
                perror("Error while writing to client");
                close(fd);
                return false;
        }

        close(fd);

        return true;

}



void studentMenu(int cfd){
        bool login = studentLogin(cfd, &s);
	if(!login){
		// send message to client about invalid login
		char buf[100] = "Invalid username or password\n";
		int wb = write(cfd, buf, strlen(buf));
		return;
	}

        if(s.isBlocked){
                char bf[200]="You do not have the permission to access the system. Reach out the admin if you think that shouldn't be the case!\n";
                int wb = write(cfd, bf, strlen(bf));
                if(wb==-1){
                        perror("error while writing to client");;
                }
                return;
        }

        char buf[100] = "Successfully logged in!\n";
        int wb = write(cfd, buf, strlen(buf));
	// display student menu
	
        for(int i=0;i<6;i++){
                printf("%d\n",s.courses[i]);
        }
        printf("%s\n",s.name);
        printf("%d\n",s.rollno);


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
                                enrol(cfd, s.rollno);
                                break;
                        }
                        case 3:
                        {
                                dropCourse(cfd);

                                break;
                        }
                        case 4:
                        {
                                // printf("id: %d\n",s->rollno);
                                // for(int i=0;i<6;i++){
                                //         printf("%d\n",s->courses[i]);
                                // }
                                viewEnroledCourses(cfd);
                                break;
                        }
                        case 5:
                        {
                                bool changed = changePassword(cfd);
                                if(!changed){
                                        char buf[100]="Unable to change password!";
                                        wb = write(cfd, buf, strlen(buf));
                                }

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


