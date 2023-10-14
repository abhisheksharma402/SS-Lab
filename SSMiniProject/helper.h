// bool read_msg(int cfd, struct message *msg)
// {
//     int readBytes;
//     bzero(msg->body, sizeof(msg->body));
//     readBytes = read(cfd, &(*msg), sizeof(*msg));
//     if (readBytes < 0)
//         return 0;

//     return 1;
// }

// bool write_msg(int cfd, int type, int action, char *body)
// {
//     int writeBytes;
//     struct message msg;
//     msg.id = 0;
//     msg.type = type;
//     msg.action = action;
//     strcpy(msg.body, body);
//     writeBytes = write(cfd, &msg, sizeof(msg));
//     if (writeBytes < 0)
//         return 0;

//     return 1;
// }


// bool write_msg2(int cfd, int type, int action, char *body, int number)
// {
//     int writeBytes;
//     struct message msg;
//     msg.id = 0;
//     msg.type = type;
//     msg.action = action;
//     sprintf(msg.body, "%s->%d\n", body, number);
//     writeBytes = write(cfd, &msg, sizeof(msg));
//     if (writeBytes < 0)
//         return 0;

//     return 1;
// }




// // bool is_validId(int type, int id)
// // {
// // 	if (id < 0)
// // 		return 0;
// // 	struct Count count;
// // 	int record_fd, rBytes, offset;
// // 	record_fd = open("count.txt", O_RDONLY);
// // 	if (record_fd == -1)
// // 	{
// // 		perror("Cannot Open File");
// // 		return 0;
// // 	}
// // 	offset = lseek(record_fd, 0 * sizeof(struct Count), SEEK_SET);
// // 	if (offset == -1)
// // 	{
// // 		perror("Error while Repositioning in Record File");
// // 		return 0;
// // 	}

// // 	/*Setting Lock*/
// // 	struct flock lock = {F_RDLCK, SEEK_SET, 0 * sizeof(struct Count), sizeof(struct Count), getpid()};
// // 	int lockingStatus = fcntl(record_fd, F_SETLKW, &lock);
// // 	if (lockingStatus == -1)
// // 	{
// // 		perror("Error obtaining read lock on Account record!");
// // 		return 0;
// // 	}
// // 	/*...........*/
// // 	rBytes = read(record_fd, &count, sizeof(count));
// // 	/*Unlocking....*/
// // 	lock.l_type = F_UNLCK;
// // 	fcntl(record_fd, F_SETLK, &lock);
// // 	/*...........*/
// // 	if (rBytes <= 0)
// // 	{
// // 		perror("Cannot read the file");
// // 		return 0;
// // 	}
// // 	switch (type)
// // 	{
// // 	case 0:
// // 		if (id >= my_record.accounts)
// // 			return 0;
// // 		break;
// // 	case 1:
// // 		if (id >= my_record.customers)
// // 			return 0;
// // 		break;
// // 	case 2:
// // 		if (id >= my_record.admins)
// // 			return 0;
// // 		break;
// // 	case 3:
// // 		if (id >= my_record.transactions)
// // 			return 0;
// // 		break;
// // 	default:
// // 		return 0;
// // 		break;
// // 	}

// // 	close(record_fd);
// // 	return 1;
// // }

// // // Record Details Getters and Setters.....
// // int get_record_details(int type)
// // {
// // 	struct record my_record;
// // 	int record_fd, rBytes, retVal, offset;
// // 	record_fd = open("./records/record_file", O_RDONLY);
// // 	if (record_fd == -1)
// // 	{
// // 		perror("Cannot Open File");
// // 		return -1;
// // 	}
// // 	offset = lseek(record_fd, 0 * sizeof(struct record), SEEK_SET);
// // 	if (offset == -1)
// // 	{
// // 		perror("Error while Repositioning in Record File");
// // 		return -1;
// // 	}

