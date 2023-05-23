#include <iostream>
#include <stdio.h>
#include <string.h>
#include "auxiliar.h"
#define MAX 100
using namespace std;

typedef struct
{
    int day;
    int month;
    int year;

} date;

typedef struct 
{
    
    char driverName[30];
    char driverLastname[30];
    char id [10];
    char driverStatus[8];
    date assignDate;

}drivers;



typedef struct 
{
    char truckCode[10];
    char truckPlate[30];
    char truckBrand[30];
    int truckYear;
    char vehicleType[30];
    char refr[2];
    drivers driverInfo;

}trucks;

trucks trucksData[MAX];
drivers driversData[MAX];
int lastReg = 0;

/*
Create
Read
Update
Delete
*/

// Create
void addTruckRegister(trucks currentTruck);
/*Read*/
void showTruck(int pos);
int searchTruckCode(char id[]);
void showTrucksRegister();
void initializeTrucks(int pos);
trucks getTruck(int pos);
/*Update*/
void updateTruck(trucks currentTruck, int pos);
/*Delete*/
void deleteTruck(int pos);

/*Menu*/
int menu();
void start();

/*Archivos
 */
FILE *truckRegistersFile;
void saveTrucks();
void readTrucks();
int calcLastRegister(FILE *archivo);

void addTruckRegister(trucks currentTruck)
{
    trucksData[lastReg] = currentTruck;
    lastReg++;
}

void showTruck(int pos)
{
    cout << endl;
    cout << "Codigo de vehiculo: " << trucksData[pos].truckCode << endl;
    cout << "Placa de vehiculo: " << trucksData[pos].truckPlate << endl;
    cout << "Marca de vehiculo: " << trucksData[pos].truckBrand << endl;
    cout << "Año de vehiculo: " << trucksData[pos].truckYear << endl;
    cout << "Tipo de vehiculo: " << trucksData[pos].vehicleType << endl;
    cout << "Refrigeracion: " << trucksData[pos].refr << endl;
    cout << "Conductor: " << trucksData[pos].driverInfo.driverName << " " <<trucksData[pos].driverInfo.driverLastname << endl;
}

trucks getTruck(int pos)
{
    return trucksData[pos];
}

int searchTruckCode(char enteredTruckCode[])
{
    int position = -1;
    for (int i = 0; i < lastReg; i++)
    {
        if (strcmp(enteredTruckCode, trucksData[i].truckCode) == 0)
        {
            position = i;
            break;
        }
    }
    return position;
}

void showTrucksRegister()
{
    system("cls||clear");
    if (lastReg == 0)
    {
        cout << "No hay registros\n";
        return;
    }
    for (int i = 0; i < lastReg; i++)
    {
        cout<< "=========================\n";
        showTruck(i);
    }
    cout<< "Ultimo registro...\n";
}

void updateTruck(trucks currentTruck, int pos)
{
    trucksData[pos] = currentTruck;
}

void deleteTruck(int pos)
{
    if (pos == lastReg)
    {
        cout << "No hay registro\n";
        return;
    }
    for (int i = pos; i < lastReg - 1; i++)
    {
        trucksData[i] = trucksData[i + 1];
    }
    lastReg--;
    initializeTrucks(lastReg);
}

void initializeTrucks(int pos)
{
    strcpy(trucksData[pos].truckCode, "");
    strcpy(trucksData[pos].truckPlate, "");
    strcpy(trucksData[pos].truckBrand, "");
    trucksData[pos].truckYear = 0;
    strcpy( trucksData[pos].vehicleType, "");
    strcpy( trucksData[pos].refr, "");
    strcpy( trucksData[pos].driverInfo.driverName, "");
    strcpy( trucksData[pos].driverInfo.driverLastname, "");
}

int menu()
{
    int op;

    gotoxy(10, 5);
    cout << " Bienvenido a VehicleSift\n";
    gotoxy(15, 6);
    cout << "Cantidad de registros: " << lastReg << endl;
    gotoxy(10, 9);
    cout << " 1. Agregar Vehiculo \n";
    gotoxy(10, 10);
    cout << " 2. Modificar Vehiculo \n";
    gotoxy(10, 11);
    cout << " 3. Eliminar Vehiculo \n";
    gotoxy(10, 12);
    cout << " 4. Buscar Vehiculo \n";
    gotoxy(10, 13);
    cout << " 5. Mostrar todos los Vehiculos \n";
    gotoxy(10, 14);
    cout << " 6. Salir \n";
    gotoxy(10, 15);
    cout << " Digite la opcion: ";
    gotoxy(29, 15);
    cin >> op;
    return op;
}

