#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>  

struct Employee {
    int id;
    char name[50];
    float hours_worked;
    float hourly_rate;
    float net_salary;
    char date_added[25];
};

float calculateGrossSalary(float hours_worked, float hourly_rate) {
    return hourly_rate * hours_worked;
}

void getCurrentDate(char* dateStr) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    snprintf(dateStr, 25, "%02d-%02d-%04d %02d:%02d:%02d", 
             tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, 
             tm.tm_hour, tm.tm_min, tm.tm_sec);
}

void addEmployee() {
    FILE *file = fopen("employee_data.txt", "a");  
    if (file == NULL) {
        printf("Unable to open file.\n");
        return;
    }

    struct Employee emp;
    printf("Enter Employee ID: ");
    scanf("%d", &emp.id);
    getchar();

    printf("Enter Employee Name: ");
    fgets(emp.name, sizeof(emp.name), stdin);
    emp.name[strcspn(emp.name, "\n")] = '\0';

    printf("Enter Hours Worked: ");
    scanf("%f", &emp.hours_worked);

    printf("Enter Hourly Rate: ");
    scanf("%f", &emp.hourly_rate);

    emp.net_salary = calculateGrossSalary(emp.hours_worked, emp.hourly_rate);

    getCurrentDate(emp.date_added);

    fprintf(file, "%d,%s,%.2f,%.2f,%.2f,%s\n", emp.id, emp.name, emp.hours_worked, emp.hourly_rate, emp.net_salary, emp.date_added);
    printf("Employee added successfully!\n");

    fclose(file);
}

void viewEmployees() {
    FILE *file = fopen("employee_data.txt", "r"); 
    if (file == NULL) {
        printf("No employee data found.\n");
        return;
    }

    struct Employee emp;
    printf("\n Employee ID |            Name         | Hours Worked | Hourly Rate | Net Salary | Date Time\n");
    printf("-----------------------------------------------------------------------------------------------\n");

    while (fscanf(file, "%d,%49[^,],%f,%f,%f,%24[^\n]\n", &emp.id, emp.name, &emp.hours_worked, &emp.hourly_rate, &emp.net_salary, emp.date_added) != EOF) {
        printf("%-12d | %-23s | %-12.2f | %-11.2f | %-10.2f | %-19s\n", emp.id, emp.name, emp.hours_worked, emp.hourly_rate, emp.net_salary, emp.date_added);
    }

    fclose(file);
}

void generatePaySlip(int empID) {
    FILE *file = fopen("employee_data.txt", "r");  
    if (file == NULL) {
        printf("No employee data found.\n");
        return;
    }

    struct Employee emp;
    int found = 0;

    while (fscanf(file, "%d,%49[^,],%f,%f,%f,%24[^\n]\n", &emp.id, emp.name, &emp.hours_worked, &emp.hourly_rate, &emp.net_salary, emp.date_added) != EOF) {
        if (emp.id == empID) {
            found = 1;
            break;
        }
    }

    fclose(file);

    if (!found) {
        printf("Employee with ID %d not found.\n", empID);
        return;
    }

    printf("+---------------------------------------+\n");
    printf("|          Monthly Pay Slip             |\n");
    printf("+---------------------------------------+\n");
    printf("| Employee ID   ----> %d\n", emp.id);
    printf("| Employee Name ----> %s\n", emp.name);
    printf("| Hours Worked  ----> %.2f\n", emp.hours_worked);
    printf("| Hourly Rate   ----> %.2f\n", emp.hourly_rate);
    printf("| Net Salary    ----> %.2f\n", emp.net_salary);
    printf("| Date Added    ----> %s\n", emp.date_added);
    printf("+--------------------------------------+\n");

    char filename[100];
    snprintf(filename, sizeof(filename), "pay_slip_%d.txt", emp.id);
    FILE *paySlipFile = fopen(filename, "w");

    if (paySlipFile != NULL) {
        fprintf(paySlipFile, "+----------------------------------------+\n");
        fprintf(paySlipFile, "|          Monthly Pay Slip              |\n");
        fprintf(paySlipFile, "+----------------------------------------+\n");
        fprintf(paySlipFile, "| Employee ID   ----> %d\n", emp.id);
        fprintf(paySlipFile, "| Employee Name ----> %s\n", emp.name);
        fprintf(paySlipFile, "| Hours Worked  ----> %.2f\n", emp.hours_worked);
        fprintf(paySlipFile, "| Hourly Rate   ----> %.2f\n", emp.hourly_rate);
        fprintf(paySlipFile, "| Net Salary    ----> %.2f\n", emp.net_salary);
        fprintf(paySlipFile, "| Date Added    ----> %s\n", emp.date_added);
        fprintf(paySlipFile, "+----------------------------------------+\n");
        fclose(paySlipFile);
        printf("Pay slip saved to %s\n", filename);
    } else {
        printf("Error saving pay slip.\n");
    }
}

int main() {
    int choice;
    do {
        printf("\nEmployee Payroll System\n");
        printf("1. Add Employee\n");
        printf("2. View Employees\n");
        printf("3. Generate Pay Slip\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addEmployee();
                break;
            case 2:
                viewEmployees();
                break;
            case 3:
                {
                    int empID;
                    printf("Enter Employee ID to generate Pay Slip: ");
                    scanf("%d", &empID);
                    generatePaySlip(empID);
                }
                break;
            case 4:
                printf("Exiting system...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}
