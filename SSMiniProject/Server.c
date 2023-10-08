#include<stdio.h>
#include<unistd.h>



void FacultyOptions(){
	while(1){
                printf("....................................Welcome to Faculty Menu....................................\n");
		
		printf("1. View Offering Courses\n");
		printf("2. Add New Course\n");
		printf("3. Remove Course from Catalog\n");
		printf("4. Update Course Details\n");
		printf("5. Change Password\n");
		printf("6. Logout and Exit\n");

		printf("Enter your choice: ");

                int choice;
                scanf("%d",&choice);

                switch(choice){
                        case 1:
                        {
                                break;
                        }
                        case 2:
                        {
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
                                printf("Enter a valid choice!\n");
                                break;
                        }
                }

        }
}



void StudentOptions(){
        while(1){
                printf("....................................Welcome to Student Menu....................................\n");

                printf("1. View All Courses\n");
                printf("2. Enroll (pick) New Course\n");
                printf("3. Drop Course\n");
                printf("4. View Enrolled Course Details\n");
                printf("5. Change Password\n");
                printf("6. Logout and Exit\n");
	
		printf("Enter your choice: ");

                int choice;
                scanf("%d",&choice);

                switch(choice){
                        case 1:
                        {
                                break;
                        }
                        case 2:
                        {
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
                                printf("Enter a valid choice!\n");
                                break;
                        }
                }

        }
}



void AdminOptions(){
        while(1){
                printf("....................................Welcome to Admin Menu....................................\n");

                printf("1. Add Student\n");
                printf("2. View Student Details\n");
                printf("3. Add Faculty\n");
                printf("4. View Faculty Details\n");
                printf("5. Activate Student\n");
		printf("6. Block Student\n");
		printf("7. Modify Student Details\n");
		printf("8. Modify Faculty Details\n");
                printf("9. Logout and Exit\n");

                printf("Enter your choice: ");

                int choice;
                scanf("%d",&choice);

                switch(choice){
                        case 1:
                        {
                                break;
                        }
                        case 2:
                        {
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
                                printf("Enter a valid choice!\n");
                                break;
                        }
                }

        }
}







int main(){

	// create a server and make it listen on a port.
	

	while(1){
		printf("....................................Welcome Back to Academia :: Course Registration....................................\n");
		
		int choice;
        	printf("Enter your role {1) Faculty 2) Student 3) Admin 4) Exit}: ");
        	scanf("%d",&choice);
		
		switch(choice){
			case 1:
			{
				// ask for login credentials and check them
				if(login()) FacultyOptions();
				else{
					printf("Username or password incorrect\n");
				}
				break;

			}
			case 2:
			{
				// ask for login credectials and check them
				if(login()) StudentOptions();
				else{
					printf("Username or password incorrect\n");
				}
				break;
			}
			case 3:
                	{
				// ask for login credectials and check them
                                if(login()) AdminOptions();
                                else{
                                        printf("Username or password incorrect\n");
                                }

                        	break;
                	}
			case 4:
			{
				return 0;
			}
			default:
			{
				printf("Enter a valid choice!\n");
				break;
			}
		}

	}





}

