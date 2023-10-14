#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
// #include "auth.h"


void addCourse(int cfd, int fid){

        int fd = open("courses.txt", O_WRONLY|O_CREAT, 0744);


        struct Course cur;

        if(fd==-1){
                perror("Error while opening course file: ");
                return;
        }
        
        char bf[1024];
        strcpy(bf, "Before CS");
        write(cfd, bf, strlen(bf));

        struct flock lock1 = {F_WRLCK, SEEK_SET, 0, 0, getpid()};

        int fs = fcntl(fd, F_SETLKW, &lock1);
        if(fs==-1){
                perror("error while locking the courses file");
        }
        
        int fd1 = open("count.txt", O_RDWR, 0744);
        if(fd1==-1){
                perror("Error while opening count file: ");
                return;
        }


        struct flock lock2 = {F_WRLCK, SEEK_SET, 0, 0, getpid()};

        int fs1 = fcntl(fd, F_SETLKW, 0,0,getpid());
   
        if(fs==-1){
                perror("error while locking the count file");
        }

        struct Count count;

        int rb = read(fd1, &count, sizeof(struct Count));
        
        cur.code = count.courses;


        char rbuf[1024],wbuf[1024]="Enter name of the course: ";

        int wb = write(cfd, wbuf, strlen(wbuf));
        if(wb==-1){
                perror("Error while asking for name: ");
                return;
        }

        rb = read(cfd, rbuf, sizeof(rbuf));

        if(rb==-1){
                perror("Error while reading name: ");
                return;
        }

        strcpy(cur.name, rbuf);

        strcpy(wbuf, "Enter the total intake of the course: ");

        wb = write(cfd, wbuf, strlen(wbuf));
        if(wb==-1){
                perror("Error while asking for intake: ");
                return;
        }

        memset(rbuf, 0, sizeof(rbuf));

        rb = read(cfd, rbuf, sizeof(rbuf));

        if(rb==-1){
                perror("Error while reading intake: ");
                return;
        }
        
        int intake = atoi(rbuf);
        cur.intake = intake;
        cur.current = 0;
        cur.faculty_id = fid;

        // add the course
        
        int l = lseek(fd, 0, SEEK_END);

        if(l==-1){
                perror("Error while moving file pointer\n");
                return;
        }

        wb = write(fd, &cur, sizeof(struct Course));
        if(wb==-1){
                perror("Error while writing into file ");
                return;
        }

        count.courses++;

        int countoffset = lseek(fd1, 0, SEEK_SET);

        if(countoffset==-1){
                perror("error while seeking to start of count file");
                return;
        }

        wb = write(fd1, &count, sizeof(struct Count));

        if(wb == -1){
                perror("error while writing to count file");
                return;
        }


        lock1.l_type = F_UNLCK;
        fcntl(fd, F_SETLKW, &lock1);

        lock2.l_type = F_UNLCK;
        fcntl(fd, F_SETLKW, &lock2);



        fd = open("faculty.txt", O_RDWR, 0744);

        struct Faculty faculty;

        int offset = lseek(fd, fid*sizeof(struct Faculty), SEEK_SET);

        if(offset==-1){
                perror("error seeking to the required record");
                return;
        }

        struct flock lock3 = {F_WRLCK, SEEK_SET, fid, fid*sizeof(struct Faculty), getpid()};
        int st = fcntl(fd, F_SETLKW, &lock3);

        if(st==-1){
                perror("error attaining write lock on the record");
                return;
        }

        rb = read(fd, &faculty, sizeof(struct Faculty));

        if(rb==-1){
                perror("error while reading record from the file");
                return;
        }
        

        
        for(int i=0;i<4;i++){
                if(faculty.courses[i]==-1){
                        faculty.courses[i]=cur.code;
                        break;
                }
        }

        offset = lseek(fd, fid*sizeof(struct Faculty), SEEK_SET);

        wb = write(fd, &faculty, sizeof(struct Faculty));
        if(wb==-1){
                perror("error while writing back faculty record");
        }


        lock3.l_type = F_UNLCK;
        fcntl(fd, F_SETLKW, &lock3);

        strcpy(wbuf, "Course added successfully\n");

        wb = write(cfd, wbuf, strlen(wbuf));

        return;

}




