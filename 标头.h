struct manager
{
	char id[20];
	char password[20];
};
struct passenger
{
	char id[20];
	char password[20];
	char ticket[20];
	int NumOfTicket;
};
struct ticket
{
	char start[20];
	char destination[20];
	int RestOfTicket;

};
void BackStage();
void Ticketing();
int main();

void ManagerLog();
void logon();
void login();

void FileManager(struct manager*);

