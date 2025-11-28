#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_TRIPS 50 
#define MAX_SEATS 50
#define MAX_TICKETS (MAX_TRIPS * MAX_SEATS)

typedef struct{
    char name[50];
    char address[100];
} Location;

typedef struct{
    char tripID[20];
    Location departure;
    Location destination;
    char date[20];
    int totalSeats;
    int bookedSeats;
} Trip;

typedef struct{
    char name[50];
    char phone[15];
} Passenger;

typedef struct{
    char ticketID[20];
    char tripID[20];
    Passenger passenger;
    int seatNumber;
    double price;
    int paymentStatus;
    char date[20];
} Ticket;



void inputString(char *content, int size) {
    if (fgets(content, size, stdin) != NULL) {
        content[strcspn(content, "\n")] = 0;
    }
}

int checkInvalidInput(char *s){
    if(strlen(s) == 0 || s[0] == ' '){
        return 1;
    }
    return 0;
}


int isValidDate(char *date) {
    if (strlen(date) != 10) return 0;
    if (date[2] != '/' || date[5] != '/'){
	 	return 0;
	 }
	int i;
    for (i = 0; i < 10; i++) {
        if (i == 2 || i == 5){
        	continue;
        }
        if (date[i] < '0' || date[i] > '9') {
			return 0;
		}
    }

    int day, month, year;
    sscanf(date, "%d/%d/%d", &day, &month, &year);

    if (day < 1 || day > 31) return 0;
    if (month < 1 || month > 12) return 0;
    if (year < 1900) return 0;

    return 1; 
}

int getValidInt(char *message){
    char buffer[50];
    int value;
    int valid;
    int i;
    
    while(1){
        printf("%s", message);
        if(fgets(buffer, sizeof(buffer), stdin) == NULL){
            return 0;
        }
        if(buffer[0] == '\n'){
            printf("Invalid. Please enter a number\n");
            continue;
        }
        buffer[strcspn(buffer, "\n")] = 0;
        
        valid = 1;
        for(i = 0; i < strlen(buffer); i++){
            if(buffer[i] < '0' || buffer[i] > '9'){
                valid = 0;
                break;
            }
        }
        if(valid == 0){
            printf("Invalid. Input contains space or letters\n");
        }else{
            sscanf(buffer, "%d", &value);
            return value;
        }
    }
}

double getValidDouble(char *message) {
    char buffer[100];
    double value;
    int valid;
    int dotCount; 
    int i;

    while (1) {
        printf("%s", message);
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            return 0.0;
        }
        
        if (buffer[0] == '\n') {
            printf("Must enter a number. Try again\n");
            continue;
        }

        buffer[strcspn(buffer, "\n")] = 0;
        
        valid = 1;
        dotCount = 0;
        for(i = 0; i < strlen(buffer); i++){
            if(buffer[i] == '.'){
                dotCount++;
            }
            else if(buffer[i] < '0' || buffer[i] > '9'){ 
                valid = 0;
                break;
            }
        }
        
        if(dotCount > 1) valid = 0; 

        if (valid == 0) {
            printf("Invalid input. Please try again\n");
        } else {
            sscanf(buffer, "%lf", &value);
            return value;
        }
    }
}

int checkDuplicate(char *id, Trip *tp, int currentIndex){
	int i;
    for(i = 0 ; i < currentIndex ; i++){
        if(strcmp(id, tp[i].tripID) == 0){
            return 1;
        }
    }
    return 0;    
}

int searchID(Trip *tp, int length, char *id){
	int i;
    for(i = 0 ; i < length; i++){
        if(strcmp(id, tp[i].tripID) == 0){
            return i;
        }
    }
    return -1;
}

int ticketID(Ticket *tk, int ticketCount, char *id){
	int i;
    for( i = 0; i < ticketCount; i ++){
        if(strcmp(id, tk[i].ticketID) == 0){
            return i;
        }
    }
    return -1;
}

void printLine(){
    printf("+------------+----------------------+--------------+-------------------------------------+--------------+-------+--------------+----------+\n");
}

void printLineTrip(){
    printf("+------------+-------------------------------------+-------------------------------------+--------------+-------+--------+\n");
}

