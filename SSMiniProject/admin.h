#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include <errno.h>
#include<stdlib.h>
// #include "auth.h"

// struct Admin;

void addStudent(int cfd){

    int fd = open("students.txt", O_RDONLY, 0744);
    struct Student cur, prev;

    if(fd==-1 && errno==ENOENT){
        cur.rollno = 0;
    }else if(fd==-1){
        perror("Error while opening file");
        return;
    }
    else{
    
        int off = lseek(fd, -sizeof(struct Student), SEEK_END);

        if(off==-1){
            perror("Error seeking to the last record ");
            return;
        }

        struct flock lock = {F_RDLCK, SEEK_SET, off, sizeof(struct Student), getpid()};

        int lockingStatus = fcntl(fd, F_SETLKW, &lock);
        if (lockingStatus == -1)
        {
            perror("Error obtaining read lock on student record!");
            return;
        }

        int rb = read(fd, &prev, sizeof(struct Student));
        if (rb == -1)
        {
            perror("Error while reading student record from file!");
            return;
        }
        printf("prev roll: %d",prev.rollno);
        lock.l_type = F_UNLCK;
        fcntl(fd, F_SETLK, &lock);
        close(fd);

        cur.rollno = prev.rollno+1;
    }

    fd = open("students.txt", O_WRONLY|O_CREAT, 0744);

    if(fd==-1){
        perror("Error while opening file");
        return;
    }

    char rbuf[1024],wbuf[1024]="Enter name of the student: ";

    int wb = write(cfd, wbuf, strlen(wbuf));
	if(wb==-1){
		perror("Error while asking for name: ");
		return;
	}

	int rb = read(cfd, rbuf, sizeof(rbuf));

	if(rb==-1){
		perror("Error while reading name: ");
		return;
	}
    strcpy(cur.name, rbuf);

    strcpy(wbuf, "Enter the username of the student: ");

    wb = write(cfd, wbuf, strlen(wbuf));
	if(wb==-1){
		perror("Error while asking for username: ");
		return;
	}

    memset(rbuf, 0, sizeof(rbuf));

    rb = read(cfd, rbuf, sizeof(rbuf));

	if(rb==-1){
		perror("Error while reading username: ");
		return;
	}
    
    strcpy(cur.username, rbuf);

    strcpy(wbuf, "Enter the password of the student: ");

    wb = write(cfd, wbuf, strlen(wbuf));
	if(wb==-1){
		perror("Error while asking for password: ");
		return;
	}

    memset(rbuf, 0, sizeof(rbuf));

    rb = read(cfd, rbuf, sizeof(rbuf));

	if(rb==-1){
		perror("Error while reading password: ");
		return;
	}
    
    strcpy(cur.password, rbuf);

    cur.isActivated=false;
    cur.isBlocked=false;

    memset(cur.courses, -1, 6*sizeof(int));

    // add the student
    
    int l = lseek(fd, 0, SEEK_END);

    if(l==-1){
        perror("Error while moving file pointer\n");
        return;
    }

    wb = write(fd, &cur, sizeof(struct Student));
    if(wb==-1){
        perror("Error while writing into file ");
        return;
    }

    strcpy(wbuf, "Student added successfully\n");

    wb = write(cfd, wbuf, strlen(wbuf));

    return;

    // memset(rbuf, 0, sizeof(rbuf));

    // rb = read(cfd, rbuf, sizeof(rbuf));

}



// void viewStudentDetails(int cfd){

//     int fd = open("students.txt", O_RDONLY|O_CREAT, 0744);
//     char rbuf[1000], wbuf[1000];
//     memset(rbuf, 0, sizeof(rbuf));
//     memset(wbuf, 0, sizeof(wbuf));
//     if(fd==-1){
//         perror("Error while opening file ");
//         int rb = read(cfd, rbuf, sizeof(rbuf));
//         return;
//     }

