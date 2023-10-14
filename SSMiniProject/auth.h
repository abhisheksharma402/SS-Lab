#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include "structs.h"
// #include "faculty.h"
// #include "student.h"
// #include "admin.h"

// student login
struct Student *studentLogin(int cfd)
{

        char user[1024], pass[1024];
        // ask for username
        int wb = write(cfd, "Enter username: ", 16);
        if (wb == -1)
        {
                perror("Error while asking for username: ");
                return NULL;
        }

        int rb = read(cfd, user, sizeof(user));

        if (rb == -1)
        {
                perror("Error while reading username: ");
                return NULL;
        }
        // ask for password

        wb = write(cfd, "Enter password: ", 16);
        if (wb == -1)
        {
                perror("Error while asking for password: ");
                return NULL;
        }

        rb = read(cfd, pass, sizeof(pass));

        if (rb == -1)
        {
                perror("Error while reading password: ");
                return NULL;
        }

        int fd = open("students.txt", O_RDONLY | O_CREAT);

        struct Student *a = NULL;

        if (fd == -1)
        {
                perror("Error opening file");
                return a;
        }

        struct Student student;

        while (read(fd, &student, sizeof(struct Student)) > 0)
        {
                if (strcmp(student.username, user) == 0 && strcmp(student.password, pass) == 0)
                {
                        a = &student;
                        break;
                }
        }

        close(fd);
        return a;

}

// faculty login
struct Faculty *facultyLogin(int cfd)
{

        char user[1024], pass[1024];
        // ask for username
        int wb = write(cfd, "Enter username: ", 16);
        if (wb == -1)
        {
                perror("Error while asking for username: ");
                return NULL;
        }

        int rb = read(cfd, user, sizeof(user));

        if (rb == -1)
        {
                perror("Error while reading username: ");
                return NULL;
        }
        // ask for password

        wb = write(cfd, "Enter password: ", 16);
        if (wb == -1)
        {
                perror("Error while asking for password: ");
                return NULL;
        }

        rb = read(cfd, pass, sizeof(pass));

        if (rb == -1)
        {
                perror("Error while reading password: ");
                return NULL;
        }

        int fd = open("faculty.txt", O_RDONLY | O_CREAT);

        struct Faculty *f = NULL;

        if (fd == -1)
        {
                perror("Error opening file");
                return f;
        }

        struct Faculty faculty;

        while (read(fd, &faculty, sizeof(struct Faculty)) > 0)
        {
                if (strcmp(faculty.username, user) == 0 && strcmp(faculty.password, pass) == 0)
                {
                        f = &faculty;
                        break;
                }
        }

        close(fd);
        return f;
}

// admin login

// bool adminLogin(int cfd){
// 	printf("inside auth\n");
// 	char user[1024],pass[1024];
// 	// ask for username
//         char wbuf[1024];
//         memset(wbuf,0,sizeof(wbuf));

//         strcpy(wbuf, "Enter username: ");

// 	int wb = write(cfd, wbuf, sizeof(wbuf));
// 	if(wb==-1){
// 		perror("Error while asking for username: ");
// 		return false;
// 	}

// 	int rb = read(cfd, user, sizeof(user));

// 	if(rb==-1){
// 		perror("Error while reading username: ");
// 		return false;
// 	}
//         printf("done reading username\n");
// 	//ask for password
//         bzero(wbuf, sizeof(wbuf));
// 	strcpy(wbuf, "Enter Password: ");
//         printf("wbuf: %s\n",wbuf);
// 	wb = write(cfd, wbuf, strlen(wbuf));
//         printf("wb: %d\n",wb);
//         if(wb==-1){
//                 perror("Error while asking for password: ");
//                 return false;
//         }

//         rb = read(cfd, pass, sizeof(pass));

//         if(rb==-1){
//                 perror("Error while reading password: ");
//                 return false;
//         }

//         if(strcmp(user, "admin1")==0 && strcmp(pass,"root123")==0){

//                 return true;

//         }

//         return false;

// 	// int fd = open("faculty.txt", O_RDONLY|O_CREAT);

// 	// struct Admin *a = NULL;

//         // if (fd == -1) {
//         //         perror("Error opening file");
//         //         return a;
//         // }

// 	// struct Admin admin;