void addTrips(Trip *tp, int *length){
    int n,i;

    do {
        n = getValidInt("Enter the number of trips to add: ");
        if (n <= 0) {
            printf("Amount must be > 0. Please enter again!\n");
        } else if (*length + n > MAX_TRIPS) { 
            printf("Not enough space! Available slots: %d. Please enter again!\n", MAX_TRIPS - *length);
        }
    } while (n <= 0 || *length + n > MAX_TRIPS);

    for(i = 0 ; i < n ; i ++){
        int valid; 
        int index = *length + i;
        printf("\n__________INPUT TRIP NUMBER %d___________\n", index + 1);
        
        do{
            valid = 1; 
            printf("Enter trip ID: ");
            inputString(tp[index].tripID, sizeof(tp[index].tripID));
            
            if(checkInvalidInput(tp[index].tripID)== 1){
                printf("Invalid!! Cannot be empty or space in first letter!\n");
                valid = 0;
            }
             else if(checkDuplicate(tp[index].tripID, tp, index) == 1){ 
                printf("Invalid!! Trip ID existed, please enter another.\n");
                valid = 0;
            }
        } while(valid == 0);
        
        do{
            valid = 1;
            printf("Enter departure name: ");
            inputString(tp[index].departure.name, sizeof(tp[index].departure.name));
            if(checkInvalidInput(tp[index].departure.name)== 1){
                printf("Invalid!! Cannot be empty or space in first letter!\n");
                valid = 0;
            }
        } while(valid == 0);

        do{
            valid = 1;
            printf("Enter departure address: ");
            inputString(tp[index].departure.address, sizeof(tp[index].departure.address));
            if(checkInvalidInput(tp[index].departure.address)== 1){
                printf("Invalid!! Cannot be empty or space in first letter!\n");
                valid = 0;
            }
        } while(valid == 0);

        do{
            valid = 1;
            printf("Enter destination name: ");
            inputString(tp[index].destination.name, sizeof(tp[index].destination.name));
            if(checkInvalidInput(tp[index].destination.name)== 1){
                printf("Invalid!! Cannot be empty or space in first letter!\n");
                valid = 0;
            }
        } while(valid == 0);

        do{
            valid = 1;
            printf("Enter destination address: ");
            inputString(tp[index].destination.address, sizeof(tp[index].destination.address));
             if(checkInvalidInput(tp[index].destination.address)== 1){
                printf("Invalid!! Cannot be empty or space in first letter!\n");
                valid = 0;
            }
        } while(valid == 0);
        
        do{
            valid = 1;
            printf("Enter time (dd/mm/yyyy): ");
            inputString(tp[index].date, sizeof(tp[index].date));
             if(checkInvalidInput(tp[index].date)== 1){
                printf("Invalid!! Cannot be empty.\n");
                valid = 0;
            }else if (isValidDate(tp[index].date) == 0) {
                printf("Invalid format! Use dd/mm/yyyy\n");
                valid = 0;
            }
        } while(valid == 0);
        
        do{
            tp[index].totalSeats = getValidInt("Enter seats: ");
            if(tp[index].totalSeats <= 0|| tp[index].totalSeats < tp[index].bookedSeats){ 
                printf("Invalid!! Total seats must above 0 and booked seats.\n");
                valid = 0;
            } else valid = 1;
        } while(valid == 0);    
        
        tp[index].bookedSeats = 0; 
        printf("Updated successfully!\n");
    }   
    *length += n;    
}