//     struct Student s;

    
//     while(read(fd, &s, sizeof(struct Student))>0){
//         char temp[1024]="";
//         char r[10];
//         sprintf(r, "%d", s.rollno);
//         strcat(temp,s.name);
//         strcat(temp,"\t");
//         strcat(temp,r);
//         strcat(temp,"\t");
//         strcat(temp,s.username);
//         strcat(temp, "\n");
//         strcat(wbuf,temp);
//     }

//     int wb = write(cfd, wbuf, sizeof(wbuf));
//     printf("wbuf: %s\n",wbuf);
//     printf("written: %d\n",wb);
//     if(wb==-1){
//         perror("Error while writing to file\n");
//         return;
//     }
    
//     // strcpy(wbuf, "Enter a character to continue: ");
//     // wb = write(cfd, wbuf, sizeof(wbuf));

//     // int rb = read(cfd, rbuf, sizeof(rbuf));

//     return;

// }



bool viewStudentDetails(int cfd, int roll){

    ssize_t readBytes, writeBytes;             // Number of bytes read from / written to the socket
    char readBuffer[1000], writeBuffer[10000]; // A buffer for reading from / writing to the socket
    char tempBuffer[1000];

    struct Student student;
    // int fd;
    struct flock lock = {F_RDLCK, SEEK_SET, 0, sizeof(struct Student), getpid()};

    if (roll == -1)
    {
        writeBytes = write(cfd, "Enter the roll number of the student you are searching for: ", strlen("Enter the roll number of the student you are searching for: "));
        if (writeBytes == -1)
        {
            perror("Error while writing GET_CUSTOMER_ID message to client!");
            return false;
        }

        bzero(readBuffer, 1000);
        readBytes = read(cfd, readBuffer, sizeof(readBuffer));
        if (readBytes == -1)
        {
            perror("Error getting customer ID from client!");
            return false;
        }

        roll = atoi(readBuffer);
    }

    int fd = open("students.txt", O_RDONLY);

    printf("roll: %d\n",roll);
    if (fd == -1)
    {
        // Customer File doesn't exist
        bzero(writeBuffer, 1000);
        strcpy(writeBuffer, "Student with this roll number does not exist");
        // strcat(writeBuffer, "^");
        writeBytes = write(cfd, writeBuffer, strlen(writeBuffer));
        if (writeBytes == -1)
        {
            perror("Error while writing message to client!");
            return false;
        }
        readBytes = read(cfd, readBuffer, sizeof(readBuffer)); // Dummy read
        return false;
    }
    int offset = lseek(fd, roll*sizeof(struct Student), SEEK_SET);
    printf("errno: %d\n",errno);
    perror("error");
    if (errno == EINVAL)
    {
        bzero(writeBuffer, 1000);
        strcpy(writeBuffer, "roll number does not exist");

        writeBytes = write(cfd, writeBuffer, strlen(writeBuffer));
        if (writeBytes == -1)
        {
            perror("Error while writing message to client!");
            return false;
        }
        readBytes = read(cfd, readBuffer, sizeof(readBuffer)); // Dummy read
        return false;
    }
    else if (offset == -1)
    {
        perror("Error while seeking to required student record!");
        return false;
    }
    lock.l_start = offset;

    int lockingStatus = fcntl(fd, F_SETLKW, &lock);
    if (lockingStatus == -1)
    {
        perror("Error while obtaining read lock on the student file!");
        return false;
    }

    readBytes = read(fd, &student, sizeof(struct Student));
    if (readBytes == -1)
    {
        perror("Error reading student record from file!");
        return false;
    }

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);

    bzero(writeBuffer, 1000);
    sprintf(writeBuffer, "Student Details - \n\tRoll Number : %d\n\tName : %s\n\tUsername : %s\n", student.rollno, student.name, student.username);

    // strcat(writeBuffer, "\n\nYou'll now be redirected to the main menu...");

    writeBytes = write(cfd, writeBuffer, strlen(writeBuffer));
    if (writeBytes == -1)
    {
        perror("Error writing student info to client!");
        return false;
    }

    // readBytes = read(cfd, readBuffer, sizeof(readBuffer)); // Dummy read
    // continue;
    return true;
}



