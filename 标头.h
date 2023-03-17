struct manager
{
	char id[50];
	char password[50];
};
struct passenger
{
	char id[50];
	char password[50];
	int NoOfTicket[20];//”√”⁄¥¢¥Ê≥µ∆±±‡∫≈
	int NumOfTicket;
};
struct ticket
{
	int no;
	char start[50];
	char destination[50];
	char StartTime[50];
	char ArriveTime[50];
	int RestOfTicket;
};
void BackStage();
void Ticketing();
int main();

void ManagerLog();
void logon();
void login();

void PassengerLog();
void plogin();
void plogon();

void site();
void AddSite();
void view();