void updateTrip(Trip *tp, int length){
    char n[20];
    int valid;
    do{
        valid = 1;
        printf("Enter trip ID: ");
        inputString(n, sizeof(n));
        if(checkInvalidInput(n) == 1){
            printf("Invalid!! Cannot be empty or space in first letter!\n");
            valid = 0;
        }
    } while(valid == 0);
	
    int index = searchID(tp, length, n);
    if(index == -1){
    	printf(">> Cannot find the trip");
    }else{
    	int subChoice;
    	do{
    	printf("\n================ UPDATE TRIP: %s =====================================\n", tp[index].tripID);
    	printf("+-------------------------------------------------------------------+\n");
        printf("| %-60s |\n","1. Update Departure (Current: %s - %s)\n", tp[index].departure.name, tp[index].departure.address);
        printf("| %-60s |\n","2. Update Destination (Current: %s - %s)\n", tp[index].destination.name, tp[index].destination.address);
        printf("| %-60s |\n","3. Update Time (Current: %s)\n", tp[index].date);
        printf("| %-60s |\n","4. Update Seats (Current: %d, Booked: %d)\n", tp[index].totalSeats, tp[index].bookedSeats);
        printf("5. Finish Updating (Back)\n");
        printf("=====================================================================\n");
    	subChoice = getValidInt("Select information to update: ");
    	switch(subChoice){
    		case 1:{
    			printf("\n--- UPDATE DEPARTURE ---\n");
    			do{
    				valid = 1;
    				printf("\nEnter new departure: ");
    				inputString(tp[index].departure.name,sizeof(tp[index].departure.name));
    				if(checkInvalidInput(tp[index].departure.name)== 1){
    					printf("Invalid!! Cannot be empty or space in first letter!\n");
               			 valid = 0;
					}
    				
				}while(valid == 0);
				
				do{
					valid = 1;
					printf("\nEnter new address: ");
					inputString(tp[index].departure.address,sizeof(tp[index].departure.address));
					if(checkInvalidInput(tp[index].departure.address) == 1){
						printf("Invalid!! Cannot be empty or space in first letter!");
						valid =0;
					}
				}while(valid == 0);
				printf(">> Departure info updated!\n");
				break;
			}
			case 2:{
				printf("\n--- UPDATE DESTINATION ---\n");
				do{
					valid =1;
					printf("\nEnter new destination: ");
					inputString(tp[index].destination.name,sizeof(tp[index].destination.name));
					
					if(checkInvalidInput(tp[index].destination.name)==1){
						printf("Invalid!! Cannot be empty or space in first letter!");
						valid = 0;
					}
				}while(valid == 0);
				
				do{
					valid = 1;
					printf("\nEnter new destination address: ");
					inputString(tp[index].destination.address,sizeof(tp[index].destination.address));
					
					if(checkInvalidInput(tp[index].destination.address) == 1){
						printf("Invalid!! Cannot be empty or space in first letter!");
						valid = 0;
					}
					
				}while(valid == 0);
				printf(">> Destination info updated!");
				break;
			}
			case 3:{
				printf("\n--- UPDATE TIME ---\n");
				do{
					valid = 1;
					printf("\nEnter new time (dd/mm/yyyy): ");
					inputString(tp[index].date,sizeof(tp[index].date));
					
					if(isValidDate(tp[index].date) == 0){
						printf("Invalid format! Use dd/mm/yyyy");
						valid = 0;
					}
				}while(valid == 0);
				printf(">> Time updated!\n");
				break;
			}
			case 4:
				printf("\n--- UPDATE SEAT ---\n");
				do{
					valid =  1;
					tp[index].totalSeats = getValidInt("Enter new seat: ");
					if(tp[index].totalSeats <= 0){
                        printf("Invalid!! Seats must be > 0.\n");
                        valid = 0;
                    } else if (tp[index].totalSeats < tp[index].bookedSeats) {
                        printf("Invalid!! Cannot reduce seats below booked count (%d).\n", tp[index].bookedSeats);
                        valid = 0;
                    }
				}while(valid == 0);
				printf(">> Total seats updated!");
				break;
			}	
		}while(1);
	}
}