void addFaculty(int cfd){

    int fd = open("faculty.txt", O_RDONLY, 0744);
    struct Faculty cur, prev;

    if(fd==-1 && errno==ENOENT){
        cur.faculty_id = 0;
    }else if(fd==-1){
        perror("Error while opening file");
        return;
    }
    else{
    
        int off = lseek(fd, -sizeof(struct Faculty), SEEK_END);

        if(off==-1){
            perror("Error seeking to the last record ");
            return;
        }

        struct flock lock = {F_RDLCK, SEEK_SET, off, sizeof(struct Faculty), getpid()};

        int lockingStatus = fcntl(fd, F_SETLKW, &lock);
        if (lockingStatus == -1)
        {
            perror("Error obtaining read lock on student record!");
            return;
        }

        int rb = read(fd, &prev, sizeof(struct Faculty));
        if (rb == -1)
        {
            perror("Error while reading faculty record from file!");
            return;
        }
        printf("prev roll: %d",prev.faculty_id);
        lock.l_type = F_UNLCK;
        fcntl(fd, F_SETLK, &lock);
        close(fd);

        cur.faculty_id = prev.faculty_id+1;
    }

    fd = open("faculty.txt", O_WRONLY|O_CREAT, 0744);

    if(fd==-1){
        perror("Error while opening file");
        return;
    }

    char rbuf[1024],wbuf[1024]="Enter name of the faculty: ";

    int wb = write(cfd, wbuf, strlen(wbuf));
	if(wb==-1){
		perror("Error while asking for name: ");
		return;
	}

	int rb = read(cfd, rbuf, sizeof(rbuf));

	if(rb==-1){
		perror("Error while reading name: ");
		return;
	}
    strcpy(cur.name, rbuf);

    strcpy(wbuf, "Enter the username of the faculty: ");

    wb = write(cfd, wbuf, strlen(wbuf));
	if(wb==-1){
		perror("Error while asking for username: ");
		return;
	}

    memset(rbuf, 0, sizeof(rbuf));

    rb = read(cfd, rbuf, sizeof(rbuf));
    
	if(rb==-1){
		perror("Error while reading username: ");
		return;
	}
    printf("username: %s\n",rbuf);
    strcpy(cur.username, rbuf);

    strcpy(wbuf, "Enter the password of the faculty: ");

    wb = write(cfd, wbuf, strlen(wbuf));
	if(wb==-1){
		perror("Error while asking for password: ");
		return;
	}

    memset(rbuf, 0, sizeof(rbuf));

    rb = read(cfd, rbuf, sizeof(rbuf));

	if(rb==-1){
		perror("Error while reading password: ");
		return;
	}
    
    strcpy(cur.password, rbuf);


    memset(cur.courses, -1, 4*sizeof(int));

    
    int l = lseek(fd, 0, SEEK_END);

    if(l==-1){
        perror("Error while moving file pointer\n");
        return;
    }

    wb = write(fd, &cur, sizeof(struct Faculty));
    if(wb==-1){
        perror("Error while writing into file ");
        return;
    }

    strcpy(wbuf, "Faculty added successfully\n");

    wb = write(cfd, wbuf, strlen(wbuf));

    return;

    // memset(rbuf, 0, sizeof(rbuf));

    // rb = read(cfd, rbuf, sizeof(rbuf));

}






