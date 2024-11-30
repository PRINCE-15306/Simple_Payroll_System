#include <stdio.h>
#include <stdlib.h>

struct Employee 
{
 int id;
 char name[50];
 float basic_salary;
 float allowances;
 float deductions;
 float gross_salary;
};

float calculateGrossSalary(float basic, float allowances, float deductions) {
 return basic + allowances - deductions;
}

void displayEmployee(struct Employee emp)
{
printf("\nEmployee ID: %d", emp.id);
 printf("\nName: %s", emp.name);
 printf("\nBasic Salary: %.2f", emp.basic_salary);
printf("\nAllowances: %.2f", emp.allowances);
 printf("\nDeductions: %.2f", emp.deductions);
 printf("\nGross Salary: %.2f\n", emp.gross_salary);
}
int main () {
 int n, i;
printf("Enter the number of employees: ");
scanf("%d", &n);

struct Employee *employees = (struct Employee *)malloc(n * sizeof(struct Employee));

for (i = 0; i < n; i++)
 {
 printf("\nEnter details for Employee %d:\n", i + 1);
printf("ID: ");
scanf("%d", &employees[i].id);
printf("Name: ");
scanf(" %[^\n]", employees[i].name); 
printf("Basic Salary: ");
 scanf("%f", &employees[i].basic_salary);
printf("Allowances: ");
scanf("%f", &employees[i].allowances);
printf("Deductions: ");
scanf("%f", &employees[i].deductions);

employees[i].gross_salary = calculateGrossSalary(employees[i].basic_salary,employees[i].allowances,employees[i].deductions);
}

printf("\nEmployee Payroll Details:\n");
for (i = 0; i < n; i++)
 {
displayEmployee(employees[i]);
}

free(employees);
return 0;
}