void buyTicket(Ticket *tk, Ticket ticket[], Trip *tp, int tripLength, int *ticketCount){
    int valid;
    int quantity;
    char tempTripID[20];
    char tempName[50];
    char tempPhone[15];
    double pricePerTicket; 
    char dateNow[20]; 
	int i;      

    do{
        valid = 1;
        printf("Enter trip ID: ");
        inputString(tempTripID, sizeof(tempTripID)); 
        if(checkInvalidInput(tempTripID) == 1){
            printf("Invalid!! Cannot be empty or space in first letter!\n");
            valid = 0;
        }
    }while(valid == 0);
    
    int index = searchID(tp, tripLength, tempTripID);
    if(index == -1){
        printf(">>>> Can't find the trip\n"); return;
    }else if(tp[index].bookedSeats >= tp[index].totalSeats){
        printf(">>>> The trip is full!\n"); return;
    }

    do{
        valid = 1;
        printf("Enter passenger name: ");
        inputString(tempName, sizeof(tempName));
        if(checkInvalidInput(tempName)==1){
            printf("Invalid!! Cannot be empty or space in first letter!\n"); valid = 0;
        }    
    }while(valid == 0);
    
    do{
        valid = 1;
        printf("Enter passenger's phone number: ");
        inputString(tempPhone, sizeof(tempPhone)); 
        if(checkInvalidInput(tempPhone) == 1){
            printf("Invalid!! Cannot be emty or space in first letter!\n"); valid = 0;
        }
        for(i = 0 ; i < strlen(tempPhone); i ++){
            if(tempPhone[i] < '0' || tempPhone[i] > '9'){
                printf("Invalid!! Phone number must be numbers\n"); valid =0; break;
            }
        }
    }while(valid == 0);
    
    do{
        int available = tp[index].totalSeats - tp[index].bookedSeats;
        char msg[100];
        sprintf(msg, "Enter number of seats (Available: %d): ", available);
        quantity = getValidInt(msg);
        
        if(quantity <= 0){
            printf("Quantity must be > 0\n"); valid = 0;
        } else if(quantity > available){
            printf("Not enough seats! Only %d left.\n", available); valid = 0;
        } else if (*ticketCount + quantity > MAX_TICKETS) {
             printf("System full!\n"); valid = 0;
        } else valid = 1;
    } while(valid == 0);
    
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(dateNow, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900); 
    
    do{
        pricePerTicket = getValidDouble("Enter price per ticket: "); 
        if (pricePerTicket <= 0) {
            printf("Invalid!! Price must above 0\n"); valid = 0;
        } else valid = 1;
    }while(valid == 0);

    printf("\n>>> Generating tickets...\n");

    for(i = 0; i < quantity; i++){
        Ticket *currentTicket = &ticket[*ticketCount];
        strcpy(currentTicket->tripID, tempTripID);
        strcpy(currentTicket->passenger.name, tempName);
        strcpy(currentTicket->passenger.phone, tempPhone);
        strcpy(currentTicket->date, dateNow);
        currentTicket->price = pricePerTicket;
        currentTicket->paymentStatus = 0; 
        currentTicket->seatNumber = tp[index].bookedSeats + 1;
        sprintf(currentTicket->ticketID, "%s%03d", tempTripID, *ticketCount + 1);

        tp[index].bookedSeats++;
        (*ticketCount)++;
        printf("  [Ticket %d] ID: %s | Seat: %d\n", i+1, currentTicket->ticketID, currentTicket->seatNumber);
    }
    printf(">>> Successfully booked %d tickets!\n", quantity);
}

void ticketStatus(Ticket *tk, Trip *tp, int ticketCount, int tripLength){
    char id[20];
    int found = 0;
    int valid;
    int i;
    
    printf("\n____________CHECK TICKET STATUS______________\n");
    do{
        valid = 1;
        printf("Enter ticket ID to check: ");
        inputString(id, sizeof(id));
        if(checkInvalidInput(id) == 1){
            printf("Invalid input!\n"); valid = 0;
        }
    } while(valid == 0);

    int index = ticketID(tk, ticketCount, id);

    if (index != -1){
    	char statusStr[15];
    	if(tk[index].paymentStatus == 0) strcpy(statusStr,"UNPAID");
        if (tk[index].paymentStatus == 1) strcpy(statusStr, "PAID");
        else if (tk[index].paymentStatus == 2) strcpy(statusStr, "LOCKED");
		else if (tk[index].paymentStatus == -1) strcpy(statusStr, "CANCEL");
        
    
        found = 1;
        printLine();
        printf("| %-10s | %-20s | %-12s | %-35s | %-12s | %-5s | %-12s | %-8s |\n", 
               "Ticket ID", "Passenger", "Phone", "Trip Info", "Date", "Seat", "Price", "Status");
        printLine();

        int tripIndex = searchID(tp, tripLength, tk[index].tripID);
        char routeBuffer[60] = "N/A";
        if(tripIndex != -1) {
            sprintf(routeBuffer, "%s -> %s", tp[tripIndex].departure.name, tp[tripIndex].destination.name);
        }

        printf("| %-10s | %-20s | %-12s | %-35.35s | %-12s | %-5d | %-12.0lf | %-8s |\n",
            tk[index].ticketID,
            tk[index].passenger.name,
            tk[index].passenger.phone,
            routeBuffer,
            tp[tripIndex].date,
            tk[index].seatNumber,
            tk[index].price,
            statusStr);
        printLine(); 
    }
    
    if(found == 0) printf(">>>> Ticket '%s' not found!\n", id);
}