bool viewFacultyDetails(int cfd, int id){

    ssize_t readBytes, writeBytes;             // Number of bytes read from / written to the socket
    char readBuffer[1000], writeBuffer[10000]; // A buffer for reading from / writing to the socket
    char tempBuffer[1000];

    struct Faculty faculty;
    // int fd;
    struct flock lock = {F_RDLCK, SEEK_SET, 0, sizeof(struct Faculty), getpid()};

    if (id == -1)
    {
        writeBytes = write(cfd, "Enter the id of the faculty you are searching for: ", strlen("Enter the id of the faculty you are searching for: "));
        if (writeBytes == -1)
        {
            perror("Error while writing message to client!");
            return false;
        }

        bzero(readBuffer, 1000);
        readBytes = read(cfd, readBuffer, sizeof(readBuffer));
        if (readBytes == -1)
        {
            perror("Error getting faculty id from client!");
            return false;
        }

        id = atoi(readBuffer);
    }

    int fd = open("faculty.txt", O_RDONLY);

    printf("id: %d\n",id);
    if (fd == -1)
    {
        bzero(writeBuffer, 1000);
        strcpy(writeBuffer, "Faculty with this id does not exist");
        // strcat(writeBuffer, "^");
        writeBytes = write(cfd, writeBuffer, strlen(writeBuffer));
        if (writeBytes == -1)
        {
            perror("Error while writing message to client!");
            return false;
        }
        readBytes = read(cfd, readBuffer, sizeof(readBuffer)); // Dummy read
        return false;
    }
    // printf("index:  %d", id);
    int offset = lseek(fd, id*sizeof(struct Faculty), SEEK_SET);
    printf("errno: %d\n",errno);
    perror("error");
    if (errno == EINVAL)
    {
        bzero(writeBuffer, 1000);
        strcpy(writeBuffer, "id does not exist");

        writeBytes = write(cfd, writeBuffer, strlen(writeBuffer));
        if (writeBytes == -1)
        {
            perror("Error while writing message to client!");
            return false;
        }
        readBytes = read(cfd, readBuffer, sizeof(readBuffer)); // Dummy read
        return false;
    }
    else if (offset == -1)
    {
        perror("Error while seeking to required faculty record!");
        return false;
    }
    lock.l_start = offset;

    int lockingStatus = fcntl(fd, F_SETLKW, &lock);
    if (lockingStatus == -1)
    {
        perror("Error while obtaining read lock on the student file!");
        return false;
    }

    readBytes = read(fd, &faculty, sizeof(struct Faculty));
    printf("read: %ld\n",readBytes);
    if (readBytes == -1)
    {
        perror("Error reading faculty record from file!");
        return false;
    }

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);

    bzero(writeBuffer, 1000);
    sprintf(writeBuffer, "Faculty Details - \n\tFaculty id: %d\n\tName : %s\n\tUsername : %s", faculty.faculty_id, faculty.name, faculty.username);


    writeBytes = write(cfd, writeBuffer, strlen(writeBuffer));
    if (writeBytes == -1)
    {
        perror("Error writing faculty info to client!");
        return false;
    }

    return true;
}


void adminMenu(int cfd){
	bool login = adminLogin(cfd);
    if(login){
        // char buf[100] = "Logged in as Admin!";
		// int wb = write(cfd, buf, sizeof(buf));
        // char rbuf[1];
        // int rb = read(cfd, rbuf, 1);

	    // display admin menu
	// if(adminLogin(cfd)){
        while(1){
            char menu[4096] = "\n....................................Welcome to Admin Menu....................................\n"
                    "1. Add Student\n"
                    "2. View Student Details\n"
                    "3. Add Faculty\n"
                    "4. View Faculty Details\n"
                    "5. Activate Student\n"
                    "6. Block Student\n"
                    "7. Modify Student Details\n"
                    "8. Modify Faculty Details\n"
                    "9. Logout and Exit\n\n"
                    "Enter your choice: \r\n";

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

            printf("choice: %d\n",choice);
            switch(choice){
                case 1:
                {
                    addStudent(cfd);
                    break;
                }
                case 2:
                {

                    viewStudentDetails(cfd, -1);
                    // if(ret)continue;

                    printf("outside\n");
                    // sleep(1);
                    // char rbf[1024];
                    // int rb = read(cfd, rbf, sizeof(rbf)); 
                    break;
                }
                case 3:
                {
                    addFaculty(cfd);
                        break;
                }
                case 4:
                {
                    viewFacultyDetails(cfd, -1);
                        break;
                }
                case 5:
                {
                        break;
                }
                case 6:
                {
                        break;
                }
                case 7:
                {
                        break;
                }
                case 8:
                {
                        break;
                }
                case 9:
                {
                        return;
                }
                default:
                {
                        // printf("Enter a valid choice!\n");
                        break;
                }
            }

            continue;
            
        }
    }



}