//         // while (read(fd, &admin, sizeof(struct Admin)) > 0) {
//         //         if (strcmp(admin.username, user) == 0 && strcmp(admin.password, pass) == 0) {
// 	// 		a = &admin;
//         //                 break;
//         //         }
//         // }

//         // close(fd);
//         // return a;

// }

bool adminLogin(int cfd)
{
        ssize_t readBytes, writeBytes;            // Number of bytes written to / read from the socket
        char readBuffer[1000], writeBuffer[1000]; // Buffer for reading from / writing to the client
        char tempBuffer[1000];
        //     struct Customer customer;

        int ID;

        memset(readBuffer, 0, sizeof(readBuffer));
        memset(writeBuffer, 0, sizeof(writeBuffer));

        strcpy(writeBuffer, "Welcome to Admin Menu");

        // Append the request for LOGIN ID message
        strcat(writeBuffer, "\n");

        strcat(writeBuffer, "Enter the username: ");

        writeBytes = write(cfd, writeBuffer, sizeof(writeBuffer));
        if (writeBytes == -1)
        {
                perror("Error writing welcome message to the client!");
                return false;
        }

        readBytes = read(cfd, readBuffer, sizeof(readBuffer));
        if (readBytes == -1)
        {
                perror("Error reading username from client!");
                return false;
        }

        // bool userFound = false;

        if (strcmp(readBuffer, "admin1") != 0)
        {
                memset(writeBuffer, 0, sizeof(writeBuffer));
                writeBytes = write(cfd, "Invalid username", sizeof("Invalid username"));
                return false;
        }
        

        memset(writeBuffer, 0, sizeof(writeBuffer));
        writeBytes = write(cfd, "Enter Password", sizeof("Enter Password"));
        if (writeBytes == -1)
        {
                perror("Error writing PASSWORD message to client!");
                return false;
        }

        memset(readBuffer, 0, sizeof(readBuffer));
        readBytes = read(cfd, readBuffer, sizeof(readBuffer));
        if (readBytes == 1)
        {
                perror("Error reading password from the client!");
                return false;
        }

        if (strcmp(readBuffer, "root123") == 0)
        {
                return true;
        }

        memset(writeBuffer, 0, sizeof(writeBuffer));
        writeBytes = write(cfd, "Invalid Password", sizeof("Invalid Password"));

        return false;
}


// bool admin_login(char *username, char *password)
// {
// 	// struct Admin admin;
// 	// admin = get_admin_details(0); // default admin credentials
// 	// if (admin. == -1)
// 	// 	return 0;
// 	if (strcmp(username, "admin1") == 0 && strcmp(password, "root123") == 0)
// 		return 1;
// 	return 0;
// }


// bool login(int cfd, int type)
// {
// 	struct message msg;
// 	char id[11];
// 	char password[11];
// 	int readBytes, writeBytes;
// 	// Login Menu
// 	// Getting Login_id
// 	write_msg(cfd, 1, 0, "\nEnter Login-Id: ");
// 	read_msg(cfd, &msg);

// 	strcpy(id, msg.body);
// 	id[10] = '\0';

// 	// Getting Password
// 	write_msg(cfd, 1, 2, "\nEnter Password: ");
// 	read_msg(cfd, &msg);

// 	strcpy(password, msg.body);
// 	password[10] = '\0';

// 	if (type == 0 && admin_login(id, password))
// 	{
// 		write_msg(cfd, 0, 1, "\nLogin Successful!\n");
//                 return true;
// 		// goto menu
// 		// adminMenu(cfd);
// 	}
// 	// else if (type == 1 && customer_login(id, password))
// 	// {
// 	// 	write_msg(cfd, 0, 1, "\nLogin Successful! ");

// 	// 	// goto menu
// 	// 	// customer_menu(cfd, atoi(id + 5));
// 	// }
// 	else
// 	{
// 		write_msg(cfd, 1, 0, "\nLogin Failed:Invalid Details or Already Login...\nDo you want to Try again(Y/N): ");
// 		read_msg(cfd, &msg);

// 		if ((msg.body[0] == 'Y' && msg.body[1] == '\0') || (msg.body[0] == 'y' && msg.body[1] == '\0'))
// 			login(cfd, type);
// 		else
// 		{
// 			write_msg(cfd, 0, 0, "");
// 		}
// 	}
// }