void displayTrips(Trip *tp, int length) {
	int i;
    if (length == 0) {
        printf("\n>> No trips available to display!\n");
        return;
    }

    char buffer[50];
    int pageSize = 10;   
    int pageLimit = 1;   
    int valid;

    do {
        valid = 0;
        printf("\n>> Enter number of rows to show (Enter = 10 rows/page): ");
        inputString(buffer, sizeof(buffer));

        if (strlen(buffer) == 0) {
            pageSize = 10;
            printf(">> Selected default (10 rows/page)\n");
            valid = 1;
        } else {
            int isNum = 1;
            for (i = 0; i < strlen(buffer); i++) {
                if (buffer[i] < '0' || buffer[i] > '9') { isNum = 0; break; }
            }
            if (isNum) {
                int val = atoi(buffer);
                if (val > 0){
				 pageSize = val; 
				 valid = 1;
				}
                else printf(">> Invalid. Number must be > 0\n");
            } else printf(">> Invalid. No contains letters or spaces.\n");
        }       
    } while (valid == 0);
    
    int systemTotalPages = (length + pageSize - 1) / pageSize;
    
    do {
        valid = 0;
        printf(">> Enter number of pages to view (1 - %d): ", systemTotalPages);
        inputString(buffer, sizeof(buffer));
        
        if (strlen(buffer) == 0) {
            printf(">> Selected default (1 page)\n");
            pageLimit = 1;
            valid = 1;
        } else {
            int isNum = 1;
            for (i = 0; i < strlen(buffer); i++) {
                if (buffer[i] < '0' || buffer[i] > '9') { 
					isNum = 0; 
					break; 
				}
            }
            if (isNum) {
                int val = atoi(buffer);
                if (val > 0 && val <= systemTotalPages) {
                    pageLimit = val; 
                    valid = 1;
                } else {
                    printf(">> Invalid. Must be between 1 and %d\n", systemTotalPages);
                }
            } else printf(">> Invalid. No contains letters or spaces.\n");
        }
    } while (valid == 0);

    int currentPage = 1;
    int choice;

    do {
        int startIndex = (currentPage - 1) * pageSize;
        int endIndex = startIndex + pageSize;
        if (endIndex > length) endIndex = length;

        printf("\n================================ LIST OF TRIPS (Page %d/%d) ================================\n", currentPage, pageLimit);
        printLineTrip(); 
        printf("| %-10s | %-35s | %-35s | %-12s | %-5s | %-6s |\n", 
               "Trip ID", "Departure Info", "Destination Info", "Date", "Total", "Booked");
        printLineTrip(); 

        for (i = startIndex; i < endIndex; i++) {
            char depInfo[100];
            char desInfo[100];
            sprintf(depInfo, "%s - %s", tp[i].departure.name, tp[i].departure.address);
            sprintf(desInfo, "%s - %s", tp[i].destination.name, tp[i].destination.address);

            printf("| %-10s | %-35.35s | %-35.35s | %-12s | %-5d | %-6d |\n",
                   tp[i].tripID, depInfo, desInfo, tp[i].date, tp[i].totalSeats, tp[i].bookedSeats);
            printLineTrip();
        }
        
        printf("[1] Next Page   [2] Previous Page   [3] Back to Menu\n");
        choice = getValidInt("Your choice: ");

        if (choice == 3) break; 
        
        if (choice == 1) {
            if (currentPage < pageLimit) {
                currentPage++;
            } else {
                printf(">> You have reached the limit of %d pages you wanted to view!\n", pageLimit);
            }
        } else if (choice == 2) {
            if (currentPage > 1) {
                currentPage--;
            } else {
                printf(">> You are on the first page!\n");
            }
        } else {
            printf(">> Invalid choice!\n");
        }

    } while (1);
}