// // 	/*Setting Lock*/
// // 	struct flock lock = {F_RDLCK, SEEK_SET, 0 * sizeof(struct record), sizeof(struct record), getpid()};
// // 	int lockingStatus = fcntl(record_fd, F_SETLKW, &lock);
// // 	if (lockingStatus == -1)
// // 	{
// // 		perror("Error obtaining read lock on Account record!");
// // 		return 0;
// // 	}
// // 	/*...........*/
// // 	rBytes = read(record_fd, &my_record, sizeof(my_record));
// // 	/*Unlocking....*/
// // 	lock.l_type = F_UNLCK;
// // 	fcntl(record_fd, F_SETLK, &lock);
// // 	/*...........*/
// // 	if (rBytes <= 0)
// // 	{
// // 		perror("Cannot read the file");
// // 		return -1;
// // 	}
// // 	// Body.................
// // 	switch (type)
// // 	{
// // 	case 0:
// // 		retVal = my_record.accounts;
// // 		break;
// // 	case 1:
// // 		retVal = my_record.customers;
// // 		break;
// // 	case 2:
// // 		retVal = my_record.admins;
// // 		break;
// // 	case 3:
// // 		retVal = my_record.transactions;
// // 		break;
// // 	default:
// // 		return -1;
// // 		break;
// // 	}

// // 	close(record_fd);
// // 	return retVal;
// // }

// // bool set_record_details(int type, int value)
// // {
// // 	struct record my_record;
// // 	int record_fd, rBytes, wBytes, offset;
// // 	// open...
// // 	record_fd = open("./records/record_file", O_RDWR);
// // 	if (record_fd == -1)
// // 	{
// // 		perror("Cannot Open File");
// // 		return 0;
// // 	}
// // 	// read...
// // 	offset = lseek(record_fd, 0 * sizeof(struct record), SEEK_SET);
// // 	if (offset == -1)
// // 	{
// // 		perror("Error while Repositioning in Record File");
// // 		return 0;
// // 	}

// // 	/*Setting Lock*/
// // 	struct flock lock = {F_RDLCK, SEEK_SET, 0 * sizeof(struct record), sizeof(struct record), getpid()};
// // 	int lockingStatus = fcntl(record_fd, F_SETLKW, &lock);
// // 	if (lockingStatus == -1)
// // 	{
// // 		perror("Error obtaining read lock on Account record!");
// // 		return 0;
// // 	}
// // 	/*...........*/
// // 	rBytes = read(record_fd, &my_record, sizeof(my_record));
// // 	/*Unlocking....*/
// // 	lock.l_type = F_UNLCK;
// // 	fcntl(record_fd, F_SETLK, &lock);
// // 	/*...........*/

// // 	if (rBytes <= 0)
// // 	{
// // 		perror("Cannot read the file");
// // 		return 0;
// // 	}
// // 	// Body.................
// // 	switch (type)
// // 	{
// // 	case 0:
// // 		my_record.accounts = value;
// // 		break;
// // 	case 1:
// // 		my_record.customers = value;
// // 		break;
// // 	case 2:
// // 		my_record.admins = value;
// // 		break;
// // 	case 3:
// // 		my_record.transactions = value;
// // 		break;
// // 	default:
// // 		return 0;
// // 		break;
// // 	}
// // 	// update....
// // 	offset = lseek(record_fd, 0 * sizeof(struct record), SEEK_SET);
// // 	if (offset == -1)
// // 	{
// // 		perror("Error while Repositioning in Record File");
// // 		return 0;
// // 	}

// // 	/*Setting Lock*/
// // 	lock.l_type = F_WRLCK;
// // 	lock.l_start = 0 * sizeof(struct record);
// // 	lockingStatus = fcntl(record_fd, F_SETLKW, &lock);
// // 	if (lockingStatus == -1)
// // 	{
// // 		perror("Error obtaining read lock on Account record!");
// // 		return 0;
// // 	}
// // 	/*...........*/
// // 	wBytes = write(record_fd, &my_record, sizeof(my_record));
// // 	/*Unlocking....*/
// // 	lock.l_type = F_UNLCK;
// // 	fcntl(record_fd, F_SETLK, &lock);
// // 	/*...........*/
// // 	if (wBytes <= 0)
// // 	{
// // 		perror("Cannot write into the file");
// // 		return 0;
// // 	}

// // 	close(record_fd);
// // 	return 1;
// // }