void start()
{
    int op, pos, resp;
    char enteredTruckCode[9];
    trucks currentTruck;
    readTrucks();
    do
    {
        system("cls||clear");
        
        op = menu();
        switch (op)
        {
        case 1:
            system("cls || clear");
            gotoxy(10, 5);
            cout << "Codigo de vehiculo:" << endl;
            gotoxy(10, 6);
            cout << "Placa de vehiculo: " << endl;
            gotoxy(10, 7);
            cout << "Marca de vehiculo: "<< endl;
            gotoxy(10, 8);
            cout << "Año de vehiculo: " << endl;
            gotoxy(10, 9);
            cout << "Tipo de vehiculo: " << endl;
            gotoxy(10, 10);
            cout << "Refrigeracion: "<< endl;
            gotoxy(10, 11);
            cout << "Conductor asignado: "<< endl;
            gotoxy(35, 5);
            scanf(" %[^\n]", currentTruck.truckCode);
            gotoxy(35, 6);
            scanf(" %[^\n]", currentTruck.truckPlate);
            gotoxy(35, 7);
            scanf(" %[^\n]", currentTruck.truckBrand);
            gotoxy(35, 8);
            cin >> currentTruck.truckYear;
            gotoxy(35, 9);
            scanf(" %[^\n]", currentTruck.vehicleType);
            gotoxy(35, 10);
            scanf(" %[^\n]", currentTruck.refr);
            gotoxy(35, 11);
            scanf(" %[^\n]", currentTruck.driverInfo.driverName); //currentTruck.driverInfo.driverLastname);
            addTruckRegister(currentTruck);
            system("pause");

            break;
        case 2:
            system("cls||clear");
            cout << "Escribe el ID a buscar: ";
            scanf(" %[^\n]", enteredTruckCode);
            pos = searchTruckCode(enteredTruckCode);
            showTruck(pos);
           gotoxy(50, 0);
            cout << "Datos a modificar "<<endl;
            gotoxy(50,1);
            cout << "Codigo de vehiculo:";
            gotoxy(50, 2);
            cout << "Placa de vehiculo: ";
            gotoxy(50, 3);
            cout << "Marca de vehiculo: ";
            gotoxy(50, 4);
            cout << "Año de vehiculo: ";
            gotoxy(50, 5);
            cout << "Tipo de vehiculo: ";
            gotoxy(50, 6);
            cout << "Refrigeracion: ";
            gotoxy(50, 7);
            cout << "Conductor asignado: ";
            gotoxy(0,0);
            cout<< "Datos actuales:                               ";
            gotoxy(70, 1);
            scanf(" %[^\n]", currentTruck.truckCode);
            gotoxy(68, 2);
            scanf(" %[^\n]", currentTruck.truckPlate);
            gotoxy(57, 3);
            scanf(" %[^\n]", currentTruck.truckBrand);
            gotoxy(72, 4);
            cin >> currentTruck.truckYear;
            gotoxy(57, 5);
            scanf(" %[^\n]", currentTruck.vehicleType);
            gotoxy(64, 6);
            scanf(" %[^\n]", currentTruck.refr);
            gotoxy(61, 7);
            scanf(" %[^\n]", currentTruck.driverInfo.driverName); //currentTruck.driverInfo.driverLastname);
            cout << "Registro actualizado...\n";
            system("cls || clear");
            updateTruck(currentTruck, pos);
            system("pause");
            break;
        case 3:
            system("cls||clear");
            if (lastReg == 0)
            {
                cout << "No hay nada que eliminar\n";
                break;
            }
            cout << "Escribe el ID del estudiante: ";
            cin >> enteredTruckCode;
            pos = searchTruckCode(enteredTruckCode);
            currentTruck = getTruck(pos);
            cout << "¿Realmente deseas eliminar el vehiculo: " << currentTruck.truckCode << "?\n";
            cout << "Escribe 1 para SI o 2 para NO: ";
            cin >> resp;
            if (resp == 1)
            {
                deleteTruck(pos);
                cout << "Registro Eliminado... \n";
            }
            else
            {
                cout << "Operacion cancelada.... \n";
            }
            system("pause");
            break;
        case 4:
            system("cls||clear");
            cout << "Escribe el ID a buscar: ";
            scanf(" %[^\n]", enteredTruckCode);
            pos = searchTruckCode(enteredTruckCode);
            cout << pos;
            if (pos!=-1)
            {
                showTruck(pos);
            }
            else
            {
                cout<<"Registro inexistente" << endl;
            }
            
           
            system("pause");
            break;
        case 5:
            system("cls||clear");
            showTrucksRegister();
            system("pause");
            break;
        case 6:
            break;
        default:
            system("clear||cls");
            cout << "Opcion invalida \n";
            system("pause");
            break;
        }
    } while (op != 6);
    saveTrucks();
}

void saveTrucks()
{
    truckRegistersFile = fopen("datos.bin", "wb");
    fwrite(trucksData, sizeof(trucks), lastReg, truckRegistersFile);
    fclose(truckRegistersFile);
}

void readTrucks()
{
    truckRegistersFile = fopen("datos.bin", "rb");
    if (truckRegistersFile == NULL)
    {
        return;
    }
    lastReg = calcLastRegister(truckRegistersFile);
    fread(trucksData, sizeof(trucks), MAX, truckRegistersFile);

    fclose(truckRegistersFile);
}

int calcLastRegister(FILE *archivo)
{
    int tam_archivo, num_trucks;
    // Obtener el tamaño del archivo
    fseek(archivo, 0, SEEK_END);
    tam_archivo = ftell(archivo);
    rewind(archivo);

    // Calcular el número de vehiculos
    num_trucks = tam_archivo / sizeof(trucks);
    return num_trucks;
}