void payTicket(Ticket *tk, int ticketCount){
	 if (ticketCount == 0) {
        printf("\n>> No tickets sold yet!\n");
        return;
	}
	 char id[20];
	int valid;
	
	do{
		valid = 1;
		printf("Enter ticket id: ");
		inputString(id,sizeof(id));
		
		if(checkInvalidInput(id) == 1){
			printf("Invalid!! Cannot be empty or space in first letter!");
            valid = 0;
		}
	}while(valid == 0);
	
	int index = ticketID(tk,ticketCount,id);
	
	if(index != -1){
		printf("\n======================= PAY TICKET =====================\n");
		if (tk[index].paymentStatus == 1) printf(">> Error: Ticket is ALREADY PAID!\n");
        else if (tk[index].paymentStatus == 2) printf(">> Error: Ticket is LOCKED. Cannot pay.\n");
        else if (tk[index].paymentStatus == -1) printf(">> Error: Ticket is CANCELLED.\n");
        else {
            printf("Confirm paying for passenger: %s - Amount: %.0lf VND\n", tk[index].passenger.name, tk[index].price);
            tk[index].paymentStatus = 1;
            printf(">>> PAYMENT SUCCESSFUL!\n");
        }
	
	}else{
		printf(">> Error: Ticket ID '%s' not found.\n", id);
	}
}

void manageTicket(Ticket *tk, Trip *tp, int ticketCount, int tripLength){
	if(ticketCount == 0){
		printf("\n>> No tickets to manage");
		return;
	}
	
	char id[20];
	int valid;
	
	printf("\n______________ TICKET MANAGEMENT ______________\n");
	do{
		valid =1;
		printf("\n>Enter ticket ID: ");
		inputString(id,sizeof(id));
		
		if(checkInvalidInput(id) == 1){
			printf("Invalid!! Cannot be empty or space in first letter!\n");
            valid = 0;
		}
	}while(valid == 0);
	
	int index = ticketID(tk,ticketCount,id);
	
	if(index == -1){
		printf(">> Can't find the ticket");
		return;
	}else{
		printf("\nFound ticket: %s (Passenger : %s)\n",tk[index].ticketID,tk[index].passenger.name);
		printf("Current status: ");
		if(tk[index].paymentStatus == 0) printf("UNPAID\n");
		else if(tk[index].paymentStatus == 1) printf("PAID\n");
		else if(tk[index].paymentStatus == 2) printf("LOCKED\n");
		else if(tk[index].paymentStatus == -1) printf("CANCELLED");
		
		if(tk[index].paymentStatus == -1){
			printf(">> Ticket is cancelled. No actions available");
		}else{
			printf("------------");
			
		}
		
		
		
	}
	
	
	
}



int main(){
    int choice;
    Trip trips[MAX_TRIPS];
    int length = 0;
    int flag = 0;
    Ticket tickets[MAX_TICKETS];
    int ticketCount = 0;
    
    do{
        printf("\n+-----------------------------------------------+\n");
        printf("|%13s%s%13s|\n","","Bus Ticket Management","");
        printf("+-----------------------------------------------+\n");
        printf("| %-45s |\n","1. Add new trip ");
        printf("| %-45s |\n","2. Update available trip");
        printf("| %-45s |\n","3. Buy ticket");
        printf("| %-45s |\n","4. Check ticket's status");
        printf("| %-45s |\n","5. Display trips");
        printf("| %-45s |\n","6. Pay ticket");
        printf("| %-45s |\n","7. Ticket management");
        printf("| %-45s |\n","8. Sales & statistic reports");
        printf("| %-45s |\n","9. Exit");
        printf("+-----------------------------------------------+\n");
        
        choice = getValidInt(">>>> Enter your option: ");
        
        switch(choice){
            case 1:{
                addTrips(trips, &length);
                flag = 1;
                break;
            }
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:{
                if(flag == 0){
                    printf("Please input trips first! Choose first function.\n");
                }else{
                    switch(choice){
                        case 2:{
                            updateTrip(trips, length);
                            break;
                        }
                        case 3:{
                            buyTicket(&tickets[ticketCount], tickets, trips, length, &ticketCount);
                            break;
                        }
                        case 4:{
                            if (ticketCount == 0) {
                                printf("No tickets have been sold yet!\n");
                            } else {
                                ticketStatus(tickets, trips, ticketCount, length);
                            }
                            break;
                        }
                        case 5:{
                            displayTrips(trips, length);
                            break;
                        }
                        case 6:{
                            payTicket(tickets, ticketCount);
                            break;
                        }
                    }
                }
                break;
            }
            case 9: {
                printf("Goodbye!\n");
                return 0;
            }
            default:{
                printf("Invalid. Please choose again.\n");
                break;
            }
        }
        
    } while(1);
}
