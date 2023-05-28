#include <iostream>
#include <bits/stdc++.h>
#include <vector>

using namespace std;

//enum Priority { Borked, WorksByCoincidence, EdgeCaseIssue, UncleanCode, WorksButCoudBeBetter };  // should be implemented differently

struct Ticket{
public:

  int priority;
  string content;
  //  string creationTime;  // need to automatically give the date
  string nameOfCodeFile; // need to check whether the file of that name exists?

  Ticket(){
    cout << "Enter Priority: [0,1,2,3...]\n";
    cin >> this->priority;
    cin.ignore();
    cout << "Enter the message:\n";
    getline(cin, this->content);
    cout << "Enter the name of the code file (ex. calculator.cpp):\n";
    cin >> this->nameOfCodeFile;
  }
  
  Ticket(int urgency, string cont, string fileName, fstream& fio){  // constructor
    this->priority = urgency;
    this->content = cont;
    //    this->creationTime = time;
    this->nameOfCodeFile = fileName;
  }
  
  void writeTicketToFile(fstream& file){
    file << "====================\n";
    file << "Priority:\n";
    file << "  " << this->priority << "\n";
    file << "Content:\n";
    file << "  " << this->content << "\n";
    //    file << "Time of creation:\n";
    //    file << "  " << this->creationTime << "\n";
    file << "Refers to the file:\n";
    file << "  " << this->nameOfCodeFile << "\n";
  }
  
  void displayTicket(){
    cout << "====================\n";
    cout << "Priority:\n";
    cout << "  " << this->priority << "\n";
    cout << "Content:\n";
    cout << "  " << this->content << "\n";
    //    cout << "Time of creation:\n";
    //    cout << "  " << this->creationTime << "\n";
    cout << "Refers to the file:\n";
    cout << "  " << this->nameOfCodeFile << "\n";
  }
};

void readTicketFile(fstream& file, int sortType){

  string tmp = "";
  vector<string> tickets;
  string ticket = "";
  
  file.open("ticketFile", ios::in);
  file.seekg(0);

  while (getline(file, tmp)) {
    if (tmp == "====================") {
      if (!ticket.empty()) {
        tickets.push_back(ticket);
        ticket.clear();
      }
    }
    ticket += tmp + "\n";
  }

  if (!ticket.empty()) {
    tickets.push_back(ticket);
  }

  file.close();

  for (const string& ticket : tickets){   // Print the contents of the vector
    cout << "Here comes a ticket!\n";  
    cout << ticket << endl;
  }

  cout << "CONTROL\n";

  for(string& ticket : tickets){
    cout << "TICKET\n";
  }

  switch(sortType){
  case 1:    // sort by priority
    {

      // NEW CODE (WORKING) BEGIN
        vector<string> sortedTickets = tickets;

        // Custom sorting function
        auto sortByPriority = [](const string& ticket1, const string& ticket2) {
            int priority1, priority2;
            stringstream ss1(ticket1), ss2(ticket2);
            string line;
            while (getline(ss1, line)) {
                if (line == "Priority:") {
                    getline(ss1, line);
                    priority1 = stoi(line);
                    break;
                }
            }
            while (getline(ss2, line)) {
                if (line == "Priority:") {
                    getline(ss2, line);
                    priority2 = stoi(line);
                    break;
                }
            }
            return priority1 < priority2;
        };

        sort(sortedTickets.begin(), sortedTickets.end(), sortByPriority);    // Sort the tickets based on priority

        for (const string& ticket : sortedTickets) {    // Print the sortedTickets vector
            cout << ticket << endl;
        }
    }
    break;
    // NEW CODE (WORKING) END

    //OLD CODE BEGIN
      //OLD CODE END
  case 2:    // sort by file name
    {

       // Custom sorting function
        auto sortByLastLine = [](const string& ticket1, const string& ticket2) {
            string lastLine1, lastLine2;
            stringstream ss1(ticket1), ss2(ticket2);
            string line;
            while (getline(ss1, line)) {
                if (line == "Refers to the file:") {
                    getline(ss1, lastLine1);
                    break;
                }
            }
            while (getline(ss2, line)) {
                if (line == "Refers to the file:") {
                    getline(ss2, lastLine2);
                    break;
                }
            }
            return lastLine1 < lastLine2;
        };

        // Sort the tickets based on the last line
        sort(tickets.begin(), tickets.end(), sortByLastLine);

        // Print the sorted tickets
        for (const string& ticket : tickets) {
            cout << ticket << endl;
        }
      
    }
    break;
  default:
    break;
  }

} // end of readTicketFile

int main(){                 // needs the possibility to open in a ticket reading mode, and ticket writing mode
  
  string cont = "some text here about the issue";
  //  string date = "02/05/2023";
  string fileName = "file.cpp";
  

  fstream file;

  file.open("ticketFile",ios::out | ios::app);

  cout << "Ticket file opened\n";
  
  if(!file){
    cout << "Error creating the file\n";
    return 0;
  }


  //  Ticket tkt1(1, cont, fileName, file);
  //  Ticket tkt2(3, cont, fileName, file);
  //  Ticket tkt3(2, cont, fileName, file);
  
  //  Ticket tkt4(1, cont, "file.hs", file);
  //  Ticket tkt5(3, cont, "file.hs", file);
  //  Ticket tkt6(2, cont, "file.c", file);    

  //  tkt1.writeTicketToFile(file);
  //  tkt2.writeTicketToFile(file);
  //  tkt3.writeTicketToFile(file);

  //  tkt4.writeTicketToFile(file);
  //  tkt5.writeTicketToFile(file);
  //  tkt6.writeTicketToFile(file);
  

  //  cout << "Ticket written to file\n";

  //  tkt1.displayTicket();
  //  tkt2.displayTicket();
  //  tkt3.displayTicket();  

  file.close();

  cout << "Ticket file closed\n";

  //  readTicketFile(file, 2);  // second argument is a sort type: 1 for priority ; 2 for file name

//Ticket tkt1(1, cont, fileName, file);
  Ticket tkt;

  tkt.displayTicket();
  
  return 0;
}