void viewCourses(int cfd, int fid){
        char rbuf[1024],wbuf[1024];
        memset(rbuf, 0, sizeof(rbuf));
        memset(wbuf, 0, sizeof(wbuf));

        int fd = open("faculty.txt", O_RDONLY, 0744);
        if(fd==-1){
                perror("error opening faculty file: ");
                return;
        }
        struct Faculty faculty;
        
        // strcpy(wbuf,"hello\n");
        // write(cfd, wbuf, strlen(wbuf));

        while(read(fd, &faculty, sizeof(struct Faculty))>0){
                memset(rbuf, 0, sizeof(rbuf));
                memset(wbuf, 0, sizeof(wbuf));
                if(faculty.faculty_id==fid){
                        struct flock lock = {F_RDLCK, SEEK_SET, fid, fid*sizeof(struct Faculty), getpid()};
                        int st = fcntl(fd, F_SETLKW, &lock);
                        if(st==-1){
                                perror("error locking the file in read mode:");
                                return;
                        }
                        char tmpbuf[1024]="Courses offered:\n";
                        printf("%s\n",tmpbuf);
                        for(int i=0;i<4;i++){
                                char temp[5];
                                sprintf(temp, "%d", faculty.courses[i]);
                                strcat(tmpbuf, temp);
                                strcat(tmpbuf, "\t");
                        }
                        strcat(tmpbuf, "\n");
                        strcpy(wbuf, tmpbuf);

                        int wb = write(cfd, wbuf, strlen(tmpbuf));
                        if(wb==-1){
                                perror("error while writing to socket");
                                return;
                        }

                        lock.l_type = F_UNLCK;
                        fcntl(fd, F_SETLK, &lock);

                        printf("wbuf: %s\n",wbuf);
                        
                        return;
                }

        }

        memset(rbuf, 0, sizeof(rbuf));
        memset(wbuf, 0, sizeof(wbuf));

        strcpy(wbuf, "faculty with corresponding id does not exist");

        int wb = write(cfd, wbuf, strlen(wbuf));


}



// void removeCourse(int cfd, int fid){
//         char rbuf[1024],wbuf[1024];
//         memset(rbuf, 0, sizeof(rbuf));
//         memset(wbuf, 0, sizeof(wbuf));

//         int fd = open("courses.txt", O_RDWR, 0744);

//         if(fd == -1){
//                 perror("Error while opening courses file: ");
//                 return;
//         }

//         struct flock lock = {F_WRLCK, SEEK_SET, 0, 0, getpid()};

//         int fst = fcntl(fd, F_SETLKW, &lock);

//         if(fst==-1){
//                 perror("Error while attaining write lock on file");
//                 return;
//         }


//         strcpy(wbuf, "Enter the id of the course you want to remove: ");
//         int wb = write(cfd, wbuf, strlen(wbuf));

//         if(wb==-1){
//                 perror("Error while writing id message to socket");
//                 return;
//         }

//         int rb = read(cfd, )        


// }

void facultyMenu(int cfd){
	struct Faculty *f = facultyLogin(cfd);
	if(f == NULL){
		// send message to client about invalid login
		char buf[100] = "Invalid username or password\n";
		int wb = write(cfd, buf, strlen(buf));
		return;
	}
        char buf[100] = "Successfully logged in!\n";
        int wb = write(cfd, buf, strlen(buf));
	// display faculty menu
	
        while(1){

                char menu[4096] = "....................................Welcome to Faculty Menu....................................\n"
                                "1. View Offering Courses\n"
                                "2. Add New Course\n"
                                "3. Remove Course from Catalog\n"
                                "4. Update Course Details\n"
                                "5. Change Password\n"
                                "6. Logout and Exit\n\n"
                                "Enter your choice: ";

                wb = write(cfd, menu, strlen(menu));

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
                                printf("id: %d\n",f->faculty_id);
                                viewCourses(cfd, f->faculty_id);
                                break;
                        }
                        case 2:
                        {

                                addCourse(cfd, f->faculty_id);
                                // char code[50];
                                // printf("Enter the course code: ");
                                // scanf(" %[^\n]s",code);
                                // enroll(s->rollno, code);
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


